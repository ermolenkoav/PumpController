set(CMAKE_PREFIX_PATH "C:\\Users\\ermol\\AppData\\Local\\Programs\\Qt\\5.15.1\\msvc2019_64")

find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)

if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
	set(LIB_DIR ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug/lib)
	file(GLOB VCPKG_LIBRARIES "${LIB_DIR}/*.lib")
elseif("${CMAKE_BUILD_TYPE}" MATCHES "Release")
	set(LIB_DIR ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib)
	file(GLOB VCPKG_LIBRARIES "${LIB_DIR}/*.lib")
endif()

set(EXTERNAL_LIBS
    ${VCPKG_LIBRARIES}
    Qt5::Widgets
    Qt5::SerialPort
    )

set(EXTERNAL_INCLUDES
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5SerialPort_INCLUDE_DIRS}
    )