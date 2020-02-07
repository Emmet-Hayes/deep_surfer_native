'''
'''
import os
import platform
from PyQt5.QtGui import QIcon #GUI importz bb
from PyQt5.QtWidgets import QWidget, QPushButton, QInputDialog, QFileDialog, QFormLayout, QLineEdit

options = QFileDialog.Options()

if platform.system() == 'Darwin':
  options |= QFileDialog.DontUseNativeDialog

class ImageClassifierParameterDialog(QWidget): #gui hyperparameters for image classifier retrainer
  def __init__(self, parent = None):
    super(ImageClassifierParameterDialog, self).__init__(parent)
    self.image_file='icons/surfingsky.png'
    self.training_steps=4000 #IC hyperparameters are initialized here
    self.learn_rate=0.01 
    self.print_misclass=False
    self.flip_l_r=False
    self.rnd_crop=0 
    self.rnd_scale=0
    self.rnd_brightness=0
    self.model_file='graphs/inception_v3_2016_08_28_frozen.pb'
    self.label_file='graphs/imagenet_slim_labels.txt'
    self.setWindowTitle("Image Classifier Parameters")
    self.setWindowIcon(QIcon('./icons/cnn-icon.png'))
    layout = QFormLayout()
    self.btnIF = QPushButton("Image File") #each line of param in gui is 6 lines of code
    self.btnIF.clicked.connect(self.setImageFile)
    self.leIF = QLineEdit()
    self.leIF.setText(str(self.image_file))
    self.leIF.setReadOnly(True)
    layout.addRow(self.btnIF, self.leIF)
    self.btnTS = QPushButton("Training Steps")
    self.btnTS.clicked.connect(self.setTrainSteps)
    self.leTS = QLineEdit()
    self.leTS.setText(str(self.training_steps))
    self.leTS.setReadOnly(True)
    layout.addRow(self.btnTS,self.leTS)
    self.btnLR = QPushButton("Learning Rate")
    self.btnLR.clicked.connect(self.setLearnRate)
    self.leLR = QLineEdit()
    self.leLR.setText(str(self.learn_rate))
    self.leLR.setReadOnly(True)
    layout.addRow(self.btnLR,self.leLR)
    self.btnMC = QPushButton("Show Misclassified Images")
    self.btnMC.clicked.connect(self.setMisclass)
    self.leMC = QLineEdit()
    self.leMC.setText("No")
    self.leMC.setReadOnly(True)
    layout.addRow(self.btnMC,self.leMC)
    self.btnFL = QPushButton("Flip Left and Right")
    self.btnFL.clicked.connect(self.setFlipLR)
    self.leFL = QLineEdit()
    self.leFL.setText("No")
    self.leFL.setReadOnly(True)
    layout.addRow(self.btnFL,self.leFL)
    self.btnRC = QPushButton("Random Crop")
    self.btnRC.clicked.connect(self.setRndCrop)
    self.leRC = QLineEdit()
    self.leRC.setText("No")
    self.leRC.setReadOnly(True)
    layout.addRow(self.btnRC,self.leRC)
    self.btnRS = QPushButton("Random Scale")
    self.btnRS.clicked.connect(self.setRndScale)
    self.leRS = QLineEdit()
    self.leRS.setText("No")
    self.leRS.setReadOnly(True)
    layout.addRow(self.btnRS,self.leRS)
    self.btnRB = QPushButton("Random Brightness")
    self.btnRB.clicked.connect(self.setRndBrightness)
    self.leRB = QLineEdit()
    self.leRB.setText("No")
    self.leRB.setReadOnly(True)
    layout.addRow(self.btnRB,self.leRB)
    self.btnMF = QPushButton("Model File")
    self.btnMF.clicked.connect(self.setModelFile)
    self.leMF = QLineEdit()
    self.leMF.setText(self.model_file)
    self.leMF.setReadOnly(True)
    layout.addRow(self.btnMF,self.leMF)
    self.btnLF = QPushButton("Label File")
    self.btnLF.clicked.connect(self.setLabelFile)
    self.leLF = QLineEdit()
    self.leLF.setText(self.label_file)
    self.leLF.setReadOnly(True)
    layout.addRow(self.btnLF,self.leLF)
    self.setLayout(layout) #set the layout to the window after you set it up

  def setImageFile(self):
    file,ok = QFileDialog.getOpenFileName(self,'Image File', os.getenv('HOME'), "Image File ( *.jpg, *.jpeg, *.png)", options=options)
    if ok:
      self.image_file=file
      self.leIF.setText(str(file))

  def setTrainSteps(self): #gui collects total training steps from user input
    num,ok = QInputDialog.getInt(self,"Training Steps",
      "Enter a Positive Integer (Don't do 20000 steps if you don't have a GPU for 4 hours to spare.)")
    if ok:
      self.training_steps=num
      self.leTS.setText(str(num))

  def setLearnRate(self): #all these set functions are the same except for type of input
    num,ok = QInputDialog.getDouble(self,"Learning Rate",
      "Enter a Positive Decimal Number", 0.01, decimals=5)
    if ok: 
      self.learning_rate=num
      self.leLR.setText(str(num))

  def setMisclass(self):
    items = ("Yes", "No")
    item, ok = QInputDialog.getItem(self, "Misclassified Test Images", 
      "Would you like the network to print misclassified test images?", items, 0, False)
    if ok and item: 
      if item is "Yes": self.print_misclass=True
      elif item is "No": self.print_misclass=False
      else: return
      self.leMC.setText(str(item))

  def setFlipLR(self):
    items = ("Yes", "No")
    item, ok = QInputDialog.getItem(self, "Flip Left and Right", 
       "Would you like the network to flip images left to right?", items, 0, False)
    if ok and item: 
      if item is "Yes": self.flip_l_r=True
      elif item is "No": self.flip_l_r=False
      else: return 
      self.leFL.setText(str(item)) 

  def setRndCrop(self):
    items = ("Yes", "No")
    item, ok = QInputDialog.getItem(self, "Random Cropping", 
       "Would you like the network to randomly crop test images?", items, 0, False)
    if ok and item: 
      if item is "Yes": self.rnd_crop=True
      elif item is "No": self.rnd_crop=False
      else: return 
      self.leRC.setText(str(item)) 

  def setRndScale(self):
    items = ("Yes", "No")
    item, ok = QInputDialog.getItem(self, "Random Scale", 
       "Would you like the network to randomly scale test images?", items, 0, False)
    if ok and item:
      if item is "Yes": self.rnd_scale=True
      elif item is "No": self.rnd_scale=False
      else: return 
      self.leRS.setText(str(item)) 

  def setRndBrightness(self):
    items = ("Yes", "No")
    item, ok = QInputDialog.getItem(self, "Random Brightness", 
       "Would you like the network to randomly brighten test images?", items, 0, False)
    if ok and item: 
      if item is "Yes": self.rnd_brightness=True
      elif item is "No": self.rnd_brightness=False
      else: return 
      self.leRB.setText(str(item))

  def setModelFile(self):
    file,ok = QFileDialog.getOpenFileName(self,'Model File', os.getenv('HOME'), "Model File ( *.pb )", options=options)
    if ok:
      self.model_file=file
      self.leMF.setText(str(file))

  def setLabelFile(self):
    file,ok = QFileDialog.getOpenFileName(self,'Label File', os.getenv('HOME'), "Text File ( *.txt )", options=options)
    if ok:
      self.label_file=file
      self.leLF.setText(str(file))

class DeepDreamParameterDialog(QWidget): #gui hyperparameters for deep dream image processing
  def __init__(self, parent = None):
    super(DeepDreamParameterDialog, self).__init__(parent)
    self.image_file='icons/surfingsky.png'
    self.dream_layer='mixed4c'
    self.naive_render_iter=20
    self.naive_step=1.0
    self.deep_render_iter=10
    self.deep_step = 1.5 
    self.octave_number=4
    self.octave_scaled=1.4
    self.downsize=255.0
    self.img_noise_size=224 
    self.imagenet_mean_init=117.0
    self.grad_tile_size=256
    self.strip_const_size=32
    self.setWindowTitle("Deep Dream Parameters")
    self.setWindowIcon(QIcon('./icons/deep-dream-icon.png'))
    layout = QFormLayout()
    self.btnIF = QPushButton("Image File")
    self.btnIF.clicked.connect(self.setImageFile)
    self.leIF = QLineEdit()
    self.leIF.setText(str(self.image_file))
    self.leIF.setReadOnly(True)
    layout.addRow(self.btnIF,self.leIF)
    self.btnDL = QPushButton("Dream Layer")
    self.btnDL.clicked.connect(self.setDreamLayer)
    self.leDL = QLineEdit()
    self.leDL.setText(str(self.dream_layer))
    self.leDL.setReadOnly(True)
    layout.addRow(self.btnDL,self.leDL)
    self.btnNRI = QPushButton("Naive Render Iterator")
    self.btnNRI.clicked.connect(self.setNRI)
    self.leNRI = QLineEdit()
    self.leNRI.setText(str(self.naive_render_iter))
    self.leNRI.setReadOnly(True)
    layout.addRow(self.btnNRI,self.leNRI)
    self.btnNS = QPushButton("Naive Step")
    self.btnNS.clicked.connect(self.setNaiveStep)
    self.leNS = QLineEdit()
    self.leNS.setText(str(self.naive_step))
    self.leNS.setReadOnly(True)
    layout.addRow(self.btnNS,self.leNS)
    self.btnDRI = QPushButton("Deep Render Iterator")
    self.btnDRI.clicked.connect(self.setDRI)
    self.leDRI = QLineEdit()
    self.leDRI.setText(str(self.deep_render_iter))
    self.leDRI.setReadOnly(True)
    layout.addRow(self.btnDRI,self.leDRI)
    self.btnDS = QPushButton("Deep Step")
    self.btnDS.clicked.connect(self.setDeepStep)
    self.leDS = QLineEdit()
    self.leDS.setText(str(self.deep_step))
    self.leDS.setReadOnly(True)
    layout.addRow(self.btnDS,self.leDS)
    self.btnON = QPushButton("Octave Number")
    self.btnON.clicked.connect(self.setOctaveNumber)
    self.leON = QLineEdit()
    self.leON.setText(str(self.octave_number))
    self.leON.setReadOnly(True)
    layout.addRow(self.btnON,self.leON)
    self.btnOS = QPushButton("Octave Scale")
    self.btnOS.clicked.connect(self.setOctaveScale)
    self.leOS = QLineEdit()
    self.leOS.setText(str(self.octave_scaled))
    self.leOS.setReadOnly(True)
    layout.addRow(self.btnOS, self.leOS)
    self.btnDZ = QPushButton("Downsize")
    self.btnDZ.clicked.connect(self.setDownsize)
    self.leDZ = QLineEdit()
    self.leDZ.setText(str(self.downsize))
    self.leDZ.setReadOnly(True)
    layout.addRow(self.btnDZ,self.leDZ)
    self.btnIN = QPushButton("Image Noise")
    self.btnIN.clicked.connect(self.setImageNoise)
    self.leIN = QLineEdit()
    self.leIN.setText(str(self.img_noise_size))
    self.leIN.setReadOnly(True)
    layout.addRow(self.btnIN,self.leIN)
    self.btnIM = QPushButton("Image Net Mean")
    self.btnIM.clicked.connect(self.setImagenetMean)
    self.leIM = QLineEdit()
    self.leIM.setText(str(self.imagenet_mean_init))
    self.leIM.setReadOnly(True)
    layout.addRow(self.btnIM,self.leIM)
    self.btnGT = QPushButton("Grad Tile Size")
    self.btnGT.clicked.connect(self.setGradTileSize)
    self.leGT = QLineEdit()
    self.leGT.setText(str(self.grad_tile_size))
    self.leGT.setReadOnly(True)
    layout.addRow(self.btnGT,self.leGT)
    self.btnSC = QPushButton("Strip Const Size")
    self.btnSC.clicked.connect(self.setStripConstSize)
    self.leSC = QLineEdit()
    self.leSC.setText(str(self.strip_const_size))
    self.leSC.setReadOnly(True)
    layout.addRow(self.btnSC,self.leSC)
    self.setLayout(layout)

  def setImageFile(self):
    file,ok = QFileDialog.getOpenFileName(self,'Image File', os.getenv('HOME'), "Image File (*.jpg, *.png)", options=options)
    if ok:
      self.image_file=file
      self.leIF.setText(str(file))

  def setDreamLayer(self):
    dream_layers = ("mixed4c", "conv2d0", "conv2d1", "conv2d2", "mixed3a", "mixed3b", "mixed4a",
     "mixed4b", "mixed4d", "mixed4e", "mixed5a", "mixed5b", "maxpool4")
    item,ok = QInputDialog.getItem(self,"Dream Layer",
      "Enter the dream layer that you want to dream on.", dream_layers, 0, False)
    if ok and item:
      self.dream_layer = item
      self.leDL.setText(item)

  def setNRI(self):
    num,ok = QInputDialog.getInt(self,"Naive Render Iterations",
      "Enter the amount of iterations you want to render in the naive state.", 20)
    if ok: 
      self.naive_render_iter=num
      self.leNRI.setText(str(num))

  def setNaiveStep(self):
    num,ok = QInputDialog.getDouble(self,"Naive Step",
      "Enter the step size of each iteration in the naive state.", 1.0, decimals=2)
    if ok: 
      self.naive_step=num
      self.leNS.setText(str(num))

  def setDRI(self):
    num,ok = QInputDialog.getInt(self,"Deep Dream Render Iterations",
      "Enter the amount of iterations you want to render in the deep dream state.", 10)
    if ok: 
      self.deep_render_iter=num
      self.leDRI.setText(str(num))

  def setDeepStep(self):
    num,ok = QInputDialog.getDouble(self,"Deep Step",
      "Enter the step size of each iteration in the deep dream state.", 1.5, decimals=2)
    if ok: 
      self.deep_step=num
      self.leDS.setText(str(num))

  def setOctaveNumber(self):
    num,ok = QInputDialog.getInt(self,"Octave Number",
      "Enter the amount of octaves you'd like to run on the image (3 or 4 is a normal dose)", 4)
    if ok: 
      self.octave_number=num
      self.leON.setText(str(num))

  def setOctaveScale(self):
    num,ok = QInputDialog.getDouble(self,"Octave Scale",
      "Enter the scale of each octave (floating decimal number)", 1.4, decimals=2)
    if ok: 
      self.octave_scaled=num
      self.leOS.setText(str(num))

  def setDownsize(self):
    num,ok = QInputDialog.getDouble(self,"Overload Truncation",
      "Enter the downsizing variable (255/256 preferred)", 255.0)
    if ok: 
      self.downsize=num
      self.leDZ.setText(str(num))

  def setImageNoise(self):
    num,ok = QInputDialog.getInt(self,"Image Noise",
      "Enter the size (x by x) of the initial image noise tile.", 224)
    if ok: 
      self.img_noise_size=num
      self.leIN.setText(str(num))

  def setImagenetMean(self):
    num,ok = QInputDialog.getDouble(self,"Imagenet Mean",
      "Enter the initial mean to use on imagenet gradient.", 117.0)
    if ok: 
      self.leIM.setText(str(num))
      self.imagenet_mean_init=num

  def setGradTileSize(self):
    num, ok = QInputDialog.getInt(self,"Gradient Tile Size",
      "Enter the size of the tiles used on imagenet gradient.", 256)
    if ok: 
      self.leGT.setText(str(num))
      self.grad_tile_size=num

  def setStripConstSize(self):
    num, ok = QInputDialog.getInt(self,"",
      "Enter the size of the buffer for tensor constants.", 32)
    if ok: 
      self.leSC.setText(str(num))
      self.strip_const_size=num

class TextGeneratorParameterDialog(QWidget): #gui hyperparameters for lstm text gen
  def __init__(self, parent = None):
    super(TextGeneratorParameterDialog, self).__init__(parent)
    self.text_file="text/bom.txt"
    self.model_file="graphs/bom.pb"
    self.num_epochs=15
    self.num_generate=400
    self.temperature=1.0
    self.trim_text = 1
    self.embedding_dim=128
    self.step_size=3
    self.seq_length=40
    self.BATCH_SIZE=128
    self.setWindowTitle("Text Generator Parameters")
    self.setWindowIcon(QIcon('./icons/text-gen-icon.png'))
    layout = QFormLayout()    
    self.btnTF = QPushButton("Text File")
    self.btnTF.clicked.connect(self.setTextFile)
    self.leTF = QLineEdit()
    self.leTF.setText(str(self.text_file))
    self.leTF.setReadOnly(True)
    layout.addRow(self.btnTF,self.leTF)    
    self.btnMF = QPushButton("Model File")
    self.btnMF.clicked.connect(self.setModelFile)
    self.leMF = QLineEdit()
    self.leMF.setText(str(self.model_file))
    self.leMF.setReadOnly(True)
    layout.addRow(self.btnMF,self.leMF)
    self.btnNE = QPushButton("Epochs of Training")
    self.btnNE.clicked.connect(self.setTrainEpochs)
    self.leNE = QLineEdit()
    self.leNE.setText(str(self.num_epochs))
    self.leNE.setReadOnly(True)
    layout.addRow(self.btnNE,self.leNE)
    self.btnNG = QPushButton("Generated Character Count")
    self.btnNG.clicked.connect(self.setNumGenerate)
    self.leNG = QLineEdit()
    self.leNG.setText(str(self.num_generate))
    self.leNG.setReadOnly(True)
    layout.addRow(self.btnNG,self.leNG)
    self.btnTP = QPushButton("Temperature")
    self.btnTP.clicked.connect(self.setTemperature)
    self.leTP = QLineEdit()
    self.leTP.setText(str(self.temperature))
    self.leTP.setReadOnly(True)
    layout.addRow(self.btnTP,self.leTP)
    self.btnTT = QPushButton("Trim Start/End Characters")
    self.btnTT.clicked.connect(self.setTrimText)
    self.leTT = QLineEdit()
    self.leTT.setText(str(self.trim_text))
    self.leTT.setReadOnly(True)
    layout.addRow(self.btnTT,self.leTT)
    self.btnED = QPushButton("Embedding Dimensions of Network")
    self.btnED.clicked.connect(self.setEmbeddingDim)
    self.leED = QLineEdit()
    self.leED.setText(str(self.embedding_dim))
    self.leED.setReadOnly(True)
    self.btnSS = QPushButton("Training Step Size")
    self.btnSS.clicked.connect(self.setStepSize)
    self.leSS = QLineEdit()
    self.leSS.setText(str(self.step_size))
    self.leSS.setReadOnly(True)
    layout.addRow(self.btnSS,self.leSS)
    self.btnSL = QPushButton("Character Sequence Length (Training)")
    self.btnSL.clicked.connect(self.setSeqLength)
    self.leSL = QLineEdit()
    self.leSL.setText(str(self.seq_length))
    self.leSL.setReadOnly(True)
    layout.addRow(self.btnSL,self.leSL)
    self.btnBS = QPushButton("Batch Size (Training)")
    self.btnBS.clicked.connect(self.setBatchSize)
    self.leBS = QLineEdit()
    self.leBS.setText(str(self.BATCH_SIZE))
    self.leBS.setReadOnly(True)
    layout.addRow(self.btnBS,self.leBS)
    self.setLayout(layout)

  def setTrainEpochs(self):
    num,ok = QInputDialog.getInt(self,"Training Epochs",
      "Enter the amount of epochs you would like to train for.")
    if ok: 
      self.num_epochs=num
      self.leNE.setText(str(num))

  def setNumGenerate(self):
    num,ok = QInputDialog.getInt(self,"Generated Character Count",
      "Enter the amount of characters you want to generate.")
    if ok: 
      self.num_generate=num
      self.leNG.setText(str(num))

  def setTemperature(self):
    num,ok = QInputDialog.getDouble(self,"Temperature",
      "Enter a Positive Decimal Number", 1.0, decimals=2)
    if ok: 
      self.temperature=num
      self.leTP.setText(str(num))

  def setTrimText(self):
    num,ok = QInputDialog.getInt(self,"Trim Character Count",
      "Enter the amount of characters you want to trim from beginning/end of file being read.")
    if ok: 
      self.trim_text=num
      self.leTT.setText(str(num))

  def setEmbeddingDim(self):
    num,ok = QInputDialog.getInt(self,"Embedding Dimensions of Network (Training)",
      "Enter the amount of embedding dimensions you want in your network.")
    if ok: 
      self.embedding_dim=num
      self.leED.setText(str(num))

  def setStepSize(self):
    num,ok = QInputDialog.getInt(self,"Training Step Size",
      "Set the size of training steps for the network.")
    if ok: 
      self.step_size=num
      self.leSS.setText(str(num))

  def setSeqLength(self):
    num,ok = QInputDialog.getInt(self,"Sequence Length (Training)",
      "Enter the length of character sequences you want the network to create.")
    if ok: 
      self.seq_length=num
      self.leSL.setText(str(num))

  def setBatchSize(self):
    num,ok = QInputDialog.getInt(self,"Batch Size (Training)",
      "Enter the size of batches you want the network to look at.")
    if ok: 
      self.BATCH_SIZE=num
      self.leBS.setText(str(num))

  def setTextFile(self):
    file,ok = QFileDialog.getOpenFileName(self,'Text File', os.getenv('HOME'), "Text File ( *.txt )", options=options)
    if ok:
      self.text_file=file
      self.leTF.setText(str(file))

  def setModelFile(self):
    file,ok = QFileDialog.getOpenFileName(self,'Model File', os.getenv('HOME'), "Model File ( *.pb )", options=options)
    if ok:
      self.model_file=file
      self.leMF.setText(str(file))

class ImageGeneratorParameterDialog(QWidget): #gui hyperparameters for wgan image gen
  def __init__(self, parent = None):
    super(ImageGeneratorParameterDialog, self).__init__(parent)
    self.INPUT_DATA_DIR="../../../Pictures-local/smallceleba/"
    self.OUTPUT_DIR="./imagegen/"
    self.IMAGE_SIZE=128 
    self.NOISE_SIZE=100 
    self.LR_D=0.00004
    self.LR_G=0.0004
    self.BATCH_SIZE=64
    self.EPOCHS=50
    self.BETA1=0.5
    self.WEIGHT_INIT_STDDEV=0.02 
    self.EPSILON=0.00005 
    self.SAMPLES_TO_SHOW=5
    self.setWindowTitle("Image Generator Parameters")
    self.setWindowIcon(QIcon('./icons/gan-icon.png'))
    layout = QFormLayout()
    btnID = QPushButton("Image Folder Directory")
    btnID.clicked.connect(self.setImageDir)
    self.leID = QLineEdit()
    self.leID.setText(str(self.INPUT_DATA_DIR))
    self.leID.setReadOnly(True)
    layout.addRow(btnID, self.leID)
    btnOD = QPushButton("Output Directory")
    btnOD.clicked.connect(self.setGenDir)
    self.leOD = QLineEdit()
    self.leOD.setText(str(self.OUTPUT_DIR))
    self.leOD.setReadOnly(True)
    layout.addRow(btnOD, self.leOD)
    btnIS = QPushButton("Image Size")
    btnIS.clicked.connect(self.setImageSize)
    self.leIS = QLineEdit()
    self.leIS.setText(str(self.IMAGE_SIZE))
    self.leIS.setReadOnly(True)
    layout.addRow(btnIS, self.leIS)
    btnNS = QPushButton("Noise Size")
    btnNS.clicked.connect(self.setNoiseSize)
    self.leNS = QLineEdit()
    self.leNS.setText(str(self.NOISE_SIZE))
    self.leNS.setReadOnly(True)
    layout.addRow(btnNS, self.leNS)
    btnDL = QPushButton("Discriminator Learning Rate")
    btnDL.clicked.connect(self.setDiscLearn)
    self.leDL = QLineEdit()
    self.leDL.setText(str(self.LR_D))
    self.leDL.setReadOnly(True)
    layout.addRow(btnDL, self.leDL)
    btnGL = QPushButton("Generator Learning Rate")
    btnGL.clicked.connect(self.setGenLearn)
    self.leGL = QLineEdit()
    self.leGL.setText(str(self.LR_G))
    self.leGL.setReadOnly(True)
    layout.addRow(btnGL, self.leGL)
    btnBS = QPushButton("Batch Size")
    btnBS.clicked.connect(self.setBatchSize)
    self.leBS = QLineEdit()
    self.leBS.setText(str(self.BATCH_SIZE))
    self.leBS.setReadOnly(True)
    layout.addRow(btnBS, self.leBS)
    btnEP = QPushButton("Epochs")
    btnEP.clicked.connect(self.setEpochs)
    self.leEP = QLineEdit()
    self.leEP.setText(str(self.EPOCHS))
    self.leEP.setReadOnly(True)
    layout.addRow(btnEP, self.leEP)
    btnBT = QPushButton("BETA1")
    btnBT.clicked.connect(self.setBETA1)
    self.leBT = QLineEdit()
    self.leBT.setText(str(self.BETA1))
    self.leBT.setReadOnly(True)
    layout.addRow(btnBT, self.leBT)
    btnES = QPushButton("Epsilon")
    btnES.clicked.connect(self.setEpsilon)
    self.leES = QLineEdit()
    self.leES.setText(str(self.EPSILON))
    self.leES.setReadOnly(True)
    layout.addRow(btnES, self.leES)
    btnIW = QPushButton("Initialize Weights STDDEV")
    btnIW.clicked.connect(self.setInitSTD)
    self.leIW = QLineEdit()
    self.leIW.setText(str(self.WEIGHT_INIT_STDDEV))
    self.leIW.setReadOnly(True)
    layout.addRow(btnIW, self.leIW)
    btnSS = QPushButton("Samples to Show")
    btnSS.clicked.connect(self.setShowSamples)
    self.leSS = QLineEdit()
    self.leSS.setText(str(self.SAMPLES_TO_SHOW))
    self.leSS.setReadOnly(True)
    layout.addRow(btnSS, self.leSS)
    self.setLayout(layout)
  
  def setImageDir(self):
    folder = QFileDialog.getExistingDirectory(self, 
      "Hint: Open a directory with images to imitate.", 
      "os.getenv('HOME')") + '/'
    if folder:
      self.INPUT_DATA_DIR=folder
      self.leID.setText(str(folder))

  def setGenDir(self):
    folder = QFileDialog.getExistingDirectory(self, 
      "Hint: Open a directory to save generated images.", 
      "os.getenv('HOME')")
    if folder:
      self.OUTPUT_DIR=folder
      self.leGD.setText(str(folder))

  def setImageSize(self):
    num,ok = QInputDialog.getInt(self,"Image Size",
      "Enter the size of the images after resizing.",
      128)
    if ok: 
      self.IMAGE_SIZE=num
      self.leIS.setText(str(num))

  def setNoiseSize(self):
    num,ok = QInputDialog.getInt(self,"Noise Size",
      "Enter the amount of noise added in data.",
      100)
    if ok: 
      self.NOISE_SIZE=num
      self.leNS.setText(str(num))

  def setDiscLearn(self):
    num,ok = QInputDialog.getDouble(self,"Discriminator Learning Rate",
      "Enter the learning rate of the discriminator.", 0.00004, decimals=8)
    if ok: 
      self.LR_D=num
      self.leDL.setText(str(num))

  def setGenLearn(self):
    num,ok = QInputDialog.getDouble(self,"Generator Learning Rate",
      "Enter the learning rate of the generator.", 0.0004, decimals=7)
    if ok:
      self.LR_G=num
      self.leGL.setText(str(num))

  def setBatchSize(self):
    num,ok = QInputDialog.getInt(self,"Batch Size",
      "Enter the number of color channels for the network", 64)
    if ok: 
      self.BATCH_SIZE=num
      self.leBS.setText(str(num))

  def setEpochs(self):
    num,ok = QInputDialog.getInt(self,"Epoch",
      "Set the number of Epochs during DCGAN training.", 50)
    if ok: 
      self.EPOCHS=num
      self.leEP.setText(str(num))

  def setBETA1(self):
    num,ok = QInputDialog.getDouble(self,"BETA1",
      "Set the BETA1 factor.", 0.5, decimals=2)
    if ok: 
      self.BETA1=num
      self.leBT.setText(str(num))

  def setEpsilon(self):
    num,ok = QInputDialog.getDouble(self,"Epsilon",
      "Set the epsilon factor.", 0.00005, decimals=7)
    if ok:
      self.EPSILON=num
      self.leES.setText(str(num))

  def setInitSTD(self):
    num,ok = QInputDialog.getDouble(self,"Initialize Standard Devation for Weights",
      "Enter the initial standard deviation for weights.", 0.02, decimals=4)
    if ok: 
      self.WEIGHT_INIT_STDDEV=num
      self.leIW.setText(str(num))

  def setShowSamples(self):
    num,ok = QInputDialog.getInt(self,"How many samples to make",
      "Enter how many samples to make at end of each epoch.", 5)
    if ok: 
      self.SAMPLES_TO_SHOW=num
      self.leSS.setText(str(num))

class MusicGeneratorParameterDialog(QWidget): #gui hyperparameters for wgan image gen
  def __init__(self, parent = None):
    super(MusicGeneratorParameterDialog, self).__init__(parent)
    self.mel_midi_file='default'
    self.mel_num_steps=128
    self.mel_temperature=1.0
    self.vae_checkpoint='musicvae/cat-drums_2bar_small.lokl.ckpt'
    self.vae_config_map='cat-drums_2bar_small'
    self.vae_batch_size=4
    self.vae_n=2
    self.vae_length=80
    self.vae_temperature=1.0
    self.mvae_batch_size=4
    self.mvae_z_size=512
    self.mvae_total_steps=512
    self.mvae_bar_seconds=2.0
    self.mvae_chord_depth=49
    self.mvae_sample_rate=44100
    self.perf_temperature=1.0
    layout = QFormLayout()
    self.btnMF = QPushButton("MelodyRNN: Midi File")
    self.btnNS = QPushButton("MelodyRNN: Number of Steps")
    self.btnMT = QPushButton("MelodyRNN: Temperature")
    self.btnCK = QPushButton("MusicVAE: Checkpoint")
    self.btnCM = QPushButton("MusicVAE: Configuration Map")
    self.btnVB = QPushButton("MusicVAE: Batch Size")
    self.btnVN = QPushButton("MusicVAE: N")
    self.btnVL = QPushButton("MusicVAE: Length")
    self.btnVT = QPushButton("MusicVAE: Temperature")
    self.btnMB = QPushButton("Multitrack MusicVAE: Batch Size")
    self.btnMZ = QPushButton("Multitrack MusicVAE: Z Size")
    self.btnMVST = QPushButton("Multitrack MusicVAE: Total Steps")
    self.btnMBS = QPushButton("Multitrack MusicVAE: Bar Seconds")
    self.btnCD = QPushButton("Multitrack MusicVAE: Chord Depth")
    self.btnSR = QPushButton("Multitrack MusicVAE: Sample Rate")
    self.btnPT = QPushButton("Performance RNN: Temperature")
    self.btnMF.clicked.connect(self.setMelMidiFile)
    self.btnNS.clicked.connect(self.setMelNumSteps)
    self.btnMT.clicked.connect(self.setMelTemperature)
    self.btnCK.clicked.connect(self.setVAECheckpoint)
    self.btnCM.clicked.connect(self.setVAEConfigMap)
    self.btnVB.clicked.connect(self.setVAEBatchSize)
    self.btnVN.clicked.connect(self.setVAEN)
    self.btnVL.clicked.connect(self.setVAELength)
    self.btnVT.clicked.connect(self.setVAETemperature)
    self.btnMB.clicked.connect(self.setMVAEBatchSize)
    self.btnMZ.clicked.connect(self.setMVAEZSize)
    self.btnMVST.clicked.connect(self.setMVAETotalSteps)
    self.btnMBS.clicked.connect(self.setMVAEBarSeconds)
    self.btnCD.clicked.connect(self.setMVAEChordDepth)
    self.btnSR.clicked.connect(self.setMVAESampleRate)
    self.btnPT.clicked.connect(self.setPerfTemperature)
    self.leMF = QLineEdit()
    self.leMF.setText(str(self.mel_midi_file))
    self.leMF.setReadOnly(True)
    layout.addRow(self.btnMF,self.leMF)
    self.leNS = QLineEdit()
    self.leNS.setText(str(self.mel_num_steps))
    self.leNS.setReadOnly(True)
    layout.addRow(self.btnNS,self.leNS)
    self.leMT = QLineEdit()
    self.leMT.setText(str(self.mel_temperature))
    self.leMT.setReadOnly(True)
    layout.addRow(self.btnMT,self.leMT)
    self.leCK = QLineEdit()
    self.leCK.setText(str(self.vae_checkpoint))
    self.leCK.setReadOnly(True)
    layout.addRow(self.btnCK,self.leCK)
    self.leCM = QLineEdit()
    self.leCM.setText(str(self.vae_config_map))
    self.leCM.setReadOnly(True)
    layout.addRow(self.btnCM,self.leCM)
    self.leVB = QLineEdit()
    self.leVB.setText(str(self.vae_batch_size))
    self.leVB.setReadOnly(True)
    layout.addRow(self.btnVB,self.leVB)
    self.leVN = QLineEdit()
    self.leVN.setText(str(self.vae_n))
    self.leVN.setReadOnly(True)
    layout.addRow(self.btnVN,self.leVN)
    self.leVL = QLineEdit()
    self.leVL.setText(str(self.vae_length))
    self.leVL.setReadOnly(True)
    layout.addRow(self.btnVL,self.leVL)
    self.leVT = QLineEdit()
    self.leVT.setText(str(self.vae_temperature))
    self.leVT.setReadOnly(True)
    layout.addRow(self.btnVT,self.leVT)
    self.leMB = QLineEdit()
    self.leMB.setText(str(self.mvae_batch_size))
    self.leMB.setReadOnly(True)
    layout.addRow(self.btnMB,self.leMB)
    self.leMZ = QLineEdit()
    self.leMZ.setText(str(self.mvae_z_size))
    self.leMZ.setReadOnly(True)
    layout.addRow(self.btnMZ,self.leMZ)
    self.leMVST = QLineEdit()
    self.leMVST.setText(str(self.mvae_total_steps))
    self.leMVST.setReadOnly(True)
    layout.addRow(self.btnMVST,self.leMVST)
    self.leMBS = QLineEdit()
    self.leMBS.setText(str(self.mvae_bar_seconds))
    self.leMBS.setReadOnly(True)
    layout.addRow(self.btnMBS,self.leMBS)
    self.leCD = QLineEdit()
    self.leCD.setText(str(self.mvae_chord_depth))
    self.leCD.setReadOnly(True)
    layout.addRow(self.btnCD,self.leCD)
    self.leSR = QLineEdit()
    self.leSR.setText(str(self.mvae_sample_rate))
    self.leSR.setReadOnly(True)
    layout.addRow(self.btnSR,self.leSR)
    self.lePT = QLineEdit()
    self.lePT.setText(str(self.perf_temperature))
    self.lePT.setReadOnly(True)
    layout.addRow(self.btnPT,self.lePT)
    self.setLayout(layout)

  def setMelMidiFile(self):
    file,ok = QFileDialog.getOpenFileName(self,'MelodyRNN: Midi File', os.getenv('HOME'), "(Midi File (*.midi, *.mid)", options=options)
    if ok:
      self.weights=file
      self.leWT.setText(str(file))

  def setMelNumSteps(self):
    num,ok = QInputDialog.getInt(self,"MelodyRNN: Number of Steps",
      "Enter the number of steps you would like to train for.")
    if ok:
      self.mel_num_steps=num
      self.leNS.setText(str(num))

  def setMelTemperature(self):
    num,ok = QInputDialog.getDouble(self, "MelodyRNN: Temperature",
      "Enter the temperature of the melody rnn's continuations.", 1.0, decimals=2)
    if ok:
      self.mel_temperature = num
      self.leMT.setText(str(num))

  def setVAECheckpoint(self):
    ckpts = ('deep_surfer/musicvae/cat-drums_2bar_small.lokl.ckpt' )
    item,ok = QInputDialog.getItem(self, "MusicVAE: Checkpoint File",
      "Emter the checkpoint file you'd like to use with the VAE", ckpts, 0, False)
    if ok and item:
      self.vae_checkpoint = item
      self.leCK.setText(item)

  def setVAEConfigMap(self):
    configs = ( 'cat-drums_2bar_small' )
    item,ok = QInputDialog.getItem(self, "MusicVAE: Configuration Map",
      "Enter the configuration map you'd like to use with the VAE", configs, 0, False)
    if ok and item:
      self.vae_config_map = item
      self.leCM.setText(item)

  def setVAEBatchSize(self):
    num,ok = QInputDialog.getInt(self, "MusicVAE: Batch Size",
      "Enter the batch size you'd like to use with the VAE")
    if ok:
      self.vae_batch_size = num
      self.leVB.setText(str(num))

  def setVAEN(self):
    num,ok = QInputDialog.getInt(self, "MusicVAE: N",
      "Enter the N you'd like to use with the VAE")
    if ok:
      self.vae_n = num
      self.leVN.setText(str(num))

  def setVAELength(self):
    num,ok = QInputDialog.getInt(self, "MusicVAE: Length",
      "Enter the length you'd like to use with the VAE")
    if ok:
      self.vae_length = num
      self.leVN.setText(str(num))

  def setVAETemperature(self):
    num,ok = QInputDialog.getDouble(self, "MusicVAE: Temperature",
      "Enter the temperature you'd like to use with the VAE", 1.0, decimals=2)
    if ok:
      self.vae_temperature = num
      self.leVN.setText(str(num))

  def setMVAEBatchSize(self):
    num,ok = QInputDialog.getInt(self, "MultitrackVAE: Batch Size",
      "Enter the batch size you'd like to use with the VAE")
    if ok:
      self.vae_length = num
      self.leVN.setText(str(num))

  def setMVAEZSize(self):
    num,ok = QInputDialog.getInt(self, "MultitrackVAE: Z Size",
      "Enter the Z size you'd like to use with the MVAE")
    if ok:
      self.mvae_z_size = num
      self.leMZ.setText(str(num))

  def setMVAETotalSteps(self):
    num,ok = QInputDialog.getInt(self, "MultitrackVAE: Total Steps",
      "Enter the total steps you'd like to take with the MVAE")
    if ok:
      self.mvae_total_steps = num
      self.leMVST.setText(str(num))

  def setMVAEBarSeconds(self):
    num,ok = QInputDialog.getDouble(self, "MultitrackVAE: Bar Seconds",
      "Enter the amount of seconds per bar you'd like to use with the VAE", 2.0, 
      decimals=2)
    if ok:
      self.vae_temperature = num
      self.leBS.setText(str(num))

  def setMVAEChordDepth(self):
    num,ok = QInputDialog.getInt(self, "MultitrackVAE: Total Steps",
      "Enter the depth of chords you'd like to set on the MVAE")
    if ok:
      self.mvae_chord_depth = num
      self.leCD.setText(str(num))

  def setMVAESampleRate(self):
    num,ok = QInputDialog.getInt(self, "MultitrackVAE: Total Steps",
      "Enter the Sample Rate you'd like to use with the MVAE")
    if ok:
      self.mvae_sample_rate = num
      self.leSR.setText(str(num))

  def setPerfTemperature(self):
    num,ok = QInputDialog.getDouble(self, "PerformanceRNN: Temperature",
      "Enter the temperature you'd like to use with the RNN", 1.0, decimals=2)
    if ok:
      self.vae_temperature = num
      self.lePT.setText(str(num))

class VideoGamerParameterDialog(QWidget): #gui hyperparameters for wgan image gen
  def __init__(self, parent = None):
    super(VideoGamerParameterDialog, self).__init__(parent)
    self.mode='test'
    self.env_name='SuperMarioBros-v0'
    self.weights='gameweights/dqn_SuperMarioBros-v0_weights.h5f'
    self.nb_episodes=10
    self.nb_steps=1750000
    self.save_interval=250000
    self.log_interval=10000
    self.enable_dueling_network=True
    self.enable_double_dqn=True
    self.policy='EpsGreedy'
    self.learning_rate=0.00025
    self.gamma=0.99
    self.delta_clip=1.
    self.target_model_update=10000
    self.nb_steps_warmup=50000
    self.seq_mem_limit=1000000
    self.random_seed=99
    self.input_shape_X=84
    self.input_shape_Y=84
    self.window_length=4
    layout = QFormLayout()
    self.btnMD = QPushButton("Mode")
    self.btnEN = QPushButton("Game Environment")
    self.btnWT = QPushButton("Weights")
    self.btnNE = QPushButton("Number of Test Episodes")
    self.btnNS = QPushButton("Number of Steps")
    self.btnSI = QPushButton("Save Interval")
    self.btnLI = QPushButton("Logging Interval")
    self.btnDN = QPushButton("Enable Dueling Network")
    self.btnDD = QPushButton("Enable Double Deep Q Network")
    self.btnPL = QPushButton("Network Policy")
    self.btnLR = QPushButton("Learning Rate")
    self.btnGM = QPushButton("Discount Factor")
    self.btnDC = QPushButton("Delta Clip")
    self.btnTM = QPushButton("Target Model Update Interval")
    self.btnNW = QPushButton("Number of Warmup Steps (Non-DQN)")
    self.btnSM = QPushButton("Sequential Memory Limit")
    self.btnRS = QPushButton("Random Seed")
    self.btnIX = QPushButton("Input Window Shape X axis")
    self.btnIY = QPushButton("Input Window Shape Y axis")
    self.btnWL = QPushButton("Window Length")
    self.btnMD.clicked.connect(self.setMode)
    self.btnEN.clicked.connect(self.setGameEnv)
    self.btnWT.clicked.connect(self.setWeights)
    self.btnNE.clicked.connect(self.setNumEpisodes)
    self.btnNS.clicked.connect(self.setNumSteps)
    self.btnSI.clicked.connect(self.setSaveInt)
    self.btnLI.clicked.connect(self.setLogInt)
    self.btnDN.clicked.connect(self.setDuelNet)
    self.btnDD.clicked.connect(self.setDoubleNet)
    self.btnPL.clicked.connect(self.setPolicy)
    self.btnLR.clicked.connect(self.setLearnRate)
    self.btnGM.clicked.connect(self.setGamma)
    self.btnDC.clicked.connect(self.setDeltaClip)
    self.btnTM.clicked.connect(self.setTargetUpdate)
    self.btnNW.clicked.connect(self.setWarmupSteps)
    self.btnSM.clicked.connect(self.setSeqMemory)
    self.btnRS.clicked.connect(self.setRandomSeed)
    self.btnIX.clicked.connect(self.setInputX)
    self.btnIY.clicked.connect(self.setInputY)
    self.btnWL.clicked.connect(self.setWindowLength)
    self.leMD = QLineEdit()
    self.leMD.setText(str(self.mode))
    self.leMD.setReadOnly(True)
    layout.addRow(self.btnMD,self.leMD)
    self.leEN = QLineEdit()
    self.leEN.setText(str(self.env_name))
    self.leEN.setReadOnly(True)
    layout.addRow(self.btnEN,self.leEN)
    self.leWT = QLineEdit()
    self.leWT.setText(str(self.weights))
    self.leWT.setReadOnly(True)
    layout.addRow(self.btnWT,self.leWT)
    self.leNE = QLineEdit()
    self.leNE.setText(str(self.nb_episodes))
    self.leNE.setReadOnly(True)
    layout.addRow(self.btnNE,self.leNE)
    self.leNS = QLineEdit()
    self.leNS.setText(str(self.nb_steps))
    self.leNS.setReadOnly(True)
    layout.addRow(self.btnNS,self.leNS)
    self.leSI = QLineEdit()
    self.leSI.setText(str(self.save_interval))
    self.leSI.setReadOnly(True)
    layout.addRow(self.btnSI,self.leSI)
    self.leLI = QLineEdit()
    self.leLI.setText(str(self.log_interval))
    self.leLI.setReadOnly(True)
    layout.addRow(self.btnLI,self.leLI)
    self.leDN = QLineEdit()
    self.leDN.setText(str(self.enable_dueling_network))
    self.leDN.setReadOnly(True)
    layout.addRow(self.btnDN,self.leDN)
    self.leDD = QLineEdit()
    self.leDD.setText(str(self.enable_double_dqn))
    self.leDD.setReadOnly(True)
    layout.addRow(self.btnDD,self.leDD)
    self.lePL = QLineEdit()
    self.lePL.setText(str(self.policy))
    self.lePL.setReadOnly(True)
    layout.addRow(self.btnPL,self.lePL)
    self.leLR = QLineEdit()
    self.leLR.setText(str(self.learning_rate))
    self.leLR.setReadOnly(True)
    layout.addRow(self.btnLR,self.leLR)
    self.leGM = QLineEdit()
    self.leGM.setText(str(self.gamma))
    self.leGM.setReadOnly(True)
    layout.addRow(self.btnGM,self.leGM)
    self.leDC = QLineEdit()
    self.leDC.setText(str(self.delta_clip))
    self.leDC.setReadOnly(True)
    layout.addRow(self.btnDC, self.leDC)
    self.leTM = QLineEdit()
    self.leTM.setText(str(self.target_model_update))
    self.leTM.setReadOnly(True)
    layout.addRow(self.btnTM,self.leTM)
    self.leNW = QLineEdit()
    self.leNW.setText(str(self.nb_steps_warmup))
    self.leNW.setReadOnly(True)
    layout.addRow(self.btnNW,self.leNW)
    self.leSM = QLineEdit()
    self.leSM.setText(str(self.seq_mem_limit))
    self.leSM.setReadOnly(True)
    layout.addRow(self.btnSM,self.leSM)
    self.leRS = QLineEdit()
    self.leRS.setText(str(self.random_seed))
    self.leRS.setReadOnly(True)
    layout.addRow(self.btnRS, self.leRS)
    self.leIX = QLineEdit()
    self.leIX.setText(str(self.input_shape_X))
    self.leIX.setReadOnly(True)
    layout.addRow(self.btnIX, self.leIX)
    self.leIY = QLineEdit()
    self.leIY.setText(str(self.input_shape_Y))
    self.leIY.setReadOnly(True)
    layout.addRow(self.btnIY, self.leIY)
    self.leWL = QLineEdit()
    self.leWL.setText(str(self.window_length))
    self.leWL.setReadOnly(True)
    layout.addRow(self.btnWL, self.leWL)
    self.setLayout(layout)

  def setMode(self):
    modes = ("test", "train")
    item,ok = QInputDialog.getItem(self,"Mode",
      "Enter the mode that you want to run the video game AI.", modes, 0, False)
    if ok and item:
        self.mode = item
        self.leMD.setText(item)

  def setGameEnv(self):
    games = ["BreakoutDeterministic"]
    for i in range(8):
      for j in range(4):
        games += ["SuperMarioBros-"+str(i+1)+"-"+str(j+1)]
    item,ok = QInputDialog.getItem(self,"Game Environment",
      "Enter the game that you want to run with the video game AI.", games, 0, False)
    if ok and item:
        self.env_name = item + "-v0"
        self.leEN.setText(item)

  def setWeights(self):
    file,ok = QFileDialog.getOpenFileName(self,'Weights', os.getenv('HOME'), "(Weights File ( *.h5f )", options=options)
    if ok:
      self.weights=file
      self.leWT.setText(str(file))

  def setNumEpisodes(self):
    num,ok = QInputDialog.getInt(self, "Number of Episodes",
      "Enter the number of episodes you want the AI to play the game.")
    if ok:
      self.nb_episodes = num
      self.leNE.setText(str(num))

  def setNumSteps(self):
    num,ok = QInputDialog.getInt(self, "Number of Step",
      "Enter the number of steps you want the AI to take during training on the game.")
    if ok:
      self.nb_steps = num
      self.leNS.setText(str(num))

  def setSaveInt(self):
    num,ok = QInputDialog.getInt(self, "Save Interval",
      "Enter the amount of steps the AI will take before creating a new save")
    if ok:
      self.save_interval = num
      self.leSI.setText(str(num))

  def setLogInt(self):
    num,ok = QInputDialog.getInt(self, "Log Interval",
      "Enter the amount of steps the AI will take before logging output to the terminal window")
    if ok:
      self.vae_batch_size = num
      self.leLI.setText(str(num))

  def setDuelNet(self):
    modes = ("On", "Off")
    item,ok = QInputDialog.getItem(self, "Dueling Network",
      "Turn on and off dueling networks", modes, 0, False)
    if ok and item:
        self.enable_dueling_network = item
        self.leDN.setText(item)

  def setDoubleNet(self):
    modes = ("On", "Off")
    item,ok = QInputDialog.getItem(self, "Double Network",
      "Turn on and off separated target network", modes, 0, False)
    if ok and item:
        self.enable_double_dqn = item
        self.leDD.setText(item)

  def setPolicy(self):
    policies = ('EpsGreedy', 'Boltzmann')
    item,ok = QInputDialog.getItem(self, "Policy",
      "Set reinforcement learning policy of network", modes, 0, False)
    if ok and item:
        self.enable_dueling_network = item
        self.lePL.setText(item)

  def setLearnRate(self):
    num,ok = QInputDialog.getDouble(self, "Learning Rate",
      "Enter the learning rate for the network", 0.00025, decimals=8)
    if ok:
      self.learning_rate = num
      self.leLR.setText(str(num))

  def setGamma(self):
    num,ok = QInputDialog.getDouble(self, "Discount Factor (Gamma)",
      "Enter the discount factor for future rewards during training",
      0.99, decimals=8)
    if ok:
      self.gamma = num
      self.leGM.setText(str(num))

  def setDeltaClip(self):
    num,ok = QInputDialog.getDouble(self, "Delta Clip",
      "Enter the delta clip for the DQN", 1.0, decimals=2)
    if ok:
      self.delta_clip = num
      self.leDC.setText(str(num))

  def setTargetUpdate(self):
    num,ok = QInputDialog.getInt(self, "Target Model Update",
      "Enter how many steps until the target network updates (double network must be on)")
    if ok:
      self.target_model_update = num
      self.leTM.setText(str(num))

  def setWarmupSteps(self):
    num,ok = QInputDialog.getInt(self, "Number of Warmup Steps",
      "Enter how many random steps the AI will take before deep reinforcement learning begins")
    if ok:
      self.nb_steps_warmup = num
      self.leNW.setText(str(num))

  def setSeqMemory(self):
    num,ok = QInputDialog.getInt(self, "Sequential Memory Limit",
      "Set the limit of sequential memory")
    if ok:
      self.seq_mem_limit = num
      self.leSM.setText(str(num))

  def setRandomSeed(self):
    num,ok = QInputDialog.getInt(self, "Random Seed",
      "Set the seed for the random initialization of the network")
    if ok:
      self.random_seed = num
      self.leRS.setText(str(num))

  def setInputX(self):
    num,ok = QInputDialog.getInt(self, "Input Shape X axis",
      "Set the size of the x-axis in the input layer of the dqn")
    if ok:
      self.input_shape_X = num
      self.leIX.setText(str(num))

  def setInputY(self):
    num,ok = QInputDialog.getInt(self, "Random Seed",
      "Set the size of the y-axis in the input layer of the dqn")
    if ok:
      self.input_shape_Y = num
      self.leIY.setText(str(num))

  def setWindowLength(self):
    num,ok = QInputDialog.getInt(self, "Window Length",
      "Set the amount of frames the network will look at each time (helps with moving objects in game)")
    if ok:
      self.window_length = num
      self.leWL.setText(str(num))