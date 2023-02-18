
add_executable(
    example 
    main.cpp
    Request.hpp
    Request.cpp
    ScreenCast.hpp
    ScreenCast.cpp
    PortalRequests.hpp
    PortalRequests.cpp


    portal/Portal.hpp
    portal/Portal.cpp
    portal/Request.hpp
    portal/ScreenCast.hpp
)

# kde_target_enable_exceptions(example)


target_link_libraries(example PRIVATE SDBusCpp::sdbus-c++ Threads::Threads ${PKG_QT}::Core)