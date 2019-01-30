#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
set(TARGET_NAME ${PROJECT_NAME}-tests)

find_package(GTest MODULE REQUIRED)

#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------

add_executable(${TARGET_NAME} mainwindowtests.cpp)

target_link_libraries(${TARGET_NAME} PRIVATE GTest::GTest GTest::Main)

add_test(NAME runAllUnitTests COMMAND ${TARGET_NAME})