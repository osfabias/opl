# Osfabias Platform Layer
OPL is an Open-Source, multi-platform library for vulkan application 
development. It provides a simple, platform-independent API for
creating windows *(on desktop platforms)* and surfaces *(on mobile and
console platform)*, reading user input, handling platform events,
efficient memory management, playing audio, etc.

Currently supported platforms:
- MacOS.

Platform to be supported (SOON):
- Linux (X11);
- Windows;
- Android;
- iOS.

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

### 3. Start binary.
```shell
# from opl/build/
cd bin
./example
```

You're done!

# Documentation
```shell
# from opl/
doxygen
cd doc/html
open index.html
```
