#ifndef KOOLBOX_GRAPHICS_PIPELINE_H
#define KOOLBOX_GRAPHICS_PIPELINE_H

#include "KoolBoxShared.h"
#include "NonCopyable.h"
#include "Vendor/TinySTL/unordered_map.h"

namespace KoolBox
{

    class Program : private NonCopyable
    {
    public:
        typedef struct Desc
        {
        public:
            VertexStructure   *inputLayout[16]          = { 0 };
            Shader            *vertexShader             = nullptr;
            Shader            *fragmentShader           = nullptr;
            BlendingOperation blendSource               = Kore::Graphics4::BlendOne;
            BlendingOperation blendDestination          = Kore::Graphics4::InverseSourceAlpha;
            BlendingOperation alphaBlendSource          = Kore::Graphics4::SourceAlpha;
            BlendingOperation alphaBlendDestination     = Kore::Graphics4::InverseSourceAlpha;

            Desc()  = default;
            ~Desc() = default;

            Desc(Shader *vs, Shader *fs, VertexStructure *vs0)
            :   Desc()
            {
                inputLayout[0] = vs0;
                vertexShader   = vs;
                fragmentShader = fs;
            }
        }
        Desc;

        Program(const Desc& desc, const CStrList constantNames, const CStrList textureUnitNames);
        ~Program();

        u32              id;
        PipelineState    pipeline;
        ConstantLocation getConstant(const char *name);
        ConstantLocation getConstant(u32 name);
        TextureUnit      getTextureUnit(const char *name);
        TextureUnit      getTextureUnit(u32 name);

    private:
        Map<u32,ConstantLocation> constants;
        Map<u32,TextureUnit>      textureunits;
    };

}

#endif

