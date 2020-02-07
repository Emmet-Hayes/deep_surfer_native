'''
'''

from PyQt5.QtGui import QColor, QIcon, QPixmap #GUI importz bb
from PyQt5.QtWidgets import QTextEdit, QWidget, QPushButton, QVBoxLayout, QHBoxLayout, QFileDialog, QMainWindow, QAction, qApp, QLabel, QApplication
from PyQt5.QtCore import Qt
import os #basic imports universal to different OS architectures
import sys
if not hasattr(sys, 'argv'):
    sys.argv  = ['']
import platform
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
from imageclassifier import ImageClassifier #check out the neural nets in these locations!
from deepdream import DeepDream
from imagegenerator import ImageGenerator
from textgenerator import TextGenerator
from musicgenerator import MusicGenerator
from atarigame import VideoGamer
from parameterdialogs import ImageClassifierParameterDialog, TextGeneratorParameterDialog, DeepDreamParameterDialog, \
  ImageGeneratorParameterDialog, MusicGeneratorParameterDialog, VideoGamerParameterDialog

class Notepad(QWidget): #Occupies center of main screen at runtime
  def __init__(self): #print welcome message, set font size
    super(Notepad, self).__init__()
    self.text = QTextEdit(self)
    self.text.setReadOnly(True)
    font = self.text.font()
    font.setPointSize(12)
    self.text.setFont(font)
    self.text.setAlignment(Qt.AlignCenter)
    self.init_ui()
    self.text.append("Woah hey! I'm just a funny little notepad. Don't mind me\n"
      + "I can connect to eleven neural networks that do different stuff..\n"
      + "Currently, there are FIVE flavors of deep learning (and ONE flavor of deep reinforcement learning)\nalgorithms to play with that are available\n\t"
      + "Text Generator\n\t"
      + "Image Classifier\n\t"
      + "Deep Dream Generator\n\t"
      + "Image Generator\n\t"
      + "Music Generator\n\t"
      + "Video Gamer\n\t"
      + "NOTE: CAREFUL TRAINING THE IMAGE GENERATOR IF YOU DON'T HAVE A GOOD GPU IT WILL TAKE FOREVER."
      + "\n\nIf you want to learn more, I have information on each network in the how to section."
      + "\n\nDetected System Information\n"
      + "OS: {0}\nSystem: {1}\nRelease: {2}".format(os.name, platform.system(), platform.release()))


  def init_ui(self): #setup general layout, of text area, buttons, and style of notepad 
    self.clr_btn = QPushButton('Clear Text')
    self.sav_btn = QPushButton('Save Text')
    self.opn_btn = QPushButton('Open Image')
    self.picture = QLabel(self)
    self.has_been_retrained = False
    self.setAutoFillBackground(True)
    p = self.palette()
    c = QColor(44, 22, 88, 255) 
    p.setColor(self.backgroundRole(), c)
    self.setPalette(p)
    self.text.setStyleSheet(" background-image: url('./icons/surfingsky.png'); " +
      "background-color: #1010a0; color:white;" +
      "background-repeat: space;" +
      "margin: 0 auto;" +
      "text-align: center;" +
      "background-position: center")
    v_layout = QVBoxLayout()
    h_layout = QHBoxLayout()
    h_layout.addWidget(self.clr_btn)
    h_layout.addWidget(self.sav_btn)
    h_layout.addWidget(self.opn_btn)
    v_layout.addWidget(self.picture)
    v_layout.addWidget(self.text)
    v_layout.addLayout(h_layout)
    self.sav_btn.clicked.connect(self.save_text)
    self.clr_btn.clicked.connect(self.clear_all)
    self.opn_btn.clicked.connect(self.run_image_classifier)
    self.setLayout(v_layout)
    self.show()

  def save_text(self): #saves text in text area at dialog location
    filename = QFileDialog.getSaveFileName(self, 'Save File', os.getenv('HOME'), "(Text File (*.txt )")
    try:
      with open(filename[0], 'w') as f:
        my_text = self.text.toPlainText()
        f.write(my_text)
    except FileNotFoundError:
      pass

  def clear_all(self): #clears text in text area and removes picture if it exists
    self.text.clear()
    self.picture.clear()
    self.text.setAlignment(Qt.AlignCenter)
    self.picture.setAlignment(Qt.AlignCenter)

  def copy_text(self): #copies text in text area to the clipboard
    self.text.copy()
    self.text.append("\ncopied!\n")

  def run_image_classifier(self, file_path='icons/surfingsky.png', rerun=False, 
    model='graphs/inception_v3_2016_08_28_frozen.pb', labels='graphs/imagenet_slim_labels.txt'): #opens a png/jpg/bmp/gif and classifies with current IC network
    self.clear_all()
    self.picture.setPixmap(QPixmap(file_path).scaledToHeight(512))
    self.text.append("Opening an image to classify...please wait...\n")
    if rerun is True:
      self.text.append(ImageClassifier.run_image_classifier(file_path, rerun, model, labels))
    else:
      self.text.append(ImageClassifier.run_image_classifier(file_path, rerun))

  def retrain_image_classifier(self, training_steps=4000, learn_rate=0.01, print_misclass=False, 
    flip_l_r=False, rnd_crop=0, rnd_scale=0, rnd_brightness=0):
    self.clear_all()
    self.text.append("Training a new image classifier!\nplease direct your attention to the console window.")
    retrain_image_dir = QFileDialog.getExistingDirectory(self, 
      "Hint: Open a directory with subfolders labeled by their desired classification.", 
      "os.getenv('HOME')")
    ImageClassifier.retrain_image_classifier(retrain_image_dir, True, training_steps, 
      learn_rate, print_misclass, flip_l_r, rnd_crop, rnd_scale, rnd_brightness)
    self.has_been_retrained = True

  def run_image_generator(self, INPUT_DATA_DIR="../../../Pictures-local/cars/cars_train/cars_train/",
    OUTPUT_DIR="./imagegen/", IMAGE_SIZE=128, NOISE_SIZE=100, LR_D=0.00004, LR_G=0.0004,
    BATCH_SIZE=64, EPOCHS=50,
    BETA1=0.5, WEIGHT_INIT_STDDEV=0.02, EPSILON=0.00005, SAMPLES_TO_SHOW=5):
    self.clear_all()
    self.text.append("Training the image generator....\n look at the terminal window to track progress\n")
    ImageGenerator.training(INPUT_DATA_DIR, OUTPUT_DIR, IMAGE_SIZE, 
    NOISE_SIZE, LR_D, LR_G, BATCH_SIZE, EPOCHS,
    BETA1, WEIGHT_INIT_STDDEV, EPSILON, SAMPLES_TO_SHOW)

  def resize_images(self, length=500, width=315):
    self.clear_all()
    src = QFileDialog.getExistingDirectory(self, 
      "Hint: Open a directory with image files in it", os.getenv('HOME'))
    dst = QFileDialog.getExistingDirectory(self, 
      "Hint: Open a directory to save resized images in", os.getenv('HOME'))    
    self.text.append("Resizing images...\n")
    ImageGenerator.resize(src, dst, length, width)

  def rgba_to_rgb(self):
    self.clear_all()
    self.text.append("Converting rgba to rgb...\n")
    src = QFileDialog.getExistingDirectory(self, 
      "Hint: Open a directory with image files in it", os.getenv('HOME'))
    dst = QFileDialog.getExistingDirectory(self, 
      "Hint: Open a directory to save reformatted images in", os.getenv('HOME'))
    ImageGenerator.rgba2rgb(src, dst)

  def run_deep_dream(self, file_path='icons/surfingsky.png', dream_layer='mixed4b', naive_render_iter=20, naive_step=1.0, 
    deep_render_iter=10, deep_step=1.5, octave_number=4, octave_scaled=1.4, downsize=255.0,
    img_noise_size=224, imagenet_mean_init=117.0, grad_tile_size=256, strip_const_size=32):
    self.clear_all()
    self.text.append("About to generate deep dream! Look at the terminal window.\n")
    dreamResult = QPixmap(DeepDream.run(file_path, dream_layer, naive_render_iter, naive_step,
      deep_render_iter, deep_step, octave_number, octave_scaled, downsize, img_noise_size, 
      imagenet_mean_init, grad_tile_size, strip_const_size)).scaledToHeight(512)
    self.picture.setPixmap(dreamResult)
    self.text.append("The resulting Dream Image is above!!")

  def train_text_generator(self, train_epochs=15, num_generate=400, temperature=1.0, trim_text=1, 
    embedding_dim=128, step_size=3, seq_length=40, BATCH_SIZE=128, file_path="text/bom.txt"):
    self.clear_all()
    self.text.append("Training the text generator on the input text. Please look at the terminal window.\n")
    TextGenerator.train_text_generator(train_epochs, num_generate, temperature,
      trim_text, embedding_dim, step_size, seq_length, BATCH_SIZE, file_path)

  def run_text_generator(self, num_generate=400, temperature=1.0, trim_text=1, embedding_dim=128,
    seq_length=40, step_size=3, file_path="text/bom.txt", ckpt_path="graphs/bom.pb"):
    self.clear_all()
    self.text.append("Here I am regenerating text from a saved model. Please wait...\n")
    TextGenerator.run_text_generator(
        num_generate, temperature, trim_text, embedding_dim,
        seq_length, step_size, file_path, ckpt_path)

  def use_music_generator(self, checkpoint='./musicvae/cat-drums_2bar_small.lokl.ckpt',
    config_map='cat-drums_2bar_small', batch_size=4, n=2, length=80, temperature=1.0):
    self.clear_all()
    self.text.append("Here turns on the music generator...\n")
    MusicGenerator.generate_musicvae(checkpoint, config_map, batch_size, n, length, temperature)
    self.text.append("Done did it!\n")

  def continue_melody(self, midi_file='default', num_steps=128, temperature=1.0):
    self.clear_all()
    self.text.append("Continuing MIDI sequence...\n")
    MusicGenerator.continue_melodyrnn(midi_file, num_steps, temperature)
    self.text.append("Done did it!\n")

  def random_multitrack(self, BATCH_SIZE=4, Z_SIZE=512, TOTAL_STEPS=512, 
    BAR_SECONDS=2.0, CHORD_DEPTH=49, SAMPLE_RATE=44100):
    self.clear_all()
    self.text.append("Generating random multitrack sequence...\n")
    MusicGenerator.random_multitrackvae(BATCH_SIZE, Z_SIZE, TOTAL_STEPS, BAR_SECONDS, CHORD_DEPTH, SAMPLE_RATE)
    self.text.append("Done did it!\n")

  def performance(self, temperature=1.0):
    self.clear_all()
    self.text.append("Generating performance...\n")
    MusicGenerator.performance_rnn(temperature)
    self.text.append("Done did it!\n")

  def play_last_generated(self):
    self.clear_all()
    self.text.append("Playing last generated music file...")
    MusicGenerator.play_last_generated()
    self.text.append("Finished!")

  def visual_last_generated(self):
    self.clear_all()
    self.text.append("Plotting last generated music file...")
    MusicGenerator.visual_last_generated()
    self.text.append("Finished!")

  def wav_to_spectrogram(self):
    self.clear_all()
    self.text.append("Find a valid wav file to convert to a spectrogram...")
    MusicGenerator.wav_to_spectrogram(self)
    self.text.append("all done!")

  def play_wav(self):
    wav_tuple = QFileDialog.getOpenFileName(self, 'Open wav', os.getenv('HOME'), "(*.wav)")
    MusicGenerator.play_wav(wav_tuple[0])

  def play_video_game(self, mode='test', env_name='SuperMarioBros-v0', weights='gameweights/dqn_SuperMarioBros-v0_weights.h5f', 
    INPUT_SHAPE_X = 84, INPUT_SHAPE_Y= 84, WINDOW_LENGTH = 4, random_seed=99,
    seq_mem_limit=1000000, policy_label='EpsGreedy', learning_rate=0.00025, nb_steps_warmup=50000, gamma=0.99, target_model_update=10000, 
    train_interval=4, delta_clip= 1., enable_double_dqn=True, enable_dueling_network=True, save_interval=250000, log_interval=10000, nb_steps=1750000,
    nb_episodes=1):
    VideoGamer.playAnyGame(mode, env_name, weights, 
      INPUT_SHAPE_X, INPUT_SHAPE_Y, WINDOW_LENGTH, random_seed,
      seq_mem_limit, policy_label, learning_rate, nb_steps_warmup, gamma, target_model_update, 
      train_interval, delta_clip, enable_double_dqn, enable_dueling_network, save_interval, log_interval, nb_steps,
      nb_episodes)

class MultinetWindow(QMainWindow): #Main Program window along with hidden popups
  def __init__(self):
    super().__init__()
    self.notepad = Notepad()
    self.setCentralWidget(self.notepad)
    self.init_ui()
    self.setWindowTitle('Deep Surfer AI Image Music and Text Tool')
    self.setWindowIcon(QIcon('./icons/main-icon.png'))
    self.showMaximized()
    self.ICpopup = ImageClassifierParameterDialog()
    self.IGpopup = ImageGeneratorParameterDialog()
    self.DDpopup = DeepDreamParameterDialog()
    self.TGpopup = TextGeneratorParameterDialog()
    self.MGpopup = MusicGeneratorParameterDialog()
    self.VGpopup = VideoGamerParameterDialog()
    self.show()

  def init_ui(self):
    bar = self.menuBar()
    fileMenu = bar.addMenu('File')
    textMenu = bar.addMenu('Text AI')
    imageMenu = bar.addMenu('Image AI')
    musicMenu = bar.addMenu('Music AI')
    gameMenu = bar.addMenu('Game AI')
    legalMenu = bar.addMenu('Legal')

    tSave = QAction('&Save Text', self)
    tClear = QAction('&Clear Text', self)
    tCopy = QAction('&Copy Text', self)
    tTrain = QAction('&Generate Text', self)
    tLoad = QAction('&Run Text Generator', self)
    tParams = QAction('&Text Generator Parameters', self)
    tHowTo = QAction('&How to Train Text Generator...', self)
    iOpenCNN = QAction('&Open Image for Classification', self)
    iTrainCNN = QAction('&Train Image Classifier on New Data', self)
    iAdvCNN = QAction('&Open Image Classifier with Model', self)
    iParamsCNN = QAction('&Image Classifier Parameters', self)
    iDream = QAction('&Apply Deep Dream to Image', self)
    iParamsDream = QAction('&Deep Dream Parameters', self)
    iResize = QAction('&Resize Images', self)
    iColorfix = QAction('&RGBA to RGB', self)
    iTrainGAN = QAction('&Train Image Generator', self)
    iParamsGAN = QAction('&Image Generator Parameters', self)
    iHowToCNN = QAction('&How to Train Image Classifier...', self)
    iHowToDream = QAction('&How to Deep Dream...', self)
    iHowToGAN = QAction("&How to Generate New Images...", self)
    mPlaylast = QAction('&Play Last Generated Piece', self)
    mDisplay = QAction('&Display Last Generated Visual', self)
    mPlayWav = QAction('&Play wav file', self)
    mSpectro = QAction('&Convert Wav to Spectrogram', self)
    mDrums = QAction('&Generate Drums', self)
    mPhrase = QAction('&Continue Melodic Phrase', self)
    mMultitrack = QAction('&Generate Random Multitrack', self)
    mPiano = QAction('&Generate Piano Performance', self)
    mParams = QAction('&Music Generator Parameters', self)
    mHowTo = QAction("&How to Generate Music...", self)
    vGame = QAction('&Run Video Game AI', self)
    vParams = QAction('&Video Game AI Parameters', self)
    legalInfo = QAction('&Info', self)
    qQuit = QAction('&Quit Application', self)

    tSave.setShortcut('Ctrl+S')
    tClear.setShortcut('Ctrl+Shift+Y')
    tCopy.setShortcut('Ctrl+C')
    tTrain.setShortcut('Ctrl+T')
    tLoad.setShortcut('Ctrl+L')
    tParams.setShortcut('Ctrl+Alt+T')
    tHowTo.setShortcut('Shift+T')
    iOpenCNN.setShortcut('Ctrl+O')
    iTrainCNN.setShortcut('Ctrl+R')
    iParamsCNN.setShortcut('Ctrl+Alt+R')
    iAdvCNN.setShortcut('Ctrl+Shift+O')
    iDream.setShortcut('Ctrl+D')
    iParamsDream.setShortcut('Ctrl+Alt+D')
    iResize.setShortcut('Ctrl+R')
    iColorfix.setShortcut('Ctrl+F')
    iTrainGAN.setShortcut('Ctrl+Shift+G')
    iParamsGAN.setShortcut('Ctrl+Alt+G')
    iHowToCNN.setShortcut('Shift+R')
    iHowToDream.setShortcut('Shift+D')
    iHowToGAN.setShortcut('Shift+G')
    mPlaylast.setShortcut('Ctrl+M')
    mDisplay.setShortcut('Ctrl+Shift+M')
    mPlayWav.setShortcut('Ctrl+W')
    mSpectro.setShortcut('Ctrl+Shift+V')
    mPiano.setShortcut('Ctrl+1')
    mMultitrack.setShortcut('Ctrl+2')
    mPhrase.setShortcut('Ctrl+3')
    mDrums.setShortcut('Ctrl+4')
    mParams.setShortcut('Ctrl+Alt+M')
    mHowTo.setShortcut('Shift+M')
    vGame.setShortcut('Ctrl+V')
    vGame.setShortcut('Ctrl+Alt+V')
    legalInfo.setShortcut('Shift+L')
    qQuit.setShortcut('Ctrl+Q')

    tSave.setStatusTip("Save the text the notepad area to a file")
    tClear.setStatusTip("Clear all text and any attached pictures")
    tCopy.setStatusTip("Copy all text to the clipboard")
    tTrain.setStatusTip("Train the text generator with default parameters on a text file")
    tLoad.setStatusTip("Load a text generator model file, along with the original text file")
    tParams.setStatusTip("Adjust the special parameters available for the long short term memory network")
    tHowTo.setStatusTip("Learn how to use the long short term memory text generator")
    iOpenCNN.setStatusTip("Open an image file to be classified by the convolutional neural network")
    iTrainCNN.setStatusTip("Train the convolutional neural network on a folder of folders of images")
    iParamsCNN.setStatusTip("Adjust the special parameters available for the convolutional neural network")
    iAdvCNN.setStatusTip("Open an image to be classfied by an alternate image classifier network")
    iDream.setStatusTip("Apply the default Deep Dream effect on an image file")
    iParamsDream.setStatusTip("Adjust the special parameters available for the deep dream's gradient ascent CNN")
    iResize.setStatusTip("Resize a folder of images to 256")
    iColorfix.setStatusTip("Removes the alpha channel from a folder of images")
    iTrainGAN.setStatusTip("Train the generative adversarial networks on a folder of images to generate new images")
    iParamsGAN.setStatusTip("Adjust the special parameters available for the generative adversarial network")
    iHowToCNN.setStatusTip("Learn how to use the convolution neural network image classifier")
    iHowToDream.setStatusTip("Learn how to use the gradient-ascent convolutional neural network deep dream")
    iHowToGAN.setStatusTip("Learn how to use the generative adversarial network image generator")
    mPlaylast.setStatusTip("Play the last MIDI file that was created, otherwise it plays a default song")
    mDisplay.setStatusTip("Display the MIDI information from the last MIDI file that was created, otherwise it displays a default song")
    mPlayWav.setStatusTip("Play a wav file from anywhere")
    mSpectro.setStatusTip("Convert a .wav file into a spectrogram for analysis purposes")
    mPiano.setStatusTip("Generate a piano performance usings a recurrent neural network just for you")
    mMultitrack.setStatusTip("Generatesa multitrack sequence using a variational autoencoder just for you")
    mPhrase.setStatusTip("Generate a melodic phrase using a recurrent neural network just for you")
    mDrums.setStatusTip("Generate a drum beat using a variational autoencoder just for you")
    mParams.setStatusTip("Adjust the special parameters available to all of the music generating algorithms")
    mHowTo.setStatusTip("Learn how to use the variational autoencoders and recurrent neural networks for generating music")
    vGame.setStatusTip("Run the deep Q learning neural network on a video game!")
    vParams.setStatusTip("Adjust the parameters of the deep Q learning neural network that plays video games")
    legalInfo.setStatusTip("Look at the app's legal info")
    qQuit.setStatusTip("Quit the application")

    fileMenu.addAction(qQuit)
    textMenu.addAction(tSave)
    textMenu.addAction(tCopy)
    textMenu.addAction(tClear)
    textMenu.addAction(tTrain)
    textMenu.addAction(tLoad)
    textMenu.addAction(tParams)
    textMenu.addAction(tHowTo)
    imageMenu.addAction(iOpenCNN)
    imageMenu.addAction(iTrainCNN)
    imageMenu.addAction(iAdvCNN)
    imageMenu.addAction(iParamsCNN)
    imageMenu.addAction(iHowToCNN)
    imageMenu.addAction(iDream)
    imageMenu.addAction(iParamsDream)
    imageMenu.addAction(iHowToDream)
    imageMenu.addAction(iTrainGAN)
    imageMenu.addAction(iParamsGAN)
    imageMenu.addAction(iHowToGAN)
    imageMenu.addAction(iResize)
    imageMenu.addAction(iColorfix)
    musicMenu.addAction(mPlaylast)
    musicMenu.addAction(mDisplay)
    musicMenu.addAction(mSpectro)
    musicMenu.addAction(mPiano)
    musicMenu.addAction(mMultitrack)
    musicMenu.addAction(mPhrase)
    musicMenu.addAction(mDrums)
    musicMenu.addAction(mParams)
    musicMenu.addAction(mHowTo)
    gameMenu.addAction(vGame)
    gameMenu.addAction(vParams)
    legalMenu.addAction(legalInfo)

    qQuit.triggered.connect(self.quitTrigger)
    fileMenu.triggered.connect(self.respond)
    textMenu.triggered.connect(self.respond)
    imageMenu.triggered.connect(self.respond)
    musicMenu.triggered.connect(self.respond)
    gameMenu.triggered.connect(self.respond)
    legalMenu.triggered.connect(self.legalInfo)
    self.show()

  def quitTrigger(self):
    self.notepad.clear_all()
    qApp.quit()

  def respond(self, q): #handles response to most GUI buttons pressed at runtime
    signal = q.text()
    '''try:'''
    if signal == '&Clear Text': #in FILE and EDIT
      self.notepad.clear_all()
    elif signal == '&Save Text':
      self.notepad.save_text()
    elif signal == '&Copy Text':
      self.notepad.copy_text()
    #Image Classification menu
    elif signal == '&Open Image for Classification':
      self.notepad.run_image_classifier(self.ICpopup.image_file, False)
    elif signal == '&Train Image Classifier on New Data':
      self.notepad.retrain_image_classifier(self.ICpopup.training_steps, 
        self.ICpopup.learn_rate, self.ICpopup.print_misclass, 
        self.ICpopup.flip_l_r, self.ICpopup.rnd_crop,
        self.ICpopup.rnd_scale, self.ICpopup.rnd_brightness)
    elif signal == '&Image Classifier Parameters':
      self.notepad.clear_all()
      self.notepad.text.append("Check out the Parameters for the Image Classifier in the other window!")
      self.ICpopup.show()
      self.ICpopup.setUpdatesEnabled(True)
    elif signal == '&Open Image Classifier with Model':
      self.notepad.run_image_classifier(self.ICpopup.image_file, True, self.ICpopup.model_file, self.ICpopup.label_file)
    #Image Generator Menu
    elif signal == '&Train Image Generator':
      self.notepad.run_image_generator(self.IGpopup.INPUT_DATA_DIR, self.IGpopup.OUTPUT_DIR, 
        self.IGpopup.IMAGE_SIZE,
        self.IGpopup.NOISE_SIZE, self.IGpopup.LR_D, self.IGpopup.LR_G, self.IGpopup.BATCH_SIZE,
        self.IGpopup.EPOCHS, self.IGpopup.BETA1, self.IGpopup.WEIGHT_INIT_STDDEV, 
        self.IGpopup.EPSILON, self.IGpopup.SAMPLES_TO_SHOW)
      self.notepad.text.append("\nAll Done!!!! Go look in the imagegen folder within the main directory of this program.\n"
        + "the generations.")
    elif signal == '&Resize Images':
      self.notepad.resize_images()
      self.notepad.text.append("\nDone!!")
    elif signal == '&RGBA to RGB':
      self.notepad.rgba_to_rgb()
      self.notepad.text.append("\nDone!!")
    elif signal == '&Image Generator Parameters':
      self.notepad.clear_all()
      self.notepad.text.append("Check out the Parameters for the Deep Dream Generator in the other window!")
      self.IGpopup.show()
      self.IGpopup.setUpdatesEnabled(True)
    #Deep Dream Menu
    elif signal == '&Apply Deep Dream to Image':
      self.notepad.run_deep_dream(self.DDpopup.image_file, self.DDpopup.dream_layer, self.DDpopup.naive_render_iter,
        self.DDpopup.naive_step, self.DDpopup.deep_render_iter, self.DDpopup.deep_step, 
        self.DDpopup.octave_number, self.DDpopup.octave_scaled, self.DDpopup.downsize,
        self.DDpopup.img_noise_size, self.DDpopup.imagenet_mean_init, self.DDpopup.grad_tile_size,
        self.DDpopup.strip_const_size)
    elif signal == '&Deep Dream Parameters':
      self.notepad.clear_all()
      self.notepad.text.append("Check out the Parameters for the Deep Dream Generator in the other window!")
      self.DDpopup.show()
      self.DDpopup.setUpdatesEnabled(True)
    #Text Generation Menu
    elif signal == '&Generate Text':
      self.notepad.train_text_generator(self.TGpopup.num_epochs, self.TGpopup.num_generate, self.TGpopup.temperature, 
        self.TGpopup.trim_text, self.TGpopup.embedding_dim, self.TGpopup.step_size, self.TGpopup.seq_length, 
        self.TGpopup.BATCH_SIZE, self.TGpopup.text_file)
    elif signal == '&Run Text Generator':
      self.notepad.run_text_generator()
    elif signal == '&Text Generator Parameters':
      self.notepad.clear_all()
      self.notepad.text.append("Check out the Parameters for the Text Generator in the other window!")
      self.TGpopup.show()
      self.ICpopup.setUpdatesEnabled(True)
    #Music Generators
    elif signal == '&Generate Drums':
      self.notepad.use_music_generator(self.MGpopup.vae_checkpoint, self.MGpopup.vae_config_map, 
        self.MGpopup.vae_batch_size, self.MGpopup.vae_n, self.MGpopup.vae_length, self.MGpopup.vae_temperature)
    elif signal == '&Continue Melodic Phrase':
      self.notepad.continue_melody(self.MGpopup.mel_midi_file, self.MGpopup.mel_num_steps, self.MGpopup.mel_temperature)
    elif signal == '&Generate Random Multitrack':
      self.notepad.random_multitrack(self.MGpopup.mvae_batch_size, self.MGpopup.mvae_z_size,
        self.MGpopup.mvae_total_steps, self.MGpopup.mvae_bar_seconds, self.MGpopup.mvae_chord_depth, self.MGpopup.mvae_sample_rate)
    elif signal == '&Generate Piano Performance':
      self.notepad.performance(self.MGpopup.perf_temperature)
    elif signal == '&Music Generator Parameters':
      self.notepad.clear_all()
      self.notepad.text.append("Check out music generator params in the other window!!!\n")
      self.MGpopup.show()
      self.MGpopup.setUpdatesEnabled(True)
    elif signal == '&Convert Wav to Spectrogram':
      self.notepad.wav_to_spectrogram()
    elif signal == '&Play wav file':
      self.notepad.play_wav()
    elif signal == '&Play Last Generated Piece':
      self.notepad.play_last_generated()
    elif signal == '&Display Last Generated Visual':
      self.notepad.visual_last_generated()
    elif signal == '&Run Video Game AI':
      self.notepad.play_video_game(self.VGpopup.mode, self.VGpopup.env_name, self.VGpopup.weights, 
        self.VGpopup.input_shape_X, self.VGpopup.input_shape_Y, self.VGpopup.window_length, self.VGpopup.random_seed,
        self.VGpopup.seq_mem_limit, self.VGpopup.policy, self.VGpopup.learning_rate, self.VGpopup.nb_steps_warmup, self.VGpopup.gamma, 
        self.VGpopup.target_model_update, self.VGpopup.window_length, self.VGpopup.delta_clip, self.VGpopup.enable_double_dqn, 
        self.VGpopup.enable_dueling_network, self.VGpopup.save_interval, self.VGpopup.log_interval, self.VGpopup.nb_steps,
        self.VGpopup.nb_episodes)
    elif signal == '&Video Game AI Parameters':
      self.notepad.clear_all()
      self.notepad.text.append("Check out video gamer AI params in the other window!!!\n")
      self.VGpopup.show()
      self.VGpopup.setUpdatesEnabled(True)
    #Help Menu
    elif signal == '&How to Train Image Classifier...':
      self.notepad.clear_all()
      self.notepad.text.append("Here's an example, which assumes you have a folder containing " +
        "CLASS-NAMED\nSUBFOLDERS, each full of images for each label.\n The example folder" +
        " flower_photos should have a structure like this:\n~/flower_photos/daisy/photo1.jpg\n" +
        "~/flower_photos/daisy/photo2.jpg\n...\n~/flower_photos/rose/anotherphoto77.jpg\n...\n~/" +
        "flower_photos/sunflower/somepicture.jpg\nThe subfolder names are important, since they " +
        "define what label is applied to\neach image, but the filenames themselves don't matter." +
        "Once your images are\nprepared (can take a long time depending on the amount of images)" +
        ",\nyou can run easily press the open button from the drop-down menu,\nor the open butto" +
        "n on the bottom right of the text area.\n" +
        "\n\nIf you'd like to know more, look up Convolutional Neural Networks.")
    elif signal == '&How to Train Text Generator...':
      self.notepad.clear_all()
      self.notepad.text.append("Just go to Train and Generate text, find a text file for it" +
        " to read and it should start to generate :}\n" +
        " longer texts take longer to train, but generally produce better results.\n" +
        "\n\nIf you'd like to know more, look up Long Short Term Memory Recurrent Neural Networks.")
    elif signal == '&How to Deep Dream...':
      self.notepad.clear_all()
      self.notepad.text.append("Find and download an image that you'd like to manipulate\n" +
        "in the dream machine.\nWhen prompted to open a file, locate the image on your computer.\n" +
        "Then wait for the output to come back. It can take a while,\n" +
        "Depending on the size of the image.\nAlso, try the parameters! Especially dream layer and octave.\n" +
        "\n\nIf you'd like to know more, look up Google Deep Dream.")
    elif signal == '&How to Generate New Images...':
      self.notepad.clear_all()
      self.notepad.text.append("FIRST OFF, DON'T TRY IT WITHOUT A GPU! ITS TOO DAMN SLOW.\n" +
        "I'm serious. Were talking 12-48 hours to get any usable results.\n" +
        "With a GPU build this will reach Epoch 50 on ~10000 images in 2-3 hours.\n" + 
        "When prompted to open a folder, locate a folder of images that you would like the\n" +
        "Image Generator to train on. It will save produced images in the imagegen folder.\n" +
        "\n\nIf you'd like to learn more, look up Deconvolutional Generative Adversarial Networks.")   
    elif signal == '&How to Generate Music...':
      self.notepad.clear_all()
      self.notepad.text.append("Generating music is easy!! All you have to do is click any\n" +
        "of the four buttons from the menu:\nGenerate Music\nContinue Musical Phrase\n" +
        "Generate Random Multitrack\nPerformance\n\nYou can play the last generated file using the\n" +
        "Play Last Generated Piece\n\nOnce you are comfortable try out the parameters!\n :)")
    elif signal == '&How to Train Video Game AI...':
      self.notepad.clear_all()
      self.notepad.text.append("Training the video gamer AI is easy!! All you have to do is change the parameters\n" +
        "it will let you select different mario levels.\n")
    #add more specific exceptions here at some point...
    '''
    except Exception as e:
      self.notepad.clear_all()
      template = "An exception of type {0} occured. Arguments:\n{1!r}"
      message = template.format(type(e).__name__, e.args)
      self.notepad.text.append(message + "\nsorry :(")
    '''

  def legalInfo(self):
    self.notepad.clear_all()
    self.notepad.text.append("PyQT5 is under a General Public License \n" +
      "Tensorflow is under an Apache 2.0 License.\n" +
      "This is Version 0.1, version. It shouldn't be able to do anything that would crash\n" +
      "the program with the generalized exception rule above.")

if __name__ == '__main__':
  app = QApplication(sys.argv)
  labelWindow = MultinetWindow()
  sys.exit(app.exec_())