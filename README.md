# KC-Community-Software-Renderer
King's Crook Community Software Renderer
================================================================

This is a software renderer project started by members of the King's Crook community.
Anyone can contribute! This is meant to be a for-fun software renderer that everyone can contribute to.

It is based off of the [PL3D-KC](https://github.com/LMP88959/PL3D-KC) project.

================================================================

Compiling for macOS/Linux:
```
  cd KC-Community-Software-Renderer

  cc -O3 -o pl *.c fw/*.c -lX11 -lXext

  ./pl
```

or use CMake for Linux, macOS or Windows -- tested with GCC, Clang, Intel oneAPI, Visual Studio, NVIDIA HPC SDK, AOCC, ...

```sh
cmake -B build
cmake --build build
build/main
```

macOS requires an X-server such as [XQuartz](https://www.xquartz.org/) running in the background.
Prerequisites for macOS can be installed via [Homebrew](https://brew.sh):

```sh
brew install libx11 xquartz
```

Don't forget to compile with max optimization!

If you have any questions feel free to leave a comment on YouTube OR
join the King's Crook Discord server :)

YouTube: https://www.youtube.com/c/LMP88

Discord: https://discord.gg/hdYctSmyQJ

itch.io: https://kingscrook.itch.io/kings-crook
