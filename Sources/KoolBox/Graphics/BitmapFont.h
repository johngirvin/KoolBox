#ifndef KOOLBOX_GRAPHICS_BITMAPFONT_H
#define KOOLBOX_GRAPHICS_BITMAPFONT_H

#include "KoolBox.h"

namespace KoolBox
{
    class BitmapFont : private NonCopyable
    {
    public:
        struct Char
        {
            int   code      = -1;
            float u         = 0;
            float v         = 0;
            float w         = 0;
            float h         = 0;
            float xSize     = 0;
            float ySize     = 0;
            float xOffset   = 0;
            float yOffset   = 0;
            float xAdvance  = 0;
        };

    public:
        BitmapFont(const char *filename, TextureRegion *region = nullptr);
        ~BitmapFont();

        Texture *getTexture();
        int     getLineHeight();
        Char    *getCharDef(char code);
        Size    getBounds(const char *text, V2 scale = { 1, 1 });
        Size    getBounds(const char *text, float scalex = 1, float scaley = 1);

    private:
        int                 lineHeight;
        int                 base;
        Texture             *page;
        Char                chars[256-32];
    };

}

#endif
