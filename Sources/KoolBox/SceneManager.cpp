#include "SceneManager.h"
#include "Scene.h"

using namespace Kore;

namespace KoolBox
{

    Scene *SceneManager::getCurrentScene()
    {
        return currentScene;
    }

    void SceneManager::changeToScene(Scene *scene)
    {
        if (currentScene)
        {
            currentScene->onExit();
        }

        if (scene)
        {
            currentScene = scene;
            currentScene->onEntry();
        }
    }

    void SceneManager::update(const GameTime *time)
    {
        if (currentScene)
        {
            currentScene->update(time);
        }
    }

    void SceneManager::draw()
    {
        if (currentScene)
        {
            currentScene->draw();
        }
    }
}
