#include "LayerBase.h"
#include "SceneBase.h"

LayerBase::LayerBase() : active(true), visible(true) {}

bool LayerBase::getActive()
{
    auto scene = (SceneBase*) this->getParent();
    if (scene == nullptr) return false;
    return !scene->getHaltState() && active;
}

bool LayerBase::init()
{
    return Layer::init();
}

void LayerBase::setActive(bool active)
{
    this->active = active;
}

bool LayerBase::getVisible()
{
    return visible;
}

void LayerBase::setVisible(bool visible)
{
    Layer::setVisible(visible);
    this->visible = visible;
}

void LayerBase::dialog(const string & str)
{
    auto scene = (SceneBase*) this->getParent();
    if (scene != nullptr)
    {
        scene->dialog(str);
    }
}

void LayerBase::updateLayer(Tag tag)
{
    auto scene = (SceneBase*) this->getParent();
    if (scene != nullptr)
    {
        scene->updateLayer(tag);
    }
}

void LayerBase::updateScene(Tag tag)
{
    auto scene = (SceneBase*) this->getParent();
    if (scene != nullptr)
    {
        scene->updateScene(tag);
    }
}
