configure_file(version.h.in		${CMAKE_CURRENT_SOURCE_DIR}/version.h)

include_directories(${EXTERNAL_INCLUDES})

file(GLOB_RECURSE BL_SOURCE_FILES *.cpp *.h *.hh)

add_library(BUSINESS_LOGIC STATIC ${BL_SOURCE_FILES})

#target_link_libraries(BUSINESS_LOGIC ${EXTERNAL_LIBS})