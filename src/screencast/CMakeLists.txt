


add_library(
    screencast
    STATIC
    DBusDecls.hpp
    PortalRequests.hpp
    PortalRequests.cpp
    Request.hpp
    Request.cpp
    ScreenCast.hpp
    ScreenCast.cpp
    Streaming.hpp

    # Generated code for sdbus-cpp
    portal/Portal.hpp
    portal/Portal.cpp
    portal/Request.hpp
    portal/ScreenCast.hpp
)

target_link_libraries(
    screencast
    PRIVATE
    sdbus-c++
)