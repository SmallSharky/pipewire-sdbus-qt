

add_library(
    video
    STATIC
    PipeWire.hpp
    PipeWire.cpp
)


target_link_libraries(video PRIVATE PkgConfig::libva PkgConfig::PipeWire)
