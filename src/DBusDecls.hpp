#pragma once

#include <map>
#include <string>
#include <variant>

namespace sdbus
{
class IConnection;

class Variant;
}

namespace DBus
{
using namespace sdbus;
using VariantMap = std::map<std::string, Variant>;
}