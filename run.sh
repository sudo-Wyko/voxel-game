#!/bin/bash

# makes the script exit immediately if any command fails
set -e

echo " --- Configuring project... ---"
cmake -B build

echo " --- Bulding project... ---"
cmake --build build

echo " --- Running executable... ---"
./build/voxel-game
