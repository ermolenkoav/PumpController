set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

option(ENABLE_UNIT_TESTS  "Unit testing included"			         OFF)
option(ENABLE_CPACK       "CPack is enabled"				         ON)
option(USE_NSIS           "Use NSIS generator to produce installer"  ON)
option(WARNINGS_AS_ERRORS "Compiler warnings as errors"	             OFF)
option(ASAN_OPTIONS       "Use adress sanitizer (debug)"             OFF)