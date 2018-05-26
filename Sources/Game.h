#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "GameShared.h"

namespace Game
{
    class GameScene;

	// Game
	// Main game class. Must override KoolBoxGame
    class Game : KoolBoxGame
    {
    public:
        Game(int argc, char** argv);
        ~Game();

        int             		windowId;
        Size            		windowSize;
		Size            		virtualSize;
		Size            		virtualHalf;
        bool 					paused;
        ViewportAdapter         *viewport;
        Mat4					viewportViewProjMatrix;

        Assets                  *assets;
        Gfx						*gfx;

    private:
		void loadContent();
		void unloadContent();
		void onEnteredBackground()					override;
		void onEnteredForeground()					override;
		void onPaused()								override;
		void onResumed()							override;
		void onUpdate(const GameTime *time) 		override;

		void onMouseReleased(int windowId, int button, int x, int y) override;
		void onTouchEnded(const Input::Touch &touch)			     override;

		GameScene *gameScene;

		void updateWindowSize(Size windowSize);

	};

	// GLOBALS
	extern Game         *GAME;
    extern RenderTarget *RETRORENDERTARGET;
	extern SceneManager *SCENEMANAGER;
}

#endif


