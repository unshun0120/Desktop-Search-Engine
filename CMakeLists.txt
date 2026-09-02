cmake_minimum_required(VERSION 3.12)
project(DesktopSearchEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(desktop-search main.cpp search.cpp)
