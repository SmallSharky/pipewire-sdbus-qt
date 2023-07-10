#pragma once

#include <memory>

class QObject;

namespace gui
{

class StreamingWindow
{
protected:
    class PImpl_;
    std::unique_ptr<PImpl_> impl_;

public:
    StreamingWindow(QObject &parent);
    virtual ~StreamingWindow();
};

} // namespace gui