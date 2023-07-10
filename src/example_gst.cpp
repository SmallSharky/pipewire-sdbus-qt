// #include "ScreenCast.hpp"
#include "Streaming.hpp"
#include "StreamingWindow.hpp"

#include "Helpers.hpp"
#include "ScreenCast.hpp"
// #include <QGuiApplication>
#include <QApplication>
#include <QDebug>
#include <gst/gst.h>
#include <gst/gstutils.h>
#include <gst/pbutils/pbutils.h>
// #include <gst/pipewire/pipewire.h>
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
    }
    case GST_MESSAGE_INSTANT_RATE_REQUEST: {
        qDebug() << "Instant rate request message";
        break;
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

static gboolean bus_callback(GstBus *bus, GstMessage *message, gpointer data)
{
    GMainLoop *loop = (GMainLoop *)data;

    switch (GST_MESSAGE_TYPE(message)) {
    case GST_MESSAGE_ERROR: {
        GError *err = nullptr;
        gchar *debug = nullptr;

        gst_message_parse_error(message, &err, &debug);
        g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(message->src), err->message);
        g_printerr("Debugging information: %s\n", (debug) ? debug : "none");
        g_clear_error(&err);
        g_free(debug);

        g_main_loop_quit(loop);
        break;
    }

    case GST_MESSAGE_EOS: {
        g_print("End of stream\n");
        g_main_loop_quit(loop);
        break;
    }

        // case GST_MESSAGE_QOS: {
        //     const GstStructure *structure = gst_message_get_structure(message);
        //     if (structure) {
        //         GstClockTime timestamp, duration;
        //         gint64 processed, dropped;
        //         gdouble jitter;
        //         if (gst_structure_get_clock_time(structure, "timestamp", &timestamp)) qDebug() << "Timestamp:" << timestamp << "ns";
        //         if (gst_structure_get_clock_time(structure, "duration", &duration)) qDebug() << "Duration:" << duration << "ns";
        //         if (gst_structure_get_int64(structure, "processed", &processed)) qDebug() << "Processed:" << processed << "bytes";
        //         if (gst_structure_get_int64(structure, "dropped", &dropped)) qDebug() << "Dropped:" << dropped << "bytes";
        //         if (gst_structure_get_double(structure, "jitter", &jitter)) qDebug() << "Jitter:" << jitter << "%";
        //         qDebug() << "QOS";

        //     }
        //     break;
        // }

    default: {
        // if(message) {
        //     dumpMessageType(message);
        // }

        break;
    }
    }

    return true;
}

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app{argc, argv};
    // QGuiApplication app{argc, argv};

    // GstElement *src;
    // GstElementFactory *srcfactory;

    // // srcfactory = gst_element_factory_find ("pipewiresrc");
    // // if(!srcfactory) {
    // //     return -1;
    // // }
    // // // g_return_if_fail (srcfactory != NULL);
    // // src = gst_element_factory_create (srcfactory, "src");
    // // if(!src) {
    // //     return -1;
    // // }

    // GError *error = nullptr;
    // std::vector<const char *> args{
    //     "ximagesrc",
    //     nullptr
    // };
    // GstElement * pipeline = (GstElement *) gst_parse_launchv (args.data(), &error);

    // if (!pipeline) {
    //     if (error) {
    //         qDebug() << "Error: pipeline could not be constructed: " << error->message;
    //     } else {
    //         qDebug() << "Error: pipeline could not be constructed.";
    //     }
    //     return 1;
    // } else if (error) {
    //     qDebug() << "Error: " << error->message;
    //     return 1;
    // }

    // auto loop = g_main_loop_new (0, false);

    // if (!GST_IS_PIPELINE (pipeline)) {
    //   GstElement *real_pipeline = gst_element_factory_make ("pipeline", NULL);

    //   if (real_pipeline == NULL) {
    //     qDebug() << "ERROR: the 'pipeline' element wasn't found.\n";
    //     return 1;
    //   }
    //   gst_bin_add (GST_BIN (real_pipeline), pipeline);
    //   pipeline = real_pipeline;
    // }

    // // gui::StreamingWindow win{app};
    // qDebug() << "Connecting to desktop portal...";
    auto clientid = helpers::generateRandomString(8);
    auto cast{screencast::ScreenCast::create(clientid, {})};

    // // cast_.emplace(std::move(tmp));
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
    // // const auto windows{qmlEng_->rootObjects()};
    int fd = cast.open();
    // for (const auto &stream : streaming->streams) {
    // //     for (auto win : windows) {
    // qDebug() << "Opening stream " << stream.id << " with fd " << fd;
    // //         auto mo = win->metaObject();
    // //         mo->invokeMethod(win,
    // //                          "addStream",
    // //                          Q_ARG(QVariant, QVariant::fromValue<uint32_t>(stream.id)),
    // //                          Q_ARG(QVariant, QStringLiteral("")),
    // //                          Q_ARG(QVariant, fd));
    // //     }
    // }
    gst_init(&argc, &argv);
    GstElement *pipeline = gst_pipeline_new(nullptr);
    GstElement *video_source = gst_element_factory_make("pipewiresrc", nullptr);
    // GstElement *video_source = gst_element_factory_make("fdsrc", "video_source");
    // GstElement *video_format = gst_element_factory_make("video/x-raw", "video_format");
    // GstElement *raw_decoder = gst_element_factory_make("decodebin", "raw_decoder");
    // GstElement *h265_encoder = gst_element_factory_make("x265enc", "h265_encoder");
    GstElement *autovideoconvert = gst_element_factory_make("autovideoconvert", nullptr);
    // GstElement *rate = gst_element_factory_make("videorate", "rate");
    // GstElement * csp_filter = gst_element_factory_make("ffmpegcolorspace", nullptr);
    GstElement *capsfilter = gst_element_factory_make("capsfilter", nullptr);
    GstElement *capssetter = gst_element_factory_make("capssetter", nullptr);
    GstElement *videoscale = gst_element_factory_make("videoscale", nullptr);
    GstElement *videoconvert = gst_element_factory_make("videoconvert", nullptr);
    GstElement *filter = gst_element_factory_make("capsfilter", nullptr);
    GstElement *decodebin = gst_element_factory_make("decodebin", nullptr);
    // GstElement *encoder = gst_element_factory_make("vaapih264enc", "encoder");
    // GstElement *parser = gst_element_factory_make("h264parse", "parser");
    // GstElement *muxer = gst_element_factory_make("mpegtsmux", "muxer");
    GstElement *encoder = gst_element_factory_make("x265enc", nullptr);
    GstElement *payload = gst_element_factory_make("rtph265pay", nullptr);
    GstElement *sink = gst_element_factory_make("udpsink", nullptr);
    // GstElement *h265_encoder = gst_element_factory_make("x265enc", "h265_encoder");

    // GstElement *autovideoconvert = gst_element_factory_make("autovideoconvert", "autovideoconvert");
    // GstElement *autovideosink = gst_element_factory_make("autovideosink", "autovideosink");

    // GstElement *rtp_payload = gst_element_factory_make("rtph264pay", "rtp_payload");
    // GstElement *rtp_sink = gst_element_factory_make("udpsink", "rtp_sink");
    if (!videoconvert || !encoder || !payload || !sink) {
        qDebug() << "Cannot create elements";
        return -1;
    }
    if (!pipeline) {
        qDebug() << "No pipeline";
        return -1;
    }
    if (!video_source) {
        qDebug() << "No video_source";
        return -1;
    }
    // if(!video_format) {qDebug() << "No video_format"; return -1;}
    // if(!raw_decoder) {qDebug() << "No raw_decoder"; return -1;}
    // if(!h265_encoder) {qDebug() << "No h265_encoder"; return -1;}
    // if(!autovideosink) {qDebug() << "No h265_encoder"; return -1;}
    // if(!rtp_payload) {qDebug() << "No rtp_payload"; return -1;}
    // if(!rtp_sink) {qDebug() << "No rtp_sink"; return -1;}

    qDebug() << " ===== set properties";

    // Set the properties of the Pipewire source element
    std::string streamId{std::to_string(streaming->streams.front().id)};
    g_object_set(G_OBJECT(video_source), "path", streamId.c_str(), "fd", fd, "always-copy", true, "do-timestamp", true, "keepalive-time", 20, nullptr);

    // g_object_set(filter, "caps", gst_caps_from_string("video/x-raw,width=640,height=480"), NULL);
    // g_object_set(
    //     G_OBJECT(encoder),
    //     "aud", true,
    //     "speed-preset", "superfast",
    //     "tune", "zerolatency",
    //     "byte-stream", true,
    //     "sliced-threads", true,
    //     "threads", 8,
    //     nullptr
    // );

    // g_object_set(
    //     G_OBJECT(capssetter),
    //     "replace", true,
    //     nullptr
    // );

    // GstCaps *caps = gst_caps_from_string("video/x-raw, format=(string)I420_10LE");
    // g_object_set (G_OBJECT (capsfilter), "caps", caps, NULL);
    // gst_caps_unref (caps);

    // GstCaps *caps = gst_caps_from_string("video/x-raw, format=(string)RGBA");
    // g_object_set (G_OBJECT (capsfilter), "caps", caps, NULL);
    // gst_caps_unref (caps);

    // set properties
    g_object_set(G_OBJECT(sink), "host", "10.20.30.97", nullptr);
    g_object_set(G_OBJECT(sink), "port", 5000, nullptr);

    g_object_set(G_OBJECT(videoscale), "n-threads", 8, nullptr);
    g_object_set(G_OBJECT(videoconvert), "n-threads", 8, nullptr);
    // g_object_set(
    //     G_OBJECT(rate),
    //     "max-rate", 60,
    //     "qos", true,
    //     "skip-to-first", true,
    //     nullptr
    // );

    // g_object_set(G_OBJECT(fd_source), "fd", fd, nullptr);
    // g_object_set(G_OBJECT(video_format), "framerate", GST_FRACTION(30, 1), nullptr);
    // Set the properties of the RTP sink element
    // g_object_set(G_OBJECT(rtp_sink), "host", "127.0.0.1", "port", 5000, nullptr);
    qDebug() << " ===== add many";
    // could be replaced by gst_bin_add(GstBin * bin, GstElement * element)
    gst_bin_add_many(GST_BIN(pipeline), video_source, videoconvert, encoder, payload, sink, nullptr);

    // Link the elements
    qDebug() << " ===== link elements";
    // could be replaced by gst_element_link (GstElement * src, GstElement * dest)
    if (!gst_element_link_many(video_source, videoconvert, encoder, payload, sink, nullptr)) {
        g_printerr("Failed to link elements");
        gst_object_unref(pipeline);
        return -1;
    }

    // // create rtpbin element
    GstElement *rtpbin = gst_element_factory_make("rtpbin", "rtpbin");
    gst_bin_add(GST_BIN(pipeline), rtpbin);

    // // link rtpbin to udpsink
    gst_element_link_pads(payload, "src", rtpbin, "send_rtp_sink_0");
    gst_element_link_pads(rtpbin, "send_rtp_src_0", sink, "sink");

    // set rtpbin properties
    g_object_set(G_OBJECT(rtpbin), "latency", 100, nullptr);
    g_object_set(G_OBJECT(rtpbin), "drop-on-latency", TRUE, nullptr);

    qDebug() << " ===== set state playing";
    // Set the pipeline to the playing state
    if (gst_element_set_state(pipeline, GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {
        g_printerr("Failed to start pipeline");
        gst_object_unref(pipeline);
        return -1;
    }

    // GstBus *bus = gst_element_get_bus(pipeline);
    // GstMessage * msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
    // // Create the main loop
    GMainLoop *loop = g_main_loop_new(nullptr, false);
    GstBus *bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));

    // // Attach the bus to the pipeline
    gst_bus_add_watch(bus, (GstBusFunc)bus_callback, loop);

    // // Start the main loop
    g_main_loop_run(loop);

    // // Clean up resources
    g_main_loop_unref(loop);
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    // printMessageTypes();
    // gui::StreamingWindow sw(app);

    // return app.exec();
}