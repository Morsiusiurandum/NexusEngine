# Nexus Engine

**Nexus Engine** is a rendering engine based on C++. Right now it is currently in the prototype design stage.

> [!NOTE]
> This project is only developed in my free time, so updates will be less frequent.

## Introduction

The project is based on Win32API and DirectX11, which means it will only run and compile under the Windows operating system. After completing the prototype design and basic functions, I may consider porting it to run under Linux, which will be a difficult process.

## Require

- CMake: 3.24
- C++ Complier: Visual Studio 17 2022
- Microsoft DirectX®: D3DX11
- OS: Windows10/11

## Release

Since this is still in the prototyping stage, you may need to compile the source files manually.

Example:

```bash
# build CMake cache
cmake -B build/release -DCMAKE_BUILD_TYPE=Release

# build binary executable file
cmake --build build/release --config Release
```
