#include "Batcher.h"

namespace KoolBox
{
    Batcher::Batcher(u16 ibCount, u16 vbCount)
    :   ibCount(ibCount),
        vbCount(vbCount),
        begun(false),
        locked(false)
    {
        assert(ibCount > 0);
        assert(vbCount > 0);

        // preallocate index buffer
        ib = new IndexBuffer(ibCount);
        assert(ib);

        // initialise batcher state
        state.clear();
        state.ib.buffer = ib;
    }

    Batcher::~Batcher()
    {
        // delete index/vertex buffers
        delete ib;

        for (auto &iter: buffersForStructures)
        {
            delete iter.second;
        }
        buffersForStructures.clear();

        state.clear();
    }

    // RENDERING

    void Batcher::set(Program *newProgram)
    {
        set(*newProgram);
    }

    void Batcher::set(Program &newProgram)
    {
        assert(begun);

        if (state.program.programId == newProgram.id) { return; }

        // flush current batch before state change
        flush();

        // update state
        Kore::Graphics4::setPipeline(const_cast<PipelineState *>( &(newProgram.pipeline) ));
        state.program.programId = newProgram.id;
        state.cnm4.clear();
        state.cnvn.clear();

        // select vertex buffer(s) to use
        for (u32 i = 0; i < 8; i++)
        {
            state.vb[i].clear();

            VertexStructure *vs = newProgram.pipeline.inputLayout[i];
            if (vs == nullptr) { continue; }

            state.vb[i].buffer = getVertexBuffer(*vs);
            state.vb[i].fpv    = state.vb[i].buffer->stride() / sizeof(float);
            assert(state.vb[i].buffer);
            assert(state.vb[i].fpv > 0);
        }

        // prepare buffers for use
        lock();
    }

    void Batcher::set(TextureUnit newUnit, Texture *newTex, TextureFilter newTexFilter, TextureAddressing newTexAddressing)
    {
        assert(begun);

        auto &result = state.texture[newUnit.id];
        if (result.textureId == newTex->id && result.filter == newTexFilter && result.addressing == newTexAddressing) { return; }

        // flush current batch before state change
        flush();

        // update state
        if (result.textureId != newTex->id)
        {
            Kore::Graphics4::setTexture(newUnit, newTex);
        }
        if (result.textureId != newTex->id || result.filter != newTexFilter)
        {
            Kore::Graphics4::setTextureMinificationFilter(newUnit , newTexFilter);
            Kore::Graphics4::setTextureMagnificationFilter(newUnit, newTexFilter);
        }
        if (result.textureId != newTex->id || result.addressing != newTexAddressing)
        {
            Kore::Graphics4::setTextureAddressing(newUnit, Kore::Graphics4::U, newTexAddressing);
            Kore::Graphics4::setTextureAddressing(newUnit, Kore::Graphics4::V, newTexAddressing);
        }
        Kore::Graphics4::setTextureMipmapFilter(newUnit, Kore::Graphics4::NoMipFilter);

        result.textureId  = newTex->id;
        result.filter     = newTexFilter;
        result.addressing = newTexAddressing;

        lock();
    }

    void Batcher::set(ConstantLocation location, float v0)
    {
        float v[] = { v0 };
        set(location, v, 1);
    }

    void Batcher::set(ConstantLocation location, float v0, float v1)
    {
        float v[] = { v0, v1 };
        set(location, v, 2);
    }

    void Batcher::set(ConstantLocation location, float v0, float v1, float v2)
    {
        float v[] = { v0, v1, v2 };
        set(location, v, 3);
    }

    void Batcher::set(ConstantLocation location, float v0, float v1, float v2, float v3)
    {
        float v[] = { v0, v1, v2, v3 };
        set(location, v, 4);
    }

    void Batcher::set(ConstantLocation location, float *values, u32 size)
    {
        assert(begun);

        auto &result = state.cnvn[location.id];
        if (result.locationId == location.id && result.size == size && std::memcmp(result.v, values, sizeof(float)*size) == 0) { return; }

        // flush current batch before state change
        flush();

        // update state
        Kore::Graphics4::setFloats(location, values, size);

        result.locationId = location.id;
        result.size       = size;
        std::memcpy(&result.v, values, sizeof(float) * size);

        lock();
    }

    void Batcher::set(ConstantLocation location, Mat4 &matrix)
    {
        assert(begun);

        auto &result = state.cnm4[location.id];
        if (result.locationId == location.id && result.mat4 == matrix) { return; }

        // flush current batch before state change
        flush();

        // update state
        Kore::Graphics4::setMatrix(location, matrix);

        result.locationId = location.id;
        result.mat4       = matrix;

        lock();
    }

    // INTERNAL

    VertexBuffer *Batcher::getVertexBuffer(const VertexStructure &vertexStructure)
    {
        assert(vertexStructure.id > 0);

        auto &vb = buffersForStructures[vertexStructure.id];
        if (vb == nullptr)
        {
            vb = new VertexBuffer(vbCount, vertexStructure);
        }

        assert(vb);
        return vb;
    }

    //

    void Batcher::begin()
    {
        assert(!begun);
        assert(!locked);

        drawCalls = 0;

        state.clear();
        state.ib.buffer = ib;

        begun = true;
    }

    void Batcher::allocate(u16 iWant, u16 vWant, int **iPtr, float **vPtr, u16 *vPos)
    {
        assert(begun);
        assert(iWant >= 0);
        assert(vWant >= 0);
        assert(iWant > 0 || vWant > 0);
        assert(iWant == 0 || (iWant != 0 && iPtr != nullptr));
        assert(vWant == 0 || (vWant != 0 && vPtr != nullptr));

        if (state.ibPos + iWant >= ibCount || state.vbPos + vWant >= vbCount)
        {
            flush();
            lock();
        }

        if (!locked)
        {
            lock();
        }
        assert(locked);

        if (iWant > 0)
        {
            assert(state.ibPos >= 0);
            assert(state.vbPos >= 0);
            *vPos = state.vbPos;

            assert(state.ib.data);
            *iPtr = (state.ib.data + state.ibPos);

            state.ibPos += iWant;
            assert(state.ibPos < ibCount);
        }

        if (vWant > 0)
        {
            assert(state.vbPos >= 0);
            *vPos = state.vbPos;

            for (u32 i = 0; i < 8; i++)
            {
                if (state.vb[i].buffer == nullptr) { break; }

                assert(state.vb[i].data);
                *(vPtr+i) = (state.vb[i].data + (state.vbPos * state.vb[i].fpv));
            }

            state.vbPos += vWant;
            assert(state.vbPos < vbCount);
        }
    }

    void Batcher::lock()
    {
        assert(!locked);
        assert(state.ib.buffer);
        assert(state.vb[0].buffer);

        state.ib.data = state.ib.buffer->lock();
        assert(state.ib.data);

        for (u32 i = 0; i < 8; i++)
        {
            if (state.vb[i].buffer == nullptr) { break; }
            state.vb[i].data  = state.vb[i].buffer->lock();
            assert(state.vb[i].data);
        }

        locked = true;
    }

    void Batcher::unlock()
    {
        assert(locked);
        assert(state.ib.buffer);
        assert(state.vb[0].buffer);

        state.ib.buffer->unlock();
        state.ib.data = nullptr;

        for (u32 i = 0; i < 8; i++)
        {
            if (state.vb[i].buffer == nullptr) { break; }
            state.vb[i].buffer->unlock();
            state.vb[i].data = nullptr;
        }

        locked = false;
    }

    void Batcher::flush()
    {
        assert(begun);

        if (locked)
        {
            unlock();
        }
        assert(!locked);

        if (state.ibPos > 0 && state.vbPos > 0)
        {
            // set buffers on the back end and submit
            VertexBuffer *vbList[8]  = { 0 };
            u32           vbListSize = 0;
            for (u32 i = 0; i < 8; i++)
            {
                if (state.vb[i].buffer == nullptr) { break; }
                vbList[vbListSize++] = state.vb[i].buffer;
            }
            assert(vbListSize > 0);

            Kore::Graphics4::setIndexBuffer(*(state.ib.buffer));
            Kore::Graphics4::setVertexBuffers(vbList, vbListSize);
            Kore::Graphics4::drawIndexedVertices(0, state.ibPos);

            state.ibPos = 0;
            state.vbPos = 0;

            drawCalls++;
        }

        assert(!locked);
        assert(state.ibPos == 0);
        assert(state.vbPos == 0);
    }

    void Batcher::end()
    {
        assert(begun);

        flush();
        state.clear();

        begun = false;
    }


}
