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

#include "ScreenCast.hpp"
#include "Streaming.hpp"

using namespace std::string_literals;

std::string generateRandomString(std::size_t length)
{
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> distribution(0, alphabet.size() - 1);

    std::string randomString;
    for (std::size_t i = 0; i < length; ++i) {
        randomString += alphabet[distribution(generator)];
    }

    return randomString;
}

void dump(const screencast::Stream &s)
{
    std::cout << "Stream (id: " << s.id << ", size: " << s.size.x << "x" << s.size.y << ", sourceType: " << static_cast<uint32_t>(s.sourceType) << ")"
              << std::endl;
}

class MyApp : public QObject
{
public:
    screencast::ScreenCast sc{screencast::ScreenCast::create(generateRandomString(8), {})};
    MyApp(QObject &parent)
        : QObject(&parent)
    {
    }

    virtual ~MyApp()
    {
    }
};

int main(int argc, char **argv)
{
    QCoreApplication app{argc, argv};
    MyApp a{app};
    auto res = a.sc.start();
    for (auto &str : res.streams) {
        dump(str);
    }

    return app.exec();
}