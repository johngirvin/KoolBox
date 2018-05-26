#ifndef KOOLBOX_SEQUENCE_H
#define KOOLBOX_SEQUENCE_H

#include "KoolBoxShared.h"
#include "NonCopyable.h"

namespace KoolBox
{

    // Sequence
    // Generates an increasing sequence of integers with each call to next()
    class Sequence : private NonCopyable
    {
    public:
        Sequence();
        ~Sequence();

        u32 next();

    private:
        std::atomic<u32> value;
    };

}

#endif
