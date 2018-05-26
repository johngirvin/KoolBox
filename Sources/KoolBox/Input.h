#ifndef KOOLBOX_INPUT_H
#define KOOLBOX_INPUT_H

#include "KoolBoxShared.h"

namespace KoolBox
{
    namespace Input
    {
        enum class KeyPhase
        {
            Pressed,
            Released
        };

        struct Key
        {
            KeyCode     code;
            int         character;
            KeyPhase    phase;
            double      time;
        };

        enum class TouchPhase
        {
            Started,
            Moved,
            Ended
        };

        struct Touch
        {
            int         id;
            double      time;
            TouchPhase  phase;
            V2          delta;
            V2          pos;
            double      startTime;
            V2          startPos;
        };
    }

}

#endif
