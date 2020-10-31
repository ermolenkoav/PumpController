find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(EXTERNAL_LIBS
    Qt5::Widgets
    Qt5::SerialPort
    )

set(EXTERNAL_INCLUDES
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5SerialPort_INCLUDE_DIRS}
    )