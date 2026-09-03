cmake_minimum_required(VERSION 3.12)
project(DesktopSearchEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(desktop-search main.cpp search.cpp)
add_executable(desktop-search-gui gui_main.cpp search.cpp)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_link_libraries(desktop-search PRIVATE Qt6::Widgets)
target_link_libraries(desktop-search-gui PRIVATE Qt6::Widgets)