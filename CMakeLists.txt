cmake_minimum_required(VERSION 3.13.0)
project(arduino_nibbles CXX)


add_executable(blink)
target_sources(blink PUBLIC "src/blink.cpp")
target_link_arduino_libraries(blink PRIVATE core)
target_enable_arduino_upload(blink)


add_executable(cereal)
target_sources(cereal PUBLIC "src/cereal.cpp")
target_link_arduino_libraries(cereal PRIVATE core)
target_enable_arduino_upload(cereal)


add_executable(i2c)
target_sources(i2c PUBLIC "src/i2c.cpp")
target_link_arduino_libraries(i2c PRIVATE core Wire)
target_enable_arduino_upload(i2c)
