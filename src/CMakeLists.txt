
add_executable(
    example
    main.cpp

    # XDG-portal
    Request.hpp
    Request.cpp
    ScreenCast.hpp
    ScreenCast.cpp
    PortalRequests.hpp
    PortalRequests.cpp
    Helpers.hpp
    Helpers.cpp

    # Generated code for sdbus-cpp
    portal/Portal.hpp
    portal/Portal.cpp
    portal/Request.hpp
    portal/ScreenCast.hpp

    # GUI
    StreamingWindow.hpp
    StreamingWindow.cpp

    example.qrc

)

# kde_target_enable_exceptions(example)


target_link_libraries(example PRIVATE sdbus-c++ Threads::Threads ${PKG_QT}::Core ${PKG_QT}::Quick)