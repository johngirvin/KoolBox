#ifndef KOOLBOX_GAME_H
#define KOOLBOX_GAME_H

#include "KoolBoxShared.h"
#include "NonCopyable.h"
#include "Input.h"

namespace KoolBox
{
    // KoolBoxGame
    // Base class for all games made with KoolBox
    // Inherit from this class as the main class of your game
    class KoolBoxGame : private NonCopyable
    {
    public:
        // Lifecycle and input callbacks.
        // Game class should override these as required.
        // Default implementations do nothing.
        virtual void onEnteredForeground();
        virtual void onEnteredBackground();
        virtual void onPaused();
        virtual void onResumed();
        virtual void onChangedOrientation(Orientation orientation);
        virtual void onWillExit();
        virtual void onUpdate(const GameTime *time);

        virtual void onKeyPressed(const Input::Key &key);
        virtual void onKeyReleased(const Input::Key &key);

        virtual void onMousePressed(int windowId, int button, int x, int y);
        virtual void onMouseReleased(int windowId, int button, int x, int y);
        virtual void onMouseMoved(int windowId, int x, int y, int dx, int dy);
        virtual void onMouseScrolled(int windowId, int d);

        virtual void onTouchStarted(const Input::Touch &touch);
        virtual void onTouchMoved(const Input::Touch &touch);
        virtual void onTouchEnded(const Input::Touch &touch);

    protected:
        KoolBoxGame();
        virtual ~KoolBoxGame();
    };

    // global reference to the KoolBoxGame singleton
    // Kore functions use this reference to call lifecycle hooks
    // @see: Kore.h
    extern KoolBoxGame *KB_GAME;
}

#endif

