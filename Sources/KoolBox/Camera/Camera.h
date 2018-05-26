#ifndef KOOLBOX_CAMERA_H
#define KOOLBOX_CAMERA_H

#include "KoolBoxShared.h"
#include "NonCopyable.h"

namespace KoolBox
{
    // Camera
    // Base class for cameras
    class Camera : private NonCopyable
    {
    public:
        // contructor, destructor
		Camera();
		virtual ~Camera();

        // access camera matrices
        virtual Mat4    getViewMatrix()            = 0;
        virtual Mat4    getProjectionMatrix()      = 0;
        virtual Mat4    getViewProjectionMatrix()  = 0;
    };

}

#endif

