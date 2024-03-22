configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h)

set(BUSINESS_LOGIC_SOURCE_CODE
        mainwindow.h
        mainwindow.cpp
        controller.h
        controller.cpp
        settings.h
        settings.cpp
        model.h
        model.cpp
        version.h
        pch.h
        csvLog.h
        csvLog.cpp
    )

add_library(BUSINESS_LOGIC STATIC ${BUSINESS_LOGIC_SOURCE_CODE} ${EXTERNAL_INCLUDES})

target_link_libraries(BUSINESS_LOGIC ${EXTERNAL_LIBS})
