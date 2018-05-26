#ifndef KOOLBOX_SCENE_H
#define KOOLBOX_SCENE_H

#include "KoolBoxShared.h"
#include "NonCopyable.h"

namespace KoolBox
{
    class SceneManager;

    class Scene : NonCopyable
    {
		friend class SceneManager;
        
    public:
        Scene();
        virtual ~Scene();

	protected:
		virtual void 	onEntry()						= 0;
		virtual void 	onExit()						= 0;
		virtual void 	update(const GameTime *time)	= 0;
		virtual void 	draw()    	                	= 0;
	};

}

#endif

