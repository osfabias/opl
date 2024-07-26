# Osfabias Platform Layer
C library that provides a **single interface** for applications
to create windows / surfaces and read mouse, keyboard, joystick and sensor screen input.

Currently supported platforms:
- MacOS.

# How to build
## Requirements:
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) (latest version)[*](https://github.com/osfabias/opl/issues/1)
- CMake (version 2.16)

```shell
git clone git@github.com:osfabias/opl.git # stop using html, okay!?
cd opl

mkdir build
cd build
cmake .. # add -DCMAKE_BUILD_TYPE=Debug for debug build
cmake --build .
```

You're done!
