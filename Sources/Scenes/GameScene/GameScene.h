#ifndef GAME_GAMESCENE_H
#define GAME_GAMESCENE_H

#include "GameShared.h"

namespace Game
{
    class GameScene : public Scene
    {
    public:
		GameScene();
        virtual ~GameScene();

		void moreBunnies();
		void lessBunnies();

	private:
		//
		Camera *camera;
		Gfx    *gfx;

		// Scene
		void onEntry()						override;
		void onExit()						override;
		void update(const GameTime *time) 	override;
		void draw()		                    override;
    };

}

#endif

