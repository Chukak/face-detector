cmake_minimum_required(VERSION 2.8)

project(face_detector)
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_definitions(-DDATA_DIRECTORY="${CMAKE_SOURCE_DIR}/extra/data")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/*.hpp")

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
