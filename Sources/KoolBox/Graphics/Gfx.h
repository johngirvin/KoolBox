#ifndef KOOLBOX_GRAPHICS_GFX_H
#define KOOLBOX_GRAPHICS_GFX_H

#include "KoolBoxShared.h"
#include "Utility.h"
#include "TextureAtlas.h"

namespace KoolBox
{
    class Batcher;

    class Gfx
    {
    public:
        struct VertexColours
        {
            VertexColours()
            :   c { Colour::White, Colour::White, Colour::White, Colour::White },
                f { asFloat(Colour::White), asFloat(Colour::White), asFloat(Colour::White), asFloat(Colour::White) }
            { }

            VertexColours(Colour ca)
            :   c { ca, ca, ca, ca },
                f { asFloat(ca), asFloat(ca), asFloat(ca), asFloat(ca) }
            { }

            VertexColours(Colour cb, Colour ct)
            :   c { cb, ct, ct, cb },
                f { asFloat(cb), asFloat(ct), asFloat(cb), asFloat(ct) }
            { }

            VertexColours(Colour cbl, Colour ctl, Colour ctr, Colour cbr)
            :   c { cbl, ctl, ctr, cbr },
                f { asFloat(cbl), asFloat(ctl), asFloat(ctr), asFloat(cbr) }
            { }

            // vertex colours in BL,TL,TR,BR order
            Colour  c[4];
            float   f[4];
        };

        struct Sprite
        {
            Sprite()
            :   region(nullptr),
                position(0.0, 0.0),
                origin(0.5, 0.5),
                scale(1.0, 1.0),
                rotation(0),
                flip({ false, false }),
                colours(Colour::White)
            { };

            TextureRegion   *region;
            V2              position;
            V2              origin;
            V2              scale;
            float           rotation;
            struct { bool x,y; } flip;
            VertexColours   colours;
        };

        Gfx();
        ~Gfx();

        // rendering must be wrapped in a begin()/end() call pair
        void begin();
        void end();

        // clear the current render target
        void clear(u32 flags, u32 color = 0, float depth = 1.0f, int stencil = 0);

        // set the pipeline to use
        void setProgram(Program *newProgram);

        // set pipeline shader parameters by text name (slow)
        void setTexture(const char *name, Texture *tex, TextureFilter texFilter = Kore::Graphics4::PointFilter, TextureAddressing texAddressing = Kore::Graphics4::Clamp);
        void setFloat1(const char *name, float v0);
        void setFloat2(const char *name, float v0, float v1);
        void setFloat3(const char *name, float v0, float v1, float v2);
        void setFloat4(const char *name, float v0, float v1, float v2, float v3);
        void setFloats(const char *name, float *values, u32 size);
        void setMatrix(const char *name, Mat4  &matrix);

        // set pipeline shader parameters by precalculated text name hash (faster)
        void setTexture(const u32 name, Texture *tex, TextureFilter texFilter = Kore::Graphics4::PointFilter, TextureAddressing texAddressing = Kore::Graphics4::Clamp);
        void setFloat1(const u32 name, float v0);
        void setFloat2(const u32 name, float v0, float v1);
        void setFloat3(const u32 name, float v0, float v1, float v2);
        void setFloat4(const u32 name, float v0, float v1, float v2, float v3);
        void setFloats(const u32 name, float *values, u32 size);
        void setMatrix(const u32 name, Mat4  &matrix);

        // set pipeline shader parameters by target (fastest)
        void setTexture(TextureUnit newUnit, Texture *tex, TextureFilter texFilter = Kore::Graphics4::PointFilter, TextureAddressing texAddressing = Kore::Graphics4::Clamp);
        void setFloat1(ConstantLocation location, float v0);
        void setFloat2(ConstantLocation location, float v0, float v1);
        void setFloat3(ConstantLocation location, float v0, float v1, float v2);
        void setFloat4(ConstantLocation location, float v0, float v1, float v2, float v3);
        void setFloats(ConstantLocation location, float *values, u32 size);
        void setMatrix(ConstantLocation location, Mat4  &matrix);

        // force a batch flush
        void flush();

        // standard rendering
        void draw(Sprite &item);

        // custom rendering support
        // allocate space for user supplied indices and vertices
        // iWant - number of indices required, or 0 to not allocate any
        //         if iWant is 0, iPtr is ignored
        // vWant - number of vertices required, or 0 to not allocate any
        //         if vWant is 0, vPtr and vPos are ignored
        // iPtr  - *iPtr will be set to the allocated index space
        // vPtr  - *vPtr[0]...*vPtr[n] will be set to the allocated vertex spaces
        //         (one per configured inputlayout in the current pipeline)
        // vPos  - *vPos will be set to the initial index allocated
        void allocate(u16 iWant, u16 vWant, int **iPtr, float **vPtr, u16 *vPos);

    private:
        Batcher *batcher;
        Program *program;
    };

}

#endif
