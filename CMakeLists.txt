cmake_minimum_required(VERSION 3.23.2)

project(2dgame)

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} include)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})