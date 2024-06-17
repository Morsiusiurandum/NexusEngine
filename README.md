# Nexus Engine

**Nexus Engine** is an easy game engine based on modern C++. Right now it is currently in the prototype design stage.

> [!NOTE]
> This project is only developed in my free time, so updates will be less frequent.

## Introduction

The project is based on Win32API and DirectX11 now, which means it will only run and compile under the Windows operating system.
After completing the prototype design and basic functions, I may consider porting it to run under Linux, which will be a difficult process.

## Quick Start

If you are interested in the project, you can configure the project for local development as follows. We recommend using CMake for development as it can be used in Visual Studio Code and CLion or other IDEs. But if you want to do graphical debugging, you must use Visual Studio for development.

Prerequisites:

- Windows 10 or newer
- CMake 3.24 or newer
- Microsoft DirectX®: [D3DX 11](https://learn.microsoft.com/en-us/windows/win32/direct3d11/d3d11-graphics-reference-d3dx11)
- Install [vcpkg](https://github.com/microsoft/vcpkg) for third-party package

If you need to build a project, just run [windows-build.bat](windows-build.bat) and the required packages will be automatically installed at build time via vcpkg.
Alternatively, you can use `vcpkg install` at the root of your project to manually install dependencies.

## Release

Since this is still in the prototyping stage, you may need to compile the source files manually.

## Thanks

This project is affected by [hw3d](https://github.com/planetchili/hw3d). I would like to express my sincere gratitude for your inspiration.
