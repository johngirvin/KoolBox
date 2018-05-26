#ifndef KOOLBOX_GRAPHICS_TEXTUREATLAS_H
#define KOOLBOX_GRAPHICS_TEXTUREATLAS_H

#include "KoolBox.h"
#include "TextureRegion.h"

using namespace KoolBox::XML;

namespace KoolBox
{
    // TextureAtlas
    // A set of TextureRegion-s sharing the same base Texture
    // Only axis-aligned rectangular regions are currently supported
    class TextureAtlas : private NonCopyable
    {
    public:
        // construct from a TexturePacker .xml file
        TextureAtlas(const char *filename);
        ~TextureAtlas();

        Texture         *getTexture()                   const;
        TextureRegion   *getRegion(const char *name)    const;
        void            addRectRegion(const char *name, const Rect &bounds, const V2 &origin = V2(0.5,0.5));

    private:
        Texture                *texture;
        Map<u32,TextureRegion> regions;
    };
}

#endif
