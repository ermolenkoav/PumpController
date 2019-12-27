find_package(GTest REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets SerialPort REQUIRED)
#set(CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu/cmake/)
find_package(cpprestsdk CONFIG REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(external_includes ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5SerialPort_INCLUDE_DIRS})

set(external_libs #${Qt5Widgets_LIBRARIES} "-lpthread"
        Qt5::Core
        Qt5::Widgets
        Qt5::SerialPort
        cpprestsdk::cpprest )
