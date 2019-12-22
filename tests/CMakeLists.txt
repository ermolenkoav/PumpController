#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
set(TEST_TARGET_NAME ${PROJECT_NAME}-tests)
set(GTest GTest::GTest GTest::Main)

find_package(GTest MODULE REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets SerialPort REQUIRED)
find_package(cpprestsdk CONFIG REQUIRED)


#-------------------------------------------------------------------------------
#	TEST CODE
#-------------------------------------------------------------------------------
list(APPEND SOURCE_FILES_TST
	commonstability.cpp
	controllertests.cpp
	csvLogtests.cpp
	mainwindowtests.cpp
	modeltests.cpp
	settingstests.cpp
)

list(APPEND LIBRARIES
	Qt5::Core
	Qt5::Widgets 
	Qt5::SerialPort
	cpprestsdk::cpprest 
)

#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------
add_executable(${TEST_TARGET_NAME} ${SOURCE_FILES_TST})

target_link_libraries(${TEST_TARGET_NAME} PUBLIC ${LIBRARIES} ${GTest})

gtest_add_tests(
	TARGET  ${TEST_TARGET_NAME}
	SOURCES ${SOURCE_FILES_TST}
	EXTRA_ARGS --gtest-list-tests --build-and-test
)
