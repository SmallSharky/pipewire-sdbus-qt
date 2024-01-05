


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(helpers)
add_subdirectory(video)
add_subdirectory(screencast)
add_subdirectory(gui)

#################################################

add_executable(
    example-gui
    example_gui.cpp
)

target_link_libraries(
    example-gui
    PRIVATE
    gui video helpers screencast
    sdbus-c++
    Threads::Threads
    ${PKG_QT}::Gui
)

#################################################

add_executable(
    example-pipewire
    example_pipewire.cpp
)

target_link_libraries(
    example-pipewire
    PRIVATE
    gui video helpers screencast
    sdbus-c++
    Threads::Threads
    ${PKG_QT}::Gui ${PKG_QT}::Widgets
)

#################################################

add_executable(
    example-gst
    example_gst.cpp
)

target_link_libraries(
    example-gst
    PRIVATE
    gui video helpers screencast
    sdbus-c++
    Threads::Threads
    PkgConfig::GStreamer PkgConfig::PipeWire
    ${PKG_QT}::Gui ${PKG_QT}::Widgets
)