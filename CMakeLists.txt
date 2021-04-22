cmake_minimum_required(VERSION 3.14...3.19)

project(PixelTetris VERSION 0.5 LANGUAGES CXX)

INCLUDE(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED SDL2)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf)

file(GLOB_RECURSE TARGET_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_executable(PixelTetris.out ${TARGET_SOURCES})

target_include_directories(PixelTetris.out PRIVATE
    include ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

target_link_libraries(PixelTetris.out  ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})

