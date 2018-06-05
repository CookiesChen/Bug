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
	
	
	return true;
}

