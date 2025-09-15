cmake_minimum_required(VERSION 3.24) # 3.24+ recommended for full C++23 support

# ========================
# Project configuration
# ========================
set(PROJECT_NAME Blackjack)
set(CORE_NAME Core)
set(APP_NAME App)

# Toggle Qt support (ON/OFF)
set(USE_QT OFF)   # <--- change to ON to ENABLE Qt globally

project(${PROJECT_NAME})
# ========================

# ========================
# Compiler settings
# ========================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Use standard C++23, not compiler-specific extensions

if(MSVC)
    set(CMAKE_MSVC_STANDARD_COMPLIANCE ON)
endif()
# ========================

# ========================
# Optional vcpkg toolchain
# ========================
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
# ========================


# ========================
# Qt settings
# ========================
if(USE_QT)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
endif()
# ========================

# ========================
# Subprojects
# ========================
add_subdirectory(${CORE_NAME})
add_subdirectory(${APP_NAME})
# ========================
