set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc")
add_executable(${PROJECT_NAME} ${GUI_TYPE} main.cpp ${app_icon_resource_windows})

target_link_libraries(${PROJECT_NAME} PUBLIC BUSINESS_LOGIC ${EXTERNAL_LIBS})

add_custom_command(
        TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        -DHEADER_DIR:PATH="${PROJECT_SOURCE_DIR}/businessLogic"
        -DCACHE_DIR:PATH="${PROJECT_SOURCE_DIR}/cmake"
        -P "${PROJECT_SOURCE_DIR}/cmake/buildCounter.cmake"
)