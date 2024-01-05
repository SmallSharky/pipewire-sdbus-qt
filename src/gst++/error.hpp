void printMessageTypes()
{
    qDebug() << "GST_MESSAGE_UNKNOWN: " << GST_MESSAGE_UNKNOWN;
    qDebug() << "GST_MESSAGE_EOS: " << GST_MESSAGE_EOS;
    qDebug() << "GST_MESSAGE_ERROR: " << GST_MESSAGE_ERROR;
    qDebug() << "GST_MESSAGE_WARNING: " << GST_MESSAGE_WARNING;
    qDebug() << "GST_MESSAGE_INFO: " << GST_MESSAGE_INFO;
    qDebug() << "GST_MESSAGE_TAG: " << GST_MESSAGE_TAG;
    qDebug() << "GST_MESSAGE_BUFFERING: " << GST_MESSAGE_BUFFERING;
    qDebug() << "GST_MESSAGE_STATE_CHANGED: " << GST_MESSAGE_STATE_CHANGED;
    qDebug() << "GST_MESSAGE_STATE_DIRTY: " << GST_MESSAGE_STATE_DIRTY;
    qDebug() << "GST_MESSAGE_STEP_DONE: " << GST_MESSAGE_STEP_DONE;
    qDebug() << "GST_MESSAGE_CLOCK_PROVIDE: " << GST_MESSAGE_CLOCK_PROVIDE;
    qDebug() << "GST_MESSAGE_CLOCK_LOST: " << GST_MESSAGE_CLOCK_LOST;
    qDebug() << "GST_MESSAGE_NEW_CLOCK: " << GST_MESSAGE_NEW_CLOCK;
    qDebug() << "GST_MESSAGE_STREAM_START: " << GST_MESSAGE_STREAM_START;
    qDebug() << "GST_MESSAGE_NEED_CONTEXT: " << GST_MESSAGE_NEED_CONTEXT;
    qDebug() << "GST_MESSAGE_HAVE_CONTEXT: " << GST_MESSAGE_HAVE_CONTEXT;
    qDebug() << "GST_MESSAGE_EXTENDED: " << GST_MESSAGE_EXTENDED;
}
void dumpMessageType(GstMessage *message)
{
    switch (GST_MESSAGE_TYPE(message)) {
    case GST_MESSAGE_UNKNOWN: {
        qDebug() << "Unknown message type";
        break;
    }
    case GST_MESSAGE_EOS: {
        qDebug() << "End-of-stream message";
        break;
    }
    case GST_MESSAGE_ERROR: {
        qDebug() << "Error message";
        break;
    }
    case GST_MESSAGE_WARNING: {
        qDebug() << "Warning message";
        break;
    }
    case GST_MESSAGE_INFO: {
        qDebug() << "Information message";
        break;
    }
    case GST_MESSAGE_TAG: {
        qDebug() << "Metadata tag message";
        break;
    }
    case GST_MESSAGE_BUFFERING: {
        qDebug() << "Buffering message";
        break;
    }
    case GST_MESSAGE_STATE_CHANGED: {
        qDebug() << "State changed message";
        break;
    }
    case GST_MESSAGE_STATE_DIRTY: {
        qDebug() << "State dirty message";
        break;
    }
    case GST_MESSAGE_STEP_DONE: {
        qDebug() << "Step done message";
        break;
    }
    case GST_MESSAGE_CLOCK_PROVIDE: {
        qDebug() << "Clock provide message";
        break;
    }
    case GST_MESSAGE_CLOCK_LOST: {
        qDebug() << "Clock lost message";
        break;
    }
    case GST_MESSAGE_NEW_CLOCK: {
        qDebug() << "New clock message";
        break;
    }
    case GST_MESSAGE_STRUCTURE_CHANGE: {
        qDebug() << "Structure change message";
        break;
    }
    case GST_MESSAGE_STREAM_STATUS: {
        qDebug() << "Stream status message";
        break;
    }
    case GST_MESSAGE_APPLICATION: {
        qDebug() << "Application message";
        break;
    }
    case GST_MESSAGE_ELEMENT: {
        qDebug() << "Element message";
        break;
    }
    case GST_MESSAGE_SEGMENT_START: {
        qDebug() << "Segment start message";
        break;
    }
    case GST_MESSAGE_SEGMENT_DONE: {
        qDebug() << "Segment done message";
        break;
    }
    case GST_MESSAGE_DURATION_CHANGED: {
        qDebug() << "Duration changed message";
        break;
    }
    case GST_MESSAGE_LATENCY: {
        qDebug() << "Latency message";
        break;
    }
    case GST_MESSAGE_ASYNC_START: {
        qDebug() << "Async start message";
        break;
    }
    case GST_MESSAGE_ASYNC_DONE: {
        qDebug() << "Async done message";
        break;
    }
    case GST_MESSAGE_REQUEST_STATE: {
        qDebug() << "Request state message";
        break;
    }
    case GST_MESSAGE_STEP_START: {
        qDebug() << "Step start message";
        break;
    }
    case GST_MESSAGE_QOS: {
        qDebug() << "Quality-of-service message";
        break;
    }
    case GST_MESSAGE_PROGRESS: {
        qDebug() << "Progress message";
        break;
    }
    case GST_MESSAGE_TOC: {
        qDebug() << "TOC message";
        break;
    }
    case GST_MESSAGE_RESET_TIME: {
        qDebug() << "Reset time message";
        break;
    }
    case GST_MESSAGE_STREAM_START: {
        qDebug() << "Stream start message";
        break;
    }
    case GST_MESSAGE_NEED_CONTEXT: {
        qDebug() << "Need context message";
        break;
    }
    case GST_MESSAGE_HAVE_CONTEXT: {
        qDebug() << "Have context message";
        break;
    }
    case GST_MESSAGE_EXTENDED: {
        qDebug() << "Extended message type";
        break;
    }
    case GST_MESSAGE_DEVICE_ADDED: {
        qDebug() << "Device added message";
        break;
    }
    case GST_MESSAGE_DEVICE_REMOVED: {
        qDebug() << "Device removed message";
        break;
    }
    case GST_MESSAGE_PROPERTY_NOTIFY: {
        qDebug() << "Property notify message";
        break;
    }
    case GST_MESSAGE_STREAM_COLLECTION: {
        qDebug() << "Stream collection message";
        break;
    }
    case GST_MESSAGE_STREAMS_SELECTED: {
        qDebug() << "Streams selected message";
        break;
    }
    case GST_MESSAGE_REDIRECT: {
        qDebug() << "Redirect message";
        break;
    }
    case GST_MESSAGE_DEVICE_CHANGED: {
        qDebug() << "Device changed message";
        break;
    }GST::Element encoder{GST::Element::make("x265enc")};
    GST::Element payload{GST::Element::make("h265pay")};
    }
    case GST_MESSAGE_ANY: {
        qDebug() << "Any message type";
        break;
    }
    default: {
        qDebug() << "Unhandled message type " << GST_MESSAGE_TYPE(message);
        break;
    }
    }
}