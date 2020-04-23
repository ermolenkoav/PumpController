configure_file(version.h.in		${CMAKE_CURRENT_SOURCE_DIR}/version.h)

include_directories(${EXTERNAL_INCLUDES}) # For external qt folders

file(GLOB_RECURSE BL_SOURCE_FILES *.cpp *.h *.hh)

add_library(BUSINESS_LOGIC STATIC ${BL_SOURCE_FILES})