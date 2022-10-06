#!/bin/bash

rm -rf build
mkdir build
cd build
conan install .. -s build_type=Release
cmake .. -DCMAKE_BUILD_TYPE=Release -DWITH_R3=ON -DWITH_HTTP_ROUTER=ON
make

