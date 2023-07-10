#include "gui/StreamingWindow.hpp"
#include "screencast/ScreenCast.hpp"
#include "screencast/Streaming.hpp"
#include <QGuiApplication>

int main(int argc, char **argv)
{
    QGuiApplication app{argc, argv};

    gui::StreamingWindow win{app};

    return app.exec();
}