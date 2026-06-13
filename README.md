# jass

Just Another Space Shooter

## Dependencies

`jass` is built with [CMake](https://cmake.org/) (>= 3.10) and a C++14
compiler. The following libraries are required:

- [OpenGL](https://www.opengl.org/)
- [GLM](https://github.com/g-truc/glm)
- [GLFW3](https://www.glfw.org/)
- [DevIL](https://openil.sourceforge.net/)
- [Boost](https://www.boost.org/) (the `filesystem` component)

[glad](https://github.com/Dav1dde/glad) and
[tinyobjloader](https://github.com/tinyobjloader/tinyobjloader) are bundled in
`libs/` and do not need to be installed separately.

### Installing dependencies

On Debian/Ubuntu:

```bash
sudo apt install build-essential cmake \
    libglm-dev libglfw3-dev libdevil-dev libboost-filesystem-dev
```

On Arch Linux:

```bash
sudo pacman -S base-devel cmake glm glfw devil boost
```

On macOS (with [Homebrew](https://brew.sh/)):

```bash
brew install cmake glm glfw devil boost
```

## Building

Configure and build from the project root:

```bash
cmake -S . -B build
cmake --build build
```

The resulting executable is placed in `exe/jass`.

> Only the `Debug` build is configured; CMake defaults to `Debug` when no build
> type is specified.

## Running

The game loads its assets from the `resources/` directory using relative paths,
so it must be launched from the project root:

```bash
./exe/jass
```
