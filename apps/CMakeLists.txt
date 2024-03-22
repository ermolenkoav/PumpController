set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc")

qt_add_executable(${PROJECT_NAME} ${GUI_TYPE} main.cpp ${APP_ICON_RESOURCE_WINDOWS})

target_link_libraries(${PROJECT_NAME} PRIVATE BUSINESS_LOGIC ${EXTERNAL_LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE ON
)

add_custom_command(
        TARGET ${PROJECT_NAME}
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        -DHEADER_DIR:PATH="${PROJECT_SOURCE_DIR}/businessLogic"
        -DCACHE_DIR:PATH="${PROJECT_SOURCE_DIR}/cmake"
        -P "${PROJECT_SOURCE_DIR}/cmake/buildCounter.cmake"
)