#set(CMAKE_PREFIX_PATH "C:\\Users\\ermol\\AppData\\Local\\Programs\\Qt\\5.15.1\\msvc2019_64")
find_package(Qt6 COMPONENTS Widgets SerialPort REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation JSON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)

if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
	set(LIB_DIR ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug/lib)
	file(GLOB VCPKG_LIBRARIES "${LIB_DIR}/*.a")
elseif("${CMAKE_BUILD_TYPE}" MATCHES "Release")
	set(LIB_DIR ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib)
	file(GLOB VCPKG_LIBRARIES "${LIB_DIR}/*.a")
endif()

set(EXTERNAL_LIBS
	#${VCPKG_LIBRARIES}
	Poco::Foundation
	Poco::JSON
	Qt6::Core
    Qt6::Widgets
    Qt6::SerialPort
   )

set(EXTERNAL_INCLUDES
    ${Qt6Widgets_INCLUDE_DIRS}
    ${Qt6SerialPort_INCLUDE_DIRS}
   )