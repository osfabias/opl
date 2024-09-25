# Osfabias Platform Layer
OPL is an Open-Source, multi-platform library for vulkan application 
development. It provides a simple, platform-independent API for
creating windows *(on desktop platforms)* and surfaces *(on mobile and
console platform)*, reading user input, handling platform events,
efficiently manageming memory, managing threads, etc.

Currently supported platforms:
- Windows;
- Linux (X11);
- MacOS.

Platform to be supported ( SOON :3 ):
- Android;
- iOS;
- PlayStation;
- XBox;
- Nintendo Switch.

# How to build
## Requirements:
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) (latest version)[*](https://github.com/osfabias/opl/issues/1)
- CMake (version 2.16+)

### 1. Clone project.
```shell
git clone git@github.com:osfabias/opl.git # stop using html, okay!?
cd opl
```

### 2. Configure and build project via CMake.
```shell
# from opl/
mkdir build
cd build
cmake -DOPL_BUILD_EXAMPLE=ON .. # add -DCMAKE_BUILD_TYPE=Debug for debug build
cmake --build .
```

### 3. Try run examples.
```shell
# from opl/build/
cd bin
./window-creation
```

You're done!

# Documentation
```shell
# from opl/
doxygen
cd doc/html
open index.html
```
