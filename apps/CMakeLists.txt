include_directories(${PROJECT_SOURCE_DIR}/)
include_directories("../businessLogic")

include_directories(${EXTERNAL_INCLUDES})

add_executable(${PROJECT_NAME} ${GUI_TYPE} main.cpp resources.rc)
target_link_libraries(${PROJECT_NAME} BUSINESS_LOGIC ${EXTERNAL_LIBS})