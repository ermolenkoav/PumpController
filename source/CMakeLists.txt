#-------------------------------------------------------------------------------
#	CONFIGURATION
#-------------------------------------------------------------------------------
configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h)

set(TARGET_NAME ${PROJECT_NAME})
set(CPACK_APPLICATION_NAME ${PROJECT_NAME})
set(CPACK_DEVELOPMENT_ORGANIZATION "SFEDU")
set(CPACK_DEVELOPMENT_ORGANIZATION_DOMAIN "https://sfedu.ru/")
set(CPACK_DEVELOPER_CONTACT ermolenkoav@yandex.ru)
set(CPACK_VERSION_MAJOR 0)
set(CPACK_VERSION_MINOR 7)
set(CPACK_VERSION_PATCH 0)
set(CPACK_PACKAGE_VERSION "${CPACK_VERSION_MAJOR}.${CPACK_VERSION_MINOR}.${CPACK_VERSION_PATCH}")

#-------------------------------------------------------------------------------
#	Settings
#-------------------------------------------------------------------------------
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)
find_package(cpprestsdk CONFIG REQUIRED)

#-------------------------------------------------------------------------------
#	SOURCE CODE
#-------------------------------------------------------------------------------
list(APPEND SOURCE_FILES
	main.cpp
	mainwindow.cpp
	controller.cpp
	model.cpp
	settings.cpp
	resources/resources.rc
)

list(APPEND HEADER_FILES
	pch.h
	mainwindow.h
	controller.h 
	model.h
	settings.h
)

list(APPEND LIBRARIES
	Qt5::Widgets 
	Qt5::SerialPort
	cpprestsdk::cpprest 
	cpprestsdk::cpprestsdk_zlib_internal 
	cpprestsdk::cpprestsdk_boost_internal 
	cpprestsdk::cpprestsdk_openssl_internal
)
#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------
# Generate the executable
add_executable(${TARGET_NAME} ${GUI_TYPE} ${SOURCE_FILES} ${HEADER_FILES})

# link libraries
target_link_libraries(${TARGET_NAME} PRIVATE ${LIBRARIES})