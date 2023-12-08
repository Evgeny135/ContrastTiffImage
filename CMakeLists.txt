cmake_minimum_required(VERSION 3.25)
project(ContrastTiffImage)

find_package(TIFF)

set(CMAKE_CXX_STANDARD 14)

add_executable(ContrastTiffImage main.cpp
        Spectrum.cpp
        Spectrum.h)

target_link_libraries(ContrastTiffImage TIFF::TIFF)