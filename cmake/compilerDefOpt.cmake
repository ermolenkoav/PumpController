# Defintion needed if you need eigen support
#add_definitions(-DEIGEN_DONT_VECTORIZE -DEIGEN_DONT_ALIGN)

###### Compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(GUI_TYPE WIN32)

    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MP /MT")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MP /MTd")

    if (VCPKG_TARGET_TRIPLET MATCHES "static")
        add_definitions(-D_UNICODE -DUNICODE -DwxUSE_GUI=1 -D__WXMSW__)
        set(CompilerFlags
            CMAKE_CXX_FLAGS
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_C_FLAGS
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELEASE
            )
        foreach(CompilerFlag ${CompilerFlags})
            string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
        endforeach()

    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    #set (CMAKE_CXX_FLAGS                "-Wextra -Wall -Wno-delete-non-virtual-dtor" -Werror=return-type)
    #set (CMAKE_CXX_FLAGS_DEBUG          "-g -O0 -DDEBUG")
    #set (CMAKE_CXX_FLAGS_RELEASE        "-O3")
    if(WARNINGS_AS_ERRORS)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werr")
    endif()

    if(OPT_ASAN)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(NOT EXISTS ${CMAKE_CXX_COMPILER})
        message( FATAL_ERROR "Clang++ not found. " )
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-register -Qunused-arguments")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-const-variable")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
endif()