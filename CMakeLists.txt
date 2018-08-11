cmake_minimum_required(VERSION 2.6)
project(machine-learning)

file(GLOB SOURCES "src/*.c")

add_executable(machine-learning ${SOURCES})
target_link_libraries(machine-learning m)