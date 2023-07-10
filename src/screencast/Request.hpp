#pragma once

#include <map>
#include <memory>

#include "DBusDecls.hpp"

namespace screencast
{

class Request
{
protected:
    class PImpl_;
    std::unique_ptr<PImpl_> impl_;
    virtual void onResponse(uint32_t code, const DBus::VariantMap &data) = 0;

public:
    using Connection = DBus::IConnection;
    Request(Connection &conn, const std::string &path);
    virtual ~Request();
};

} // namespace screencast