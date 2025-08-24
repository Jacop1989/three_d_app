# three_d_app

A simple 3D wireframe renderer written in C.

## Installation

- GCC or another C17-compatible compiler
- SDL2 development libraries
- Make (optional)

## Build

Compile the project with:

```
gcc src/app/main.c src/app/camera.c src/math/vec.c src/renderer/framebuffer.c src/renderer/line.c -I src -lSDL2 -lm -o cad_wireframe
```

## Run

Execute the compiled program with:

```
./cad_wireframe
```

