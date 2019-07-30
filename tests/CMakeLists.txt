#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
set(TEST_TARGET_NAME ${PROJECT_NAME}-tests)
set(GTest GTest::GTest GTest::Main)

find_package(GTest MODULE REQUIRED)

#-------------------------------------------------------------------------------
#	TEST CODE
#-------------------------------------------------------------------------------
list(APPEND SOURCE_FILES
	commonstability.cpp
	mainwindowtests.cpp
)

#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------
add_executable(${TEST_TARGET_NAME} ${SOURCE_FILES})
target_link_libraries(${TEST_TARGET_NAME} PRIVATE ${GTest})

gtest_add_tests(
	TARGET  ${TEST_TARGET_NAME}
	SOURCES ${SOURCE_FILES}
	EXTRA_ARGS --gtest-list-tests --build-and-test
)