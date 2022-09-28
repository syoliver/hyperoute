rmdir /Q /S build
mkdir build
pushd build
conan install .. -s build_type=Debug --build=missing
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
popd