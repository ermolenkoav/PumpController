set(HEADER_FILE "${HEADER_DIR}/version.h")
set(CACHE_FILE "${CACHE_DIR}/BuildNumberCache.txt")

IF(EXISTS ${CACHE_FILE})
    file(READ ${CACHE_FILE} BUILD_NUMBER)
    math(EXPR BUILD_NUMBER "${BUILD_NUMBER}+1")
ELSE()
    set(BUILD_NUMBER "1")
ENDIF()

#Update the cache
file(WRITE ${CACHE_FILE} "${BUILD_NUMBER}")

#Create the header
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    file(READ ${HEADER_FILE} DEF_LIST)
    string(REGEX REPLACE  "#define BUILD_NUMBER(\t)+[0-9]+"	"#define BUILD_NUMBER\t\t\t\t\t${BUILD_NUMBER}" DEF_LIST ${DEF_LIST})
    file(WRITE ${HEADER_FILE} ${DEF_LIST})
endif()

#Feedback
message("Build number: ${BUILD_NUMBER}")