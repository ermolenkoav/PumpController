#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.8)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
project(Odorator-tests)
set(TARGET_NAME ${PROJECT_NAME})

enable_testing()
find_package(GTest MODULE REQUIRED)

#-------------------------------------------------------------------------------
#	COMPILE FLAGS
#-------------------------------------------------------------------------------
if (MSVC)
	set(GUI_TYPE WIN32) 
    set(CMAKE_CXX_FLAGS_DEBUG "/MP /MDd /std:c++latest /GS /analyze /Gd /Od /RTC1 /RTCs /RTCu /W3 ") # /Wall
	set(CMAKE_CXX_FLAGS_RELEASE "/MP /MD /std:c++latest /Ox")
endif(MSVC)

#-------------------------------------------------------------------------------
#	ADDITIONAL LIBRARIES
#-------------------------------------------------------------------------------

list(APPEND LIBRARIES GTest::GTest GTest::Main)

#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------
# Generate the executable
add_executable(${TARGET_NAME} mainwindowtests.cpp)

# link libraries
target_link_libraries(${TARGET_NAME} PRIVATE GTest::GTest GTest::Main)

add_test(EvenDivideTest ${TARGET_NAME})