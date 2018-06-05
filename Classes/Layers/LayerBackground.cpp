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
    auto compass_1 = Sprite::create("compass_1.png");
    auto compass_2 = Sprite::create("compass_2.png");
    auto compass_3 = Sprite::create("compass_3.png");

    compass_1->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));
    compass_2->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));
    compass_3->setPosition(Vec2(visibleSize.width / 2, origin.y + 20));

    // ±³¾°Í¼
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/2));

    this->addChild(compass_1, 3, "compass_1");
    this->addChild(compass_2, 2, "compass_2");
    this->addChild(compass_3, 1, "compass_3");
    this->addChild(background, 0);

	return true;
}

