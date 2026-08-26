# Tests CMake configuration
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/.. ${MOONLIGHT_COMMON_DIR}/src)

add_executable(test_apollo_protocol test_apollo_protocol.cpp)
target_link_libraries(test_apollo_protocol PRIVATE moonlight_common)
add_test(NAME ApolloProtocolTests COMMAND test_apollo_protocol)

add_executable(test_vdisplay
    test_vdisplay.cpp
    ../app/backend/vdisplay_manager.cpp
)
target_link_libraries(test_vdisplay PRIVATE Threads::Threads)
add_test(NAME VirtualDisplayTests COMMAND test_vdisplay)

add_executable(test_clipboard_sync test_clipboard_sync.cpp)
target_link_libraries(test_clipboard_sync PRIVATE Threads::Threads)
add_test(NAME ClipboardSyncTests COMMAND test_clipboard_sync)
