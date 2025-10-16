#!/bin/bash
set -e  # stop on error

# Make build folder if it doesn't exist
mkdir -p build
cd build

# Generate build system and compile
cmake ..
cmake --build .