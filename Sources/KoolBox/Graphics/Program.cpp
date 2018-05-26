#include "Program.h"
#include "Utility.h"

namespace KoolBox
{

    Program::Program(const Desc &desc, const CStrList constantNames, const CStrList textureUnitNames)
    {
        id = pipeline.id;

        assert(desc.inputLayout[0]);
        assert(desc.vertexShader);
        assert(desc.fragmentShader);

        for (int i = 0; i < 16; i++)
        {
            pipeline.inputLayout[i] = desc.inputLayout[i];
        }
        pipeline.vertexShader = desc.vertexShader;
        pipeline.fragmentShader = desc.fragmentShader;

        pipeline.blendSource = desc.blendSource;
        pipeline.blendDestination = desc.blendDestination;
        pipeline.alphaBlendSource = desc.alphaBlendSource;
        pipeline.alphaBlendDestination = desc.alphaBlendDestination;

        pipeline.compile();

        for (auto name: constantNames)
        {
            constants.insert({ hash(name), pipeline.getConstantLocation(name) });
        }

        for (auto name: textureUnitNames)
        {
            TextureUnit tu = pipeline.getTextureUnit(name);
            tu.id = (u32) tu.unit;

            textureunits.insert({ hash(name), tu });
        }
    }

    Program::~Program()
    {
    }

    //

    ConstantLocation Program::getConstant(const char *name)
    {
        return getConstant(hash(name));
    }

    ConstantLocation Program::getConstant(u32 name)
    {
        auto fnd = constants.find(name);
        assert(fnd != constants.end());
        return fnd->second;
    }

    TextureUnit Program::getTextureUnit(const char *name)
    {
        return getTextureUnit(hash(name));
    }

    TextureUnit Program::getTextureUnit(u32 name)
    {
        auto fnd = textureunits.find(name);
        assert(fnd != textureunits.end());
        return fnd->second;
    }

}
