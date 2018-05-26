#ifndef KOOLBOX_GRAPHICS_BATCHER_H
#define KOOLBOX_GRAPHICS_BATCHER_H

#include "KoolBox.h"
#include "Vendor/TinySTL/unordered_map.h"

namespace KoolBox
{

    class Batcher : private NonCopyable
    {
    public:
        // constructor
        // ibCount - number of indices to batch at most
        // vbCount - number of vertices to batch at most
        Batcher(u16 ibCount = UINT16_MAX-4, u16 vbCount = UINT16_MAX-4);
        ~Batcher();

        // batcher lifecycle management
        // call begin() before attempting any batcher operations
        // call end() after the last batcher operation
        void begin();
        void end();

        // pipeline state management
        // the batcher will avoid redundant updates of pipeline state where possible
        // each update that is required will force a flush() (ie: a draw call)
        void set(Program *newProgram);
        void set(Program &newProgram);
        void set(TextureUnit newUnit, Texture *newTex, TextureFilter newTexFilter = Kore::Graphics4::PointFilter, TextureAddressing newTexAddressing = Kore::Graphics4::Clamp);
        void set(ConstantLocation location, float v0);
        void set(ConstantLocation location, float v0, float v1);
        void set(ConstantLocation location, float v0, float v1, float v2);
        void set(ConstantLocation location, float v0, float v1, float v2, float v3);
        void set(ConstantLocation location, float *values, u32 size);
        void set(ConstantLocation location, Mat4 &matrix);

        // allocate space in the batcher's buffers to store user indices and vertices
        // iWant - number of indices required, or 0 to not allocate any
        //         if iWant is 0, iPtr is ignored
        // vWant - number of vertices required, or 0 to not allocate any
        //         if vWant is 0, vPtr and vPos are ignored
        // iPtr  - *iPtr will be set to the allocated index space
        // vPtr  - *vPtr[0]...*vPtr[n] will be set to the allocated vertex spaces
        //         (one per configured inputlayout in the current pipeline)
        // vPos  - *vPos will be set to the initial vertex index allocated
        void allocate(u16 iWant, u16 vWant, int **iPtr, float **vPtr, u16 *vPos);

        // force a flush of the currently batched primitives
        void flush();

        // TODO: more statistics
        u32     drawCalls;

    private:
        // number of indices in index buffer
        u16     ibCount;
        // number of vertices in each vertex buffer
        u16     vbCount;

        // status flags
        bool    begun;
        bool    locked;

        // pipeline state management
        typedef struct PrState
        {
            u32     programId = UINT32_MAX;
        }
        PrState;

        typedef struct TxState
        {
            u32               textureId  = UINT32_MAX;
            TextureFilter     filter     = Kore::Graphics4::PointFilter;
            TextureAddressing addressing = Kore::Graphics4::Clamp;
        }
        TxState;

        typedef struct CnVnState
        {
            u32     locationId  = UINT32_MAX;
            u32     size        = 0;
            float   v[4]        = { 0 };
        }
        CnVnState;

        typedef struct CnM4State
        {
            u32     locationId = UINT32_MAX;
            Mat4    mat4;
        }
        CnM4State;

        typedef struct IbState
        {
            IndexBuffer *buffer = nullptr;
            int         *data   = nullptr;

            void clear()
            {
                buffer = nullptr;
                data   = nullptr;
            }
        }
        IbState;

        typedef struct VbState
        {
            VertexBuffer *buffer = nullptr;
            float       *data    = nullptr;
            u32         fpv      = 0;

            void clear()
            {
                buffer = nullptr;
                data   = nullptr;
                fpv    = 0;
            }
        }
        VbState;

        struct BatcherState
        {
            PrState              program;
            Map<u32,TxState>     texture;
            Map<u32,CnVnState>   cnvn;
            Map<u32,CnM4State>   cnm4;

            IbState ib;
            VbState vb[8];

            // current index/vertex positions
            u16     ibPos;
            u16     vbPos;

            void clear()
            {
                program.programId = UINT32_MAX;
                texture.clear();
                cnvn.clear();
                cnm4.clear();
                ib.clear();
                for (int i = 0; i < 8; i++) {
                    vb[i].clear();
                }
                ibPos = 0;
                vbPos = 0;
            }
        }
        state;

        // the index buffer
        IndexBuffer *ib = nullptr;

        // map indicating which VertexBuffer to use for a given VertexStructure id
        Map<u32,VertexBuffer*> buffersForStructures;

        // get or create a VertexBuffer to hold vertices in vertexStructure format
        // one buffer will be allocated per batcher per unique vertexStructure
        VertexBuffer *getVertexBuffer(const VertexStructure &vertexStructure);

        // prepare buffers for use
        void lock();
        void unlock();
    };

}

#endif

