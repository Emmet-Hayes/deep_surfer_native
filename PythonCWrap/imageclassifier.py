import numpy as np
import tensorflow as tf
from tensorflow.python.platform import gfile
from tensorflow.python.util import compat
from tensorflow.python.framework import graph_util
import os, sys, re, random, hashlib
from datetime import datetime
from six.moves import urllib
import cv2

MAX_NUM_IMAGES_PER_CLASS = 2 ** 27 - 1

class ImageClassifier:
	@staticmethod #r dict with dir, train images, test images, validation images
	def create_image_lists(image_dir, testing_percentage, validation_percentage):
		if not gfile.Exists(image_dir):
			print("Image directory '" + image_dir + "' not found.")
			return None
		result = {}
		sub_dirs = [x[0] for x in gfile.Walk(image_dir)]
		is_root_dir = True
		for sub_dir in sub_dirs:
			if is_root_dir:
				is_root_dir = False
				continue
			extensions = ['jpg', 'jpeg', 'JPG', 'JPEG']
			file_list = []
			dir_name = os.path.basename(sub_dir)
			if dir_name == image_dir:
				continue 
			print("Looking for images in '" + dir_name + "'")
			for extension in extensions:
				file_glob = os.path.join(image_dir, dir_name, '*.' + extension)
				file_list.extend(gfile.Glob(file_glob))
			if not file_list:
				tf.logging.warning('No files found')
				continue
			if len(file_list) < 20:
				print('WARNING: Folder has less than 20 images, which may cause issues.')
			elif len(file_list) > MAX_NUM_IMAGES_PER_CLASS: 
				print('WARNING: Folder {} has more than {} images. Some images will '
						'never be selected.'.format(dir_name, MAX_NUM_IMAGES_PER_CLASS))
			label_name = re.sub(r'[^a-z0-9]+', ' ', dir_name.lower())
			training_images = []
			testing_images = []
			validation_images = [] 
			for file_name in file_list:
				base_name = os.path.basename(file_name)
				hash_name = re.sub(r'_nohash_.*$', '', file_name)
				hash_name_hashed = hashlib.sha1(compat.as_bytes(hash_name)).hexdigest()
				percentage_hash = ((int(hash_name_hashed, 16) % (MAX_NUM_IMAGES_PER_CLASS + 1)) *
					(100.0 / MAX_NUM_IMAGES_PER_CLASS))
				if percentage_hash < validation_percentage:
					validation_images.append(base_name)
				elif percentage_hash < (testing_percentage + validation_percentage):
					testing_images.append(base_name)
				else:
					training_images.append(base_name)
			result[label_name] = {'dir': dir_name,
					'training': training_images,
					'testing': testing_images,
					'validation': validation_images,
			}
		return result

	@staticmethod #r the full path to the image in the list
	def get_image_path(image_lists, label_name, index, image_dir, category):
		if label_name not in image_lists:
			print('Label does not exist %s.'.format(label_name))
		label_lists = image_lists[label_name]
		if category not in label_lists:
			print('Category does not exist %s.'.format(category))
		category_list = label_lists[category]
		if not category_list:
			print('Label ' + label_name + ' has no images in the category ' + category)
		mod_index = index % len(category_list)
		base_name = category_list[mod_index]
		sub_dir = label_lists['dir']
		full_path = os.path.join(image_dir, sub_dir, base_name)
		return full_path

	@staticmethod #r the full path to the bottleneck based on image in list
	def get_bottleneck_path(image_lists, label_name, index, bottleneck_dir, category, architecture):
		return ImageClassifier.get_image_path(image_lists, label_name, index, bottleneck_dir,
			category) + '_' + architecture + '.txt'

	@staticmethod #r the model graph, bottleneck_tensor, resized_input_tensor based on model
	def create_model_graph(model_info, model_dir = ''):
		with tf.Graph().as_default() as graph:
			model_path = os.path.join(model_dir, model_info['model_file_name'])
			print('Model path: ', model_path)
			with gfile.FastGFile(model_path, 'rb') as f:
				graph_def = tf.GraphDef()
				graph_def.ParseFromString(f.read())
				bottleneck_tensor, resized_input_tensor = (tf.import_graph_def(
					graph_def,
					name='',
					return_elements=[ model_info['bottleneck_tensor_name'],
						model_info['resized_input_tensor_name'],
					]
				))
		return graph, bottleneck_tensor, resized_input_tensor

	@staticmethod #r the computed bottleneck values
	def run_bottleneck_on_image(sess, image_data, image_data_tensor, decoded_image_tensor, 
		resized_input_tensor, bottleneck_tensor):
		resized_input_values = sess.run(decoded_image_tensor,
			{image_data_tensor: image_data})
		bottleneck_values = sess.run(bottleneck_tensor,
			{resized_input_tensor: resized_input_values})
		bottleneck_values = np.squeeze(bottleneck_values)
		return bottleneck_values

	@staticmethod #downloads the default model file if it doesn't already exist
	def maybe_download_and_extract(data_url, model_dir = 'graphs'):
		dest_directory = model_dir
		if not os.path.exists(dest_directory):
			os.makedirs(dest_directory)
		filename = data_url.split('/')[-1]
		filepath = os.path.join(dest_directory, filename)
		if not os.path.exists(filepath):
			def _progress(count, block_size, total_size):
				sys.stdout.write('\r>> Downloading %s %.1f%%' % (filename,
					float(count * block_size) / float(total_size) * 100.0))
				sys.stdout.flush()
			filepath, _ = urllib.request.urlretrieve(data_url, filepath, _progress)
			print()
			statinfo = os.stat(filepath)
			print('Successfully downloaded %s %s bytes', filename, statinfo.st_size)
			print('Extracting file from ', filepath)
			gfile.open(filepath, 'r:gz').extractall(dest_directory)
		else:
			print('Not extracting or downloading files, model already present in disk')

	@staticmethod #makes the directory if it doesnt exist
	def ensure_dir_exists(dir_name):
		if not os.path.exists(dir_name):
			os.makedirs(dir_name)

	@staticmethod #creates a bottleneck file for the network
	def create_bottleneck_file(bottleneck_path, image_lists, label_name, index, image_dir, 
		category, sess, jpeg_data_tensor, decoded_image_tensor, resized_input_tensor, bottleneck_tensor):
		print('Creating bottleneck at ' + bottleneck_path)
		image_path = ImageClassifier.get_image_path(image_lists, label_name, index,
																image_dir, category)
		if not gfile.Exists(image_path):
			print('File does not exist %s', image_path)
		image_data = gfile.FastGFile(image_path, 'rb').read()
		try:
			bottleneck_values = ImageClassifier.run_bottleneck_on_image(
					sess, image_data, jpeg_data_tensor, decoded_image_tensor,
					resized_input_tensor, bottleneck_tensor)
		except Exception as e:
			raise RuntimeError('Error during processing file %s (%s)' % (image_path, str(e)))
		bottleneck_string = ','.join(str(x) for x in bottleneck_values)
		with open(bottleneck_path, 'w') as bottleneck_file:
			bottleneck_file.write(bottleneck_string)

	@staticmethod #r the bottleneck values. if they dont exist yet they will be created
	def get_or_create_bottleneck(sess, image_lists, label_name, index, image_dir, category, 
		bottleneck_dir, jpeg_data_tensor, decoded_image_tensor, resized_input_tensor, 
		bottleneck_tensor, architecture):
		label_lists = image_lists[label_name]
		sub_dir = label_lists['dir']
		sub_dir_path = os.path.join(bottleneck_dir, sub_dir)
		ImageClassifier.ensure_dir_exists(sub_dir_path)
		bottleneck_path = ImageClassifier.get_bottleneck_path(image_lists, label_name, index,
																					bottleneck_dir, category, architecture)
		if not os.path.exists(bottleneck_path):
			ImageClassifier.create_bottleneck_file(bottleneck_path, image_lists, label_name, index,
														 image_dir, category, sess, jpeg_data_tensor,
														 decoded_image_tensor, resized_input_tensor,
														 bottleneck_tensor)
		with open(bottleneck_path, 'r') as bottleneck_file:
			bottleneck_string = bottleneck_file.read()
		did_hit_error = False
		try:
			bottleneck_values = [float(x) for x in bottleneck_string.split(',')]
		except ValueError:
			print('Invalid float found, recreating bottleneck')
			did_hit_error = True
		if did_hit_error:
			ImageClassifier.create_bottleneck_file(bottleneck_path, image_lists, label_name, index,
														 image_dir, category, sess, jpeg_data_tensor,
														 decoded_image_tensor, resized_input_tensor,
														 bottleneck_tensor)
			with open(bottleneck_path, 'r') as bottleneck_file:
				bottleneck_string = bottleneck_file.read()
			bottleneck_values = [float(x) for x in bottleneck_string.split(',')]
		return bottleneck_values

	@staticmethod #store created bottlenecks into the cache 
	def cache_bottlenecks(sess, image_lists, image_dir, bottleneck_dir, jpeg_data_tensor, 
		decoded_image_tensor, resized_input_tensor, bottleneck_tensor, architecture):
		how_many_bottlenecks = 0
		ImageClassifier.ensure_dir_exists(bottleneck_dir)
		for label_name, label_lists in image_lists.items():
			for category in ['training', 'testing', 'validation']:
				category_list = label_lists[category]
				for index, unused_base_name in enumerate(category_list):
					ImageClassifier.get_or_create_bottleneck(
							sess, image_lists, label_name, index, image_dir, category,
							bottleneck_dir, jpeg_data_tensor, decoded_image_tensor,
							resized_input_tensor, bottleneck_tensor, architecture)

					how_many_bottlenecks += 1
					if how_many_bottlenecks % 100 == 0:
						print(str(how_many_bottlenecks) + ' bottleneck files created.')

	@staticmethod #r cached random bottlenecks
	def get_random_cached_bottlenecks(sess, image_lists, how_many, category, bottleneck_dir, 
		image_dir, jpeg_data_tensor, decoded_image_tensor, resized_input_tensor, 
		bottleneck_tensor, architecture):
		class_count = len(image_lists.keys())
		bottlenecks = []
		ground_truths = []
		filenames = []
		if how_many >= 0:
			for unused_i in range(how_many):
				label_index = random.randrange(class_count)
				label_name = list(image_lists.keys())[label_index]
				image_index = random.randrange(MAX_NUM_IMAGES_PER_CLASS + 1)
				image_name = ImageClassifier.get_image_path(image_lists, label_name, image_index,
																		image_dir, category)
				bottleneck = ImageClassifier.get_or_create_bottleneck(
						sess, image_lists, label_name, image_index, image_dir, category,
						bottleneck_dir, jpeg_data_tensor, decoded_image_tensor,
						resized_input_tensor, bottleneck_tensor, architecture)
				bottlenecks.append(bottleneck)
				ground_truths.append(label_index)
				filenames.append(image_name)
		else:
			for label_index, label_name in enumerate(image_lists.keys()):
				for image_index, image_name in enumerate(
						image_lists[label_name][category]):
					image_name = ImageClassifier.get_image_path(image_lists, label_name, image_index,
																			image_dir, category)
					bottleneck = ImageClassifier.get_or_create_bottleneck(
							sess, image_lists, label_name, image_index, image_dir, category,
							bottleneck_dir, jpeg_data_tensor, decoded_image_tensor,
							resized_input_tensor, bottleneck_tensor, architecture)
					bottlenecks.append(bottleneck)
					ground_truths.append(label_index)
					filenames.append(image_name)
		return bottlenecks, ground_truths, filenames

	@staticmethod# r distorted random bottlenecks
	def get_random_distorted_bottlenecks(sess, image_lists, how_many, category, image_dir, 
		input_jpeg_tensor, distorted_image, resized_input_tensor, bottleneck_tensor):
		class_count = len(image_lists.keys())
		bottlenecks = []
		ground_truths = []
		for unused_i in range(how_many):
			label_index = random.randrange(class_count)
			label_name = list(image_lists.keys())[label_index]
			image_index = random.randrange(MAX_NUM_IMAGES_PER_CLASS + 1)
			image_path = ImageClassifier.get_image_path(image_lists, label_name, image_index, image_dir,
																	category)
			if not gfile.Exists(image_path):
				print('File does not exist %s', image_path)
			jpeg_data = gfile.FastGFile(image_path, 'rb').read()
			distorted_image_data = sess.run(distorted_image,
																			{input_jpeg_tensor: jpeg_data})
			bottleneck_values = sess.run(bottleneck_tensor,
																	 {resized_input_tensor: distorted_image_data})
			bottleneck_values = np.squeeze(bottleneck_values)
			bottlenecks.append(bottleneck_values)
			ground_truths.append(label_index)
		return bottlenecks, ground_truths

	@staticmethod# r yes or no
	def should_distort_images(flip_left_right, random_crop, random_scale, random_brightness):
		return (flip_left_right or (random_crop != 0) or (random_scale != 0) or
						(random_brightness != 0))

	@staticmethod #r jpeg data, distorted images
	def add_input_distortions(flip_left_right, random_crop, random_scale, random_brightness, 
		input_width, input_height, input_depth, input_mean, input_std):
		jpeg_data = tf.placeholder(tf.string, name='DistortJPGInput')
		decoded_image = tf.image.decode_jpeg(jpeg_data, channels=input_depth)
		decoded_image_as_float = tf.cast(decoded_image, dtype=tf.float32)
		decoded_image_4d = tf.expand_dims(decoded_image_as_float, 0)
		margin_scale = 1.0 + (random_crop / 100.0)
		resize_scale = 1.0 + (random_scale / 100.0)
		margin_scale_value = tf.constant(margin_scale)
		resize_scale_value = tf.random_uniform(tensor_shape.scalar(), minval=1.0, maxval=resize_scale)
		scale_value = tf.multiply(margin_scale_value, resize_scale_value)
		precrop_width = tf.multiply(scale_value, input_width)
		precrop_height = tf.multiply(scale_value, input_height)
		precrop_shape = tf.stack([precrop_height, precrop_width])
		precrop_shape_as_int = tf.cast(precrop_shape, dtype=tf.int32)
		precropped_image = tf.image.resize_bilinear(decoded_image_4d, precrop_shape_as_int)
		precropped_image_3d = tf.squeeze(precropped_image, squeeze_dims=[0])
		cropped_image = tf.random_crop(precropped_image_3d,
																	 [input_height, input_width, input_depth])
		if flip_left_right:
			flipped_image = tf.image.random_flip_left_right(cropped_image)
		else:
			flipped_image = cropped_image
		brightness_min = 1.0 - (random_brightness / 100.0)
		brightness_max = 1.0 + (random_brightness / 100.0)
		brightness_value = tf.random_uniform(tensor_shape.scalar(),
																				 minval=brightness_min,
																				 maxval=brightness_max)
		brightened_image = tf.multiply(flipped_image, brightness_value)
		offset_image = tf.subtract(brightened_image, input_mean)
		mul_image = tf.multiply(offset_image, 1.0 / input_std)
		distort_result = tf.expand_dims(mul_image, 0, name='DistortResult')
		return jpeg_data, distort_result

	@staticmethod #computes variable summaries for tensorboard
	def variable_summaries(var):
		with tf.name_scope('summaries'):
			mean = tf.reduce_mean(var)
			tf.summary.scalar('mean', mean)
			with tf.name_scope('stddev'):
				stddev = tf.sqrt(tf.reduce_mean(tf.square(var - mean)))
			tf.summary.scalar('stddev', stddev)
			tf.summary.scalar('max', tf.reduce_max(var))
			tf.summary.scalar('min', tf.reduce_min(var))
			tf.summary.histogram('histogram', var)

	@staticmethod #finalizes training with the new layers
	def add_final_training_ops(class_count, final_tensor_name, bottleneck_tensor, bottleneck_tensor_size, quantize_layer, learning_rate = 0.01):
		with tf.name_scope('input'):
			bottleneck_input = tf.placeholder_with_default(
					bottleneck_tensor,
					shape=[None, bottleneck_tensor_size],
					name='BottleneckInputPlaceholder')
			ground_truth_input = tf.placeholder(
					tf.int64, [None], name='GroundTruthInput')
		layer_name = 'final_training_ops'
		with tf.name_scope(layer_name):
			with tf.name_scope('weights'):
				initial_value = tf.truncated_normal(
						[bottleneck_tensor_size, class_count], stddev=0.001)
				layer_weights = tf.Variable(initial_value, name='final_weights')
				if quantize_layer:
					quantized_layer_weights = quant_ops.MovingAvgQuantize(
							layer_weights, is_training=True)
					ImageClassifier.variable_summaries(quantized_layer_weights)
				ImageClassifier.variable_summaries(layer_weights)
			with tf.name_scope('biases'):
				layer_biases = tf.Variable(tf.zeros([class_count]), name='final_biases')
				if quantize_layer:
					quantized_layer_biases = quant_ops.MovingAvgQuantize(
							layer_biases, is_training=True)
					ImageClassifier.variable_summaries(quantized_layer_biases)
				ImageClassifier.variable_summaries(layer_biases)
			with tf.name_scope('Wx_plus_b'):
				if quantize_layer:
					logits = tf.matmul(bottleneck_input,
														 quantized_layer_weights) + quantized_layer_biases
					logits = quant_ops.MovingAvgQuantize(
							logits,
							init_min=-32.0,
							init_max=32.0,
							is_training=True,
							num_bits=8,
							narrow_range=False,
							ema_decay=0.5)
					tf.summary.histogram('pre_activations', logits)
				else:
					logits = tf.matmul(bottleneck_input, layer_weights) + layer_biases
					tf.summary.histogram('pre_activations', logits)
		final_tensor = tf.nn.softmax(logits, name=final_tensor_name)
		tf.summary.histogram('activations', final_tensor)
		with tf.name_scope('cross_entropy'):
			cross_entropy_mean = tf.losses.sparse_softmax_cross_entropy(
					labels=ground_truth_input, logits=logits)
		tf.summary.scalar('cross_entropy', cross_entropy_mean)
		with tf.name_scope('train'):
			optimizer = tf.train.GradientDescentOptimizer(learning_rate)
			train_step = optimizer.minimize(cross_entropy_mean)
		return (train_step, cross_entropy_mean, bottleneck_input, ground_truth_input,
						final_tensor)

	@staticmethod #r the prediction based on the result and ground tensor
	def add_evaluation_step(result_tensor, ground_truth_tensor):
		with tf.name_scope('accuracy'):
			with tf.name_scope('correct_prediction'):
				prediction = tf.argmax(result_tensor, 1)
				correct_prediction = tf.equal(prediction, ground_truth_tensor)
			with tf.name_scope('accuracy'):
				evaluation_step = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
		tf.summary.scalar('accuracy', evaluation_step)
		return evaluation_step, prediction

	@staticmethod #saves the final resulting graph
	def save_graph_to_file(sess, graph, graph_file_name, final_tensor_name = 'final_result'):
		output_graph_def = graph_util.convert_variables_to_constants(
				sess, graph.as_graph_def(), [final_tensor_name])
		with gfile.FastGFile(graph_file_name, 'wb') as f:
			f.write(output_graph_def.SerializeToString())
		return

	@staticmethod #clears previous files in starting and intermediate storage locations
	def prepare_file_system(summaries_dir = 'tmp/retrain_logs', 
		intermediate_store_frequency = 0, 
		intermediate_output_graphs_dir = 'tmp/intermediate_graph/'):
		if tf.gfile.Exists(summaries_dir):
			tf.gfile.DeleteRecursively(summaries_dir)
		tf.gfile.MakeDirs(summaries_dir)
		if intermediate_store_frequency > 0:
			ImageClassifier.ensure_dir_exists(intermediate_output_graphs_dir)
		return

	@staticmethod #r dict with the CNN model's info, based on architecture
	def create_model_info(architecture):
		architecture = architecture.lower()
		is_quantized = False
		if architecture == 'inception_v3':
			data_url = 'http://download.tensorflow.org/models/image/imagenet/inception-2015-12-05.tgz'
			bottleneck_tensor_name = 'pool_3/_reshape:0'
			bottleneck_tensor_size = 2048
			input_width = 299
			input_height = 299
			input_depth = 3
			resized_input_tensor_name = 'Mul:0'
			model_file_name = 'graphs/classify_image_graph_def.pb'
			input_mean = 128
			input_std = 128
		elif architecture.startswith('mobilenet_'):
			parts = architecture.split('_')
			if len(parts) != 3 and len(parts) != 4:
				print("Couldn't understand architecture name '%s'", architecture)
				return None
			version_string = parts[1]
			if (version_string != '1.0' and version_string != '0.75' and
					version_string != '0.50' and version_string != '0.25'):
				print("""The Mobilenet version should be '1.0', '0.75', '0.50', or '0.25',
							but found '%s' for architecture '%s'""", version_string, architecture)
				return None
			size_string = parts[2]
			if (size_string != '224' and size_string != '192' and
					size_string != '160' and size_string != '128'):
				print("""The Mobilenet input size should be '224', '192', '160', or '128',
	 						but found '%s' for architecture '%s'""", size_string, architecture)
				return None
			if len(parts) == 3:
				is_quantized = False
			else:
				if parts[3] != 'quantized':
					print( "Couldn't understand architecture suffix '%s' for '%s'", parts[3], architecture)
					return None
				is_quantized = True
			if is_quantized:
				data_url = 'http://download.tensorflow.org/models/mobilenet_v1_'
				data_url += version_string + '_' + size_string + '_quantized_frozen.tgz'
				bottleneck_tensor_name = 'MobilenetV1/Predictions/Reshape:0'
				resized_input_tensor_name = 'Placeholder:0'
				model_dir_name = ('mobilenet_v1_' + version_string + '_' + size_string +
													'_quantized_frozen')
				model_base_name = 'quantized_frozen_graph.pb'
			else:
				data_url = 'http://download.tensorflow.org/models/mobilenet_v1_'
				data_url += version_string + '_' + size_string + '_frozen.tgz'
				bottleneck_tensor_name = 'MobilenetV1/Predictions/Reshape:0'
				resized_input_tensor_name = 'input:0'
				model_dir_name = 'mobilenet_v1_' + version_string + '_' + size_string
				model_base_name = 'frozen_graph.pb'
			bottleneck_tensor_size = 1001
			input_width = int(size_string)
			input_height = int(size_string)
			input_depth = 3
			model_file_name = os.path.join(model_dir_name, model_base_name)
			input_mean = 127.5
			input_std = 127.5
		else:
			print("Couldn't understand architecture name '%s'", architecture)
			raise ValueError('Unknown architecture', architecture)
		return {
				'data_url': data_url,
				'bottleneck_tensor_name': bottleneck_tensor_name,
				'bottleneck_tensor_size': bottleneck_tensor_size,
				'input_width': input_width,
				'input_height': input_height,
				'input_depth': input_depth,
				'resized_input_tensor_name': resized_input_tensor_name,
				'model_file_name': model_file_name,
				'input_mean': input_mean,
				'input_std': input_std,
				'quantize_layer': is_quantized,
		}

	@staticmethod #r jpeg data and the multipled image
	def add_jpeg_decoding(input_width, input_height, input_depth, input_mean, input_std):
		jpeg_data = tf.placeholder(tf.string, name='DecodeJPGInput')
		decoded_image = tf.image.decode_jpeg(jpeg_data, channels=input_depth)
		decoded_image_as_float = tf.cast(decoded_image, dtype=tf.float32)
		decoded_image_4d = tf.expand_dims(decoded_image_as_float, 0)
		resize_shape = tf.stack([input_height, input_width])
		resize_shape_as_int = tf.cast(resize_shape, dtype=tf.int32)
		resized_image = tf.image.resize_bilinear(decoded_image_4d,
																						 resize_shape_as_int)
		offset_image = tf.subtract(resized_image, input_mean)
		mul_image = tf.multiply(offset_image, 1.0 / input_std)
		return jpeg_data, mul_image

	@staticmethod #retrains and saves a new CNN image classifier with new top layers to the tmp directory.
	def retrain_image_classifier(retrain_image_dir, has_retrain_parameters=False, 
		how_many_training_steps=4000, learning_rate=0.01, 
		print_misclassified_test_images=False, flip_left_right=False, 
		random_crop=0, random_scale=0, random_brightness=0):
		output_graph = 'tmp/output_graph.pb'
		intermediate_output_graphs_dir = 'tmp/intermediate_graph/'
		intermediate_store_frequency = 0
		output_labels = 'tmp/output_labels.txt'
		summaries_dir = 'tmp/retrain_logs'
		testing_percentage = 10
		validation_percentage = 10
		eval_step_interval = 10
		train_batch_size = 100
		test_batch_size = -1
		validation_batch_size = 100
		model_dir = 'tmp/imagenet'
		bottleneck_dir = 'tmp/bottleneck'
		final_tensor_name = 'final_result'
		architecture = 'inception_v3'
		text_output = 'Retraining image classifier, this might take a while...\n'
		ImageClassifier.prepare_file_system()
		model_info = ImageClassifier.create_model_info(architecture)
		if not model_info:
			text_output += 'Error: Did not recognize architecture parameter...'
			return -1
		ImageClassifier.maybe_download_and_extract(model_info['data_url'])
		graph, bottleneck_tensor, resized_image_tensor = (
			ImageClassifier.create_model_graph(model_info))
		image_lists = ImageClassifier.create_image_lists(retrain_image_dir, testing_percentage,
			validation_percentage)
		class_count = len(image_lists.keys())
		if class_count == 0:
			text_output += 'Error: No valid folders of images found at ' + retrain_image_dir
			return -1
		if class_count == 1:
			text_output += 'Only one valid folder of images found at ' + retrain_image_dir + ' - multiple classes are needed for classification.'
			return -1
		do_distort_images = ImageClassifier.should_distort_images(
			flip_left_right, random_crop, random_scale, random_brightness)
		with tf.Session(graph=graph) as sess:
			jpeg_data_tensor, decoded_image_tensor = ImageClassifier.add_jpeg_decoding(
				model_info['input_width'], model_info['input_height'],
				model_info['input_depth'], model_info['input_mean'],
				model_info['input_std'])
			if do_distort_images:
				(distorted_jpeg_data_tensor, distorted_image_tensor) = ImageClassifier.add_input_distortions(
					flip_left_right, random_crop, random_scale,
					random_brightness, model_info['input_width'],
					model_info['input_height'], model_info['input_depth'],
					model_info['input_mean'], model_info['input_std'])
			else:
				ImageClassifier.cache_bottlenecks(sess, image_lists, retrain_image_dir,
													bottleneck_dir, jpeg_data_tensor,
													decoded_image_tensor, resized_image_tensor,
													bottleneck_tensor, architecture)
			(train_step, cross_entropy, bottleneck_input, ground_truth_input,
			 final_tensor) = ImageClassifier.add_final_training_ops(
					 len(image_lists.keys()), final_tensor_name, bottleneck_tensor,
					 model_info['bottleneck_tensor_size'], model_info['quantize_layer'])
			evaluation_step, prediction = ImageClassifier.add_evaluation_step(
					final_tensor, ground_truth_input)
			merged = tf.summary.merge_all()
			train_writer = tf.summary.FileWriter(summaries_dir + '/train',
																					 sess.graph)
			validation_writer = tf.summary.FileWriter(
					summaries_dir + '/validation')
			init = tf.global_variables_initializer()
			sess.run(init)
			for i in range(how_many_training_steps):
				if do_distort_images:
					(train_bottlenecks,
					 train_ground_truth) = ImageClassifier.get_random_distorted_bottlenecks(
							 sess, image_lists, train_batch_size, 'training',
							 retrain_image_dir, distorted_jpeg_data_tensor,
							 distorted_image_tensor, resized_image_tensor, bottleneck_tensor)
				else:
					(train_bottlenecks,
					 train_ground_truth, _) = ImageClassifier.get_random_cached_bottlenecks(
							 sess, image_lists, train_batch_size, 'training',
							 bottleneck_dir, retrain_image_dir, jpeg_data_tensor,
							 decoded_image_tensor, resized_image_tensor, bottleneck_tensor,
							 architecture)
				train_summary, _ = sess.run(
						[merged, train_step],
						feed_dict={bottleneck_input: train_bottlenecks,
											 ground_truth_input: train_ground_truth})
				train_writer.add_summary(train_summary, i)
				is_last_step = (i + 1 == how_many_training_steps)
				if (i % eval_step_interval) == 0 or is_last_step:
					train_accuracy, cross_entropy_value = sess.run(
							[evaluation_step, cross_entropy],
							feed_dict={bottleneck_input: train_bottlenecks,
												 ground_truth_input: train_ground_truth})
					print('%s: Step %d: Train accuracy = %.1f%%' %
													(datetime.now(), i, train_accuracy * 100))
					print('%s: Step %d: Cross entropy = %f' %
													(datetime.now(), i, cross_entropy_value))
					validation_bottlenecks, validation_ground_truth, _ = (
							ImageClassifier.get_random_cached_bottlenecks(
									sess, image_lists, validation_batch_size, 'validation',
									bottleneck_dir, retrain_image_dir, jpeg_data_tensor,
									decoded_image_tensor, resized_image_tensor, bottleneck_tensor,
									architecture))
					validation_summary, validation_accuracy = sess.run(
							[merged, evaluation_step],
							feed_dict={bottleneck_input: validation_bottlenecks,
												 ground_truth_input: validation_ground_truth})
					validation_writer.add_summary(validation_summary, i)
					print('%s: Step %d: Validation accuracy = %.1f%% (N=%d)' %
						(datetime.now(), i, validation_accuracy * 100, len(validation_bottlenecks)))
				intermediate_frequency = intermediate_store_frequency
				if (intermediate_frequency > 0 and (i % intermediate_frequency == 0)
						and i > 0):
					intermediate_file_name = (intermediate_output_graphs_dir +
																		'intermediate_' + str(i) + '.pb')
					text_output += 'Save intermediate result to: ' + intermediate_file_name
					ImageClassifier.save_graph_to_file(sess, graph, intermediate_file_name)
			test_bottlenecks, test_ground_truth, test_filenames = (
					ImageClassifier.get_random_cached_bottlenecks(
							sess, image_lists, test_batch_size, 'testing',
							bottleneck_dir, retrain_image_dir, jpeg_data_tensor,
							decoded_image_tensor, resized_image_tensor, bottleneck_tensor,
							architecture))
			test_accuracy, predictions = sess.run(
					[evaluation_step, prediction],
					feed_dict={bottleneck_input: test_bottlenecks,
										 ground_truth_input: test_ground_truth})
			text_output += 'Final Test Accuracy = %.1f%% (N=%d)' % (test_accuracy * 100, len(test_bottlenecks))
			if print_misclassified_test_images:
				tf.logging.info('=== MISCLASSIFIED TEST IMAGES ===')
				for i, test_filename in enumerate(test_filenames):
					if predictions[i] != test_ground_truth[i]:
						tf.logging.info('%70s  %s' %
														(test_filename,
														 list(image_lists.keys())[predictions[i]]))
			ImageClassifier.save_graph_to_file(sess, graph, output_graph)
			with gfile.FastGFile(output_labels, 'w') as f:
				f.write('\n'.join(image_lists.keys()) + '\n')
			print("image classifier is done training. navigate back to the main window!")
		return text_output

	@staticmethod #r a graph based on model file
	def load_graph(model_file):
		graph = tf.Graph()
		graph_def = tf.GraphDef()
		with open(model_file, "rb") as f:
			graph_def.ParseFromString(f.read())
		with graph.as_default():
			tf.import_graph_def(graph_def)
		return graph

	@staticmethod #r resulting tensor based on image
	def read_tensor_from_image_file(file_name, input_height=299, input_width=299, input_mean=0, input_std=255):
		input_name = "file_reader"
		output_name = "normalized"
		file_reader = tf.read_file(file_name, input_name)
		if file_name.endswith(".png"):
			image_reader = tf.image.decode_png(file_reader, channels = 3, name='png_reader')
		elif file_name.endswith(".gif"):
			image_reader = tf.squeeze(tf.image.decode_gif(file_reader, name='gif_reader'))
		elif file_name.endswith(".bmp"):
			image_reader = tf.image.decode_bmp(file_reader, name='bmp_reader')
		else:
			image_reader = tf.image.decode_jpeg(file_reader, channels = 3, name='jpeg_reader')
		float_caster = tf.cast(image_reader, tf.float32)
		dims_expander = tf.expand_dims(float_caster, 0);
		resized = tf.image.resize_bilinear(dims_expander, [input_height, input_width])
		normalized = tf.divide(tf.subtract(resized, [input_mean]), [input_std]) 
		sess = tf.Session()
		result = sess.run(normalized)
		return result

	@staticmethod #r loaded labels from the file
	def load_labels(label_file):
		labels = []
		proto_as_ascii_lines = tf.gfile.GFile(label_file).readlines()
		for l in proto_as_ascii_lines:
			labels.append(l.rstrip())
		return labels

	@staticmethod #runs the classifier that was last trained or default
	def run_image_classifier(file_path='icons/surfingsky.png', rerun=False, 
		model_file='graphs/inception_v3_2016_08_28_frozen.pb',
		label_file='graphs/imagenet_slim_labels.txt'):
		print('thinking... please wait.\n')
		text_output = ""
		input_height, input_width, input_mean, input_std = 299, 299, 0, 255
		input_layer = "input"
		output_layer = "InceptionV3/Predictions/Reshape_1"
		if rerun is True:
			input_layer = "Mul"
			output_layer = "final_result"
		try:
			graph = ImageClassifier.load_graph(model_file)
			t = ImageClassifier.read_tensor_from_image_file(file_path, input_height=input_height,
				input_width=input_width, input_mean=input_mean, input_std=input_std)
			input_name = "import/" + input_layer 
			output_name = "import/" + output_layer
			input_operation = graph.get_operation_by_name(input_name);
			output_operation = graph.get_operation_by_name(output_name);
			with tf.Session(graph=graph) as sess:
				results = sess.run(output_operation.outputs[0], {input_operation.outputs[0]: t})
			results = np.squeeze(results)
			top_k = results.argsort()[-5:][::-1]
			labels = ImageClassifier.load_labels(label_file)
			index = 0
			for i in top_k:
				guess = str('My artificial brain is ' + "%.2f" % (results[i] * 100) + '% sure that this is an image of a')
				if labels[i].startswith('a') or labels[i].startswith('e') or labels[i].startswith('i') or labels[i].startswith('o') or labels[i].startswith('u'): #if the image label first letter is a vowel
					guess += 'n'
				guess += ' ' + labels[i] + '.\n'
				if index == 0: guess += 'This is my main guess.\n\n\n\n'
				text_output += guess
				index += 1
		except FileNotFoundError:
			text_output += "File Not Found!\n{0}\n".format(file_path)
		except Exception as e:
			template = "Uh oh! an exception of type {0} occured. Arguments in the exception are :\n{1!r}"
			message = template.format(type(e).__name__, e.args)
			text_output += message
		print("done thinking...")
		return text_output

if __name__ == '__main__':
	print(ImageClassifier.run_image_classifier())