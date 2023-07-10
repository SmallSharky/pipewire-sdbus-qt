
#include "helpers/Strings.hpp"
#include "screencast/ScreenCast.hpp"
#include "screencast/Streaming.hpp"
#include "video/PipeWire.hpp"

#include <QApplication>
#include <QDebug>

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app{argc, argv};

    auto clientid = helpers::generateRandomString(8);
    auto cast{screencast::ScreenCast::create(clientid, {})};

    qDebug() << "Requesting stream...";
    std::optional<screencast::Streaming> streaming;
    try {
        streaming.emplace(std::move(cast.start()));

    } catch (std::exception &e) {
        qDebug() << e.what();
    }
    if (!streaming) {
        qDebug() << "Failed to start streaming";
        return -1;
    }

    qDebug() << "There are " << streaming->streams.size() << " streams";
    int fd = cast.open();
    uint32_t streamId = streaming->streams.front().id;

    video::pipewire::Stream s{fd, streamId};

    return app.exec();
}