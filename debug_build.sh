if [ ! -d "build" ]; then
    mkdir -p build && cd build
    echo "Folder created: $folder_path"
else
    cd build
fi

cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-fuse-ld=lld" -DCMAKE_CXX_FLAGS="-fuse-ld=lld"
cmake --build . -- -j 10
