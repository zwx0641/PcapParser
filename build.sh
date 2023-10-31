cd build
cmake .. -G Ninja -DCMAKE_C_FLAGS="-fuse-ld=lld" -DCMAKE_CXX_FLAGS="-fuse-ld=lld"
cmake --build . -- -j 10
