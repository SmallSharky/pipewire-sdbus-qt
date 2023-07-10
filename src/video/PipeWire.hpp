#pragma once

#include <memory>
namespace video
{

namespace pipewire
{

// struct Context;
// // TODO: use FD type instead of int
// Context& context(int fd);

class Stream final
{
private:
    struct PImpl_;
    std::unique_ptr<PImpl_> impl_;

public:
    Stream(int32_t fd, uint32_t id);
    ~Stream();
};
}

}