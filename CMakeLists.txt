#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.8)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
project(Odorator)
enable_testing()

#-------------------------------------------------------------------------------
#	CONFIGURATION
#-------------------------------------------------------------------------------
set(TARGET_NAME ${PROJECT_NAME})
set(APPLICATION_NAME ${TARGET_NAME})
set(APPLICATION_ORGANIZATION "sfedu")
set(APPLICATION_ORGANIZATION_DOMAIN "https://sfedu.ru/")
#configure_file(include/appinfo.h.in appinfo.h @ONLY NEWLINE_STYLE UNIX)

#-------------------------------------------------------------------------------
#	Settings
#-------------------------------------------------------------------------------
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) 

find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

add_subdirectory(tests)
#-------------------------------------------------------------------------------
#	SOURCE CODE
#-------------------------------------------------------------------------------
list(APPEND SOURCE_FILES
	source/main.cpp
	source/mainwindow.cpp
	source/controller.cpp
    resources/resources.qrc
)

list(APPEND HEADER_FILES
	source/pch.h
	source/mainwindow.h
	source/controller.h 
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
#	ADDITIONAL LIBRARIES
#-------------------------------------------------------------------------------

list(APPEND LIBRARIES Qt5::Widgets Qt5::SerialPort)

#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------
# Generate the executable
add_executable(${TARGET_NAME} ${GUI_TYPE} ${SOURCE_FILES} ${HEADER_FILES} ${RESOURCES})

# link libraries
target_link_libraries(${TARGET_NAME} ${LIBRARIES})
