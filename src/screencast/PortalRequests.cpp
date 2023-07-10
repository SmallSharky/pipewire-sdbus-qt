

#include "PortalRequests.hpp"
#include "DBusDecls.hpp"
#include "Request.hpp"
#include <cstdint>
#include <exception>
#include <sdbus-c++/Types.h>
#include <stdexcept>

#include <iostream>

namespace
{

using Entry = DBus::Struct<uint32_t, DBus::VariantMap>;
using EntryArray = std::vector<Entry>;

using SizeType = DBus::Struct<int32_t, int32_t>;

} // namespace

namespace screencast
{

RequestSessionStart::RequestSessionStart(Connection &conn, const std::string &path)
    : Request(conn, path)
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

std::string RequestSessionStart::wait()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    f_.wait();
    return f_.get();
}

RequestSessionStart::~RequestSessionStart()
{
}

//-----------------------------------------------------

RequestSelectSources::RequestSelectSources(Connection &conn, const std::string &path)
    : Request(conn, path)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void RequestSelectSources::onResponse(uint32_t code, const DBus::VariantMap &data)
{
    std::ignore = data;
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    try {
        if (code) {
            throw std::runtime_error("Request failed with code " + std::to_string(code));
        }

        p_.set_value();
    } catch (...) {
        p_.set_exception(std::current_exception());
    }
}

void RequestSelectSources::wait()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    f_.wait();
}

RequestSelectSources::~RequestSelectSources()
{
}

//-----------------------------------------------------

RequestStart::RequestStart(Connection &conn, const std::string &path)
    : Request(conn, path)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void RequestStart::onResponse(uint32_t code, const DBus::VariantMap &data)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    try {
        if (code) {
            throw std::runtime_error("Request failed with code " + std::to_string(code));
        }
        Streaming st;
        auto it = data.find("streams");
        if (it == data.end()) {
            throw std::runtime_error("No streams provided");
        }

        const auto &entries = it->second.get<EntryArray>();
        for (auto &entry : entries) {
            Stream s{.id = entry.get<0>()};
            const auto &eParams = entry.get<1>();
            auto sizeIt = eParams.find("size");
            if (sizeIt != eParams.end()) {
                const auto &sizeVal = sizeIt->second.get<SizeType>();
                s.size = {.x = sizeVal.get<0>(), .y = sizeVal.get<1>()};
            }
            auto stIt = eParams.find("source_type");
            if (stIt != eParams.end()) {
                s.sourceType = static_cast<SourceType>(stIt->second.get<uint32_t>());
            }

            st.streams.emplace_back(s);
        }

        p_.set_value(std::move(st));
    } catch (...) {
        p_.set_exception(std::current_exception());
    }
}

Streaming RequestStart::wait()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    f_.wait();
    return f_.get();
}

RequestStart::~RequestStart()
{
}

} // namespace screencast