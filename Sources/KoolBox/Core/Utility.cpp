#include "Utility.h"

namespace KoolBox
{
    //
    // MATHS
    //

    bool isPowerOfTwo(int x)
    {
        assert(x >= 0);
        return ((x != 0) && !(x & (x - 1)));
    }

    // fast cos approximation
    // http://stackoverflow.com/a/28050328
    //
    // average error compared to std::cos is ~0.03
    // or ~0.0005 in extra precision mode
    float cosa(float x)
    {
        static const float tp = (float) (1.0f / (2.0f * M_PI));
        x *= tp;
        x -= 0.25f + Kore::floor(x + 0.25f);
        x *= 16.0f * (Kore::abs(x) - 0.5f);
        // reduces average error to 0.0005
        x += 0.225f * x * (Kore::abs(x) - 1.0f);
        return x;
    }

    float sina(float x)
    {
        return cosa(x - (float) M_PI_2);
    }

    // FNV1A-32 hash a block of memory
    u32 hash(const void* data, u32 length)
    {
        assert(data);
        assert(length > 0);

        byte *ptr = (byte *) data;
        u32  hash = 0x811c9dc5;
        while (length--) {
            hash = (*ptr++ ^ hash) * 16777619;
        }

        return hash;
    }

    u32 hash(const char* data)
    {
        assert(data);

        byte *ptr = (byte *) data;
        u32  hash = 0x811c9dc5;
        while (*ptr != 0) {
            hash = (*ptr++ ^ hash) * 16777619;
        }

        return hash;
    }

    //
    // GRAPHICS
    //

    int floatsPerData(const VertexData &data)
    {
        switch (data)
        {
            case VertexData::NoVertexData:
                return 0;
            case VertexData::ColorVertexData:
                return 1;
            case VertexData::Float1VertexData:
                return 1;
            case VertexData::Float2VertexData:
                return 2;
            case VertexData::Float3VertexData:
                return 3;
            case VertexData::Float4VertexData:
                return 4;
            case VertexData::Float4x4VertexData:
                return 4 * 4;
        }

        return 0;
    };

    int floatsPerVertex(const VertexStructure &vs)
    {
        int floatsPerVertex = 0;

        for (int i = 0, c = vs.size; i < c; i++)
        {
            floatsPerVertex += floatsPerData(vs.elements[i].data);
        }

        return floatsPerVertex;
    }

    VertexStructure *newVertexStructure(const VertexElementList &attributes)
    {
        assert(attributes.size() > 0);

        VertexStructure *structure = new VertexStructure();
        for (const VertexElement &attribute: attributes)
        {
            assert(attribute.name != nullptr);
            structure->add(attribute.name, attribute.data);
        }

        return structure;
    }

    Shader *loadNewShader(const char *name, ShaderType type)
    {
        assert(name);
        assert(strlen(name) < 500);
        assert(type == ShaderType::VertexShader || type == ShaderType::FragmentShader);

        char path[512];
        strcpy(path, name);
        switch (type)
        {
            case ShaderType::VertexShader  : strcat(path, ".vert"); break;
            case ShaderType::FragmentShader: strcat(path, ".frag"); break;
            default                        : assert(false);
        }

        Kore::FileReader fr(path);
        int   srclen = fr.size();
        assert(srclen > 0);

        void *src = fr.readAll();
        assert(src != nullptr);

        Shader *shader = new Shader(src, srclen, type);
        assert(shader);
        return shader;
    }

    void loadNewVertexFragmentShaders(const char *name, Shader **vptr, Shader **fptr)
    {
        *vptr = loadNewShader(name, Kore::Graphics4::VertexShader);
        *fptr = loadNewShader(name, Kore::Graphics4::FragmentShader);
    }

    float asFloat(Colour &col)
    {
        u32 c =
              ((((u32)col.A) * 255) << 24)
            | ((((u32)col.R) * 255) << 16)
            | ((((u32)col.G) * 255) <<  8)
            | ((((u32)col.B) * 255)      );

        return *((float *)&c);
    }

    float asFloat(u32 col)
    {
        u32 c = col;
        return *((float *)&c);
    }

    //
    // MISC
    //

    StringReader::StringReader(const char *filename)
    {
        FileReader reader(filename);

        length = reader.size();
        data   = new char[length+1];

        if (length > 0)
        {
            reader.read((void *) data, length);
            reader.close();
        }

        data[length] = 0;
    }

    StringReader::~StringReader()
    {
        delete [] data;
    }
}







