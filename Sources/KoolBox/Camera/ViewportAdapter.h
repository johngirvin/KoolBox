#ifndef KOOLBOX_VIEWPORTADAPTER_H
#define KOOLBOX_VIEWPORTADAPTER_H

#include "KoolBoxShared.h"
#include "NonCopyable.h"

namespace KoolBox
{
    // ViewportAdapter
    // Helper to scale a source rect to a target rect using a variety of fit strategies
    class ViewportAdapter : private NonCopyable
    {
    public:
        // construct adapter for the specified sizes
		ViewportAdapter(Size sourceSize, Size targetSize);

        // destructor
        virtual ~ViewportAdapter();

        // update source and target size
        virtual void    setSourceSize(Size newSize);
        virtual void    setTargetSize(Size newSize);

        // get rect in Target that Source occupies when scaled
        Rect            getRect()       { return targetRect;   };
        float           getRectX()      { return targetRect.x; };
        float           getRectY()      { return targetRect.y; };
        float           getRectWidth()  { return targetRect.w; };
        float           getRectHeight() { return targetRect.h; };

    protected:
        // recalculate for a different source/target size
        virtual void    resize() = 0;

        Size            sourceSize;
        Size            targetSize;
        Rect            targetRect;
    };

    // ----------------------------------------------------------------------------------------------
    // FillViewportAdapter
    // Source is scaled so that the entire Target is filled.
    // Source will extend outside Target either horizontally or vertically if their
    // aspect ratios are different.
    // ----------------------------------------------------------------------------------------------

    class FillViewportAdapter : public ViewportAdapter
    {
    public:
        FillViewportAdapter(Size sourceSize, Size targetSize);

    private:
        void resize() override;
    };

    // ----------------------------------------------------------------------------------------------
    // FitViewportAdapter
    // Source is scaled so that it fits into Target without cropping, expanding to
    // entirely fill either height or width of Target. Letter/Pillarboxing will happen.
    // ----------------------------------------------------------------------------------------------

    class FitViewportAdapter : public ViewportAdapter
    {
    public:
        FitViewportAdapter(Size sourceSize, Size targetSize);

    private:
        void resize() override;
    };

    // ----------------------------------------------------------------------------------------------
    // IntegerFitViewportAdapter
    // Like FitViewportAdapter except the scale factor will be rounded down to an integer.
    // Letter/Pillarboxing will happen more.
    // ----------------------------------------------------------------------------------------------

    class IntegerFitViewportAdapter : public ViewportAdapter
    {
    public:
        IntegerFitViewportAdapter(Size sourceSize, Size targetSize);

    private:
        void resize() override;
    };

}

#endif
