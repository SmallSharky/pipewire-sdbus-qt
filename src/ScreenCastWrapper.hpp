#pragma once

#include "DBusDecls.hpp"
#include <memory>

class ScreenCastWrapper
{
protected:
    class PImpl_;
    std::unique_ptr<PImpl_> impl_;

public:
    enum class CursorMode : uint32_t { HIDDEN = 1 << 0, EMBEDDED = 1 << 1, METADATA = 1 << 2 };

    enum class SourceType : uint32_t { MONITOR = 1 << 0, WINDOW = 1 << 1, VIRTUAL = 1 << 2 };

    enum class PersistMode : uint32_t { NONE = 0, UNTIL_EXIT = 1, UNTIL_REVOKED = 2 };

    ScreenCastWrapper(const std::string &token);
    virtual ~ScreenCastWrapper();
};