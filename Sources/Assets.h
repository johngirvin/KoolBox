#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H

#include "GameShared.h"
#include "TextureAtlas.h"

namespace Game
{
    class PosTexColProgram;

    class Assets
    {
    public:
        Assets();
        ~Assets();

        static u32 nextId();

        // vertex structures
        static VertexStructure *vs_posTexCol;

        // programs
        static PosTexColProgram *pr_posTexCol;

        //
        static TextureAtlas *sprites;
    };

}

#endif

