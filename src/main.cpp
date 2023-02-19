#include <QGuiApplication>
// #include <QObject>
// #include <algorithm>
// #include <functional>
// #include <future>
// #include <iostream>
// #include <optional>
// #include <random>
// #include <stdexcept>
// #include <string>
// #include <thread>
// #include <vector>

#include "ScreenCast.hpp"
#include "Streaming.hpp"
#include "StreamingWindow.hpp"

// void dump(const screencast::Stream &s)
// {
//     std::cout << "Stream (id: " << s.id << ", size: " << s.size.x << "x" << s.size.y << ", sourceType: " << static_cast<uint32_t>(*s.sourceType) << ")"
//               << std::endl;
// }

// class MyApp : public QObject
// {
// public:
//     screencast::ScreenCast sc{screencast::ScreenCast::create(generateRandomString(8), {})};
//     MyApp(QObject &parent)
//         : QObject(&parent)
//     {
//     }

//     virtual ~MyApp()
//     {
//     }
// };

int main(int argc, char **argv)
{
    QGuiApplication app{argc, argv};

    gui::StreamingWindow win{app};
    // MyApp a{app};
    // auto res = a.sc.start();
    // for (auto &str : res.streams) {
    // dump(str);
    // }

    return app.exec();
}