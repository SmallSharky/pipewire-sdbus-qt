
/*
 * This file was automatically generated by sdbus-c++-xml2cpp; DO NOT EDIT!
 */

#ifndef __sdbuscpp__ScreenCast_hpp__proxy__H__
#define __sdbuscpp__ScreenCast_hpp__proxy__H__

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>

namespace org
{
namespace freedesktop
{
namespace portal
{

class ScreenCast_proxy
{
public:
    static constexpr const char *INTERFACE_NAME = "org.freedesktop.portal.ScreenCast";

protected:
    ScreenCast_proxy(sdbus::IProxy &proxy)
        : proxy_(proxy)
    {
    }

    ~ScreenCast_proxy() = default;

public:
    sdbus::ObjectPath CreateSession(const std::map<std::string, sdbus::Variant> &options)
    {
        sdbus::ObjectPath result;
        proxy_.callMethod("CreateSession").onInterface(INTERFACE_NAME).withArguments(options).storeResultsTo(result);
        return result;
    }

    sdbus::ObjectPath SelectSources(const sdbus::ObjectPath &session_handle, const std::map<std::string, sdbus::Variant> &options)
    {
        sdbus::ObjectPath result;
        proxy_.callMethod("SelectSources").onInterface(INTERFACE_NAME).withArguments(session_handle, options).storeResultsTo(result);
        return result;
    }

    sdbus::ObjectPath Start(const sdbus::ObjectPath &session_handle, const std::string &parent_window, const std::map<std::string, sdbus::Variant> &options)
    {
        sdbus::ObjectPath result;
        proxy_.callMethod("Start").onInterface(INTERFACE_NAME).withArguments(session_handle, parent_window, options).storeResultsTo(result);
        return result;
    }

    sdbus::UnixFd OpenPipeWireRemote(const sdbus::ObjectPath &session_handle, const std::map<std::string, sdbus::Variant> &options)
    {
        sdbus::UnixFd result;
        proxy_.callMethod("OpenPipeWireRemote").onInterface(INTERFACE_NAME).withArguments(session_handle, options).storeResultsTo(result);
        return result;
    }

public:
    uint32_t AvailableSourceTypes()
    {
        return proxy_.getProperty("AvailableSourceTypes").onInterface(INTERFACE_NAME);
    }

    uint32_t AvailableCursorModes()
    {
        return proxy_.getProperty("AvailableCursorModes").onInterface(INTERFACE_NAME);
    }

    uint32_t version()
    {
        return proxy_.getProperty("version").onInterface(INTERFACE_NAME);
    }

private:
    sdbus::IProxy &proxy_;
};

}
}
} // namespaces

#endif
