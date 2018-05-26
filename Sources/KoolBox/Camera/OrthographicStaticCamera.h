#ifndef KOOLBOX_ORTHOGRAPHICSTATICCAMERA_H
#define KOOLBOX_ORTHOGRAPHICSTATICCAMERA_H

#include "KoolBoxShared.h"
#include "Camera.h"

namespace KoolBox
{
    // OrthographicStaticCamera
    // Non-Moving camera with orthographic projection
    class OrthographicStaticCamera : public Camera
    {
    public:
		OrthographicStaticCamera(Size viewSize);
		~OrthographicStaticCamera();

        // Camera
        Mat4    getViewMatrix();
        Mat4    getProjectionMatrix();
        Mat4    getViewProjectionMatrix();

        // OrthographicStaticCamera
        // change view size eg: if display size is changed
        void    setViewSize(Size viewSize);

    private:
        // recalculate for new view size
        void    resize();

    private:
        Size    viewSize;
        Mat4    viewMatrix;
        Mat4    projMatrix;
        Mat4    viewProjMatrix;
    };
}

#endif
