# OpenGL

## Intro

This is a simple and easy-to-use "library" made mainly for educational purposes.
The codebase was designed in a way that allows you to easily modify, change, rewrite and remake the original codebase.
This repository serves more like a learning field than the actual, ready-to-use and ready-to-ship piece of technology.
Feel free to use this repository however you want.

## Philosophy

This library was made for educational purposes. Covered topics:
- setting up OpenGL window (with SDL3 and GLFW);
- setting up OpenGL renderer;
- creating a simple quad and texture batcher;
- creating and loading textures (with stb_image.h);
- creating and loading fonts (with freetype);
- subdirectory build with CMake;
- fetching dependencies with CMake;
- building multiple sample programs using CMake;

Window, renderer and font are generic objects (void \*), which you can remake by yourself.
You don't need to rely only on my implementation, extend them to your needs.

## Getting started

### Dependencies:

To setup this project you need:
- [cmake](https://cmake.org/);
- [git](https://git-scm.com/);

The library itself is dependent on a few external libraries (and their own dependencies):
- [Dav1dde/glad](https://github.com/Dav1dde/glad) - OpenGL loader;
- [libsdl-org/SDL](https://github.com/libsdl-org/SDL) - Windowing;
- [glfw/glfw](https://github.com/glfw/glfw) - Windowing;
- [nothings/stb](https://github.com/nothings/stb) - Single-Header utility libraries;
- [recp/cglm](https://github.com/recp/cglm) - Math;
- [freetype/freetype](https://github.com/freetype/freetype) - Font loading;

### Building:

- Clone this repository:
```console
$ git clone https://github.com/itsYakub/OpenGL.git
$ cd OpenGL/
```

- Create a build directory:
```console
$ mkdir bin/
$ cd bin/
```

- Run CMake:
```console
$ cmake ..
$ cmake --build .
```

Now you should be able to test the library using sample programs, that should me created in `bin/samples/` directory.

## LICENCE

This project doesn't claim to be an OpenGL itself. This library is mainly for educational purposes.
Thus, this library is under the [UNLICENSE](./LICENCE) licence.

