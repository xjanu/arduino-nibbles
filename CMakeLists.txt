cmake_minimum_required(VERSION 3.13.0)
project(arduino_nibbles CXX)

add_executable(blink)
target_sources(blink PUBLIC "src/blink.cpp")
target_link_arduino_libraries(blink PRIVATE core)
target_enable_arduino_upload(blink)
