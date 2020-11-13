set(CMAKE_PREFIX_PATH "C:\\Users\\ermol\\AppData\\Local\\Programs\\Qt\\5.15.1\\msvc2019_64")
find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)

if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
	set(LIB_DIR ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug/lib)
	link_directories(${LIB_DIR})
elseif("${CMAKE_BUILD_TYPE}" MATCHES "Release")
	set(LIB_DIR ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib)
	link_directories(${LIB_DIR})
endif()

set(EXTERNAL_LIBS
    Qt5::Widgets
    Qt5::SerialPort
   )

set(EXTERNAL_INCLUDES
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5SerialPort_INCLUDE_DIRS}
   )

add_subdirectory(businessLogic)
add_subdirectory(apps)
if(ENABLE_UNIT_TESTS)
	add_subdirectory(tests)
endif(ENABLE_UNIT_TESTS)