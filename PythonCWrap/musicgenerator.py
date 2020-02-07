import os
import platform
import tensorflow as tf
from PyQt5.QtWidgets import QFileDialog
from PyQt5.QtGui import QPixmap
from scipy.io import wavfile
from scipy import signal
import soundfile #convert 24 bit wav to 16 bit
from pydub import AudioSegment #
from pydub.playback import play as dubPlay #play wav files
import pygame #play midi files
import numpy as np #cool math stuff
import matplotlib
import matplotlib.pyplot as plt #plot spectrograms and midi files
if platform.release() == "Darwin":
  matplotlib.use('PS') #flag ~bypasses issues for MacOS
import magenta #magical music library headed by google
import magenta.music as mm
from magenta.music.sequences_lib import concatenate_sequences
from magenta.models.melody_rnn import melody_rnn_sequence_generator
from magenta.models.performance_rnn import performance_sequence_generator
from magenta.protobuf import generator_pb2
from magenta.protobuf import music_pb2
from magenta.models.music_vae import configs
from magenta.models.music_vae.trained_model import TrainedModel

#THIS IS OUR MIXER RIGHT HERE BABY YEAH AUDIO
freq = 44100    # audio CD quality
bitsize = -16   # unsigned 16 bit
channels = 2    # 1 is mono, 2 is stereo
buffer = 1024    # number of samples
pygame.mixer.init(freq, bitsize, channels, buffer)

import mido
import matplotlib as mpl
from matplotlib.colors import colorConverter

# inherit the origin mido class
class MidiFile(mido.MidiFile):

  def __init__(self, filename):

    mido.MidiFile.__init__(self, filename)
    self.sr = 10
    self.meta = {}
    self.events = self.get_events()

  def get_events(self):
    mid = self
    print(mid)

    # There is > 16 channel in midi.tracks. However there is only 16 channel related to "music" events.
    # We store music events of 16 channel in the list "events" with form [[ch1],[ch2]....[ch16]]
    # Lyrics and meta data used a extra channel which is not include in "events"

    events = [[] for x in range(16)]

    # Iterate all event in the midi and extract to 16 channel form
    for track in mid.tracks:
      for msg in track:
        try:
          channel = msg.channel
          events[channel].append(msg)
        except AttributeError:
          try:
            if type(msg) != type(mido.UnknownMetaMessage):
              self.meta[msg.type] = msg.dict()
            else:
              pass
          except:
            print("error",type(msg))

    return events

  def getRoll(self):
    events = self.get_events()
    # Identify events, then translate to piano roll
    # choose a sample ratio(sr) to down-sample through time axis
    sr = self.sr

    # compute total length in tick unit
    length = self.get_total_ticks()

    # allocate memory to numpy array
    roll = np.zeros((16, 128, length // sr), dtype="int8")

    # use a register array to save the state(no/off) for each key
    note_register = [int(-1) for x in range(128)]

    # use a register array to save the state(program_change) for each channel
    timbre_register = [1 for x in range(16)]


    for idx, channel in enumerate(events):

      time_counter = 0
      volume = 100
      # Volume would change by control change event (cc) cc7 & cc11
      # Volume 0-100 is mapped to 0-127

      print("channel", idx, "start")
      for msg in channel:
        if msg.type == "control_change":
          if msg.control == 7:
            volume = msg.value
            # directly assign volume
          if msg.control == 11:
            volume = volume * msg.value // 127
            # change volume by percentage
          # print("cc", msg.control, msg.value, "duration", msg.time)

        if msg.type == "program_change":
          timbre_register[idx] = msg.program
          print("channel", idx, "pc", msg.program, "time", time_counter, "duration", msg.time)



        if msg.type == "note_on":
          print("on ", msg.note, "time", time_counter, "duration", msg.time, "velocity", msg.velocity)
          note_on_start_time = time_counter // sr
          note_on_end_time = (time_counter + msg.time) // sr
          intensity = volume * msg.velocity // 127



          # When a note_on event *ends* the note start to be play 
          # Record end time of note_on event if there is no value in register
          # When note_off event happens, we fill in the color
          if note_register[msg.note] == -1:
            note_register[msg.note] = (note_on_end_time,intensity)
          else:
          # When note_on event happens again, we also fill in the color
            old_end_time = note_register[msg.note][0]
            old_intensity = note_register[msg.note][1]
            roll[idx, msg.note, old_end_time: note_on_end_time] = old_intensity
            note_register[msg.note] = (note_on_end_time,intensity)


        if msg.type == "note_off":
          print("off", msg.note, "time", time_counter, "duration", msg.time, "velocity", msg.velocity)
          note_off_start_time = time_counter // sr
          note_off_end_time = (time_counter + msg.time) // sr
          note_on_end_time = note_register[msg.note][0]
          intensity = note_register[msg.note][1]
          # fill in color
          roll[idx, msg.note, note_on_end_time:note_off_end_time] = intensity

          note_register[msg.note] = -1  # reinitialize register

        time_counter += msg.time

        # TODO : velocity -> done, but not verified
        # TODO: Pitch wheel
        # TODO: Channel - > Program Changed / Timbre catagory
        # TODO: real time scale of roll

      # if there is a note not closed at the end of a channel, close it
      for key, data in enumerate(note_register):
        if data != -1:
          note_on_end_time = data[0]
          intensity = data[1]
          # print(key, note_on_end_time)
          note_off_start_time = time_counter // sr
          roll[idx, key, note_on_end_time:] = intensity
        note_register[idx] = -1

    return roll

  def getRoll_image(self):
    roll = self.getRoll()
    plt.ioff()

    K = 16

    transparent = colorConverter.to_rgba('black')
    colors = [mpl.colors.to_rgba(mpl.colors.hsv_to_rgb((i / K, 1, 1)), alpha=1) for i in range(K)]
    cmaps = [mpl.colors.LinearSegmentedColormap.from_list('my_cmap', [transparent, colors[i]], 128) for i in
         range(K)]

    for i in range(K):
      cmaps[i]._init()  # create the _lut array, with rgba values
      # create your alpha array and fill the colormap with them.
      # here it is progressive, but you can create whathever you want
      alphas = np.linspace(0, 1, cmaps[i].N + 3)
      cmaps[i]._lut[:, -1] = alphas

    fig = plt.figure(figsize=(4, 3))
    a1 = fig.add_subplot(111)
    a1.axis("equal")
    a1.set_facecolor("black")

    array = []

    for i in range(K):
      try:
        img = a1.imshow(roll[i], interpolation='nearest', cmap=cmaps[i], aspect='auto')
        array.append(img.get_array())
      except IndexError:
        pass
    return array

  def drawRoll(self):


    roll = self.getRoll()
    print("Inside draw roll\n")
    # build and set fig obj
    plt.ioff()
    fig = plt.figure(figsize=(4, 3))
    a1 = fig.add_subplot(111)
    a1.axis("equal")
    a1.set_facecolor("black")

    # change unit of time axis from tick to second
    tick = self.get_total_ticks()
    second = mido.tick2second(tick, self.ticks_per_beat, self.get_tempo())
    print(second)
    if second > 10:
      x_label_period_sec = second // 10
    else:
      x_label_period_sec = second / 10  # ms
    print(x_label_period_sec)
    x_label_interval = mido.second2tick(x_label_period_sec, self.ticks_per_beat, self.get_tempo()) / self.sr
    print(x_label_interval)
    plt.xticks([int(x * x_label_interval) for x in range(20)], [round(x * x_label_period_sec, 2) for x in range(20)])

    # change scale and label of y axis
    plt.yticks([y*16 for y in range(8)], [y*16 for y in range(8)])

    # build colors
    channel_nb = 16
    transparent = colorConverter.to_rgba('black')
    colors = [mpl.colors.to_rgba(mpl.colors.hsv_to_rgb((i / channel_nb, 1, 1)), alpha=1) for i in range(channel_nb)]
    cmaps = [mpl.colors.LinearSegmentedColormap.from_list('my_cmap', [transparent, colors[i]], 128) for i in
         range(channel_nb)]

    # build color maps
    for i in range(channel_nb):
      cmaps[i]._init()
      # create your alpha array and fill the colormap with them.
      alphas = np.linspace(0, 1, cmaps[i].N + 3)
      # create the _lut array, with rgba values
      cmaps[i]._lut[:, -1] = alphas


    # draw piano roll and stack image on a1
    for i in range(channel_nb):
      try:
        a1.imshow(roll[i], origin="lower", interpolation='nearest', cmap=cmaps[i], aspect='auto')
      except IndexError:
        pass

    # draw color bar
    '''
    colors = [mpl.colors.hsv_to_rgb((i / channel_nb, 1, 1)) for i in range(channel_nb)]
    cmap = mpl.colors.LinearSegmentedColormap.from_list('my_cmap', colors, 16)
    a2 = fig.add_axes([0.05, 0.80, 0.9, 0.15])
    cbar = mpl.colorbar.ColorbarBase(a2, cmap=cmap,
                    orientation='horizontal',
                    ticks=list(range(16)))'''

    # show piano roll
    plt.draw()
    plt.ion()
    plt.show(block=True)
    print("done with draw roll\n")

  def get_tempo(self):
    try:
      return self.meta["set_tempo"]["tempo"]
    except:
      return 500000

  def get_total_ticks(self):
    max_ticks = 0
    for channel in range(16):
      ticks = sum(msg.time for msg in self.events[channel])
      if ticks > max_ticks:
        max_ticks = ticks
    return max_ticks

class MusicGenerator:
  LAST_MUSIC_FILE='music/performance0.8.mid'
  
  @staticmethod
  def make_note_sequence():
    note_sequence = music_pb2.NoteSequence()
    note_sequence.notes.add(pitch=36, start_time=0, end_time=0.125, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=38, start_time=0, end_time=0.125, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=42, start_time=0, end_time=0.125, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=46, start_time=0, end_time=0.125, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=42, start_time=0.25, end_time=0.375, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=42, start_time=0.375, end_time=0.5, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=42, start_time=0.5, end_time=0.625, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=50, start_time=0.5, end_time=0.625, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=36, start_time=0.75, end_time=0.875, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=38, start_time=0.75, end_time=0.875, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=42, start_time=0.75, end_time=0.875, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=45, start_time=0.75, end_time=0.875, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=36, start_time=1, end_time=1.125, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=42, start_time=1, end_time=1.125, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=46, start_time=1, end_time=1.125, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=42, start_time=1.25, end_time=1.375, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=48, start_time=1.25, end_time=1.375, is_drum=True, instrument=10, velocity=80)
    note_sequence.notes.add(pitch=50, start_time=1.25, end_time=1.375, is_drum=True, instrument=10, velocity=80)
    note_sequence.total_time = 1.375
    note_sequence.tempos.add(qpm=60)
    mm.sequence_proto_to_midi_file(note_sequence, 'music/note_sequence.mid')
    return note_sequence

  @staticmethod
  def continue_melodyrnn(midi_file='default', num_steps=128, temperature=1.0):
    mm.notebook_utils.download_bundle('basic_rnn.mag', 'magentarnn')
    bundle = mm.sequence_generator_bundle.read_bundle_file('magentarnn/basic_rnn.mag')
    generator_map = melody_rnn_sequence_generator.get_generator_map()
    melody_rnn = generator_map['basic_rnn'](checkpoint=None, bundle=bundle)
    melody_rnn.initialize()
    print('melodyrnn is initialized\n')
    # Model options. Change these to get different generated sequences! 
    if midi_file is 'default':
      input_sequence = MusicGenerator.make_note_sequence() # change this to teapot if you want
    else: input_sequence = mm.midi_to_sequence_proto(midi_file)
    # Set the start time to begin on the next step after the last note ends.
    last_end_time = (max(n.end_time for n in input_sequence.notes)
                      if input_sequence.notes else 0)
    qpm = input_sequence.tempos[0].qpm 
    seconds_per_step = 60.0 / qpm / melody_rnn.steps_per_quarter
    total_seconds = num_steps * seconds_per_step

    generator_options = generator_pb2.GeneratorOptions()
    generator_options.args['temperature'].float_value = temperature
    generate_section = generator_options.generate_sections.add(
      start_time=last_end_time + seconds_per_step,
      end_time=total_seconds)
    # Ask the model to continue the sequence.
    continued_sequence = melody_rnn.generate(input_sequence, generator_options)
    mm.sequence_proto_to_midi_file(continued_sequence, 'music/continued_sequence.mid')
    MusicGenerator.LAST_MUSIC_FILE = 'music/continued_sequence.mid'
    print("Done with melodyrnn\n")

  @staticmethod
  def generate_musicvae(checkpoint='musicvae/cat-drums_2bar_small.lokl.ckpt',
    config_map='cat-drums_2bar_small', batch_size=4, n=2, length=80, temperature=1.0):
    print("Initializing Music VAE...")
    music_vae = TrainedModel( configs.CONFIG_MAP[config_map], 
          batch_size=batch_size, checkpoint_dir_or_path='musicvae/cat-drums_2bar_small.lokl.ckpt')
    generated_sequences = music_vae.sample(n=n, length=length, temperature=temperature)
    for idx, ns in enumerate(generated_sequences):
      mm.sequence_proto_to_midi_file(ns, 'music/generated_sequence' + str(idx) + '.mid')
      MusicGenerator.LAST_MUSIC_FILE = 'music/generated_sequence' + str(idx) + '.mid'
    print("Done with vae\n")

  @staticmethod
  def random_multitrackvae(BATCH_SIZE=4, Z_SIZE=512, TOTAL_STEPS=512, 
    BAR_SECONDS=2.0, CHORD_DEPTH=49, SAMPLE_RATE=44100):
    
    def slerp(p0, p1, t): # Spherical linear interpolation.
      omega = np.arccos(np.dot(np.squeeze(p0/np.linalg.norm(p0)), np.squeeze(p1/np.linalg.norm(p1))))
      so = np.sin(omega)
      return np.sin((1.0-t)*omega) / so * p0 + np.sin(t*omega)/so * p1
    
    def chord_encoding(chord): # Chord encoding tensor.
      index = mm.TriadChordOneHotEncoding().encode_event(chord)
      c = np.zeros([TOTAL_STEPS, CHORD_DEPTH])
      c[0,0] = 1.0
      c[1:,index] = 1.0
      return c

    def trim_sequences(seqs, num_seconds=BAR_SECONDS): # Trim sequences to exactly one bar.
      for i in range(len(seqs)):
        seqs[i] = mm.extract_subsequence(seqs[i], 0.0, num_seconds)
        seqs[i].total_time = num_seconds
    
    def fix_instruments_for_concatenation(note_sequences): # Consolidate instrument numbers by MIDI program.
      instruments = {}
      for i in range(len(note_sequences)):
        for note in note_sequences[i].notes:
          if not note.is_drum:
            if note.program not in instruments:
              if len(instruments) >= 8:
                instruments[note.program] = len(instruments) + 2
              else:
                instruments[note.program] = len(instruments) + 1
            note.instrument = instruments[note.program]
          else:
            note.instrument = 9
    config = configs.CONFIG_MAP['hierdec-trio_16bar']
    model = TrainedModel(
        config, batch_size=BATCH_SIZE,
        checkpoint_dir_or_path='./musicvae/hierdec-trio_16bar.ckpt')
    model._config.data_converter._max_tensors_per_input = None
    temperature = 0.2 #@param {type:"slider", min:0.01, max:1.5, step:0.01}
    seqs = model.sample(n=BATCH_SIZE, length=TOTAL_STEPS, temperature=temperature)
    trim_sequences(seqs)
    i = 0
    for seq in seqs:
      mm.sequence_proto_to_midi_file(seq, "./music/random_seq" + str(i) + ".mid")
      i += 1
    #@title Interpolation Between Random Samples
    num_bars = 32 #@param {type:"slider", min:4, max:64, step:1}
    temperature = 0.3 #@param {type:"slider", min:0.01, max:1.5, step:0.01}
    z1 = np.random.normal(size=[Z_SIZE])
    z2 = np.random.normal(size=[Z_SIZE])
    z = np.array([slerp(z1, z2, t)
                  for t in np.linspace(0, 1, num_bars)])
    seqs = model.decode(length=TOTAL_STEPS, z=z, temperature=temperature)
    trim_sequences(seqs)
    fix_instruments_for_concatenation(seqs)
    interp_ns = concatenate_sequences(seqs)
    mm.sequence_proto_to_midi_file(interp_ns, "./music/random_interpolation.mid")
    MusicGenerator.LAST_MUSIC_FILE = "./music/random_interpolation.mid"
    print("done with random multitrack interpolation vae\n")

  @staticmethod
  def performance_rnn(temperature=1.0):
    BUNDLE_DIR = './magentarnn/'
    MODEL_NAME = 'performance_with_dynamics'
    BUNDLE_NAME = MODEL_NAME + '.mag'
    mm.notebook_utils.download_bundle(BUNDLE_NAME, BUNDLE_DIR)
    bundle = mm.sequence_generator_bundle.read_bundle_file(os.path.join(BUNDLE_DIR, BUNDLE_NAME))
    generator_map = performance_sequence_generator.get_generator_map()
    generator = generator_map[MODEL_NAME](checkpoint=None, bundle=bundle)
    generator.initialize()
    generator_options = generator_pb2.GeneratorOptions()
    generator_options.args['temperature'].float_value = temperature  # Higher is more random; 1.0 is default. 
    generate_section = generator_options.generate_sections.add(start_time=0, end_time=30)
    sequence = generator.generate(music_pb2.NoteSequence(), generator_options)
    mm.sequence_proto_to_midi_file(sequence, "./music/performance.mid")
    MusicGenerator.LAST_MUSIC_FILE = "./music/performance.mid"
    print("Done with performance rnn\n")

  @staticmethod
  def wav_to_spectrogram(notepadwidget):
    wav_tuple = QFileDialog.getOpenFileName(notepadwidget, "Open wav file", 
      os.getenv('HOME'), "Audio (*.wav)")
    wav_file = wav_tuple[0]
    data, samplerate = soundfile.read(wav_file[:-4] + '.wav') #converts to 16 bit wav
    soundfile.write(wav_file[:-4] + '16bit.wav', data, samplerate, subtype='PCM_16' )
    sound = AudioSegment.from_wav(wav_file[:-4] + '16bit.wav')
    sound = sound.set_channels(1) # sets it to mono
    sound.export(wav_file[:-4] + '16bitmono.wav', format="wav")
    sample_rate, samples = wavfile.read(wav_file[:-4] + '16bitmono.wav')
    frequencies, times, spectrogram = signal.spectrogram(samples, sample_rate)
    plt.pcolormesh(times, frequencies, np.log(spectrogram))
    plt.show()

  @staticmethod
  def play_music(music_file):
    clock = pygame.time.Clock()
    try:
        pygame.mixer.music.load(music_file)
        print("Music file %s loaded!" % music_file)
    except pygame.error:
        print("File %s not found! (%s)" % (music_file, pygame.get_error()))
        return
    pygame.mixer.music.play()

  @staticmethod
  def play_wav(wav_file):
    print("in it\n")
    sound = AudioSegment.from_wav(wav_file)
    dubPlay(sound)
    print("did it?")

  @staticmethod
  def play_last_generated():
    MusicGenerator.play_music(MusicGenerator.LAST_MUSIC_FILE)

  @staticmethod
  def visual_last_generated():
    midiRoll = MidiFile(MusicGenerator.LAST_MUSIC_FILE)
    midiRoll.drawRoll()

if __name__ == '__main__':
  print('Magenta version: ' + magenta.__version__)
  print('Tensorflow version: ' + tf.__version__)
  print('Testing the functions of the generator here...')
  MusicGenerator.continue_melodyrnn()
  MusicGenerator.generate_musicvae()
  MusicGenerator.random_multitrackvae()
  MusicGenerator.performance_rnn()
  print('if you are reading this, everything worked correctly.\n')
