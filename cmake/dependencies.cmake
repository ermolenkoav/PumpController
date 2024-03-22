find_package(Qt6 REQUIRED COMPONENTS Core Widgets SerialPort)
find_package(Poco REQUIRED COMPONENTS Foundation Json)
qt_standard_project_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(EXTERNAL_INCLUDES
		${Qt6Widgets_INCLUDE_DIRS}
		${Qt6SerialPort_INCLUDE_DIRS}
)

set(EXTERNAL_LIBS
		Poco::Foundation
		Poco::JSON
		Qt6::Core
		Qt6::Widgets
		Qt6::SerialPort
)
