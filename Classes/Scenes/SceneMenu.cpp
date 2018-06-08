#include "SceneMenu.h"

Scene* SceneMenu::createScene()
{
    return SceneMenu::create();
}

bool SceneMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    return true;
}

void SceneMenu::updateLayer()
{}

void SceneMenu::updateScene()
{}
