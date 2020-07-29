cmake_minimum_required(VERSION 3.5)

project(DataReader)
set(SOURCES
    main.cpp
    DataReader.cpp
)

find_package(OpenCV REQUIRED)

add_executable(tt ${SOURCES})

target_link_libraries(tt ${OpenCV_LIBS})