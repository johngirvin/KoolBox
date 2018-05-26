#ifndef KOOLBOX_GRAPHICS_TEXTUREREGION_H
#define KOOLBOX_GRAPHICS_TEXTUREREGION_H

#include "KoolBox.h"

namespace KoolBox
{
    struct TextureRegion
    {
        TextureRegion(Texture *texture, const Rect &bounds, const V2 &origin)
        :   texture(texture),
            bounds(bounds),
            origin(origin)
        {
            float tw = texture->texWidth;
            float th = texture->texHeight;
            uv = { bounds.x / tw, bounds.y / th, (bounds.x + bounds.w) / tw, (bounds.y + bounds.h) / th };
        };

        Texture     *texture;
        Rect        bounds;
        Rect        uv;
        V2          origin;
    };
}

#endif
