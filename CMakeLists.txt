# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (Larry)

set(	SOURCES
	Source/Scraper.hpp

	Source/Larry.cpp
	Source/Scraper.cpp
	Source/Chisel.cpp
)
add_executable(Larry ${SOURCES})

target_include_directories(Larry PRIVATE Include)

add_library(json.hpp INTERFACE)
target_include_directories(json.hpp INTERFACE Lib)
target_link_libraries(Larry PRIVATE json.hpp)