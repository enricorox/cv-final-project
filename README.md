# cv-final-project
Final project of Computer Vision course @ University of Padua
## How to compile
`mkdir build && cd build`  
`cmake ../src`  
`make`
## How to use
Use `./train` to train the cascade classifier.  
The train folder can be downloaded [here](https://drive.google.com/file/d/1vrBPPh942Z7U03tG9T_cIbfjxtfk4ysQ/view?usp=sharing)
and must be put in the `data` folder  
  
Use `./find-tree` to test images on `data/test` directory

N.B.: some parameter can be tuned on source file 