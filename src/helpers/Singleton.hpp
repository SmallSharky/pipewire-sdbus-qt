#pragma once

namespace helpers
{

template<typename T>
class Singleton
{
protected:
    Singleton() = default;

public:
    Singleton(const Singleton &) = delete;
    Singleton(const Singleton &&) = delete;

    static T &get()
    {
        static T instance;
        return instance;
    };
};

} // namespace helpers