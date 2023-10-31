cmake_minimum_required(VERSION 3.20.0)

project(PcapParser)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_CXX_STANDARD 20)
set(INCS include include/simba)
file(GLOB SRC src/*.cpp)

include_directories(${INCS})

add_executable(PcapParser ${SRC})