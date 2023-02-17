
#include <sdbus-c++/IConnection.h>
#include <sdbus-c++/ProxyInterfaces.h>
#include <sdbus-c++/Types.h>
#include <sdbus-c++/sdbus-c++.h>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <optional>
#include <iostream>
// #include <QDebug>
// #include <QString>


#include "portal/ScreenCast.hpp"
#include "portal/Portal.hpp"

#include "ScreenCastWrapper.hpp"
#include "PortalRequests.hpp"


using ScreenCastProxy = org::freedesktop::portal::ScreenCast_proxy;

class ScreenCastWrapper::PImpl_: protected DBus::ProxyInterfaces<ScreenCastProxy> {
protected:
    const std::string token_;
    std::optional<std::string> connName_;


    const std::string& connName() {
        if(connName_) {
            return *connName_;
        }
        connName_ = getProxy().getConnection().getUniqueName();
        auto it = std::remove(connName_->begin(), connName_->end(), ':');
        connName_->erase(it, connName_->end());
        std::replace(connName_->begin(), connName_->end(), '.', '_');
        return *connName_;
    }
    std::string sessionToken() {
        return Portal::objectPath + "/session/" + connName() + '/' +  token();
    }
    std::string requestToken() {
        return Portal::objectPath + "/request/" + connName() + '/' +  token();
    }
public:
    PImpl_(const std::string& token):
        ProxyInterfaces(DBus::createSessionBusConnection(), Portal::serviceName, Portal::objectPath),
        token_(token)
    {
        registerProxy();
    }

    virtual ~PImpl_() {
        unregisterProxy();
    }

    inline const std::string& token() {return token_;}

    void createSession() {
        std::cout<< __PRETTY_FUNCTION__ << std::endl;
        std::map<std::string, sdbus::Variant> options;
        
        options["session_handle_token"] = token();
        options["handle_token"] = token();

        RequestSessionStart rs{getProxy().getConnection(), requestToken()};

        auto reqPath = this->CreateSession(options);

        auto res = rs.sessionToken();
        if(res != sessionToken()) {
            std::cerr << "Invalid session_handle returned" << std::endl;
        }
        std::cout << "Created session " << res << std::endl;
    }

};

ScreenCastWrapper::ScreenCastWrapper(const std::string& token):
    impl_(new PImpl_(token)) 
{
    std::cout<<__PRETTY_FUNCTION__<<std::endl;
    impl_->createSession();
}

ScreenCastWrapper::~ScreenCastWrapper() {

}