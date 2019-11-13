#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.13)
project(Odorator LANGUAGES CXX)

#-------------------------------------------------------------------------------
#	COMPILE FLAGS
#-------------------------------------------------------------------------------
if (MSVC)
set(GUI_TYPE WIN32)
set(CMAKE_CXX_FLAGS_DEBUG "/MP /MDd /std:c++17 /GS /analyze /Gd /Od /RTC1 /RTCs /RTCu ") # /Wall /W3 
set(CMAKE_CXX_FLAGS_RELEASE "/MP /MD /std:c++latest /Ox")
elseif(GNU)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -gnu:c++17 -fPIC -w -Wextra -Wall -g -ggdb ")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -gnu:c++17 -fPIC")
endif(MSVC)

#-------------------------------------------------------------------------------
#	PROJECT STRUCTURE
#-------------------------------------------------------------------------------
#set(CMAKE_CXX_CPPCHECK "cppcheck")

enable_testing()

add_subdirectory(source)
add_subdirectory(tests)