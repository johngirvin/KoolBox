#ifndef KOOLBOX_UTILITY_H
#define KOOLBOX_UTILITY_H

#include "KoolBoxShared.h"
#include "NonCopyable.h"

namespace tinystl
{
    // specialisation for pre-hashed keys
    template<>
    inline size_t hash(const KoolBox::u32& value) {
        return value;
    }
}

namespace KoolBox
{
    // MATHS
    extern float cosa(float x);
    extern float sina(float x);
    extern u32 hash(const void* data, u32 length);
    extern u32 hash(const char* data);
    extern bool isPowerOfTwo(int x);

    inline bool operator ==(const Mat4& l, const Mat4& r) {
        return (std::memcmp(l.matrix, r.matrix, sizeof(l.matrix)) == 0);
    }

    // GRAPHICS

    extern int floatsPerData(const VertexData &data);
    extern int floatsPerVertex(const VertexStructure &vs);

    extern VertexStructure *newVertexStructure(const VertexElementList &attributes);
    extern Shader *loadNewShader(const char *name, ShaderType type);
    extern void loadNewVertexFragmentShaders(const char *name, Shader **vptr, Shader **fptr);

    extern float asFloat(Colour &col);
    extern float asFloat(u32 col);

    // MISC

    // StringReader
    // Enables reading of null-terminated cstrings from FileReader
    class StringReader : private NonCopyable
    {
    public:
        StringReader(const char *filename);
        ~StringReader();

        char        *data;
        int         length;
    };

}

#endif
