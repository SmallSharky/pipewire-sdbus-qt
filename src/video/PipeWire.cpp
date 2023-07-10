

#include "PipeWire.hpp"
#include "helpers/Singleton.hpp"

#include <pipewire/pipewire.h>
#include <pipewire/properties.h>

#include <functional>
#include <iostream>
#include <thread>

namespace video
{
namespace pipewire
{
namespace
{

class PipeWire : public helpers::Singleton<PipeWire>
{
protected:
    pw_loop *mainLoop_{nullptr};
    bool mainLoopRunning_{true};
    std::thread mainLoopThr_{std::bind(&PipeWire::handleMainLoop_, this)};

    void handleMainLoop_()
    {
        std::cout << "PipeWire::handleMainLoop_" << std::endl;
        while (!mainLoop_)
            ;
        while (mainLoopRunning_) {
            std::cout << "handleMainLoop_ pw_loop_iterate" << std::endl;
            pw_loop_iterate(mainLoop_, -1);
        }
    }

public:
    PipeWire()
    {
        std::cout << "PipeWire::PipeWire() pw_init" << std::endl;
        pw_init(nullptr, nullptr);
        std::cout << "PipeWire::PipeWire() pw_loop_new" << std::endl;
        mainLoop_ = pw_loop_new(nullptr);
        std::cout << "PipeWire::PipeWire() DONE" << std::endl;
    }

    ~PipeWire()
    {
        std::cout << "PipeWire::~PipeWire()" << std::endl;
        mainLoopRunning_ = false;
        spa_loop_control_leave(mainLoop_->control);
        mainLoopThr_.join();
        pw_deinit();
    }

    pw_loop *mainLoop()
    {
        // if(!mainLoop_) {
        //     mainLoop_ =
        // }
        return mainLoop_;
    }
};

struct Context {
    int fd;
    pw_context *ctx;
    pw_core *core;

    Context(int fdArg)
        : fd(fdArg)
        , ctx(pw_context_new(PipeWire::get().mainLoop(), nullptr, 0))
        , core(pw_context_connect_fd(ctx, fd, nullptr, 0))
    {
        std::cout << "Context::Context" << std::endl;
        std::cout << "Context::ctx " << ((void *)ctx) << std::endl;
        std::cout << "Context::core " << ((void *)core) << std::endl;
        // auto& pwinst = PipeWire::get();
    }
};

void on_stream_started(void *data, uint64_t code)
{
    std::cout << "on_stream_started" << std::endl;
    // Handle stream started event
}

void on_stream_error(void *data, uint64_t code)
{
    std::cout << "on_stream_error" << std::endl;
    // Handle stream error event
}

void on_stream_eos(void *data, uint64_t code)
{
    std::cout << "on_stream_eos" << std::endl;
    // Handle end of stream event
}

void on_stream_format_changed(void *data, uint64_t code)
{
    std::cout << "on_stream_format_changed" << std::endl;
    // Handle format changed event
}

} // namespace {

struct Stream::PImpl_ {
    int id;
    Context ctx;
    pw_stream *stream;
    PImpl_(int fd, uint32_t id)
        : id(id)
        , ctx(fd)
        , stream(pw_stream_new(ctx.core, "video", nullptr))
    {
        std::cout << "Stream::PImpl_::PImpl_() pw_stream_connect" << std::endl;
        int res = pw_stream_connect(stream, PW_DIRECTION_INPUT, id, PW_STREAM_FLAG_AUTOCONNECT, nullptr, 0);
        std::cout << "Stream pw_stream_connect status: " << res << std::endl;
        std::cout << "Stream::PImpl_::stream " << ((void *)stream) << std::endl;
        auto props = pw_stream_get_properties(stream);
        std::cout << "Stream::PImpl_::props " << ((void *)stream) << std::endl;
        void *iter = nullptr;
        const char *key = nullptr;
        while (key = pw_properties_iterate(props, &iter)) {
            const char *val{pw_properties_get(props, key)};
            std::cout << "Stream::PImpl_::props " << key << ": " << val << std::endl;
        }

        // pw_stream_events_subscribe(stream, &loop->defer, PW_STREAM_EVENT_STARTED | PW_STREAM_EVENT_ERROR | PW_STREAM_EVENT_EOS |
        // PW_STREAM_EVENT_FORMAT_CHANGED, NULL);
        pw_loop_add_event(PipeWire::get().mainLoop(), on_stream_started, stream);
        pw_loop_add_event(PipeWire::get().mainLoop(), on_stream_error, stream);
        pw_loop_add_event(PipeWire::get().mainLoop(), on_stream_eos, stream);
        pw_loop_add_event(PipeWire::get().mainLoop(), on_stream_format_changed, stream);
    }

    ~PImpl_()
    {
        std::cout << "Stream::PImpl_::~PImpl_()" << std::endl;
        // close(fd);
    }
};

Stream::Stream(int fd, uint32_t id)
    : impl_(new PImpl_(fd, id))
{
    std::cout << "Stream::Stream()" << std::endl;
}

Stream::~Stream()
{
    std::cout << "Stream::~Stream()" << std::endl;
}

} // namespace pipewire
} // namespace video
