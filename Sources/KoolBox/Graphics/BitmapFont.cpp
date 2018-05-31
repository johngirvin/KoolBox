#include "BitmapFont.h"
#include "Utility.h"

using namespace KoolBox::XML;

namespace KoolBox
{
    // ----------------------------------------------------------------------------------------------
    // CONSTRUCTORS

    BitmapFont::BitmapFont(const char *filename, TextureRegion *region)
    {
        // load and parse font definition
		XMLDocument doc;
        {
            char fn[512];
            strncpy(fn, filename, 512-4-1);
            strcat(fn, ".fnt");

            FileReader reader(fn);
            doc.Parse((const char *) reader.readAll(), static_cast<size_t>(reader.size()));
            reader.close();
        }

        // reference <font> element
        XMLElement *xmlFont = doc.FirstChildElement("font");
        assert(xmlFont != nullptr);

        // parse <common>
        XMLElement *xmlCommon = xmlFont->FirstChildElement("common");
        assert(xmlCommon != nullptr);

        lineHeight = xmlCommon->IntAttribute("lineHeight");
        base       = xmlCommon->IntAttribute("base");

        // load the page textures
        // TODO: doesn't support multiple pages
        float x0, y0;
        if (region == nullptr)
        {
            // use filename in definition file to load page texture
            XMLElement *xmlPages = xmlFont->FirstChildElement("pages");
            assert(xmlPages != nullptr);

            XMLElement *xmlPage = xmlPages->FirstChildElement("page");
            assert(xmlPage != nullptr);

            page = new Texture(xmlPage->Attribute("file"));
            x0   = 0;
            y0   = 0;
        }
        else
        {
            // use supplied region texture
            page = region->texture;
            x0   = region->bounds.x;
            y0   = region->bounds.y;
        }
        assert(page);

        // load the character definitions
        XMLElement *xmlChars = xmlFont->FirstChildElement("chars");
        assert(xmlChars != nullptr);

        XMLElement *xmlChar = xmlChars->FirstChildElement("char");
        while (xmlChar != nullptr)
        {
            int code = xmlChar->IntAttribute("id");
            assert(code >= 32 && code <= 255);

            Char *c = &(chars[code-32]);
            assert(c->code == -1);

            c->code     = code;
            c->u        = (x0 + (float) xmlChar->IntAttribute("x")) / (float) page->texWidth;
            c->v        = (y0 + (float) xmlChar->IntAttribute("y")) / (float) page->texHeight;
            c->w        = (float) xmlChar->IntAttribute("width")    / (float) page->texWidth;
            c->h        = (float) xmlChar->IntAttribute("height")   / (float) page->texHeight;
            c->xSize    = (float) xmlChar->IntAttribute("width");
            c->ySize    = (float) xmlChar->IntAttribute("height");
            c->xOffset  = (float) xmlChar->IntAttribute("xoffset");
            c->yOffset  = (float) xmlChar->IntAttribute("yoffset");
            c->xAdvance = (float) xmlChar->IntAttribute("xadvance");

            xmlChar = xmlChar->NextSiblingElement("char");
        }
    }

    BitmapFont::~BitmapFont()
    {
        delete page;
    }

    // ----------------------------------------------------------------------------------------------
    // BitmapFont

    Texture *BitmapFont::getTexture()
    {
        return page;
    }

    int BitmapFont::getLineHeight()
    {
        return lineHeight;
    }

    Size BitmapFont::getBounds(const char *text, V2 scale)
    {
        return getBounds(text, scale.x, scale.y);
    }

    Size BitmapFont::getBounds(const char *text, float sx, float sy)
    {
        Size bounds(0, 0);

        for (int i = 0, c = (int) strlen(text); i < c; i++)
        {
            Char *cdef = getCharDef(text[i]);
            if (i < c-1)
            {
                bounds.w += cdef->xAdvance;
            }
            else
            {
                bounds.w += cdef->xOffset + cdef->xAdvance;
            }
        }

        bounds.w = sx * bounds.w;
        bounds.h = sy * lineHeight;
        return bounds;
    }

    BitmapFont::Char *BitmapFont::getCharDef(char code)
    {
        assert(code >= 32 && code <= 255);
        Char *c = &(chars[code-32]);
        assert(c->code == code);
        return c;
    }

}


