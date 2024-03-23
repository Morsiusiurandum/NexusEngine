# Nexus Engine

**Nexus Engine** is a rendering engine based on C++. Right now it is currently in the prototype design stage.

> [!NOTE]
> This project is only developed in my free time, so updates will be less frequent.

## Introduction

The project is based on Win32API and DirectX11, which means it will only run and compile under the Windows operating system. After completing the prototype design and basic functions, I may consider porting it to run under Linux, which will be a difficult process.

## Quick Start

If you are interested in the project, you can configure the project for local development as follows. We recommend using CMake for development as it can be used in Visual Studio Code and CLion or other IDEs. But if you want to do graphical debugging, you must use Visual Studio for development.

### Develop with CMake

Prerequisites:

- Windows 10 or newer
- CMake 3.24 or newer
- Microsoft DirectX®: [D3DX 11](https://learn.microsoft.com/en-us/windows/win32/direct3d11/d3d11-graphics-reference-d3dx11)
- Install [vcpkg](https://github.com/microsoft/vcpkg)

Since the project depends on some third-party packages, you need to use vcpkg to install these packages before starting.

```bash
# install imgui package
.\vcpkg install imgui[win32-binding]
.\vcpkg install imgui[dx11-binding]

# install directxtex
.\vcpkg install directxtex
```

After the installation is complete, you should be able to use the following command to generate the release version of CMake cache and build the application normally.

```bash
# build CMake cache 
cmake -B build/release -DCMAKE_BUILD_TYPE=Release

# build binary executable file
cmake --build build/release --config Release
```

### Develop with Visual Studio

Prerequisites:

- Windows 10 or newer
- Microsoft DirectX®: D3DX11
- Install [vcpkg](https://github.com/microsoft/vcpkg)

Since the project depends on some third-party packages, you need to use vcpkg to install these packages before starting. After completion, the file will be able to be compiled and debugged normally.

```bash
# install imgui package
.\vcpkg install imgui[win32-binding]
.\vcpkg install imgui[dx11-binding]

# install directxtex
.\vcpkg install directxtex
```

## Release

Since this is still in the prototyping stage, you may need to compile the source files manually.

## Thanks

This project is affected by [hw3d](https://github.com/planetchili/hw3d). I would like to express my sincere gratitude for your inspiration.
