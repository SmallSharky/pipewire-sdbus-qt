#include "RequestWrapper.hpp"
#include "portal/Portal.hpp"

#include <sdbus-c++/IConnection.h>
#include <sdbus-c++/ProxyInterfaces.h>
#include <sdbus-c++/Types.h>
#include <sdbus-c++/sdbus-c++.h>

#include <functional>

#include "DBusDecls.hpp"
#include "portal/Request.hpp"

using RequestProxy = org::freedesktop::portal::Request_proxy;

class RequestWrapper::PImpl_ : public DBus::ProxyInterfaces<RequestProxy>
{
public:
    using Handler = std::function<void(uint32_t, const DBus::VariantMap &)>;

    PImpl_(sdbus::IConnection &conn, const std::string &path, const Handler &h)
        : ProxyInterfaces(conn, Portal::serviceName, path)
        , handler_(h)
    {
        registerProxy();
    }

    virtual ~PImpl_()
    {
        unregisterProxy();
    }

protected:
    Handler handler_;
    virtual void onResponse(const uint32_t &code, const DBus::VariantMap &data)
    {
        handler_(code, data);
    }
};

RequestWrapper::RequestWrapper(Connection &conn, const std::string &path)
    : impl_(std::unique_ptr<PImpl_>(new PImpl_(conn, path, std::bind(&RequestWrapper::onResponse, this, std::placeholders::_1, std::placeholders::_2))))
{
}

RequestWrapper::~RequestWrapper()
{
}