#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.11)
project(Odorator LANGUAGES CXX)

#-------------------------------------------------------------------------------
#	COMPILE FLAGS
#-------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    set(GUI_TYPE WIN32)
elseif(GNU)
    set(CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu/cmake/)
endif(MSVC)

#-------------------------------------------------------------------------------
#	PROJECT STRUCTURE
#-------------------------------------------------------------------------------
include_directories(source)
add_subdirectory(source)
add_subdirectory(tests)

option(BUILD_TESTING "Create tests using CMake" ON)
if(BUILD_TESTING)
    enable_testing()
endif()