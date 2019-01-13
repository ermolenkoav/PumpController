#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------
set(TARGET_NAME ${PROJECT_NAME}-tests)

find_package(GTest MODULE REQUIRED)
find_package(Threads REQUIRED)

#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------

add_executable(${TARGET_NAME} mainwindowtests.cpp)

target_link_libraries(${TARGET_NAME} GTest::GTest GTest::Main Threads::Threads)

add_test(NAME runAllUnitTests COMMAND ${TARGET_NAME})