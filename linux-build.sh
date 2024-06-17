#!/bin/bash

# Run CMake to configure the project
cmake -S . -B ./.cache/build/release -DCMAKE_BUILD_TYPE=Release

# Build the project using the configured build system
cmake --build ./.cache/build/release --config Release

# Pause to keep the terminal window open (optional)
read -r -p "Press any key to continue..."
