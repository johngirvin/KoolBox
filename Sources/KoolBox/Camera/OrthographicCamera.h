#ifndef KOOLBOX_ORTHOGRAPHICCAMERA_H
#define KOOLBOX_ORTHOGRAPHICCAMERA_H

#include "KoolBoxShared.h"
#include "Camera.h"

namespace KoolBox
{
    // OrthographicStaticCamera
    // Camera with ortho projection that is capable of moving around the world
    class OrthographicCamera : public Camera
    {
    public:
		OrthographicCamera(Size viewSize);
		~OrthographicCamera();

        // Camera
        Mat4                 getViewMatrix();
        Mat4                 getProjectionMatrix();
        Mat4                 getViewProjectionMatrix();

        // OrthographicCamera
        // access camera transform
        void                 setViewSize(Size viewSize);
        Vec2                 getPosition();
        float                getRotation();
        float                getZoom();

        // modify camera transform
        OrthographicCamera  *moveTo(Vec2 pos);
        OrthographicCamera  *moveTo(float dx, float dy);
        OrthographicCamera  *moveBy(Vec2 delta);
        OrthographicCamera  *moveBy(float dx, float dy);

        OrthographicCamera  *zoomTo(float zoom);
        OrthographicCamera  *zoomBy(float zoom);

        OrthographicCamera  *rotateTo(float radians);
        OrthographicCamera  *rotateBy(float radians);

    private:
        void                 resize();

    private:
        Size                 viewSize;
        Vec2                 position;
        Vec2                 origin;
        float                rotation;
        float                zoom;
        Mat4                 viewMatrix;
        Mat4                 projMatrix;
    };
}

#endif
