#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.13)
project(Odorator)

#-------------------------------------------------------------------------------
#	COMPILE FLAGS
#-------------------------------------------------------------------------------
if (MSVC)
	set(GUI_TYPE WIN32) 
    set(CMAKE_CXX_FLAGS_DEBUG "/MP /MDd /std:c++latest /GS /analyze /Gd /Od /RTC1 /RTCs /RTCu /W3 ") # /Wall
	set(CMAKE_CXX_FLAGS_RELEASE "/MP /MD /std:c++latest /Ox")
endif(MSVC)

#-------------------------------------------------------------------------------
#	PROJECT STRUCTURE
#-------------------------------------------------------------------------------
enable_testing()

add_subdirectory(source)
add_subdirectory(tests)
