#include "ScreenCast.hpp"
#include "Streaming.hpp"
#include "StreamingWindow.hpp"
#include <QGuiApplication>

int main(int argc, char **argv)
{
    QGuiApplication app{argc, argv};

    gui::StreamingWindow win{app};

    return app.exec();
}