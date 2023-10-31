cmake_minimum_required(VERSION 3.0.0)

project(futuremade)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(Deps "/home/zwx0641/thirdparty-libs")
set(INCS ${Deps}/include)
set(LIBS ${Deps}/lib)

add_subdirectory(src)