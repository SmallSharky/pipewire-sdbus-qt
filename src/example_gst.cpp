// #include "ScreenCast.hpp"

#include "gui/StreamingWindow.hpp"

#include "helpers/Strings.hpp"
#include "helpers/Singleton.hpp"
#include "screencast/ScreenCast.hpp"
#include "screencast/Streaming.hpp"

#include "gst++/elements.hpp"
// #include <gst++/error.hpp>
// #include <QGuiApplication>
#include <QApplication>
#include <QDebug>
#include "video/PipeWire.hpp"
#include <thread>
#include <chrono>

#include <pipewire/pipewire.h>

// #include <gst/pipewire/pipewire.h>



namespace glibpp {

class GMainLoop: public helpers::Singleton<GMainLoop> {
public:
    GMainLoop() {
        loop_ = g_main_loop_new(nullptr, false);

    }
    ~GMainLoop() {
        g_main_loop_unref(loop_);
        loop_ = nullptr;
    }

    void quit () {
        g_main_loop_quit(loop_);
    }

    void run () {
        g_main_loop_run(loop_);
    }
private:
    ::GMainLoop *loop_{nullptr};

}; // class GMainLoop

} // namespace glibpp



static gboolean bus_callback(GstBus *bus, GstMessage *message, gpointer data)
{
    // GMainLoop *loop = (GMainLoop *)data;

    switch (GST_MESSAGE_TYPE(message)) {
    case GST_MESSAGE_ERROR: {
        GError *err = nullptr;
        gchar *debug = nullptr;

        gst_message_parse_error(message, &err, &debug);
        g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(message->src), err->message);
        g_printerr("Debugging information: %s\n", (debug) ? debug : "none");
        g_clear_error(&err);
        g_free(debug);

        // g_main_loop_quit(loop);
        glibpp::GMainLoop::get().quit();

        break;
    }

    case GST_MESSAGE_EOS: {
        g_print("End of stream\n");
        // g_main_loop_quit(loop);
        glibpp::GMainLoop::get().quit();
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
    case GST_MESSAGE_STATE_CHANGED: {
        GstState old_state, new_state, pending_state;
        gst_message_parse_state_changed(message, &old_state, &new_state, &pending_state);
        qDebug() << "State changed from" << gst_element_state_get_name(old_state) << "to" << gst_element_state_get_name(new_state);
        break;
    }

    case GST_MESSAGE_STREAM_START: {
        qDebug() << "Stream start";
        break;
    }

    case GST_MESSAGE_LATENCY: {
        qDebug() << "Latency";
        break;
    }

    case GST_MESSAGE_ASYNC_DONE: {
        qDebug() << "Async done";
        break;
    }

    case GST_MESSAGE_STREAM_STATUS: {
        // qDebug() << "Stream status";

        GstStreamStatusType status;
        GstElement* owner;
        gst_message_parse_stream_status(message, &status, &owner);
        qDebug() << "Status:" << status;
        break;
    }
    default: {

        if(message) {
            qDebug() << "Message:" << GST_MESSAGE_TYPE_NAME(message);
        //     dumpMessageType(message);
        }

        break;
    }
    }

    return true;
}



void exit_handler(int signal)
{
    qDebug() << "exit_handler";
    glibpp::GMainLoop::get().quit();
}

int main(int argc, char **argv)
{
    signal(SIGINT, exit_handler);
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

    uint32_t streamIdNumber = streaming->streams.front().id;




    gst_init(&argc, &argv);

    // ksvideosrc ! decodebin2 ! ffmpegcolorspace ! schronc ! matroskamux ! filesink location=gopro2.mkv
    // ksvideosrc num-buffers=500 ! decodebin2 ! ffmpegcolorspace ! x264enc ! mp4mux ! filesink location=gopro2.mp4
    // v4l2src ! ffmpegcolorspace ! jpegenc ! avimux ! filesink location=output.avi

    gst::Pipeline pipeline;

    gst::PipewireSource video_source;

    // gst::Element decoder{gst::Element::make("decodebin")};
    gst::Element converter{gst::Element::make("videoconvert")};
    gst::Element scaler{gst::Element::make("videoscale")};
    gst::Element rate{gst::Element::make("videorate")};
    gst::Element progress{gst::Element::make("progressreport")};
    gst::Element encoder{gst::Element::make("x264enc")};
    gst::Element mux{gst::Element::make("mp4mux")};
    // gst::Element sink{gst::Element::make("udpsink")};
    gst::FileSink sink{"out.mp4"};

    qDebug() << " ===== set properties";

    std::string streamId{std::to_string(streamIdNumber)};
    video_source.setPropertyStr("path", streamId);
    video_source.setPropertyInt("fd", fd);
    video_source.setPropertyInt("keepalive-time", 40);
    video_source.setPropertyBool("autoconnect", true);

    converter.setPropertyStr("framerate", std::string("30/1"));

    // sink.setProperty("host", std::string("127.0.0.1"));
    // sink.setProperty("port", 9001);
    mux.setPropertyUInt("fragment-duration", 1000);
    mux.setPropertyBool("streamable", true);
    // mux.setProperty("faststart", true);
    // mux.setProperty("faststart-file", std::string("/tmp/faststartfile.bin"));

    qDebug() << " ===== add many";

    // pipeline.add(decoder);
    pipeline.add(video_source);
    pipeline.add(converter);
    pipeline.add(scaler);
    pipeline.add(rate);
    pipeline.add(progress);
    pipeline.add(encoder);
    pipeline.add(mux);
    pipeline.add(sink);

    qDebug() << " ===== link elements";
    video_source.link(converter);
    converter.link(scaler);
    scaler.link(rate);
    rate.link(progress);
    progress.link(encoder);
    encoder.link(mux);
    mux.link(sink);

    // Now they are managed by pipeline
    video_source.ptr = nullptr;
    converter.ptr = nullptr;
    scaler.ptr = nullptr;
    rate.ptr = nullptr;
    progress.ptr = nullptr;
    encoder.ptr = nullptr;
    mux.ptr = nullptr;
    // sink.ptr = nullptr;

    qDebug() << " ===== set state playing";
    //    // Set the pipeline to the playing state
    if (gst_element_set_state(pipeline.ptr, GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {
        throw std::runtime_error("Failed to start pipeline");
        //    g_printerr("Failed to start pipeline");
        //    gst_object_unref(pipeline.ptr);
        //    return -1;
    }

    // GMainLoop *loop = g_main_loop_new(nullptr, false);
    GstBus *bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline.ptr));
    gst_bus_add_watch(bus, (GstBusFunc)bus_callback, nullptr);


    glibpp::GMainLoop::get().run();
    qDebug() << " ===== STOP";
    // gst_element_set_state(pipeline.ptr, GST_STATE_PAUSED);
    // gst_element_set_state(sink.ptr, GST_STATE_PAUSED);
    // glibpp::GMainLoop::get().run();
    // gst_element_set_state(sink.ptr, GST_STATE_NULL);
    sink.ptr = nullptr;
    gst_element_set_state(pipeline.ptr, GST_STATE_NULL);



    // g_main_loop_unref(loop);
    gst_object_unref(bus);
}