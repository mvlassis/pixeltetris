cmake_minimum_required(VERSION 3.14...3.19)

project(PixelTetris VERSION 0.5 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB_RECURSE TARGET_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

if (WIN32)
	string(REPLACE "/include/SDL2" "/include/" SDL2_PARENT_DIR ${SDL2_INCLUDE_DIR})
	add_executable(PixelTetris WIN32 ${TARGET_SOURCES})
else()
	add_executable(PixelTetris ${TARGET_SOURCES})
endif()


target_include_directories(PixelTetris PRIVATE ${SDL2_PARENT_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(PixelTetris ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})