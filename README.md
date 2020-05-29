# deep_surfer_native
This is a showcase of neural networks for image classification, text generation, image generation, music generation, deep dream image manipulation, and teaching AI agents to act in video game environments using reinforcement techniques. This is a very large wrapper for lots of powerful cutting edge algorithms that I did not invent! Rather than having to go into the code to change each neural networks hyper parameters, users can interact with the user interface to change them! All of this is implemented using tensorflow and OpenAI Gym.


Here are some sample images from the image generator trained on celebA dataset:

128x128 Inputs:
![alt text](people-gan/inputs/inputs_0.png)

128x128 Outputs after 99 Epochs on 10000 images:
![alt text](people-gan/epochs/samples_91.png)
![alt text](people-gan/epochs/samples_92.png)
![alt text](people-gan/epochs/samples_93.png)
![alt text](people-gan/epochs/samples_94.png)
![alt text](people-gan/epochs/samples_95.png)
![alt text](people-gan/epochs/samples_96.png)
![alt text](people-gan/epochs/samples_97.png)
![alt text](people-gan/epochs/samples_98.png)
![alt text](people-gan/epochs/samples_99.png)
![alt text](people-gan/epochs/samples_100.png)



Here is an example deep dream image at 4 octaves:
![alt text](PythonCWrap/icons/surfingsky-mixed4b.png)


(https://salty-sands-81911.herokuapp.com/deep_surfer "Check out the demo version of this app here!")
Note: Demo only scratches the surface, it can only do low-res deep dream image manipulation, and generate text from pretrained models
This is because it is live on a free Heroku server, to make SOME of its functionalities tangible to anyone with internet access :)



# To Build This Project:

To build this you will need quite a few things ;)

I recommend using Windows 10 or Ubuntu Linux 18.04, as Tensorflow no longer carries GPU support for Mac :(

That said, if you have a Mac, you will need xcode.
this command will both check for xcode and also install if it is not present on your machine.
    `xcode-select --install`


an ANSI C-compiler
Python 3.6 interpreter (I'd recommend 3.6.9 or latest 3.6 version)

you can install most dependencies using pip.. that said, there are a lot of them. i wish you good luck because there can be cases
of version of these dependencies that clash, in that case I recommend 

    pip install magenta-gpu tensorflow-gpu keras numpy scipy pygame pydub pillow opencv-python gym gym_super_mario_bros nes_py soundfile matplotlib PyQt5

(it will run with CPU-version of magenta and tensorflow, but don't expect much speed from the AI gaming agent or the image generator...
 seriously. they will both take multiple days to run.)
