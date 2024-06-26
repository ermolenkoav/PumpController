if("${CMAKE_BUILD_TYPE}" MATCHES     "Release")
    option(ENABLE_CPACK              "CPack is enabled"				             ON)
    option(USE_NSIS                  "Use NSIS generator to produce installer"   ON)
elseif("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    option(ENABLE_UNIT_TESTS         "Unit testing included"			         ON)
    option(WARNINGS_AS_ERRORS        "Compiler warnings as errors"	             OFF)
    option(OPT_ASAN                  "Address Sanitizer"	                     OFF)
endif()


