#include "ViewportAdapter.h"

using namespace Kore;

namespace KoolBox
{
    // ----------------------------------------------------------------------------------------------
    // CONSTRUCTORS

    ViewportAdapter::ViewportAdapter(Size sourceSize, Size targetSize)
    : sourceSize(sourceSize),
      targetSize(targetSize),
      targetRect(0, 0, targetSize.w, targetSize.h)
    {
    }

    ViewportAdapter::~ViewportAdapter()
    {
    }

    // ----------------------------------------------------------------------------------------------
    // ACCESSORS

    void ViewportAdapter::setSourceSize(Size newSize)
    {
        sourceSize = newSize;
        resize();
    }

    void ViewportAdapter::setTargetSize(Size newSize)
    {
        targetSize = newSize;
        resize();
    }

    // ----------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------
    // FillViewportAdapter
    // ----------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------

    FillViewportAdapter::FillViewportAdapter(Size sourceSize, Size targetSize)
    :   ViewportAdapter(sourceSize, targetSize)
    {
        resize();
    }

    void FillViewportAdapter::resize()
    {
        targetRect = Rect(0, 0, targetSize.w, targetSize.h);
    }

    // ----------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------
    // FitViewportAdapter
    // ----------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------

    FitViewportAdapter::FitViewportAdapter(Size sourceSize, Size targetSize)
    :   ViewportAdapter(sourceSize, targetSize)
    {
        resize();
    }

    void FitViewportAdapter::resize()
    {
        // calculate largest rect that fits in the target while preserving aspect ratio
        float aspect = sourceSize.w / sourceSize.h;
        targetRect.w = targetSize.w ;
        targetRect.h = targetRect.w / aspect;

        // switch to pillarbox if height doesn't fit in to the screen
        if (targetRect.h > targetSize.h)
        {
            targetRect.h = targetSize.h;
            targetRect.w = targetRect.h * aspect;
        }

        // make width and height even
        targetRect.w = Kore::floor(targetRect.w * 0.5f) * 2.0f;
        targetRect.h = Kore::floor(targetRect.h * 0.5f) * 2.0f;

        // center in target
        targetRect.x = (targetSize.w - targetRect.w) * 0.5f;
        targetRect.y = (targetSize.h - targetRect.h) * 0.5f;
    }

    // ----------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------
    // IntegerFitViewportAdapter
    // ----------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------

    IntegerFitViewportAdapter::IntegerFitViewportAdapter(Size sourceSize, Size targetSize)
    :   ViewportAdapter(sourceSize, targetSize)
    {
        resize();
    }

    void IntegerFitViewportAdapter::resize()
    {
        // calculate largest integer scale that will still fit
        float scale  = Kore::min(Kore::floor(targetSize.w / sourceSize.w), Kore::floor(targetSize.h / sourceSize.h));
        targetRect.w = sourceSize.w * scale;
        targetRect.h = sourceSize.h * scale;

        // make width and height even
        targetRect.w = Kore::floor(targetRect.w * 0.5f) * 2.0f;
        targetRect.h = Kore::floor(targetRect.h * 0.5f) * 2.0f;

        // center in target
        targetRect.x = (targetSize.w - targetRect.w) * 0.5f;
        targetRect.y = (targetSize.h - targetRect.h) * 0.5f;
    }

}
