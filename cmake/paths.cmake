if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_PREFIX_PATH /usr/lib/x86_64-linux-gnu/cmake/)
    set(GTest_DIR /usr/lib/)
endif()
#set(EXECUTABLE_OUTPUT_PATH ${OPT_BIN_DIR})
#set(LIBRARY_OUTPUT_PATH    ${OPT_BIN_DIR})


#set(OPT_BIN_DIR ${PROJECT_BINARY_DIR}/../bin${PLATFORM})

#set(EXECUTABLE_OUTPUT_PATH ${OPT_BIN_DIR})

#needed when dynamic linking
#set(LIBRARY_OUTPUT_PATH    ${OPT_BIN_DIR})

# #default test_data_location
# set(TEST_DATA_DIR "${PROJECT_SOURCE_DIR}/../test-images")

# #TODO: check if an env variable exists with the name and use it instead to be able to move test data easily
# add_definitions(-DTEST_DATA_DIR="${TEST_DATA_DIR}")
