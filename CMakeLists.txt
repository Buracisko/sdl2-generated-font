cmake_minimum_required(VERSION 3.6)

project(sdl2-generated-font VERSION 1.0
	#DESCRIPTION "Simple example project" #Only from version 3.9
	LANGUAGES C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${sdl2-generated-font_SOURCE_DIR}/sdl2-cmake-scripts")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)

# Add inlude directory to help IDE
include_directories(${SDL2_INCLUDE_DIR} PRIVATE include)

add_executable(hello main.c)

target_link_libraries(hello PRIVATE ${SDL2_LIBRARY})

#Not sure how clean it is, but I want this flags
if(MSVC)
	add_compile_options(/W3 /WX)
else()
	add_compile_options(-W -Wall -Werror -pedantic)
endif()
