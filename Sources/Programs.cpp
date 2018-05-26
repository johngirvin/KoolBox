#include "Programs.h"

namespace Game
{

    // ----------------------------------------------------------------------------------------------

    PosTexColProgramBase::PosTexColProgramBase()
    :   id(Assets::nextId())
    {
    }

    PosTexColProgramBase::~PosTexColProgramBase()
    {
        delete shaders[0];
        delete shaders[1];
        delete state;
    }

    // ----------------------------------------------------------------------------------------------

    PosTexColProgram::PosTexColProgram()
    :   PosTexColProgramBase()
    {
        KoolBox::loadNewVertexFragmentShaders("PosTexCol", &shaders[0], &shaders[1]);

        state = new Program(Program::Desc(shaders[0], shaders[1], Assets::vs_posTexCol), {"u_vp"}, {"u_texture"});
    }

    PosTexColProgram::~PosTexColProgram()
    {
    }

}
