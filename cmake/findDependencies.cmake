find_package(Qt5 COMPONENTS Core Widgets SerialPort REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(EXTERNAL_LIBS
        Qt5::Core ${Qt5Core_LIBRARIES}
        Qt5::Gui ${Qt5Gui_LIBRARIES}
        Qt5::Widgets ${Qt5Widgets_LIBRARIES}
        Qt5::SerialPort ${Qt5SerialPort_LIBRARIES}
        jsoncpp_lib
        )

set(EXTERNAL_INCLUDES ${Qt5Core_INCLUDE_DIRS}
                      ${Qt5Gui_INCLUDE_DIRS} 
                      ${Qt5Widgets_INCLUDE_DIRS} 
                      ${Qt5SerialPort_INCLUDE_DIRS}
                      ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include
                      ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/gtest
                      )