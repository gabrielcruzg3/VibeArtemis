cmake_minimum_required(VERSION 3.20)
project(VibeArtemis VERSION 0.2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

option(BUILD_TESTS "Build test suite" ON)

# Find System Dependencies
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

# Try finding Qt6 first, fallback to Qt5
find_package(Qt6 COMPONENTS Core Quick Network QuickControls2 Svg QUIET)
if (NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Core Quick Network QuickControls2 Svg QUIET)
endif()

# SDL2 & Opus
find_package(PkgConfig QUIET)
if (PKG_CONFIG_FOUND)
    pkg_check_modules(SDL2 sdl2)
    pkg_check_modules(SDL2_TTF SDL2_ttf)
    pkg_check_modules(OPUS opus)
    pkg_check_modules(FFMPEG libavcodec libavformat libswscale libavutil)
    pkg_check_modules(VAAPI libva)
    pkg_check_modules(VDPAU vdpau)
endif()

# Submodule directories
set(MOONLIGHT_COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/moonlight-common-c/moonlight-common-c)

# Build moonlight-common-c
file(GLOB COMMON_C_SOURCES
    ${MOONLIGHT_COMMON_DIR}/src/*.c
    ${MOONLIGHT_COMMON_DIR}/enet/*.c
    ${MOONLIGHT_COMMON_DIR}/reedsolomon/*.c
)
list(FILTER COMMON_C_SOURCES EXCLUDE REGEX ".*(RecorderCallbacks).*")

add_library(moonlight_common STATIC ${COMMON_C_SOURCES})
target_include_directories(moonlight_common PUBLIC
    ${MOONLIGHT_COMMON_DIR}/src
    ${MOONLIGHT_COMMON_DIR}/enet/include
    ${MOONLIGHT_COMMON_DIR}/reedsolomon
)
target_link_libraries(moonlight_common PUBLIC OpenSSL::Crypto OpenSSL::SSL Threads::Threads)
if (UNIX AND NOT APPLE)
    target_link_libraries(moonlight_common PUBLIC m)
endif()

# Artemis Core Subsystem Library (Apollo Client, Virtual Display Manager, Smart Clipboard)
set(VIBEARTEMIS_EXT_SOURCES
    app/backend/vdisplay_manager.cpp
    app/backend/clipboardsync.cpp
)

# Automated Unit Tests
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# CPack Packaging Configuration
set(CPACK_PACKAGE_NAME "vibeartemis")
set(CPACK_PACKAGE_VENDOR "VibeArtemis Team")
set(CPACK_PACKAGE_VERSION "0.2.0-alpha.1-agy")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "VibeArtemis: Next-Gen Apollo & Moonlight Desktop Client")
set(CPACK_PACKAGE_CONTACT "gabrielcruzg3")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "gabrielcruzg3")
set(CPACK_DEBIAN_PACKAGE_SECTION "video")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/gabrielcruzg3/VibeArtemis")

include(CPack)
