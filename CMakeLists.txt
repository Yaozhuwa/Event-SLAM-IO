cmake_minimum_required(VERSION 3.5)

project(DataReader)

# set(CMAKE_CXX_FLAGS "${SSE_FLAGS} -O0 -g -std=c++0x -march=native" )

set(SOURCES
    main.cpp
    DataReader.cpp
    Camera.cpp
    FrameProcessor.cpp
    MyTools.cpp
)

find_package(OpenCV REQUIRED)

add_executable(tt ${SOURCES})

target_link_libraries(tt ${OpenCV_LIBS})