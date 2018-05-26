#ifndef KOOLBOX_KOREHOOKS_H
#define KOOLBOX_KOREHOOKS_H

#include "KoolBoxShared.h"

namespace KoolBox
{
    // lifecycle callback hook functions
    // kore will call these functions at the appropriate times
    extern void OnGameEnteredForeground();
    extern void OnGameEnteredBackground();
    extern void OnGamePaused();
    extern void OnGameResumed();
    extern void OnGameChangedOrientation(Kore::Orientation orientation);
    extern void OnGameWillExit();
    extern void OnGameUpdate();
    extern void OnInputKeyDown(Kore::KeyCode code);
    extern void OnInputKeyUp(Kore::KeyCode code);
    extern void OnInputMousePressed(int windowId, int button, int x, int y);
    extern void OnInputMouseReleased(int windowId, int button, int x, int y);
    extern void OnInputMouseMoved(int windowId, int x, int y, int dx, int dy);
    extern void OnInputMouseScrolled(int windowId, int d);
    extern void OnInputTouchStarted(int ti, int x, int y);
    extern void OnInputTouchMoved(int ti, int x, int y);
    extern void OnInputTouchEnded(int ti, int x, int y);
}

#endif

