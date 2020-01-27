configure_file(version.h.in ${PROJECT_SOURCE_DIR}/businessLogic/version.h)

file(GLOB_RECURSE SOURCE_FILES *.cpp *.cc)
file(GLOB_RECURSE HEADER_FILES *.h *.hpp)

include_directories(${EXTERNAL_INCLUDES})

add_library(BUSINESS_LOGIC STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(BUSINESS_LOGIC ${EXTERNAL_LIBS})