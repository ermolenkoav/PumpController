include_directories(${PROJECT_SOURCE_DIR}/)
include_directories("../common")

include_directories(${external_includes})

add_executable(${PROJECT_NAME} ${GUI_TYPE} main.cpp resources.rc)
target_link_libraries(${PROJECT_NAME} common ${external_libs})
