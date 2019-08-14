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
    set(CMAKE_CXX_FLAGS_DEBUG "/MP /MDd /std:c++17 /GS /analyze /Gd /Od /RTC1 /RTCs /RTCu /W3 ") # /Wall
	set(CMAKE_CXX_FLAGS_RELEASE "/MP /MD /std:c++latest /Ox")
elseif(CMAKE_COMPILER_IS_GNUCXX)
	add_compile_options(
    "$<$<CONFIG:RELEASE>:/MP /MD /std:c++latest /Ox>"
    "$<$<CONFIG:DEBUG>:/MP /MDd /std:c++latest /GS /analyze /Gd /Od /RTC1 /RTCs /RTCu /W3>"
	)
endif(MSVC)

#-------------------------------------------------------------------------------
#	PROJECT STRUCTURE
#-------------------------------------------------------------------------------
#set(CMAKE_CXX_CPPCHECK "cppcheck")

enable_testing()

add_subdirectory(source)
add_subdirectory(tests)