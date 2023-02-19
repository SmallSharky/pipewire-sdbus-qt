#pragma once

#include "Request.hpp"
#include "Streaming.hpp"
#include <future>
#include <string>

namespace screencast
{

class RequestSessionStart : protected Request
{
protected:
    virtual void onResponse(uint32_t code, const DBus::VariantMap &data) final;

    std::promise<std::string> p_;
    std::future<std::string> f_{p_.get_future()};

public:
    using Connection = Request::Connection;
    RequestSessionStart(Connection &conn, const std::string &path);

    std::string wait();
    virtual ~RequestSessionStart();
};

class RequestSelectSources : protected Request
{
protected:
    virtual void onResponse(uint32_t code, const DBus::VariantMap &data) final;

    std::promise<void> p_;
    std::future<void> f_{p_.get_future()};

public:
    using Connection = Request::Connection;
    RequestSelectSources(Connection &conn, const std::string &path);

    void wait();
    virtual ~RequestSelectSources();
};

class RequestStart : protected Request
{
protected:
    virtual void onResponse(uint32_t code, const DBus::VariantMap &data) final;

    std::promise<Streaming> p_;
    std::future<Streaming> f_{p_.get_future()};

public:
    using Connection = Request::Connection;
    RequestStart(Connection &conn, const std::string &path);

    Streaming wait();

    virtual ~RequestStart();
};

} // namespace screencast