#include "Game.h"
#include "GameScene.h"

using namespace Kore;
using namespace KoolBox;

namespace Game
{
    Game         *GAME              = nullptr;
    RenderTarget *RETRORENDERTARGET = nullptr;
    SceneManager *SCENEMANAGER      = nullptr;
}

namespace Game
{
    // ----------------------------------------------------------------------------------------------
    // CONSTRUCTORS

    Game::Game(int argc, char** argv)
	:   KoolBoxGame(),
        paused(true)
    {
        // initialise
        System::setName("K007");
        System::setKeepScreenOn(true);

        // initialise window
        virtualSize = Size(1334, 750);
        virtualHalf = Size(virtualSize.w * 0.5f, virtualSize.h * 0.5f);

        WindowOptions options;
        options.title           = System::name();
        options.x               = 0;
        options.y               = 0;
        options.vSync           = true;
		#if (KORE_WINDOWS || KORE_MACOS)
		options.mode			= WindowMode::WindowModeWindow;
		options.width			= 1334;
		options.height			= 750;
        #elif KORE_IOS
        options.mode            = WindowMode::WindowModeFullscreen;
		options.width			= 1334;
		options.height			= 750;
		#else
		options.mode			= WindowMode::WindowModeWindow;
        #endif
		options.targetDisplay   = -1;
        options.rendererOptions.textureFormat     = 0;
        options.rendererOptions.depthBufferBits   = 0;
        options.rendererOptions.stencilBufferBits = 0;
        options.rendererOptions.antialiasing      = 0;

        windowId   = System::initWindow(options);
        windowSize = Size(System::windowWidth(windowId), System::windowHeight(windowId));

        // load content
        loadContent();

        // create view
        viewport = new FitViewportAdapter(virtualSize, windowSize);
        updateWindowSize(windowSize);

        // create global singletons
        GAME              = this;
        SCENEMANAGER      = new SceneManager();
        RETRORENDERTARGET = new RenderTarget(
             virtualSize.w,
             virtualSize.h,
             0,
             false,
             RenderTargetFormat::Target32Bit,
             -1,
             windowId
        );

        //
        gfx = new Gfx();

        // run initial scene
        gameScene = new GameScene();
        SCENEMANAGER->changeToScene(gameScene);
        paused = false;
    }

    Game::~Game()
    {
        paused  = true;

        delete gameScene;
        delete viewport;

        unloadContent();

        delete gfx;

        delete SCENEMANAGER;       SCENEMANAGER = nullptr;
        delete RETRORENDERTARGET;  RETRORENDERTARGET  = nullptr;
        
        GAME = nullptr;
    }

    // ----------------------------------------------------------------------------------------------
    // LIFECYCLE

    void Game::loadContent()
    {
        assets = new Assets();
    }

    void Game::unloadContent()
    {
        delete assets; assets = nullptr;
    }

    void Game::onEnteredBackground()
    {
        Kore::log(Info, "OnEnteredBackground");
    }

    void Game::onEnteredForeground()
    {
        Kore::log(Info, "OnEnteredForeground");
    }

    void Game::onPaused()
    {
        Kore::log(Info, "OnPaused");
        paused = true;
    }

    void Game::onResumed()
    {
        Kore::log(Info, "OnResumed");
        paused = false;
    }

    void Game::updateWindowSize(Size newWindowSize)
    {
        viewport->setTargetSize(newWindowSize);

        Rect t = viewport->getRect();
        viewportViewProjMatrix = Mat4::orthogonalProjection(t.x, t.x+t.w, t.y, t.y+t.h, -100, 100);

        windowSize = newWindowSize;
    }

    // ----------------------------------------------------------------------------------------------
    // INPUT

    void Game::onMouseReleased(int windowId, int button, int x, int y)
    {
        if (!gameScene) { return; }

        if (x < windowSize.w * 0.5f) {
            gameScene->lessBunnies();
        } else {
            gameScene->moreBunnies();
        }
    }

    void Game::onTouchEnded(const Input::Touch &touch)
    {
        if (!gameScene) { return; }

        if (touch.pos.x < windowSize.w * 0.5f) {
            gameScene->lessBunnies();
        } else {
            gameScene->moreBunnies();
        }
    }

    // ----------------------------------------------------------------------------------------------
    // UPDATE & RENDER

    void Game::onUpdate(const GameTime *time)
    {
        //
        // UPDATE
        //

        // handle screen/window size change
        Size newWindowSize = Size(System::windowWidth(windowId), System::windowHeight(windowId));
        if (windowSize != newWindowSize)
        {
            updateWindowSize(newWindowSize);
        }
        
        // update current scene
        SCENEMANAGER->update(time);

        //
        // RENDER
        //

        // render scene to lowres buffer
        Graphics4::begin();
        {
            Graphics4::viewport(
                    (int) 0,
                    (int) 0,
                    (int) windowSize.w,
                    (int) windowSize.h
            );
            Graphics4::disableScissor();

            //Graphics4::setRenderTarget(RETRORENDERTARGET);
            {
                SCENEMANAGER->draw();
            }
            //Graphics4::restoreRenderTarget();
        }
        Graphics4::end();

        /*
        // render lowresbuffer to screen
        Graphics4::begin();
        {
            // clear display
            Graphics4::viewport(
                (int) 0,
                (int) 0,
                (int) windowSize.w,
                (int) windowSize.h
            );
            Graphics4::disableScissor();
            Graphics4::clear(Graphics4::ClearColorFlag, Colour::Cyan);

            // clear target rect to background colour
            Rect targetRect = viewport->getRect();
            Graphics4::viewport(
                (int) targetRect.x,
                (int) targetRect.y,
                (int) targetRect.w,
                (int) targetRect.h
            );
            Graphics4::scissor(
                (int) targetRect.x,
                (int) targetRect.y,
                (int) targetRect.w,
                (int) targetRect.h
            );
            Graphics4::clear(Graphics4::ClearColorFlag, Colour::Blue);

            // write vertex data to buffer
            // 1-2  1,2,0
            // |/|  0,2,3
            // 0-3
            int ci = Colour::White;
            float c = *((float *) &ci);

            float *vbp = vb->lock();
            // 0
            *vbp++ = targetRect.x;
            *vbp++ = targetRect.y + targetRect.h;
            *vbp++ = 0;
            *vbp++ = 0;
            *vbp++ = c;

            // 1
            *vbp++ = targetRect.x;
            *vbp++ = targetRect.y;
            *vbp++ = 0;
            *vbp++ = 1;
            *vbp++ = c;

            // 2
            *vbp++ = targetRect.x + targetRect.w;
            *vbp++ = targetRect.y;
            *vbp++ = 1;
            *vbp++ = 1;
            *vbp++ = c;

            // 3
            *vbp++ = targetRect.x + targetRect.w;
            *vbp++ = targetRect.y + targetRect.h;
            *vbp++ = 1;
            *vbp++ = 0;
            *vbp   = c;
            vb->unlock();

            posTexColParams.u_vp         = viewportViewProjMatrix;
            posTexColParams.u_texture_rt = RETRORENDERTARGET;
            Materials::posTexCol->use(posTexColParams);
            Graphics4::setIndexBuffer(*ib);
            Graphics4::setVertexBuffer(*vb);
            Graphics4::drawIndexedVertices();
        }
        Graphics4::end();
        */

        //
        // NEXT FRAME
        //

        Graphics4::swapBuffers(windowId);
    }

    // ----------------------------------------------------------------------------------------------

}
