cmake_minimum_required(VERSION 3.20)
project(ColoredLines)

set(CMAKE_CXX_STANDARD 17)

if (DEFINED LOCAL_SOURCE_PACKAGE_DIR OR DEFINED ENV{LOCAL_SOURCE_PACKAGE_DIR})
    if (NOT LOCAL_SOURCE_PACKAGE_DIR)
        set(LOCAL_SOURCE_PACKAGE_DIR $ENV{LOCAL_SOURCE_PACKAGE_DIR})
    endif ()
endif ()

include(FetchContent)

if (DEFINED LOCAL_SOURCE_PACKAGE_DIR)
    FetchContent_Declare(tungsten
        URL "file://${LOCAL_SOURCE_PACKAGE_DIR}/Tungsten-0.1.3.4.tar.gz")
else ()
    FetchContent_Declare(tungsten
        GIT_REPOSITORY "https://github.com/jebreimo/Tungsten.git"
        GIT_TAG v0.1.3)
endif ()

FetchContent_MakeAvailable(tungsten)

list(APPEND CMAKE_MODULE_PATH ${tungsten_SOURCE_DIR}/tools/cmake)

include(TungstenTargetEmbedShaders)

add_executable(ColoredLines
    src/ColoredLines/ColoredLines.cpp
    src/ColoredLines/ColoredLinesShaderProgram.cpp
    src/ColoredLines/ColoredLinesShaderProgram.hpp
    )

target_link_libraries(ColoredLines
    PRIVATE
        Tungsten::Tungsten
    )

tungsten_target_embed_shaders(ColoredLines
    FILES
        src/ColoredLines/ColoredLines-frag.glsl
        src/ColoredLines/ColoredLines-vert.glsl
    )
