# Open Landscape Stacker

This is an extremely work in progress stacker for nightscape images. This probably isn't interesting to anyone but me at the moment ;) 

## Building

OLS currently has the following dependencies:
* QT6
* OpenCV 4

### Windows

Currently, the CMake buildsystem assumes that QT6 is installed at the following path:

```
C:\Qt\6.0.0\msvc2019_64\
```
Also note that it's expected that the environment variable ***OPENCV_DIR*** is set to the path to the OpenCV install.
