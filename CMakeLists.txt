cmake_minimum_required(VERSION 3.12)
project(DesktopSearchEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(desktop-search-core
    search.cpp
    rag.cpp
    ollama.cpp
)

add_executable(desktop-search
    main.cpp
)

add_executable(desktop-search-gui
    gui_main.cpp
)

add_executable(rag-test
    rag_test.cpp
)

target_link_libraries(desktop-search
    PRIVATE desktop-search-core
)

target_link_libraries(desktop-search-core
    PUBLIC Qt6::Network
)

target_link_libraries(desktop-search-gui
    PRIVATE
    desktop-search-core
    Qt6::Widgets
)

target_link_libraries(rag-test
    PRIVATE desktop-search-core
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

set_target_properties(desktop-search-gui PROPERTIES
    WIN32_EXECUTABLE ON
)