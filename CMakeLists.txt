cmake_minimum_required(VERSION 3.0)
project(BadPiggies)

add_subdirectory(vendor/SDL)
add_subdirectory(vendor/spdlog)

add_executable(BadPiggies main.cpp)
target_link_libraries(BadPiggies PRIVATE SDL2::SDL2 spdlog)