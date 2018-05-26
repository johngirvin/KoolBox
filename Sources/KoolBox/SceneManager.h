#ifndef KOOLBOX_SCENEMANAGER_H
#define KOOLBOX_SCENEMANAGER_H

#include "KoolBoxShared.h"
#include "NonCopyable.h"

namespace KoolBox
{
	class Scene;

	class SceneManager : NonCopyable
	{
	public:
        Scene *getCurrentScene();
        void  changeToScene(Scene *scene);

		void	update(const GameTime *time);
		void 	draw();

	private:
		Scene *currentScene;
	};
}

#endif

