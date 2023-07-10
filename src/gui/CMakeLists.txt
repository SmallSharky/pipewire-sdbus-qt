


add_library(
    gui 
    OBJECT
    StreamingWindow.hpp
    StreamingWindow.cpp
    example.qrc
)

target_link_libraries(
    gui
    PRIVATE
    ${PKG_QT}::Core ${PKG_QT}::Quick  ${PKG_QT}::Qml ${PKG_QT}::Gui ${PKG_QT}::QuickControls2 ${PKG_QT}::Widgets 
    KF5::Kirigami2 KF5::I18n 
    screencast
)

# target_link_options(gui PRIVATE "-Wl,--whole-archive")
# set_target_properties(gui PROPERTIES LINK_FLAGS "-Wl,--whole-archive")