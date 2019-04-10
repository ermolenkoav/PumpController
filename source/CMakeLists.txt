#-------------------------------------------------------------------------------
#	CONFIGURATION
#-------------------------------------------------------------------------------
set(TARGET_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_VERSION_MAJOR 0)
set(CPACK_VERSION_MINOR 7)
set(CPACK_VERSION_PATCH 2)
set(ORGANIZATION_NAME "SFEDU")
set(ORGANIZATION_URL "https://sfedu.ru/www/stat_pages22.show?p=ELs/sotr/D&x=ELS/10484")
set(ORGANIZATION_LOGO "logoSFEDU.ico")
set(ORGANIZATION_EMAIL "ermolenkoav@yandex.ru")
set(CPACK_PACKAGE_VERSION "${CPACK_VERSION_MAJOR}.${CPACK_VERSION_MINOR}.${CPACK_VERSION_PATCH}")
configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h)

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

# Link libraries
target_link_libraries(${TARGET_NAME} PRIVATE ${LIBRARIES})

#-------------------------------------------------------------------------------
#	GENERATE INSTALLER
#-------------------------------------------------------------------------------
if (CMAKE_BUILD_TYPE MATCHES Release)
	message("Enable CPack.")

	file(GLOB DYNAMIC_LINK_LIB ${CMAKE_BINARY_DIR}/source/*.dll)
	install(TARGETS ${TARGET_NAME} DESTINATION /)
	install(FILES ${DYNAMIC_LINK_LIB} DESTINATION /)
	install(DIRECTORY ${CMAKE_BINARY_DIR}/source/plugins/ DESTINATION plugins/)

	set(CPACK_GENERATOR NSIS)
	set(CPACK_NSIS_MODIFY_PATH OFF)
	set(CPACK_MONOLITHIC_INSTALL ON)
	set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
	set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "CreateShortCut \\\"$DESKTOP\\\\${TARGET_NAME}.lnk\\\" \\\"$INSTDIR\\\\${TARGET_NAME}.exe\\\"")
	set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "Delete \\\"$DESKTOP\\\\${TARGET_NAME}.lnk\\\"")
	set(CPACK_NSIS_MUI_ICON ${PROJECT_SOURCE_DIR}/source/resources/${ORGANIZATION_LOGO})
	set(CPACK_PACKAGE_INSTALL_DIRECTORY "${TARGET_NAME}")
	set(CPACK_NSIS_URL_INFO_ABOUT ${ORGANIZATION_URL})
	set(CPACK_CREATE_DESKTOP_LINKS "${TARGET_NAME}")
	set(CPACK_PACKAGE_VENDOR ${ORGANIZATION_NAME})
	set(CPACK_NSIS_CONTACT ${ORGANIZATION_EMAIL})
	set(CPACK_NSIS_PACKAGE_NAME "${TARGET_NAME}")
	include(CPack)
endif()