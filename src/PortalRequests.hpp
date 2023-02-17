#pragma once

#include "RequestWrapper.hpp"
#include <future>
#include <string>

class RequestSessionStart : protected RequestWrapper
{
protected:
    virtual void onResponse(uint32_t code, const DBus::VariantMap &data);

    std::promise<std::string> p_;
    std::future<std::string> f_{p_.get_future()};

public:
    using Connection = RequestWrapper::Connection;
    RequestSessionStart(Connection &conn, const std::string &path);

    std::string sessionToken();
    virtual ~RequestSessionStart();
};
