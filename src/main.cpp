#include <QCoreApplication>
#include <QObject>
#include <algorithm>
#include <functional>
#include <future>
#include <iostream>
#include <optional>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "ScreenCastWrapper.hpp"

using namespace std::string_literals;

std::string generateRandomString(std::size_t length)
{
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> distribution(0, alphabet.size() - 1);

    std::string randomString;
    for (std::size_t i = 0; i < length; ++i)
    {
        randomString += alphabet[distribution(generator)];
    }

    return randomString;
}

// using ScreenCastProxy = org::freedesktop::portal::ScreenCast_proxy;

// class ScreenCast: public DBus::ProxyInterfaces<ScreenCastProxy> {
// protected:
//     std::string token_;
//     DBus::ObjectPath path_;
//     DBus::ObjectPath registeredAs_;

    

//     uint32_t cursorModes_;
//     uint32_t sourceTypes_;


// public:


//     enum class CursorMode: uint32_t {
//         HIDDEN = 1<<0,
//         EMBEDDED = 1<<1,
//         METADATA = 1<<2
//     };

//     enum class SourceType: uint32_t {
//         MONITOR = 1<<0,
//         WINDOW = 1<<1,
//         VIRTUAL = 1<<2
//     };

//     enum class PersistMode: uint32_t {
//         NONE = 0,
//         UNTIL_EXIT = 1,
//         UNTIL_REVOKED = 2
//     };

    

//     ScreenCast(const std::string& token = generateRandomString(8)):
//         ProxyInterfaces(DBus::createSessionBusConnection(), Portal::serviceName, Portal::objectPath),
//         token_(token)
//     {
        
        
//         registerProxy();

//         std::map<std::string, sdbus::Variant> options;
//         auto cname = getProxy().getConnection().getUniqueName();
//         std::cout << "Connection name is" << cname << std::endl;
//         {
//             auto it = std::remove(cname.begin(), cname.end(), ':');
//             cname.erase(it, cname.end());
//             std::replace(cname.begin(), cname.end(), '.', '_');
//         }
//         std::string sessionToken = "/org/freedesktop/portal/desktop/session/" + cname + "/" + token;
//         std::string requestToken = "/org/freedesktop/portal/desktop/request/" + cname + "/" + token;
//         options["session_handle_token"] = token;
//         options["handle_token"] = token;
//         {
//             std::promise<std::string> sp;
//             auto spf = sp.get_future();
//             Request r{getProxy().getConnection(), requestToken, [&](const uint32_t& response, const std::map<std::string, sdbus::Variant>& results){
//                 std::cout << "Wee recieved";
//                 if(response) {
//                     sp.set_exception(nullptr);
//                 }
//                 for(auto& vp: results) {
//                     std::cout<<"Entry \"" << vp.first << "\"" << std::endl;
//                     if(vp.first == "session_handle"s) {
//                         sp.set_value(vp.second.get<std::string>());
//                     }
//                 }
//             }};

//             std::cout<<"Request handler created"<<std::endl;

//             auto reqPath = CreateSession(options);

//             std::cout << "Handler for session is: " << reqPath << std::endl;
            
//             cursorModes_ = AvailableCursorModes();
//             sourceTypes_ = AvailableSourceTypes();
//             spf.wait();
//             path_ = spf.get();
//             std::cout<<"DONE"<<std::endl;
//         }
        

        
//         {
//             std::promise<void> sp;
//             auto spf = sp.get_future();
//             Request r{getProxy().getConnection(), requestToken, [&](const uint32_t& response, const std::map<std::string, sdbus::Variant>& results){
//                 if(response) {
//                     sp.set_exception(nullptr);
//                 }
//                 std::cout << "Received results: " << results.size() << std::endl;
//                 for(auto& vp: results) {
//                     std::cout<<"Got res: " << vp.first << std::endl;
//                 } 
//                 sp.set_value();
//             }};
//             selectSources(SourceType::WINDOW, CursorMode::METADATA, PersistMode::UNTIL_EXIT);
//             spf.wait();
//         }


//         {
//             std::promise<void> sp;
//             auto spf = sp.get_future();
//             Request r{getProxy().getConnection(), requestToken, [&](const uint32_t& response, const std::map<std::string, sdbus::Variant>& results){
//                 if(response) {
//                     sp.set_exception(nullptr);
//                 }
//                 std::cout << "Received results: " << results.size() << std::endl;
//                 for(auto& vp: results) {
//                     std::cout<<"Got res: " << vp.first << " | " 
//                     << (vp.second.containsValueOfType<std::string>() ? vp.second.get<std::string>():""s) 
//                     << std::endl;
//                 } 
//                 sp.set_value();
//             }};
//             std::map<std::string, sdbus::Variant> options;
//             options["handle_token"] = token_;
//             Start(path_, "", options);
//             // selectSources(SourceType::MONITOR, CursorMode::METADATA, PersistMode::UNTIL_EXIT);
//             spf.wait();
//         }
        
        
//     }

//     ~ScreenCast() {
//         unregisterProxy();
//     }

//     const auto& getPath() const {
//         return path_;
//     }

//     bool cursorModeAvailable(CursorMode mode) {
//         return cursorModes_ & static_cast<uint32_t>(mode);
//     }

//     bool sourceTypeAvailable(SourceType type) {
//         return sourceTypes_ & static_cast<uint32_t>(type);
//     }

//     void selectSources(SourceType st, CursorMode cm, PersistMode pm) {
//         std::map<std::string, sdbus::Variant> options;
//         options["handle_token"] = token_;
//         options["types"] = static_cast<uint32_t>(st);
//         options["cursor_mode"] = static_cast<uint32_t>(cm);
//         options["persist_mode"] = static_cast<uint32_t>(pm);
//         auto res = SelectSources(path_, options);
//         std::cout << "SelectSources: " << res << std::endl;

//     }


// };


class MyApp: public QObject {
public:
    ScreenCastWrapper sc {generateRandomString(8)};
    MyApp(QObject& parent): QObject(&parent)
    {

    }

    virtual ~MyApp() {

    }
};


int main(int argc, char ** argv)
{

    QCoreApplication app{argc, argv};
    MyApp a{app};
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    // return app.run();

    return app.exec();
}