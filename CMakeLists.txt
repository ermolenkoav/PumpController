#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.8)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
project(Odorator)

#-------------------------------------------------------------------------------
#	CONFIGURATION
#-------------------------------------------------------------------------------
set(TARGET_NAME ${PROJECT_NAME})
set(APPLICATION_NAME ${TARGET_NAME})
set(APPLICATION_ORGANIZATION "sfedu")
set(APPLICATION_ORGANIZATION_DOMAIN "https://sfedu.ru/")
#configure_file(include/appinfo.h.in appinfo.h @ONLY NEWLINE_STYLE UNIX)

#-------------------------------------------------------------------------------
#	Qt Settings
#-------------------------------------------------------------------------------
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) 

find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

#-------------------------------------------------------------------------------
#	SOURCE CODE
#-------------------------------------------------------------------------------
list(APPEND SOURCE_FILES
	main.cpp
	mainwindow.cpp
    #resources.qrc
)

list(APPEND HEADER_FILES
	pch.h
	mainwindow.h 
)

#-------------------------------------------------------------------------------
#	COMPILE FLAGS
#-------------------------------------------------------------------------------
if (MSVC)
	set(GUI_TYPE WIN32) 
        set(CMAKE_CXX_FLAGS_DEBUG "/MP /MDd /std:c++latest /GS /analyze /Gd /Od /RTC1 /RTCs /RTCu /W3 ") # /Wall
	set(CMAKE_CXX_FLAGS_RELEASE "/MP /MD /std:c++latest /Ox")
endif(MSVC)

#-------------------------------------------------------------------------------
#	SOURCE GROUPS
#-------------------------------------------------------------------------------
#source_group(generated REGULAR_EXPRESSION ".*_automoc.cpp")
#source_group(resources REGULAR_EXPRESSION ".*[.][q]?rc")
#source_group(source REGULAR_EXPRESSION ".*[.]cpp")
#source_group(headers REGULAR_EXPRESSION ".*[.]h")
#source_group(continuous-integration REGULAR_EXPRESSION ".*[.]yml")

#-------------------------------------------------------------------------------
#	ADDITIONAL LIBRARIES
#-------------------------------------------------------------------------------

list(APPEND QT5_LIBRARIES Qt5::Widgets Qt5::SerialPort GTest::GTest GTest::Main)

#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------
# Generate the executable
add_executable(${TARGET_NAME} ${GUI_TYPE} ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCES})

# link libraries
target_link_libraries(${TARGET_NAME} ${QT5_LIBRARIES})

#-------------------------------------------------------------------------------
#	TEST SECTION
#-------------------------------------------------------------------------------
enable_testing()
list(APPEND TEST_FILES
	tests/mainwindowtests.cpp
)
find_package(GTest MODULE REQUIRED)
add_test(${TEST_FILES} ${TARGET_NAME}) 