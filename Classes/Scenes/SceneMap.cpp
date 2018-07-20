#include "SceneMap.h"

SceneBase* SceneMap::createScene()
{
    return SceneMap::create();
}

bool SceneMap::init()
{
    if (!SceneBase::init()) return false;

    return true;
}

void SceneMap::updateLayer(Tag tag)
{}

void SceneMap::updateScene(Tag tag)
{}
