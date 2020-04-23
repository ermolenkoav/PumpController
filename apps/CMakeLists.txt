add_executable(${PROJECT_NAME} ${GUI_TYPE} main.cpp resources.rc)

target_link_libraries(${PROJECT_NAME} BUSINESS_LOGIC ${EXTERNAL_LIBS})