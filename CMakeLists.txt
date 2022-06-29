cmake_minimum_required(VERSION 3.19)

project(2dgame)

# Add all c source files under the src directory
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# add sdl library
find_package(SDL2 REQUIRED)

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} include /usr/local/include)
# /usr/local/include needed for mac 
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})