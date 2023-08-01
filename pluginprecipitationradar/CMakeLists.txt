cmake_minimum_required(VERSION, 2.3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(weathermonitor VERSION 1.0)

add_executable(weathermonitor, *.cpp)