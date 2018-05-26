#ifndef KOOLBOX_SHARED_H
#define KOOLBOX_SHARED_H

// ----------------------------------------------------------------------------------------------
// Standard Library

#define _USE_MATH_DEFINES
#include <cstddef>
#include <cassert>
#include <cstdint>
#include <cfloat>
#include <cmath>
#include <cstring>
#include <utility>
#include <atomic>
#include <initializer_list>

// ----------------------------------------------------------------------------------------------
// Kore

#include <Kore/pch.h>
#include <Kore/System.h>
#include <Kore/Error.h>
#include <Kore/ErrorArgs.h>
#include <Kore/Log.h>
#include <Kore/LogArgs.h>
#include <Kore/Math/Random.h>
#include <Kore/Input/Keyboard.h>
#include <Kore/Input/Mouse.h>
#include <Kore/Input/Surface.h>
#include <Kore/IO/FileReader.h>
#include <Kore/Graphics1/Color.h>
#include <Kore/Graphics4/Graphics.h>
#include <Kore/Graphics4/Texture.h>
#include <Kore/Graphics4/PipelineState.h>
#include <Kore/Graphics4/Shader.h>
#include <Kore/Audio1/Sound.h>
#include <Kore/Audio1/SoundStream.h>
#include <Kore/Audio3/Audio.h>
#include "Vendor/TinyXML/tinyxml2.h"
#include "Vendor/TinySTL/unordered_map.h"
#include "Vendor/TSL/robin_map.h"
#include "Vendor/TSL/hopscotch_map.h"

// ----------------------------------------------------------------------------------------------
// Vendors

// tinystl
namespace tinystl {}
namespace KoolBox
{
    namespace stl = ::tinystl;
}

namespace tsl {}
namespace KoolBox
{
    namespace tsl = ::tsl;
}

// tinyxml
namespace tinyxml2 {}
namespace KoolBox
{
    namespace XML = ::tinyxml2;
}

// ----------------------------------------------------------------------------------------------
// koolbox

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#define DEG2RAD(X) (X * (M_PI / 180))
#define DEG2RADF(X) ((float) DEG2RAD(X))

// ----------------------------------------------------------------------------------------------
// types

namespace KoolBox
{
	// ----------------------------------------------------------------------------------------------

	// kore type aliases for convenience
    using FileReader            = Kore::FileReader;
    using KeyCode               = Kore::KeyCode;
    using Orientation           = Kore::Orientation;

    using Colour                = Kore::Graphics1::Color;
    using BlendingOperation     = Kore::Graphics4::BlendingOperation;
    using ConstantLocation      = Kore::Graphics4::ConstantLocation;
    using TextureUnit           = Kore::Graphics4::TextureUnit;
    using PipelineState         = Kore::Graphics4::PipelineState;
    using Texture               = Kore::Graphics4::Texture;
    using TextureFilter         = Kore::Graphics4::TextureFilter;
    using TextureAddressing     = Kore::Graphics4::TextureAddressing;
    using RenderTarget          = Kore::Graphics4::RenderTarget;
    using RenderTargetFormat    = Kore::Graphics4::RenderTargetFormat;
    using VertexBuffer          = Kore::Graphics4::VertexBuffer;
    using IndexBuffer           = Kore::Graphics4::IndexBuffer;
    using Texture               = Kore::Graphics4::Texture;
    using Shader                = Kore::Graphics4::Shader;
    using ShaderType            = Kore::Graphics4::ShaderType;
    using VertexStructure       = Kore::Graphics4::VertexStructure;
    using VertexElement         = Kore::Graphics4::VertexElement;
    using VertexData            = Kore::Graphics4::VertexData;

    using Vec2                  = Kore::vec2;
    using Vec3                  = Kore::vec3;
    using Vec4                  = Kore::vec4;
    using Vec2I                 = Kore::vec2i;
    using Vec3I                 = Kore::vec3i;
    using Vec4I                 = Kore::vec4i;
    using Mat3                  = Kore::mat3;
    using Mat4                  = Kore::mat4;

    template <typename K, typename V> using Map  = tsl::robin_map<K,V>;

    typedef std::initializer_list<VertexElement> VertexElementList;
    typedef std::initializer_list<char*>         CStrList;

    // standard types
    using byte  = int8_t;
	using ubyte = uint8_t;
    using u8 	= uint8_t;
    using i8 	= int8_t;
    using u16 	= uint16_t;
    using i16 	= int16_t;
	using i32   = int32_t;
	using u32   = uint32_t;
    using i64   = int64_t;
    using u64   = uint64_t;

    // ----------------------------------------------------------------------------------------------

    // frame timing information
    // supplied to frame update callback
    struct GameTime
    {
        double startTime;	// timestamp of game initial start
        double totalTime;	// time since game initial start
        double lastTime;	// timestamp of last frame
        double thisTime;	// timestamp of this frame
        double deltaTime;	// delta time between last and this frame
		float  deltaTimeF;
        long   count;		// frame count
    };

	// ----------------------------------------------------------------------------------------------

    template<class T>
    struct Handle
    {
        u32 id = UINT32_MAX;
        inline bool valid() { return (id != UINT32_MAX); };
    };

    // lightweight convenience structures to hold various multiple values
    template <typename T>
    struct V2T
    {
        V2T(T a, T b)
        {
            set(a, b);
        };

        V2T() : V2T(0, 0) { };

        void set(T a, T b)
        {
            v[0] = a;
            v[1] = b;
        }

        bool operator==(const V2T<T>& rhs) const {
            return x == rhs.x && y == rhs.y;
        }

        bool operator!=(const V2T<T>& rhs) const {
            return x != rhs.x || y == rhs.y;
        }

        V2T<T>& operator+=(const V2T<T> &rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        V2T<T>& operator-=(const V2T<T> &rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        V2T<T>& operator*=(const float rhs)
        {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        V2T<T>& operator/=(const float rhs)
        {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        V2T<T> operator+(const V2T<T> &rhs) const
        {
            V2T<T> result = *this;
            result.x += rhs.x;
            result.y += rhs.y;
            return result;
        }

        V2T<T> operator-(const V2T<T> &rhs) const
        {
            V2T<T> result = *this;
            result.x -= rhs.x;
            result.y -= rhs.y;
            return result;
        }

        V2T<T> operator*(const V2T<T> &rhs) const
        {
            V2T<T> result = *this;
            result.x *= rhs.x;
            result.y *= rhs.y;
            return result;
        }

        V2T<T> operator*(const float &rhs) const
        {
            V2T<T> result = *this;
            result.x *= rhs;
            result.y *= rhs;
            return result;
        }

        V2T<T> operator/(const V2T<T> &rhs) const
        {
            V2T<T> result = *this;
            result.x /= rhs.x;
            result.y /= rhs.y;
            return result;
        }

        V2T<T> operator/(const float &rhs) const
        {
            V2T<T> result = *this;
            result.x /= rhs;
            result.y /= rhs;
            return result;
        }

        T length() const
        {
            return static_cast<T>( Kore::sqrt(length2()) );
        }

        T length2() const
        {
            return (x * x) + (y * y);
        }

        V2T<T>& truncate(float maxlen)
        {
            float m = static_cast<float>(length2());
            if (m > maxlen*maxlen)
            {
                m = Kore::sqrt(m);
                x = (x / m) * maxlen;
                y = (y / m) * maxlen;
            }
            return *this;
        }

        V2T<T>& clamp(float lb, float ub)
        {
            float m = static_cast<float>(length());
            if (m < lb || m > ub)
            {
                m = Kore::abs((m < lb ? lb : ub) / m);
                x *= m;
                y *= m;
            }
            return *this;
        }

        union
        {
            T v[2];
            union
            {
                struct
                {
                    T x, y;
                };
                struct
                {
                    T a, b;
                };
                struct
                {
                    T w, h;
                };
            };
        };
    };

    typedef V2T<float> V2;
    typedef V2T<int>   V2I;

    using P2    = V2;
    using P2I   = V2I;
    using Size  = V2;
    using SizeI = V2I;

    // ----------------------------------------------------------------------------------------------

    template <typename T>
    struct V3T
    {
        V3T(T a, T b, T c)
        {
            set(a, b, c);
        };

        V3T() : V3T(0, 0, 0) { };

        void set(T a, T b, T c)
        {
            v[0] = a;
            v[1] = b;
            v[2] = c;
        }

        union
        {
            T v[3];
            struct
            {
                T x, y, z;
            };
            struct
            {
                T a, b, c;
            };
        };
    };

    typedef V3T<float> V3;
    typedef V3T<int>   V3I;

    using P3 = V3;
    using P3I = V3I;

    // ----------------------------------------------------------------------------------------------

    template <typename T>
    struct V4T
    {
        V4T(T a, T b, T c, T d)
        {
            set(a, b, c, d);
        };

        V4T() : V4T(0, 0, 0, 0) { };

        void set(T a, T b, T c, T d)
        {
            v[0] = a;
            v[1] = b;
            v[2] = c;
            v[3] = d;
        }

        union
        {
            T v[4];
            struct
            {
                T x, y, z, w;
            };
            struct
            {
                T a, b, c, d;
            };
        };
    };

    typedef V4T<float> V4;
    typedef V4T<int>   V4I;

    // ----------------------------------------------------------------------------------------------

    template <typename T>
    struct RectT
    {
        RectT(float x, float y, float w, float h)
        {
            set(x, y, w, h);
        };

        RectT() : RectT(0, 0, 0, 0) { };

        void set(T x, T y, T w, T h)
        {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }

        union
        {
            T v[4];
            struct
            {
                T x, y, w, h;
            };
            struct
            {
                T x0, y0, x1, y1;
            };
        };
    };

    typedef RectT<float> Rect;
    typedef RectT<int>   RectI;

}

#endif

