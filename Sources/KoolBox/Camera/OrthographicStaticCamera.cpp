#include "OrthographicStaticCamera.h"

namespace KoolBox
{
    // ----------------------------------------------------------------------------------------------
    // CONSTRUCTORS

    OrthographicStaticCamera::OrthographicStaticCamera(Size viewSize)
    :   viewSize(viewSize)
    {
        resize();
    }

    OrthographicStaticCamera::~OrthographicStaticCamera()
    {
    }

    // ----------------------------------------------------------------------------------------------
    // Camera

    Mat4 OrthographicStaticCamera::getViewMatrix()
    {
        return viewMatrix;
    }

    Mat4 OrthographicStaticCamera::getProjectionMatrix()
    {
        return projMatrix;
    }

    Mat4 OrthographicStaticCamera:: getViewProjectionMatrix()
    {
        return viewProjMatrix;
    }

    // ----------------------------------------------------------------------------------------------
    // OrthographicStaticCamera

    void OrthographicStaticCamera::setViewSize(Size viewSize)
    {
        this->viewSize = viewSize;
        resize();
    }

    void OrthographicStaticCamera::resize()
    {
        viewMatrix     = Mat4::Identity();
        projMatrix     = Mat4::orthogonalProjection(0, viewSize.w, 0, viewSize.h, -1, 1);
        viewProjMatrix = projMatrix /* * viewMatrix */ ;
    }

}


