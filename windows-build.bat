@echo off

:: build CMake cache 
cmake -S . -B ./.cache/build/release -DCMAKE_BUILD_TYPE=Release

:: build binary executable file
cmake --build ./.cache/build/release --config Release

pause 