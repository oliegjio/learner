cmake_minimum_required(VERSION 2.6)
project(machine-learning)

file(GLOB SOURCES "src/*.c")
# set(CMAKE_CXX_FLAGS "-Wall")

add_executable(machine-learning ${SOURCES})
target_link_libraries(machine-learning m)
target_link_libraries(machine-learning pthread)
