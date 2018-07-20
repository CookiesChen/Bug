#include "LayerMessageDialog.h"
#include "SceneBase.h"

bool SceneBase::init()
{
    if (!Scene::init()) return false;

    // 预加载图片资源
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Graphics/System/SceneLoginAndRegister.plist");

    d = LayerMessageDialog::createLayer();
    d->setActive(false);
    d->setVisible(false);

    this->addChild(d, 1001);

    return true;
}

void SceneBase::dialog(const string& str)
{
    ((LayerMessageDialog*) d)->setString(str);
    d->setActive(true);
    d->setVisible(true);
}

bool SceneBase::getHaltState()
{
    return d->getVisible();
}
