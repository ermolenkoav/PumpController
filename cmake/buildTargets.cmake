include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(businessLogic)
add_subdirectory(apps)
if(ENABLE_UNIT_TESTS)
	add_subdirectory(tests)
endif(ENABLE_UNIT_TESTS)