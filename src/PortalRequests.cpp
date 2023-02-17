

#include "PortalRequests.hpp"
#include "RequestWrapper.hpp"
#include <exception>
#include <sdbus-c++/Types.h>
#include <stdexcept>

#include <iostream>

RequestSessionStart::RequestSessionStart(Connection &conn, const std::string &path)
    : RequestWrapper(conn, path)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void RequestSessionStart::onResponse(uint32_t code, const DBus::VariantMap &data)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    try {
        if (code) {
            throw std::runtime_error("Request failed with code " + std::to_string(code));
        }
        const auto it = data.find("session_handle");
        if (it == data.end()) {
            throw std::runtime_error("No session_handle in response");
        }
        p_.set_value(it->second.get<std::string>());
    } catch (...) {
        p_.set_exception(std::current_exception());
    }
}

std::string RequestSessionStart::sessionToken()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    f_.wait();
    return f_.get();
}

RequestSessionStart::~RequestSessionStart()
{
}