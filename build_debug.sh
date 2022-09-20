#!/bin/bash

rm -rf build
mkdir build
cd build
conan install .. -s build_type=Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON
make

