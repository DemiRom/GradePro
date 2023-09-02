cmake_minimum_required(VERSION 3.26)
project(GradePro)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)

include_directories(libs/imgui)
include_directories(libs/SDL/src)
include_directories(libs/libdxfrw/src)

#=================== EXAMPLE ===================
if(BUILD_EXAMPLES)
    add_executable(example_sdl3_opengl3)
    target_sources(example_sdl3_opengl3 PUBLIC ${CMAKE_SOURCE_DIR}/libs/imgui/examples/example_sdl3_opengl3/main.cpp)
    target_link_libraries(example_sdl3_opengl3 IMGUI)
    set_target_properties(example_sdl3_opengl3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

set(SRCS src/main.cpp
        src/DxfWindow.cpp
        src/DxfWindow.h
        src/FileDialog.cpp
        src/FileDialog.h
        src/FileDialogConfig.h
        src/Style.h
        src/DxfInterface.cpp
        src/DxfInterface.h
        src/DxfData.cpp
        src/DxfData.h
        src/DxfPolyline.cpp
        src/DxfPolyline.h
        src/LaserWindow.cpp
        src/LaserWindow.h
        src/AbstractWindow.cpp
        src/AbstractWindow.h)

add_executable(GradePro ${SRCS})
target_link_libraries(GradePro IMGUI Dxflib::Dxflib)
set_target_properties(GradePro PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})