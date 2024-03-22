find_package(GTest CONFIG REQUIRED)

set(TARGET_NAME ${PROJECT_NAME}UnitTests)

add_subdirectory(unit)

enable_testing()

add_executable(${TARGET_NAME} unit_tests.cpp ${TEST_SOURCE_FILES})

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/businessLogic)

target_link_libraries(${TARGET_NAME} PUBLIC ${BUSINESS_LOGIC}
                                            ${EXTERNAL_LIBS}
                                            GTest::gmock GTest::gtest
                     )