cmake_minimum_required(VERSION 3.7)

project(2dgame)

find_package(SDL2 REQUIRED)
#find_library(SDL2_LIBRARY NAME SDL2)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Engine.cpp
    src/Projectile.cpp
    src/Enemy.cpp
)

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} include /usr/local/include)
# /usr/local/include needed for mac 
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})