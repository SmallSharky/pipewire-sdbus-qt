

#include "StreamingWindow.hpp"
#include "Helpers.hpp"
#include "ScreenCast.hpp"

#include <QLoggingCategory>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>

namespace gui
{

class StreamingWindow::PImpl_ : public QObject
{
protected:
    QQmlApplicationEngine *qmlEng_;

public:
    PImpl_(QObject &parent)
        : QObject(&parent)
        , qmlEng_(new QQmlApplicationEngine(this))
    {
        qmlEng_->rootContext()->setContextProperty(QStringLiteral("app"), this);
        qmlEng_->load(QUrl(QStringLiteral("qrc:/StreamingWindow.qml")));
    }
};

StreamingWindow::StreamingWindow(QObject &parent)
    : impl_(new PImpl_(parent))
{
    screencast::ScreenCast sc{screencast::ScreenCast::create(helpers::generateRandomString(8), {})};
}

StreamingWindow::~StreamingWindow()
{
}

} // namespace gui
