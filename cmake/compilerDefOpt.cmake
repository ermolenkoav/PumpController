###### Compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" OR "Clang")
    set(GUI_TYPE WIN32)

    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MP /MT /UTF-8")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MP /MTd /UTF-8")
endif()
#[[
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set (CMAKE_CXX_FLAGS                "-Wextra -Wno-delete-non-virtual-dtor -Werror=return-type")
    set (CMAKE_CXX_FLAGS_DEBUG          "-fPIC -Wall -g -O0 -DDEBUG")
    set (CMAKE_CXX_FLAGS_RELEASE        "-fPIC -O3")

    if(WARNINGS_AS_ERRORS)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-Werror")
    endif()

    if(OPT_ASAN)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(NOT EXISTS ${CMAKE_CXX_COMPILER})
        message( FATAL_ERROR "Clang++ not found. " )
    endif()

    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register -Qunused-arguments")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-const-variable")
    set (CMAKE_CXX_FLAGS_DEBUG          "-fPIC -Wall -g -O0 -DDEBUG")
    set (CMAKE_CXX_FLAGS_RELEASE        "-fPIC -O3")

endif()]]