#include "LayerBackground.h"
#include "SceneLoginAndRegister.h"

Layer * LayerBackground::createLayer()
{
	return LayerBackground::create();
}

bool LayerBackground::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
    // ÂŞÅÌ
    auto compass = Sprite::create("compass_500.png");
    compass->setScale(0.7);
    compass->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));

    // ±³¾°Í¼
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/2));

    this->addChild(compass, 1, "compass");
    this->addChild(background, 0);

	return true;
}

