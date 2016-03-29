# s3tc_test
## Prerequisite

You need to install cmake at least at version 3.1 as build system.
You also need to install the following libraries:
  * glfw3
  * glew

### Linux  
  * sudo apt-get install cmake
  * sudo apt-get install libglew-dev

### Ubuntu 14.04 and above
  GLFW3 unfortunately it's not present in default repository. Follow these istrucionts:

  sudo add-apt-repository ppa:keithw/glfw3

  sudo apt-get update
  
  sudo apt-get install libglfw3-dev

### Ubuntu 16.04
  sudo apt-get install libglfw-dev

## Build
### Linux
  git clone https://github.com/edukaj/s3tc_test.git

  cd s3tc_test

  mkdir build

  cd build

  cmake ..

  make
