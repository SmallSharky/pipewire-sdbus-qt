#include <QDebug>
#include <filesystem>
#include <gst/gst.h>
#include <gst/gstutils.h>
#include <gst/pbutils/pbutils.h>
#include <stdexcept>
// struct GstElement;

namespace gst
{

struct Element {
    GstElement *ptr;
    Element(GstElement *element)
        : ptr(element)
    {
        if (!ptr) {
            throw std::runtime_error("Failed to create element");
        }
    }

    ~Element()
    {
        unref();
    }

    static Element make(const std::string &factoryName, const std::string &elementName)
    {
        qDebug() << "make element " << factoryName.c_str() << " (name: " << elementName.c_str() << ")";
        return Element(gst_element_factory_make(factoryName.c_str(), elementName.c_str()));
    }

    static Element make(const std::string &factoryName)
    {
        qDebug() << "make element " << factoryName.c_str();
        return Element(gst_element_factory_make(factoryName.c_str(), nullptr));
    }

    void setPropertyStr(const std::string &propertyName, const std::string &value)
    {
        g_object_set(G_OBJECT(ptr), propertyName.c_str(), value.c_str(), nullptr);
    }

    void setPropertyInt(const std::string &propertyName, int value)
    {
        g_object_set(G_OBJECT(ptr), propertyName.c_str(), value, nullptr);
    }

    void setPropertyUInt(const std::string &propertyName, unsigned value)
    {
        g_object_set(G_OBJECT(ptr), propertyName.c_str(), value, nullptr);
    }

    void setPropertyBool(const std::string &propertyName, bool value)
    {
        g_object_set(G_OBJECT(ptr), propertyName.c_str(), value, nullptr);
    }

    void link(Element &other)
    {
        qDebug() << "Link:" << gst_element_get_name(ptr) << "->" << gst_element_get_name(other.ptr);
        if (!gst_element_link(ptr, other.ptr)) {
            throw std::runtime_error("Failed to link elements");
        }
    }

    void unref()
    {   if (ptr) {
            gst_object_unref(ptr);
            ptr = nullptr;
        }
    }
};

struct Pipeline : Element {
    Pipeline()
        : Element(gst_pipeline_new(nullptr))
    {
    }

    bool add(Element &element)
    {
        qDebug() << "Add:" << gst_element_get_name(ptr) << "<-" << gst_element_get_name(element.ptr) ;
        return gst_bin_add(GST_BIN(ptr), element.ptr);
    }
};

struct PipewireSource : Element {
    PipewireSource()
        : Element(Element::make("pipewiresrc"))
    {
    }
};

struct Autovideoconvert : Element {
    Autovideoconvert()
        : Element(Element::make("autovideoconvert"))
    {
    }
};

struct Videoconvert : Element {
    Videoconvert()
        : Element(Element::make("videoconvert"))
    {
    }
};

struct FileSink : Element {
    FileSink(const std::filesystem::path &path)
        : Element(Element::make("filesink"))
    {
        g_object_set(G_OBJECT(ptr), "location", path.c_str(), nullptr);
    }
};

} // namespace gst