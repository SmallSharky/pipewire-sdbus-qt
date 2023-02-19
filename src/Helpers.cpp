
#include "Helpers.hpp"

#include <random>
#include <string_view>

using namespace std::string_literals;

namespace helpers
{

std::string generateRandomString(std::size_t length)
{
    static constexpr std::string_view alphabet{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> distribution(0, alphabet.size() - 1);

    std::string randomString;
    for (std::size_t i = 0; i < length; ++i) {
        randomString += alphabet[distribution(generator)];
    }

    return randomString;
}

} // namespace helpers