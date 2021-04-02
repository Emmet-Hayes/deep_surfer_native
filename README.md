# deep_surfer_native
This is a showcase of neural networks for image classification, text generation, image generation, music generation, deep dream image manipulation, and teaching AI agents to act in video game environments using reinforcement techniques. This is a very large wrapper for lots of powerful cutting edge algorithms that I did not invent! Rather than restricting usage of these powerful AI algorithms to developers by having to go into the code to change each neural networks hyper parameters, users can interact with a simple, yet populous user interface to change them! All of this is implemented using PyQt, tensorflow, keras, and OpenAI Gym, as well as several other python 3 libraries for text, image, and musical data processing.


Here are some sample images from the image generator trained on celebA dataset:

128x128 Inputs:
![alt text](people-gan/inputs/inputs_0.png)

128x128 Outputs after 99 Epochs on 10000 images:
![alt text](people-gan/epochs/samples_1.png)
![alt text](people-gan/epochs/samples_2.png)
![alt text](people-gan/epochs/samples_3.png)
![alt text](people-gan/epochs/samples_4.png)
![alt text](people-gan/epochs/samples_5.png)
![alt text](people-gan/epochs/samples_6.png)
![alt text](people-gan/epochs/samples_7.png)
![alt text](people-gan/epochs/samples_8.png)
![alt text](people-gan/epochs/samples_9.png)
![alt text](people-gan/epochs/samples_10.png)
![alt text](people-gan/epochs/samples_11.png)
![alt text](people-gan/epochs/samples_12.png)
![alt text](people-gan/epochs/samples_13.png)
![alt text](people-gan/epochs/samples_14.png)
![alt text](people-gan/epochs/samples_15.png)
![alt text](people-gan/epochs/samples_16.png)
![alt text](people-gan/epochs/samples_17.png)
![alt text](people-gan/epochs/samples_18.png)
![alt text](people-gan/epochs/samples_19.png)
![alt text](people-gan/epochs/samples_20.png)
![alt text](people-gan/epochs/samples_21.png)
![alt text](people-gan/epochs/samples_22.png)
![alt text](people-gan/epochs/samples_23.png)
![alt text](people-gan/epochs/samples_24.png)
![alt text](people-gan/epochs/samples_25.png)
![alt text](people-gan/epochs/samples_26.png)
![alt text](people-gan/epochs/samples_27.png)
![alt text](people-gan/epochs/samples_28.png)
![alt text](people-gan/epochs/samples_29.png)
![alt text](people-gan/epochs/samples_30.png)
![alt text](people-gan/epochs/samples_31.png)
![alt text](people-gan/epochs/samples_32.png)
![alt text](people-gan/epochs/samples_33.png)
![alt text](people-gan/epochs/samples_34.png)
![alt text](people-gan/epochs/samples_35.png)
![alt text](people-gan/epochs/samples_36.png)
![alt text](people-gan/epochs/samples_37.png)
![alt text](people-gan/epochs/samples_38.png)
![alt text](people-gan/epochs/samples_39.png)
![alt text](people-gan/epochs/samples_40.png)
![alt text](people-gan/epochs/samples_41.png)
![alt text](people-gan/epochs/samples_42.png)
![alt text](people-gan/epochs/samples_43.png)
![alt text](people-gan/epochs/samples_44.png)
![alt text](people-gan/epochs/samples_45.png)
![alt text](people-gan/epochs/samples_46.png)
![alt text](people-gan/epochs/samples_47.png)
![alt text](people-gan/epochs/samples_48.png)
![alt text](people-gan/epochs/samples_49.png)
![alt text](people-gan/epochs/samples_50.png)
![alt text](people-gan/epochs/samples_51.png)
![alt text](people-gan/epochs/samples_52.png)
![alt text](people-gan/epochs/samples_53.png)
![alt text](people-gan/epochs/samples_54.png)
![alt text](people-gan/epochs/samples_55.png)
![alt text](people-gan/epochs/samples_56.png)
![alt text](people-gan/epochs/samples_57.png)
![alt text](people-gan/epochs/samples_58.png)
![alt text](people-gan/epochs/samples_59.png)
![alt text](people-gan/epochs/samples_60.png)
![alt text](people-gan/epochs/samples_61.png)
![alt text](people-gan/epochs/samples_62.png)
![alt text](people-gan/epochs/samples_63.png)
![alt text](people-gan/epochs/samples_64.png)
![alt text](people-gan/epochs/samples_65.png)
![alt text](people-gan/epochs/samples_66.png)
![alt text](people-gan/epochs/samples_67.png)
![alt text](people-gan/epochs/samples_68.png)
![alt text](people-gan/epochs/samples_69.png)
![alt text](people-gan/epochs/samples_70.png)
![alt text](people-gan/epochs/samples_71.png)
![alt text](people-gan/epochs/samples_72.png)
![alt text](people-gan/epochs/samples_73.png)
![alt text](people-gan/epochs/samples_74.png)
![alt text](people-gan/epochs/samples_75.png)
![alt text](people-gan/epochs/samples_76.png)
![alt text](people-gan/epochs/samples_77.png)
![alt text](people-gan/epochs/samples_78.png)
![alt text](people-gan/epochs/samples_79.png)
![alt text](people-gan/epochs/samples_80.png)
![alt text](people-gan/epochs/samples_81.png)
![alt text](people-gan/epochs/samples_82.png)
![alt text](people-gan/epochs/samples_83.png)
![alt text](people-gan/epochs/samples_84.png)
![alt text](people-gan/epochs/samples_85.png)
![alt text](people-gan/epochs/samples_86.png)
![alt text](people-gan/epochs/samples_87.png)
![alt text](people-gan/epochs/samples_88.png)
![alt text](people-gan/epochs/samples_89.png)
![alt text](people-gan/epochs/samples_90.png)
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


you can install most dependencies using pip.. that said, there are a lot of them. I 
recommend installing all of the versions listed on the requirements.txt file in the PythonCWrap folder.

(it will run with CPU-version of magenta and tensorflow, but don't expect much speed from the AI gaming agent or the image generator...
 seriously. they will both take multiple days to run.)
