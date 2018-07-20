#include "SceneRoom.h"
#include "LayerRoom.h"

Scene* SceneRoom::createScene()
{
    return SceneRoom::create();
}

bool SceneRoom::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    layerRoom = LayerRoom::createLayer();
    

    return true;
}

void SceneRoom::updateLayer(Tag tag)
{
}

void SceneRoom::updateScene(Tag tag)
{

}
