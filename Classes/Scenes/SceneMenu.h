#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include "cocos2d.h"
USING_NS_CC;

class SceneMenu : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();

    CREATE_FUNC(SceneMenu);
};

#endif //__SCENE_MENU_H__
