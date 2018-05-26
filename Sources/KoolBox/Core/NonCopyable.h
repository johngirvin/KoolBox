#ifndef KOOLBOX_NONCOPYABLE_H
#define KOOLBOX_NONCOPYABLE_H

namespace KoolBox
{
    class NonCopyable
    {
    protected:
        NonCopyable() {}
        virtual ~NonCopyable() {}

    private:
        NonCopyable(const NonCopyable &);
        NonCopyable &operator=(const NonCopyable &);
    };
}

#endif

