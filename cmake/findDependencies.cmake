find_package(Qt5 COMPONENTS Core Widgets SerialPort REQUIRED)
find_package(cpprestsdk CONFIG REQUIRED)
#find_package(Cuda REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(external_includes ${Qt5Core_INCLUDE_DIRS}
                      ${Qt5Gui_INCLUDE_DIRS} 
                      ${Qt5Widgets_INCLUDE_DIRS} 
                      ${Qt5SerialPort_INCLUDE_DIRS}
                      ${CPPREST_INCLUDE_DIRS}
                      )

set(EXTERNAL_LIBS
        Qt5::Core ${Qt5Core_LIBRARIES}
        Qt5::Gui ${Qt5Gui_LIBRARIES}
        Qt5::Widgets ${Qt5Widgets_LIBRARIES}
        Qt5::SerialPort ${Qt5SerialPort_LIBRARIES}
        cpprestsdk::cpprest 
        )
