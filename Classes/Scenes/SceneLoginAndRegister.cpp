#include "SceneLoginAndRegister.h"
#include "SimpleAudioEngine.h"
#include "LayerLogin.h"

USING_NS_CC;

Scene* SceneLoginAndRegister::createScene()
{
	return SceneLoginAndRegister::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SceneLoginAndRegister::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto LoginAndRegister = LayerLogin::createLayer();
	this->addChild(LoginAndRegister);

	return true;
}
