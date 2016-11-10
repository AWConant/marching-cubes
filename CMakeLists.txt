cmake_minimum_required(VERSION 2.8.11)
project(Final)

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

#grrr. poorly documented
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS})


#get symlink_data macro
#include(${CMAKE_SOURCE_DIR}/cmake_modules/helpers.cmake)

#set(QTHDRS
#  mainwindow.h
#  mypanelopengl.h
#)

#window design files
#set(QTFORMS mainwindow.ui)

#Run qt tools to auto generate C++ compatible files
#QT5_WRAP_CPP(QTHDRS_MOC ${QTHDRS})
#QT5_WRAP_UI(QTFORMS_HDRS ${QTFORMS})
#set(MYQTFILES ${QTHDRS_MOC} ${QTFORMS_HDRS})


# Build the library of shapes
# TODO: gradually add new shape headers/src as you implement them
#set(LIBHDRS drawable.h triangle.h rectangle.h line.h circle.h geomfun.h)
#set(LIBSRC  drawable.cpp triangle.cpp rectangle.cpp line.cpp circle.cpp geomfun.cpp)
#add_library(libfinal ${LIBHDRS} ${LIBSRC})

#normal source files
#set(SRC
#  main.cpp
#  mainwindow.cpp
#  mypanelopengl.cpp
#)

# Allow shaders to show up in QT Creator
#set(SHADERS
#  shaders/vshader.glsl
#  shaders/fshader.glsl
#)


#compile
#add_executable(final ${SRC} ${LIBHDRS} ${MYQTFILES} ${SHADERS})
#link against QT libs
#set(EXTLIBS ${OPENGL_LIBRARY} Qt5::Widgets Qt5::OpenGL)
#target_link_libraries(final libfinal ${EXTLIBS})
#symlink_data(final-shaders shaders)
