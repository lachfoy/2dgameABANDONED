cmake_minimum_required(VERSION 3.1)

project(2dgame)

# specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add all c source files under the src directory
file(GLOB SOURCES "src/*.h" "src/*.cc")
add_executable(${PROJECT_NAME} ${SOURCES})

INCLUDE(FindPkgConfig)

# add sdl library
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)

include_directories(
    ${PROJECT_NAME} PRIVATE
    /usr/local/include # /usr/local/include needed for mac
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS}
    ${SDL2MIXER_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    -L/usr/local/lib -lSDL2 # needed for mac also??
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
    ${SDL2MIXER_LIBRARIES}
) 