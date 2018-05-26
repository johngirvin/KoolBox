#ifndef GAME_PROGRAMS_H
#define GAME_PROGRAMS_H

#include "GameShared.h"

using namespace KoolBox;

namespace Game
{

    // base class for all PosColText format pipelines
    class PosTexColProgramBase
    {
    public:
        PosTexColProgramBase();
        virtual ~PosTexColProgramBase();

        u32     id;
        Program *state;

    protected:
        Shader  *shaders[2];
    };

    // standard PosTexCol pipeline
    class PosTexColProgram : public PosTexColProgramBase
    {
    public:
        PosTexColProgram();
        ~PosTexColProgram();
    };

}

#endif

