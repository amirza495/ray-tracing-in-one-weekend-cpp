cmake_minimum_required(VERSION 3.14)
project(ray_tracing_weekend)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-O3")

add_executable(main 
    src/main.cc
    src/geometry/hit_record.cc)

target_include_directories(main PRIVATE include)

