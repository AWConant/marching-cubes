cmake_minimum_required(VERSION 2.8.11)
project(final)

set(CMAKE_CXX_FLAGS "-g -Wall")

#required CMake options for QT Apps
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#for window widgets
find_package(OpenGL REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS})

#get symlink_data macro
include(${CMAKE_SOURCE_DIR}/cmake_modules/helpers.cmake)

#QT headers requiring MOC (meta object compiler)
set(QTHDRS
  mainwindow.h
  mypanelopengl.h
  )

#window design files
set(QTFORMS mainwindow.ui)

#Run qt tools to auto generate C++ compatible files
QT5_WRAP_CPP(QTHDRS_MOC ${QTHDRS})
QT5_WRAP_UI(QTFORMS_HDRS ${QTFORMS})
SET(MYQTFILES ${QTHDRS_MOC} ${QTFORMS_HDRS})

#normal source files
set(SRC
  main.cpp
  mainwindow.cpp
  mypanelopengl.cpp
)

set(SHADERS
  shaders/vshader.glsl
  shaders/fshader.glsl
)

set(SHDRS matrixstack.h printmatrix.h camera.h)
set(SSRC matrixstack.cpp printmatrix.cpp camera.cpp)

add_library(libfinal ${SHDRS} ${SSRC})

ADD_EXECUTABLE(terrain ${SRC} ${SHDRS} ${MYQTFILES} ${SHADERS}) # terrainData.txt)
# ADD_EXECUTABLE(parseTerrainData parseData.cpp)

set(EXTLIBS ${OPENGL_LIBRARY} Qt5::Widgets Qt5::OpenGL)

TARGET_LINK_LIBRARIES(terrain libfinal ${EXTLIBS})

symlink_data(final_shaders shaders)
# symlink_data(final_png data)
# symlink_data(final_data terrainData.txt)
