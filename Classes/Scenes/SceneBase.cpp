#include "LayerMessageDialog.h"
#include "SceneBase.h"

bool SceneBase::init()
{
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

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
    auto msgDialog = (LayerMessageDialog*) d;
    msgDialog->setString(str);
    msgDialog->show();
}

bool SceneBase::getHaltState()
{
    return d->getVisible();
}
