#include "Assets.h"
#include "Programs.h"
#include "TextureAtlas.h"

namespace Game
{

    // ----------------------------------------------------------------------------------------------

    u32 Assets::nextId()
    {
        static Sequence idSequence;
        return idSequence.next();
    }

    VertexStructure *Assets::vs_posTexCol  = nullptr;
    PosTexColProgram *Assets::pr_posTexCol = nullptr;

    TextureAtlas     *Assets::sprites      = nullptr;

    BitmapFont       *Assets::font         = nullptr;

    // ----------------------------------------------------------------------------------------------

    Assets::Assets()
    {
        // create vertex structures
        vs_posTexCol = KoolBox::newVertexStructure({
            VertexElement("i_pos"   , VertexData::Float2VertexData),
            VertexElement("i_uv0"   , VertexData::Float2VertexData),
            VertexElement("i_colour", VertexData::ColorVertexData)
        });
        vs_posTexCol->id = nextId();

        // create programs
        pr_posTexCol = new PosTexColProgram();
        pr_posTexCol->id = nextId();

        // load test texture atlas
        sprites = new TextureAtlas("sprites");

        // load test bitmap font
        font = new BitmapFont("PressStart", sprites->getRegion("PressStart"));
    }

    Assets::~Assets()
    {
        delete vs_posTexCol;
        delete pr_posTexCol;
    }

}
