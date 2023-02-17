#pragma once

#include <memory>
#include <map>


#include "DBusDecls.hpp"

class RequestWrapper {
protected:
    class PImpl_;
    std::unique_ptr<PImpl_> impl_;
    virtual void onResponse(uint32_t code, const DBus::VariantMap& data) = 0;

public:
    using Connection = DBus::IConnection;
    RequestWrapper(Connection& conn, const std::string& path);
    virtual ~RequestWrapper();
};


