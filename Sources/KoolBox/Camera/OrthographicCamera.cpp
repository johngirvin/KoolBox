#include "OrthographicCamera.h"

namespace KoolBox
{
    // ----------------------------------------------------------------------------------------------
    // CONSTRUCTORS

    OrthographicCamera::OrthographicCamera(Size viewSize)
    :   viewSize(viewSize), position(0,0), zoom(1), rotation(0)
    {
        resize();
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    // ----------------------------------------------------------------------------------------------
    // Camera

    Mat4 OrthographicCamera::getViewMatrix()
    {
        // TODO: optimise this:
        // (1) cache and update only if transform dirty
        // (2) combine first two translations
        // (3) unroll matrix muls - many elements will be 0 or 1

        viewMatrix =
            Mat4::Translation(-position.x(), -position.y(), 0)
                * Mat4::Translation(origin.x(), origin.y(), 0)
                * Mat4::Scale(zoom, zoom, 1)
                * Mat4::RotationZ(rotation)
                * Mat4::Translation(-origin.x(), -origin.y(), 0);

        return viewMatrix;
    }

    Mat4 OrthographicCamera::getProjectionMatrix()
    {
        return projMatrix;
    }

    Mat4 OrthographicCamera:: getViewProjectionMatrix()
    {
        // TODO: optimise this
        // (1) cache and update only if dirty
        return getProjectionMatrix() * getViewMatrix();
    }

    // ----------------------------------------------------------------------------------------------
    // OrthographicCamera

    void OrthographicCamera::setViewSize(Size viewSize)
    {
        this->viewSize = viewSize;
        resize();
    }

    Vec2 OrthographicCamera::getPosition()
    {
        return position;
    }

    float OrthographicCamera::getRotation()
    {
        return rotation;
    }

    float OrthographicCamera::getZoom()
    {
        return zoom;
    }

    OrthographicCamera *OrthographicCamera::moveTo(Vec2 pos)
    {
        position = pos;
        return this;
    }

    OrthographicCamera  *OrthographicCamera::moveTo(float x, float y)
    {
        position.set(x, y);
        return this;
    }

    OrthographicCamera *OrthographicCamera::moveBy(Vec2 delta)
    {
        position += delta;
        return this;
    }

    OrthographicCamera *OrthographicCamera::moveBy(float dx, float dy)
    {
        position.set(position.x() + dx, position.y() + dy);
        return this;
    }

    OrthographicCamera *OrthographicCamera::rotateTo(float radians)
    {
        rotation = radians;
        return this;
    }

    OrthographicCamera *OrthographicCamera::rotateBy(float delta)
    {
        rotation += delta;
        return this;
    }

    OrthographicCamera *OrthographicCamera::zoomTo(float zoom)
    {
        this->zoom = zoom;
        return this;
    }

    OrthographicCamera *OrthographicCamera::zoomBy(float delta)
    {
        this->zoom += delta;
        return this;
    }

    void OrthographicCamera::resize()
    {
        origin.set(viewSize.w * 0.5f, viewSize.h * 0.5f);
        projMatrix = Mat4::orthogonalProjection(0, viewSize.w, 0, viewSize.h, -1, 1);
    }

}


