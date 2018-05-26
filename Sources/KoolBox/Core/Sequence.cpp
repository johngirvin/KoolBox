#include "Sequence.h"

using namespace Kore;

namespace KoolBox
{

    Sequence::Sequence()
    :   value(0)
    {
    }

    Sequence::~Sequence()
    {
    }

    u32 Sequence::next()
    {
        return ++value;
    }

}