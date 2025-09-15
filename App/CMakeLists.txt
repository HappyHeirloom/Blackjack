# Always define the executable
add_executable(${APP_NAME}
    Source/main.cpp
)

# App needs to see Core’s public headers
target_include_directories(${APP_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/${CORE_NAME}/include
)

# Link against Core
target_link_libraries(${APP_NAME} PRIVATE ${CORE_NAME})

# Qt-enabled app
if(USE_QT)
    find_package(Qt6 COMPONENTS Widgets REQUIRED
        PATHS "$ENV{QT6_DIR}"
        NO_DEFAULT_PATH
    )

    target_sources(${APP_NAME} PRIVATE
        Source/main.cpp
    )

    target_link_libraries(${APP_NAME} PRIVATE Qt6::Widgets)

    # On Windows, run windeployqt after build to bundle the Qt DLLs.
    if (Qt6_FOUND AND WIN32)
        add_custom_command(TARGET ${APP_NAME} POST_BUILD
            COMMAND "${Qt6_DIR}/../../../bin/windeployqt.exe"
                "$<TARGET_FILE:${APP_NAME}>"
            COMMENT "Running windeployqt on ${APP_NAME}"
        )
    endif()

# Non-Qt app (pure C++ main)
else()
    target_sources(${APP_NAME} PRIVATE
        Source/main.cpp
    )
endif()
