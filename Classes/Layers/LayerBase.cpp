#include "LayerBase.h"
#include "SceneBase.h"

LayerBase::LayerBase() : active(true) {}

bool LayerBase::getActive()
{
    return active;
}

void LayerBase::setActive(bool active)
{
    this->active = active;
}

void LayerBase::updateLayer()
{
    auto scene = (SceneBase*) this->getParent();
    scene->updateLayer();
}
