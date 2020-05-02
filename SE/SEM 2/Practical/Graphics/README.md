# OPEN-GL Installion Notes

1. Open a terminal and enter the following commands to install the necessary libraries for OpenGL development:
```
sudo apt-get update
sudo apt-get install freeglut3
sudo apt-get install freeglut3-dev
sudo apt-get install binutils-gold
sudo apt-get install g++ cmake
sudo apt-get install libglew-dev
sudo apt-get install g++
sudo apt-get install mesa-common-dev
sudo apt-get install build-essential
sudo apt-get install libglew1.5-dev libglm-dev
sudo apt-get install mesa-utils
```


2. After your development libraries have been installed to get information about the OpenGL and GLX implementations running on a given X display.

`glxinfo | grep OpenGL`


## Install libgraph
1) `sudo apt-get install build-essential`

2)Intall some additional packages by typing 
sudo apt-get install libsdl-image1.2 libsdl-image1.2-dev guile-1.8 \
  guile-1.8-dev libsdl1.2debian libart-2.0-dev libaudiofile-dev \
  libesd0-dev libdirectfb-dev libdirectfb-extra libfreetype6-dev \
  libxext-dev x11proto-xext-dev libfreetype6 libaa1 libaa1-dev \
  libslang2-dev libasound2 libasound2-dev

3) Now extract the downloaded libgraph-1.0.2.tar.gz file.

4) Goto extracted folder and run following command
```
./configure
make
sudo make install
sudo cp /usr/local/lib/libgraph.* /usr/lib
```
Command to Compile
```
gcc Line.c -lGL -lglut -lGLU -lm
```


