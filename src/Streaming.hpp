#pragma once

#include <string>
#include <vector>

namespace screencast
{

enum class CursorMode : uint32_t { HIDDEN = 1 << 0, EMBEDDED = 1 << 1, METADATA = 1 << 2 };

enum class SourceType : uint32_t { MONITOR = 1 << 0, WINDOW = 1 << 1, VIRTUAL = 1 << 2 };

enum class PersistMode : uint32_t { NONE = 0, UNTIL_EXIT = 1, UNTIL_REVOKED = 2 };

struct Stream {
    struct Size {
        int32_t x;
        int32_t y;
    };

    uint32_t id;
    Size size;
    SourceType sourceType;
};

struct Streaming {
    std::string restoreToken;
    std::vector<Stream> streams;
};

} // namespace screencast
