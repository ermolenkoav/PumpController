if (CMAKE_BUILD_TYPE MATCHES Debug)
#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
set(TEST_TARGET_NAME ${PROJECT_NAME}-tests)

find_package(GTest MODULE REQUIRED)

enable_testing()
#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------
message("Enable testing.")

add_executable(${TEST_TARGET_NAME} mainwindowtests.cpp)

target_link_libraries(${TEST_TARGET_NAME} PRIVATE GTest::GTest GTest::Main)

add_test(NAME runAllUnitTests COMMAND ${TEST_TARGET_NAME})

endif()
