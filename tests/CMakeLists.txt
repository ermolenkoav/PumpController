find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(${external_includes})

add_subdirectory(unit)

set(TARGET_NAME ${PROJECT_NAME}_unit_tests)

### TEST MODULE COMMON ###
add_executable(${TARGET_NAME} tests_all.cpp ${srcs_tst_common_all} )
target_link_libraries(${TARGET_NAME} ${GTEST_BOTH_LIBRARIES} common ${EXTERNAL_LIBS} )
