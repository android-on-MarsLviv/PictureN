cmake_minimum_required(VERSION 3.4.1)

add_library(
        capture-lib
        SHARED
        capture.cpp
)

find_library(
        log-lib
        log
)

target_link_libraries(
        capture-lib
        ${log-lib}
)