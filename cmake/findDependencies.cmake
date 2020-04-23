set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)

if(PORT STREQUAL "qt5")
    set(VCPKG_LIBRARY_LINKAGE dynamic)
endif()

if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
	add_definitions(-D_DEBUG)
	include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
elseif("${CMAKE_BUILD_TYPE}" MATCHES "Release")
	include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
endif()

find_package(Qt5 COMPONENTS Core Widgets SerialPort REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(EXTERNAL_INCLUDES ${Qt5Core_INCLUDE_DIRS}
                      ${Qt5Gui_INCLUDE_DIRS} 
                      ${Qt5Widgets_INCLUDE_DIRS} 
                      ${Qt5SerialPort_INCLUDE_DIRS}
                      
                      )

set(EXTERNAL_LIBS
        Qt5::Core ${Qt5Core_LIBRARIES}
        Qt5::Gui ${Qt5Gui_LIBRARIES}
        Qt5::Widgets ${Qt5Widgets_LIBRARIES}
        Qt5::SerialPort ${Qt5SerialPort_LIBRARIES}
        jsoncpp_lib
        )