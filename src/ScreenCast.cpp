
#include <algorithm>
#include <iostream>
#include <numeric>
#include <optional>
#include <sdbus-c++/IConnection.h>
#include <sdbus-c++/ProxyInterfaces.h>
#include <sdbus-c++/Types.h>
#include <sdbus-c++/sdbus-c++.h>
#include <stdexcept>
#include <string>

#include "portal/Portal.hpp"
#include "portal/ScreenCast.hpp"

#include "PortalRequests.hpp"
#include "ScreenCast.hpp"

using ScreenCastProxy = org::freedesktop::portal::ScreenCast_proxy;

namespace screencast
{

class ScreenCast::PImpl_ : protected DBus::ProxyInterfaces<ScreenCastProxy>
{
protected:
    const std::string token_;
    std::optional<std::string> connName_;

    const std::string &connName()
    {
        if (connName_) {
            return *connName_;
        }
        connName_ = getProxy().getConnection().getUniqueName();
        auto it = std::remove(connName_->begin(), connName_->end(), ':');
        connName_->erase(it, connName_->end());
        std::replace(connName_->begin(), connName_->end(), '.', '_');
        return *connName_;
    }
    std::string sessionToken()
    {
        return Portal::objectPath + "/session/" + connName() + '/' + token();
    }
    std::string requestToken()
    {
        return Portal::objectPath + "/request/" + connName() + '/' + token();
    }

public:
    PImpl_(const std::string &token)
        : ProxyInterfaces(DBus::createSessionBusConnection(), Portal::serviceName, Portal::objectPath)
        , token_(token)
    {
        registerProxy();
    }

    virtual ~PImpl_()
    {
        unregisterProxy();
    }

    inline const std::string &token()
    {
        return token_;
    }

    void createSession()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::map<std::string, sdbus::Variant> options;

        options["session_handle_token"] = token();
        options["handle_token"] = token();

        RequestSessionStart rs{getProxy().getConnection(), requestToken()};

        auto reqPath = this->CreateSession(options);

        auto res = rs.wait();
        if (res != sessionToken()) {
            throw std::runtime_error{"Invalid session_handle returned (\"" + res + "\", expected \"" + sessionToken() + "\")"};
        }
        std::cout << "Created session " << res << std::endl;
    }

    void selectSources(const Config &cfg)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::map<std::string, sdbus::Variant> options;
        options["handle_token"] = token();
        options["types"] = std::accumulate(cfg.sources.begin(), cfg.sources.end(), uint32_t(0), [](uint32_t a, SourceType b) {
            return a | static_cast<uint32_t>(b);
        });
        options["cursor_mode"] = static_cast<uint32_t>(cfg.cursor);
        options["persist_mode"] = static_cast<uint32_t>(cfg.persist);
        options["multiple"] = cfg.multiple;
        if (!cfg.restoreToken.empty()) {
            options["restore_token"] = cfg.restoreToken;
        }

        RequestSelectSources rs{getProxy().getConnection(), requestToken()};

        this->SelectSources(sessionToken(), options);
        rs.wait();
    }

    Streaming start(const std::string &window)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::map<std::string, sdbus::Variant> options;
        options["handle_token"] = token();

        RequestStart rs{getProxy().getConnection(), requestToken()};

        this->Start(sessionToken(), window, options);
        return rs.wait();
    }

    int open()
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::map<std::string, sdbus::Variant> options;

        // RequestStart rs{getProxy().getConnection(), requestToken()};

        // this->Start(sessionToken(), window, options);
        auto res = this->OpenPipeWireRemote(sessionToken(), options);
        return res.release();
        // return rs.wait();
    }
};

ScreenCast::ScreenCast(const std::string &token)
    : impl_(new PImpl_(token))
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

ScreenCast ScreenCast::create(const std::string &token, const Config &cfg)
{
    ScreenCast sc{token};
    auto &impl = *sc.impl_;
    impl.createSession();
    impl.selectSources(cfg);
    return sc;
}

Streaming ScreenCast::start(const std::string &window)
{
    return impl_->start(window);
}

int ScreenCast::open()
{
    return impl_->open();
}

ScreenCast::ScreenCast(ScreenCast &&) = default;
ScreenCast &ScreenCast::operator=(ScreenCast &&) = default;

ScreenCast::~ScreenCast()
{
}

} // namespace screencast
