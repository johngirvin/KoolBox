#include "KoolBoxGame.h"

#include "KoreHooks.h"

using namespace Kore;

namespace KoolBox
{
    // ----------------------------------------------------------------------------------------------
    // GLOBALS

    KoolBoxGame *KB_GAME = nullptr;

    // ----------------------------------------------------------------------------------------------
    // CONSTRUCTORS

    KoolBoxGame::KoolBoxGame()
    {
		// set singleton
        KB_GAME = this;

        // initialise system
        System::setup();

        // initialise callbacks
        System::setForegroundCallback(KoolBox::OnGameEnteredForeground);
        System::setBackgroundCallback(KoolBox::OnGameEnteredBackground);
        System::setPauseCallback(KoolBox::OnGamePaused);
        System::setResumeCallback(KoolBox::OnGameResumed);
        System::setOrientationCallback(KoolBox::OnGameChangedOrientation);
        System::setShutdownCallback(KoolBox::OnGameWillExit);
        System::setCallback(KoolBox::OnGameUpdate);

        auto keyboard = Keyboard::the();
        keyboard->KeyDown   = KoolBox::OnInputKeyDown;
        keyboard->KeyUp     = KoolBox::OnInputKeyUp;

        auto mouse = Mouse::the();
        mouse->Move         = KoolBox::OnInputMouseMoved;
        mouse->Press        = KoolBox::OnInputMousePressed;
        mouse->Release      = KoolBox::OnInputMouseReleased;
        mouse->Scroll       = KoolBox::OnInputMouseScrolled;

        auto surface = Surface::the();
        surface->TouchStart = KoolBox::OnInputTouchStarted;
        surface->Move       = KoolBox::OnInputTouchMoved;
        surface->TouchEnd   = KoolBox::OnInputTouchEnded;

        // TODO: GamePad callbacks
        // ? how to support multiple gamepads
        // ? how to detect gamepad add/remove
    }

    KoolBoxGame::~KoolBoxGame()
    {
        KB_GAME = nullptr;
    }

    // ----------------------------------------------------------------------------------------------
    // LIFECYCLE

    void KoolBoxGame::onEnteredBackground()
    {
    }

    void KoolBoxGame::onEnteredForeground()
    {
    }

    void KoolBoxGame::onPaused()
    {
    }

    void KoolBoxGame::onResumed()
    {
    }

    void KoolBoxGame::onChangedOrientation(Orientation orientation)
    {
    }

    void KoolBoxGame::onWillExit()
    {
    }

    void KoolBoxGame::onUpdate(const GameTime *time)
    {
    }

    // ----------------------------------------------------------------------------------------------
    // INPUT

    void KoolBoxGame::onKeyPressed(const Input::Key &key)
    {
    }

    void KoolBoxGame::onKeyReleased(const Input::Key &key)
    {
    }

    //

    void KoolBoxGame::onMouseMoved(int windowId, int x, int y, int dx, int dy)
    {
    }

    void KoolBoxGame::onMousePressed(int windowId, int button, int x, int y)
    {
    }

    void KoolBoxGame::onMouseReleased(int windowId, int button, int x, int y)
    {
    }

    void KoolBoxGame::onMouseScrolled(int windowId, int d)
    {
    }

    //

    void KoolBoxGame::onTouchStarted(const Input::Touch &touch)
    {
    }

    void KoolBoxGame::onTouchMoved(const Input::Touch &touch)
    {
    }

    void KoolBoxGame::onTouchEnded(const Input::Touch &touch)
    {
    }

}


