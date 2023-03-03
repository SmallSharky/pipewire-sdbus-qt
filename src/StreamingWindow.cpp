

#include "StreamingWindow.hpp"
#include "Helpers.hpp"
#include "ScreenCast.hpp"

#include <QDebug>
#include <QLoggingCategory>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>
#include <QTimer>

namespace gui
{

class StreamingWindow::PImpl_ : public QObject
{
    Q_OBJECT
protected:
    QQmlApplicationEngine *qmlEng_;
    std::optional<screencast::ScreenCast> cast_;
    std::optional<screencast::Streaming> streaming_;

public:
    PImpl_(QObject &parent)
        : QObject(&parent)
        , qmlEng_(new QQmlApplicationEngine(this))
    {
        qmlEng_->rootContext()->setContextProperty(QStringLiteral("app"), this);
        qmlEng_->load(QUrl(QStringLiteral("qrc:/StreamingWindow.qml")));
    }

    Q_SCRIPTABLE void selectSource()
    {
        if (cast_) {
            qDebug() << "Stream already exists. Destroying...";
        }
        if (streaming_) {
            qDebug() << "There are some streams probably. Destroying...";
            const auto windows{qmlEng_->rootObjects()};
            for (const auto &stream : streaming_->streams) {
                for (auto win : windows) {
                    auto mo = win->metaObject();
                    mo->invokeMethod(win, "removeStream", Q_ARG(QVariant, QVariant::fromValue<uint32_t>(stream.id)));
                }
            }
        }
        qDebug() << "Connecting to desktop portal...";
        auto tmp{screencast::ScreenCast::create(helpers::generateRandomString(8), {})};
        cast_.emplace(std::move(tmp));
        qDebug() << "Requesting stream...";
        // std::optional<screencast::Streaming> s;
        try {
            streaming_.emplace(std::move(cast_->start()));

        } catch (std::exception &e) {
            qDebug() << e.what();
        }
        if (!streaming_) {
            qDebug() << "Failed to start streaming";
            return;
        }

        qDebug() << "There are " << streaming_->streams.size() << " streams";
        const auto windows{qmlEng_->rootObjects()};
        int fd = cast_->open();
        for (const auto &stream : streaming_->streams) {
            for (auto win : windows) {
                qDebug() << "Opening stream " << stream.id << " with fd " << fd;
                auto mo = win->metaObject();
                mo->invokeMethod(win,
                                 "addStream",
                                 Q_ARG(QVariant, QVariant::fromValue<uint32_t>(stream.id)),
                                 Q_ARG(QVariant, QStringLiteral("")),
                                 Q_ARG(QVariant, fd));
            }
        }
    }
};

StreamingWindow::StreamingWindow(QObject &parent)
    : impl_(new PImpl_(parent))
{
}

StreamingWindow::~StreamingWindow()
{
}

} // namespace gui

#include "StreamingWindow.moc"
