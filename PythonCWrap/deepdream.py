import os
import numpy as np
import cv2
from PIL import Image
import tensorflow as tf

class DeepDream:
  @staticmethod #dream-effects an input image and saves it in the output location
  def run(file_path = 'icons/surfingsky.png', dream_layer='mixed4b', naive_render_iter=20, naive_step=1.0, 
    deep_render_iter=10, deep_step=1.5, octave_number=4, octave_scaled=1.4, downsize=255.0,
    img_noise_size=224, imagenet_mean_init=117.0, grad_tile_size=256, strip_const_size=32):
    dream_file = file_path[:-4] + '-' + dream_layer + '.png'
    if file_path is '':
      return
    data_dir = 'deepdreamdata/'
    img_noise = np.random.uniform(size=(img_noise_size,img_noise_size,3)) + 100.0
    model_fn = 'tensorflow_inception_graph.pb'
    print("Give me some time to dream...")
    graph = tf.Graph() #Creating Tensorflow session and loading the model
    sess = tf.InteractiveSession(graph=graph)
    with tf.gfile.FastGFile(os.path.join(data_dir, model_fn), 'rb') as f:
      graph_def = tf.GraphDef()
      graph_def.ParseFromString(f.read())
    t_input = tf.placeholder(np.float32, name='input') # define the input tensor
    imagenet_mean = imagenet_mean_init
    t_preprocessed = tf.expand_dims(t_input-imagenet_mean, 0)
    tf.import_graph_def(graph_def, {'input':t_preprocessed})
    #for op in graph.get_operations():
      #print(op.name)
    layers = [op.name for op in graph.get_operations() if op.type=='Conv2D' and 'import/' in op.name]
    feature_nums = [int(graph.get_tensor_by_name(name+':0').get_shape()[-1]) for name in layers]
    
    print('Number of layers', len(layers))
    print('Total number of feature channels:', sum(feature_nums))
    print('Dreaming...please wait...')
    print('zzzzz...')
    # Helper functions for TF Graph visualization
    #pylint: disable=unused-variable
    def strip_consts(graph_def, max_const_size=strip_const_size):
      """Strip large constant values from graph_def."""
      strip_def = tf.GraphDef()
      for n0 in graph_def.node:
        n = strip_def.node.add() #pylint: disable=maybe-no-member
        n.MergeFrom(n0)
        if n.op == 'Const':
          tensor = n.attr['value'].tensor
          size = len(tensor.tensor_content)
          if size > max_const_size:
            tensor.tensor_content = "<stripped %d bytes>"%size
      return strip_def

    def rename_nodes(graph_def, rename_func):
      res_def = tf.GraphDef()
      for n0 in graph_def.node:
        n = res_def.node.add() #pylint: disable=maybe-no-member
        n.MergeFrom(n0)
        n.name = rename_func(n.name)
        for i, s in enumerate(n.input):
          n.input[i] = rename_func(s) if s[0]!='^' else '^'+rename_func(s[1:])
      return res_def

    def save_dream_image(img, path='deepdreamdata/autosave/currentsave.png'):
      try:
        img = np.uint8(np.clip(img, 0, 1)*255)
        print("printing path: " + path)
        cv2.imwrite(path, img)
      except PermissionError as e:
        print("Permission Denied Access to write file to that location. The file is not saved " + 
        "at all")

    def visstd(a, s=0.1):
      '''Normalize the image range for visualization'''
      return (a-a.mean())/max(a.std(), 1e-4)*s + 0.5

    def T(layer):
      '''Helper for getting layer output tensor'''
      return graph.get_tensor_by_name("import/%s:0"%layer)

    def render_naive(t_obj, img0=img_noise, iter_n=naive_render_iter, step=naive_step):
      t_score = tf.reduce_mean(t_obj) # defining the optimization objective
      t_grad = tf.gradients(t_score, t_input)[0] # behold the power of automatic differentiation!
      img = img0.copy()
      for _ in range(iter_n):
        g, _ = sess.run([t_grad, t_score], {t_input:img})
        # normalizing the gradient, so the same step size should work 
        g /= g.std()+1e-8         # for different layers and networks
        img += g*step
      save_dream_image(visstd(img))
      showarray(visstd(img))

    def tffunc(*argtypes):
      '''Helper that transforms TF-graph generating function into a regular one.
      See "resize" function below.
      '''
      placeholders = list(map(tf.placeholder, argtypes))
      def wrap(f):
        out = f(*placeholders)
        def wrapper(*args, **kw):
          return out.eval(dict(zip(placeholders, args)), session=kw.get('session'))
        return wrapper
      return wrap

    def resize(img, size):
      img = tf.expand_dims(img, 0)
      return tf.image.resize_bilinear(img, size)[0,:,:,:]

    resize = tffunc(np.float32, np.int32)(resize)

    def calc_grad_tiled(img, t_grad, tile_size=grad_tile_size):
      '''Compute the value of tensor t_grad over the image in a tiled way.
      Random shifts are applied to the image to blur tile boundaries over 
      multiple iterations.'''
      sz = tile_size
      h, w = img.shape[:2]
      sx, sy = np.random.randint(sz, size=2)
      img_shift = np.roll(np.roll(img, sx, 1), sy, 0)
      grad = np.zeros_like(img)
      for y in range(0, max(h-sz//2, sz),sz):
        for x in range(0, max(w-sz//2, sz),sz):
          sub = img_shift[y:y+sz,x:x+sz]
          g = sess.run(t_grad, {t_input:sub})
          grad[y:y+sz,x:x+sz] = g
      return np.roll(np.roll(grad, -sx, 1), -sy, 0)    

    def render_deepdream(t_obj, img0=img_noise,
      iter_n=deep_render_iter, step=deep_step, octave_n=octave_number, 
      octave_scale=octave_scaled, save_path=dream_file):
      t_score = tf.reduce_mean(t_obj) # defining the optimization objective
      t_grad = tf.gradients(t_score, t_input)[0] # behold the power of automatic differentiation!

      # split the image into a number of octaves
      img = img0
      octaves = []
      for _ in range(octave_n-1):
        hw = img.shape[:2]
        lo = resize(img, np.int32(np.float32(hw)/octave_scale))
        hi = img-resize(lo, hw)
        img = lo
        octaves.append(hi)

      for i, octave in enumerate(range(octave_n)): # generate details each octave
        if octave>0:
          hi = octaves[-octave]
          img = resize(img, hi.shape[:2])+hi
        for _ in range(iter_n):
          g = calc_grad_tiled(img, t_grad)
          img += g*(step / (np.abs(g).mean()+1e-7))
        save_dream_image(img/downsize)
        save_dream_image(img/downsize, save_path)
        print("in octave: %i" % i)

    img0 = cv2.imread(file_path) #open image
    img0 = np.float32(img0)
    
    render_deepdream(tf.square(T(dream_layer)), img0) # Apply gradient ascent to chosen layer
    print("the deep dream has ended. navigate back to the main window!")
    sess.close()

    return dream_file

if __name__ == '__main__':
  DeepDream.run()
  print("if you are reading this, everything worked in the dream!")