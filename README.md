
![Logo](https://img.freepik.com/premium-vector/mammoth-vector-logo-icon-illustration-mascot_1893-1246.jpg?w=1380)


# Mammoth

Mammoth is an object-oriented api-agnostic rendering framework currently supporting OpenGL and Vulkan, with Metal and DX12 support currently in the pipeline.

This is currently the project that I'm devoting most of my time to, so expect bugs, frequent changes and inconsistencies, as I continue to learn from other open source projects.

## Features

- Object-oriented
- API-agnostic
- Highly Modular
- Unit Tests
- CMake build system


## Installation

Currently only compiling on MacOS, with windows support being worked on.

Clone and build with CMake.

```bash
git clone [link-to-repo]

mkdir -p build
cd build
cmake -S ../ -B .
make
cd ..

// Or use the unixbuild.sh script.
./unixbuild.sh

// To run the demo after building.
build/testbed/demo/demo

```
    