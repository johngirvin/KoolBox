#include "KoreHooks.h"
#include "KoolBox.h"

using namespace Kore;
using namespace KoolBox;
using namespace KoolBox::Input;

namespace KoolBox
{
    // ----------------------------------------------------------------------------------------------
    // LIFECYCLE

    void OnGameUpdate()
    {
        static GameTime timer;
        static bool     timerInitialised = false;

        const double now = System::time();
        if (!timerInitialised)
        {
            timer.deltaTime = 1.0/60.0;
            timer.totalTime = timer.deltaTime;
            timer.startTime = now - timer.deltaTime;
            timer.lastTime  = timer.startTime;
            timer.thisTime  = now;
            timer.count     = 0;

            timerInitialised = true;
        }
        else
        {
            timer.lastTime  = timer.thisTime;
            timer.thisTime  = now;
            timer.deltaTime = now - timer.lastTime;
            timer.totalTime = now - timer.startTime;
            timer.count     ++;
        }
        
        #ifdef DEBUG
        timer.deltaTime = Kore::min(timer.deltaTime, 1.0/15.0);
        #endif

        timer.deltaTimeF = (float) timer.deltaTime;

        KB_GAME->onUpdate(&timer);
    }

    void OnGameEnteredBackground()
    {
        KB_GAME->onEnteredBackground();
    }

    void OnGameEnteredForeground()
    {
        KB_GAME->onEnteredForeground();
    }

    void OnGameChangedOrientation(Orientation orientation)
    {
        KB_GAME->onChangedOrientation(orientation);
    }

    void OnGamePaused()
    {
        KB_GAME->onPaused();
    }

    void OnGameResumed()
    {
        KB_GAME->onResumed();
    }

    void OnGameWillExit()
    {
        KB_GAME->onWillExit();
    }

    void OnInputMousePressed(int windowId, int button, int x, int y)
    {
        KB_GAME->onMousePressed(windowId, button, x, y);
    }

    void OnInputMouseReleased(int windowId, int button, int x, int y)
    {
        KB_GAME->onMouseReleased(windowId, button, x, y);
    }

    void OnInputMouseMoved(int windowId, int x, int y, int dx, int dy)
    {
        KB_GAME->onMouseMoved(windowId, x, y, dx, dy);
    }

    void OnInputMouseScrolled(int windowId, int d)
    {
        KB_GAME->onMouseScrolled(windowId, d);
    }

    // ----------------------------------------------------------------------------------------------
    // KEY INPUT HANDLING

    void OnInputKeyDown(KeyCode code)
    {
        Key key;
        key.code        = code;
        key.phase       = KeyPhase::Pressed;
        key.time        = System::time();
        KB_GAME->onKeyPressed(key);
    }

    void OnInputKeyUp(KeyCode code)
    {
        Key key;
        key.code        = code;
        key.phase       = KeyPhase::Released;
        key.time        = System::time();
        KB_GAME->onKeyReleased(key);
    }

    // ----------------------------------------------------------------------------------------------
    // TOUCH INPUT HANDLING

    static Touch touches[16];

    void OnInputTouchStarted(int ti, int x, int y)
    {
        if (ti >= 16) { return; }

        Touch &touch = touches[ti];
        touch.id        = ti;
        touch.time      = System::time();
        touch.phase     = TouchPhase::Started;
        touch.delta     = { 0, 0 };
        touch.pos       = { (float) x, (float) y };
        touch.startPos  = touch.pos;
        touch.startTime = touch.time;

        KB_GAME->onTouchStarted(touch);
    }

    void OnInputTouchMoved(int ti, int x, int y)
    {
        if (ti >= 16) { return; }

        Touch &touch = touches[ti];
        touch.time      = System::time();
        touch.phase     = TouchPhase::Moved;
        touch.delta     = { x - touch.pos.x, y - touch.pos.y };
        touch.pos       = { (float) x, (float) y };

        KB_GAME->onTouchMoved(touch);
    }

    void OnInputTouchEnded(int ti, int x, int y)
    {
        if (ti >= 16) { return; }

        Touch &touch = touches[ti];
        touch.time      = System::time();
        touch.phase     = TouchPhase::Ended;
        touch.delta     = { x - touch.pos.x, y - touch.pos.y };
        touch.pos       = { (float) x, (float) y };

        KB_GAME->onTouchEnded(touch);
    }

}


