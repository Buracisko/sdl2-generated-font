cmake_minimum_required(VERSION 3.6)

project(sdl2-generated-font VERSION 1.0
	#DESCRIPTION "Simple example project" #Only from version 3.9
	LANGUAGES C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${sdl2-generated-font_SOURCE_DIR}/cmake-scripts")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)

# Add inlude directory to help IDE
include_directories(${SDL2_INCLUDE_DIR} PRIVATE include)

add_executable(testFont main.c spriteFont.c)

target_link_libraries(testFont PRIVATE ${SDL2_LIBRARY})

if (CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(testFont PRIVATE -Wall -Wextra -Werror -pedantic)
endif()
if (MSVC)
    target_compile_options(testFont PRIVATE /W4 /WX)
endif()