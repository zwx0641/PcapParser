if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <build_type>"
    exit 1
fi

if [ ! -d "build" ]; then
    mkdir -p build && cd build
    echo "Folder created: $folder_path"
else
    cd build
fi

cmake .. -G Ninja -DCMAKE_BUILD_TYPE="$1"
cmake --build . -- -j 10
