add_executable(${PROJECT_NAME} ${GUI_TYPE} main.cpp resources.rc)

target_link_libraries(${PROJECT_NAME} PUBLIC BUSINESS_LOGIC ${EXTERNAL_LIBS})

add_custom_command(
        TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        -DHEADER_DIR:PATH="${PROJECT_SOURCE_DIR}/businessLogic"
        -DCACHE_DIR:PATH="${PROJECT_SOURCE_DIR}/cmake"
        -P "${PROJECT_SOURCE_DIR}/cmake/buildCounter.cmake"
)