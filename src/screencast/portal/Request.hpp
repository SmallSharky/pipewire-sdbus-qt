
/*
 * This file was automatically generated by sdbus-c++-xml2cpp; DO NOT EDIT!
 */

#ifndef __sdbuscpp_____Request_hpp__proxy__H__
#define __sdbuscpp_____Request_hpp__proxy__H__

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>

namespace org
{
namespace freedesktop
{
namespace portal
{

class Request_proxy
{
public:
    static constexpr const char *INTERFACE_NAME = "org.freedesktop.portal.Request";

protected:
    Request_proxy(sdbus::IProxy &proxy)
        : proxy_(proxy)
    {
        proxy_.uponSignal("Response").onInterface(INTERFACE_NAME).call([this](const uint32_t &response, const std::map<std::string, sdbus::Variant> &results) {
            this->onResponse(response, results);
        });
    }

    ~Request_proxy() = default;

    virtual void onResponse(const uint32_t &response, const std::map<std::string, sdbus::Variant> &results) = 0;

public:
    void Close()
    {
        proxy_.callMethod("Close").onInterface(INTERFACE_NAME);
    }

private:
    sdbus::IProxy &proxy_;
};

}
}
} // namespaces

#endif
