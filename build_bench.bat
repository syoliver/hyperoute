rmdir /Q /S build
mkdir build
pushd build
conan install .. -s build_type=Release --build=missing
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
popd