#!/bin/bash

rm -rf build
mkdir build
cd build
conan install .. -s build_type=Debug --build=missing
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON -DTEST_OUTPUT=JUNIT
make

