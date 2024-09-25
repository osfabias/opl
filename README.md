# Osfabias Platform Layer
OPL is an Open-Source, multi-platform library for Vulkan applications.
It provides simple, platform-independent API for creating windows and
surfaces and reading user input.

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

## Requirements:
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) (latest version)[*](https://github.com/osfabias/opl/issues/1)
- CMake (version 2.16+)

# How to use
```cmake
add_subdirectory(opl)
target_link_libraries(<target> <mode> opl)
```

# How to build
### 1. Clone project.
```shell
git clone git@github.com:osfabias/opl.git
cd opl
```

### 2. Configure and build project via CMake.
```shell
# from opl/
mkdir build
cd build
# add -DCMAKE_BUILD_TYPE=Debug for debug build
cmake ..
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
