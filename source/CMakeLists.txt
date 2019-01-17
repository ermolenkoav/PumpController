#-------------------------------------------------------------------------------
#	CONFIGURATION
#-------------------------------------------------------------------------------
set(TARGET_NAME ${PROJECT_NAME})
#set(APPLICATION_NAME ${PROJECT_NAME})
set(APPLICATION_ORGANIZATION "sfedu")
set(APPLICATION_ORGANIZATION_DOMAIN "https://sfedu.ru/")
#configure_file(include/appinfo.h.in appinfo.h @ONLY NEWLINE_STYLE UNIX)

#-------------------------------------------------------------------------------
#	Settings
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
	setupcontroller.cpp
	startcontroller.cpp
	model.cpp
	resources/resources.qrc
)

list(APPEND HEADER_FILES
	pch.h
	mainwindow.h
	setupcontroller.h 
	startcontroller.h
	model.h
)

#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------
# Generate the executable
add_executable(${TARGET_NAME} ${GUI_TYPE} ${SOURCE_FILES} ${HEADER_FILES})

# link libraries
target_link_libraries(${TARGET_NAME} Qt5::Widgets Qt5::SerialPort)