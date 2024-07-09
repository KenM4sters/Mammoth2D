
![Logo](https://img.freepik.com/premium-vector/mammoth-vector-logo-icon-illustration-mascot_1893-1246.jpg?w=1380)


# Mammoth2D

Mammoth2D is a 2d game engine written in C++ that uses the Vulkan API for graphics rendering. It also makes use of custom Maths, Phycsics and ECS libraries, also written by myself.

This is currently the project that I'm devoting most of my time to, so expect bugs, frequent changes and inconsistencies, as I continue to learn from other open source projects.

## Features

- Highly Modular
- Unit Tests
- CMake build system
- Fast collision detection using a BVH tree.
- Impulse and friction resolution
- Sprite animations
- Flexible Entity Component System (ECS)


## Installation

Currently only supporting MacOS, with windows support currently being worked on.

Clone and build with CMake.

```bash
git clone [link-to-repo]

mkdir -p build
cd build
cmake -S ../ -B .
make
cd ..

// To run the test tutorials...
build/Tests/Tutorial1/Tutorial1
```
    