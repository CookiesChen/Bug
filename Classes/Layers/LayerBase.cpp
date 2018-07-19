#include "LayerBase.h"
#include "SceneBase.h"

LayerBase::LayerBase() : active(true), visible(true) {}

bool LayerBase::getActive()
{
    return active;
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
