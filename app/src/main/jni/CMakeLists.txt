cmake_minimum_required(VERSION 3.4.1)

add_library(
        capture-lib
        SHARED
        capture.cpp
        CameraProvader.cpp
)

find_library(
        log-lib
        log
)

find_library(
        camera-lib
        camera2ndk
)

find_library(
        media-lib
        mediandk
)

find_library(
        android-lib
        android
)

find_library(
        gl-lib
        GLESv2
)

target_link_libraries(
        capture-lib
        ${log-lib}
        ${camera-lib}
        ${media-lib}
        ${android-lib}
        ${gl-lib}
)