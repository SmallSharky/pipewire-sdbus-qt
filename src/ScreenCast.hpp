#pragma once

#include "DBusDecls.hpp"
#include "Streaming.hpp"
#include <memory>
#include <optional>
#include <vector>

namespace screencast
{

class ScreenCast
{
protected:
    class PImpl_;
    std::unique_ptr<PImpl_> impl_;

    ScreenCast(const std::string &token);

public:
    struct Config {
        CursorMode cursor{CursorMode::METADATA};
        PersistMode persist{PersistMode::NONE};
        std::vector<SourceType> sources{SourceType::MONITOR, SourceType::WINDOW};
        bool multiple{false};
        std::string restoreToken{};
    };

    /*
     * Here are functions to obtain ScreenCast properly.
     * And Start function which takes no parameters.
     */
    static ScreenCast create(const std::string &token, const Config &cfg);

    Streaming start(const std::string &window = "");

    ScreenCast(const ScreenCast &) = delete;
    ScreenCast(ScreenCast &&) = default;
    virtual ~ScreenCast();
};

} // namespace screencast
