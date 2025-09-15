# Use the variable CORE_NAME defined in top-level CMakeLists.txt
add_library(${CORE_NAME} STATIC
    Source/card.cpp
    Source/deck.cpp
    Source/hand.cpp
    Source/player.cpp
    Source/dealer.cpp
    Source/game.cpp
    Include/card.h
    Include/deck.h
    Include/hand.h
    Include/player.h
    Include/dealer.h
    Include/game.h
)

target_include_directories(${CORE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(USE_QT)
    find_package(Qt6 COMPONENTS Core REQUIRED
        PATHS "$ENV{QT6_CMAKE}"
        NO_DEFAULT_PATH
    )
    target_link_libraries(${CORE_NAME} PUBLIC Qt6::Core)
endif()