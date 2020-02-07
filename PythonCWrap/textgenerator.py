import os
import sys
import random
import numpy as np
import tensorflow as tf
from tensorflow.python.data.ops.dataset_ops import BatchDataset
from tensorflow.keras.layers import Dense, LSTM
from tensorflow.keras import Sequential
from tensorflow.keras.callbacks import LambdaCallback, ModelCheckpoint
from tensorflow.keras.optimizers import RMSprop
from PyQt5.QtWidgets import QFileDialog

class TextGenerator:
  @staticmethod #saves the resulting model with lowest loss
  def train_text_generator(train_epochs=15, num_generate=400, temperature=1.0, trim_text=1, 
    embedding_dim=128, step_size=3, seq_length=40, BATCH_SIZE=128, file_path="text/bom.txt"):
    text = open(file_path, encoding="utf8", errors="ignore").read().lower()
    print ('File Path: ' + file_path + '\nLength of text: {} characters'.format(len(text)))
    text = text[trim_text:-trim_text]
    chars = sorted(list(set(text)))
    char_indices = dict((c, i) for i, c in enumerate(chars))
    indices_char = dict((i, c) for i, c in enumerate(chars))
    sentences = []
    next_chars = []
    for i in range(0, len(text) - seq_length, step_size):
      sentences.append(text[i: i + seq_length])
      next_chars.append(text[i + seq_length])
    print('Total sentences:', len(sentences))

    print('Vectorization...')
    x = np.zeros((len(sentences), seq_length, len(chars)), dtype=np.bool)
    y = np.zeros((len(sentences), len(chars)), dtype=np.bool)
    for i, sentence in enumerate(sentences):
      for t, char in enumerate(sentence):
        x[i, t, char_indices[char]] = 1
        y[i, char_indices[next_chars[i]]] = 1

    print('Build model...') # build the model: a single LSTM
    model = Sequential()
    model.add(LSTM(embedding_dim, input_shape=(seq_length, len(chars))))
    model.add(Dense(len(chars), activation='softmax'))
    optimizer = RMSprop(lr=0.01)
    model.compile(loss='categorical_crossentropy', optimizer=optimizer)

    def sample(preds, temperature=1.0):
      # helper function to sample an index from a probability array
      preds = np.asarray(preds).astype('float64')
      preds = np.log(preds) / temperature
      exp_preds = np.exp(preds)
      preds = exp_preds / np.sum(exp_preds)
      probas = np.random.multinomial(1, preds, 1)
      return np.argmax(probas)

    def on_epoch_end(epoch, _):
      # Function invoked at end of each epoch. Prints generated text.
      print('\n----- Generating text after Epoch: %d' % epoch)
      start_index = random.randint(0, len(text) - seq_length - 1)
      for diversity in [temperature/2., temperature]:
        print('\n----- diversity: %.1f \n' % diversity)
        generated = ''
        sentence = text[start_index: start_index + seq_length]
        generated += sentence
        print('\n----- Generating with seed: "' + sentence + '"\n')
        sys.stdout.write(generated)
        for i in range(num_generate):
          x_pred = np.zeros((1, seq_length, len(chars)))
          for t, char in enumerate(sentence):
            x_pred[0, t, char_indices[char]] = 1
          preds = model.predict(x_pred, verbose=0)[0]
          next_index = sample(preds, diversity)
          next_char = indices_char[next_index]
          generated += next_char
          sentence = sentence[1:] + next_char
          sys.stdout.write(next_char)
          sys.stdout.flush()

    ckpt_path = "graphs/textgen-autosave.pb"
    ckpt = ModelCheckpoint(ckpt_path, monitor='loss', verbose=1, save_best_only=True, mode='min')
    print_callback = LambdaCallback(on_epoch_end=on_epoch_end)
    callbacks_list = [print_callback, ckpt]
    model.fit(x, y,
              batch_size=BATCH_SIZE, epochs=train_epochs, callbacks=callbacks_list)
    #tfjs.converters.save_keras_model(model, ckpt_path[:-2] + "h5")
    print("text generator is done. (check autosave) navigate back to the main window!")  
    sys.stdout.flush()

  @staticmethod #runs an lstm model, requires the source text
  def run_text_generator(num_generate=400, temperature=1.0, trim_text=1, embedding_dim=128, seq_length=40,
    step_size=3, file_path="text/bom.txt", ckpt_path = "graphs/bom.pb"):
    text = open(file_path, encoding="utf8", errors="ignore").read().lower()
    print ('Length of text: {} characters'.format(len(text)))
    text = text[trim_text:-trim_text]
    text_collector = ""
    chars = sorted(list(set(text)))
    char_indices = dict((c, i) for i, c in enumerate(chars))
    indices_char = dict((i, c) for i, c in enumerate(chars))
    sentences = []
    next_chars = []
    for i in range(0, len(text) - seq_length, step_size):
      sentences.append(text[i: i + seq_length])
      next_chars.append(text[i + seq_length])
    print('Total sentences:', len(sentences))

    print('Vectorization...')
    x = np.zeros((len(sentences), seq_length, len(chars)), dtype=np.bool)
    y = np.zeros((len(sentences), len(chars)), dtype=np.bool)
    for i, sentence in enumerate(sentences):
      for t, char in enumerate(sentence):
        x[i, t, char_indices[char]] = 1
        y[i, char_indices[next_chars[i]]] = 1
    print('Build model...') # build the model: a single LSTM
    model = Sequential()
    model.add(LSTM(embedding_dim, input_shape=(seq_length, len(chars))))
    model.add(Dense(len(chars), activation='softmax'))
    optimizer = RMSprop(lr=0.01)
    model.compile(loss='categorical_crossentropy', optimizer=optimizer)
    model.load_weights(ckpt_path)
    
    def sample(preds, temperature=1.0):
      # helper function to sample an index from a probability array
      preds = np.asarray(preds).astype('float64')
      preds = np.log(preds) / temperature
      exp_preds = np.exp(preds)
      preds = exp_preds / np.sum(exp_preds)
      probas = np.random.multinomial(1, preds, 1)
      return np.argmax(probas)

    # Function invoked at end of each epoch. Prints generated text.
    start_index = random.randint(0, len(text) - seq_length - 1)
    for diversity in [temperature/2., temperature]:
      print('\n----- diversity: %.1f \n' % diversity)
      generated = ''
      sentence = text[start_index: start_index + seq_length]
      generated += sentence
      print('\n----- Generating with seed: "' + sentence + '"\n')
      sys.stdout.write(generated)
      for i in range(num_generate):
        x_pred = np.zeros((1, seq_length, len(chars)))
        for t, char in enumerate(sentence):
          x_pred[0, t, char_indices[char]] = 1
        preds = model.predict(x_pred, verbose=0)[0]
        next_index = sample(preds, diversity)
        next_char = indices_char[next_index]
        generated += next_char
        sentence = sentence[1:] + next_char
        sys.stdout.write(next_char)
        sys.stdout.flush()
      text_collector += generated
    print("text generator is done. please navigate back to the main window!")
    sys.stdout.flush()
    print(text_collector)

if __name__ == '__main__':
  TextGenerator.run_text_generator()