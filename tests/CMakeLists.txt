set(TARGET_NAME ${PROJECT_NAME}_unit_tests)

find_package(GTest CONFIG REQUIRED)
find_package(pthreads CONFIG)

include_directories(${EXTERNAL_INCLUDES})
add_subdirectory(unit)

enable_testing()

add_executable(${TARGET_NAME} unit_tests.cpp ${TEST_SOURCE_FILES})
target_link_libraries(${TARGET_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT}
                                             GTest::gtest
                                             GTest::gmock
                                             BUSINESS_LOGIC
                                             ${EXTERNAL_LIBS}
                                             )
