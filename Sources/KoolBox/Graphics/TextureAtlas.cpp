#include "TextureAtlas.h"

namespace KoolBox
{
    // ----------------------------------------------------------------------------------------------
    // CONSTRUCTORS

    TextureAtlas::TextureAtlas(const char *filename)
    :   texture(nullptr)
    {
        // load and parse atlas definition
		XMLDocument doc;
        {
            char fn[512];
            strncpy(fn, filename, 512-4-1);
            strcat(fn, ".xml");

            FileReader reader(fn);
            doc.Parse((const char *) reader.readAll(), static_cast<size_t>(reader.size()));
            reader.close();
        }

        // reference <TextureAtlas> element
        XMLElement *xmlTextureAtlas = doc.FirstChildElement("TextureAtlas");
        assert(xmlTextureAtlas);

        // load the backing texture
        texture = new Texture(xmlTextureAtlas->Attribute("imagePath"));
        assert(texture);
        const float tw = texture->texWidth;
        const float th = texture->texHeight;

        // process the child <sprite> elements
        XMLElement *xmlSprite = xmlTextureAtlas->FirstChildElement("sprite");
        if (xmlSprite->FirstChildElement("vertices"))
        {
            // TODO: polygonal regions
            assert(false);
        }
        else
        {
            // initialise regions
            while (xmlSprite != nullptr)
            {
                // create region from xml <sprite> element
                // <sprite n="el1" x="133" y="229" w="190" h="186" pX="0.5" pY="0.5" />
                addRectRegion(
                    xmlSprite->Attribute("n"),
                    { xmlSprite->FloatAttribute("x"), xmlSprite->FloatAttribute("y"), xmlSprite->FloatAttribute("w"), xmlSprite->FloatAttribute("h") },
                    { xmlSprite->FloatAttribute("pX"), xmlSprite->FloatAttribute("pY") }
                );

                // move to next <sprite> element
                xmlSprite = xmlSprite->NextSiblingElement("sprite");
            }
        }
    }

    //

    TextureAtlas::~TextureAtlas()
    {
        regions.clear();
        delete texture;
    }

    // ----------------------------------------------------------------------------------------------
    // TextureAtlas

    Texture *TextureAtlas::getTexture() const
    {
        return texture;
    }

    TextureRegion *TextureAtlas::getRegion(const char *name) const
    {
        auto res = regions.find(hash(name));
        assert(res != regions.end());

        return const_cast<TextureRegion*>( &(res->second) );
    }

    // ----------------------------------------------------------------------------------------------
    // TextureAtlas : Rect Regions

    void TextureAtlas::addRectRegion(const char *name, const Rect &bounds, const V2& origin)
    {
        auto res = regions.insert({ hash(name), { texture, bounds, origin } });
        assert(res.second);
    }

//    void TextureAtlas::split(const char *name, int w, int h)
//    {
//        TextureRegion *src = getRegion(name);
//        assert(src);
//
//        // count the split regions
//        int count = (int) ( floorf(src->bounds.w / float(w)) * floorf(src->bounds.h / float(h)) );
//
//        // allocate vertex storage for split regions
//        Rect                    bounds(0, 0, w, h);
//        TextureRegion::Vertices &verts = allocateRectRegionVertices(count);
//
//        // initialise split region name buffer
//        // split regions will be named name_NNNN
//        char subName[256];
//        strcpy(subName, name);
//        char *subNameSuffix = subName + strlen(name);
//
//        // initialise split regions
//        int i  = 0;
//        int x0 = (int) src->bounds.x;
//        int x1 = x0 + (int) src->bounds.w - w;
//        int y0 = (int) src->bounds.y;
//        int y1 = y0 + (int) src->bounds.h - h;
//        for (int y = y0; y <= y1; y += h)
//        {
//            bounds.y = y;
//
//            for (int x = x0; x <= x1; x += w, i++)
//            {
//                // create split region and insert into atlas region map
//                assert(i < count);
//
//                bounds.x = x;
//
//                sprintf(subNameSuffix, "_%04d", i);
//                addRectRegion(subName, i, bounds, verts);
//            }
//        }
//    }

}


