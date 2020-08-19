cmake_minimum_required(VERSION 3.10)
project(opencv.image)

add_executable(imageread src/imageread.cpp)
target_include_directories(imageread PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(imageread fmt::fmt CONAN_PKG::opencv)
