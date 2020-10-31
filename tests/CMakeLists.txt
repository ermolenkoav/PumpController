set(TARGET_NAME ${PROJECT_NAME}_unit_tests)
find_package(Threads REQUIRED)
add_subdirectory(unit)

enable_testing()

add_executable(${TARGET_NAME} unit_tests.cpp ${TEST_SOURCE_FILES})

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/businessLogic)

target_link_libraries(${TARGET_NAME} PUBLIC  #${CMAKE_THREAD_LIBS_INIT}
                                             ${CMAKE_THREAD_LIBS_INIT}
                                             #GTest::gtest 
                                             #GTest::gmock
                                             gtest
                                             BUSINESS_LOGIC 
                                             ${EXTERNAL_LIBS}
                                             )