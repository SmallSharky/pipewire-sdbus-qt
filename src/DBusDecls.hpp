#pragma once

#include <variant>
#include <map>
#include <string>


namespace sdbus {
    class IConnection;

    class Variant;
}

namespace DBus {
    using namespace sdbus;
    using VariantMap = std::map<std::string, Variant>;
}