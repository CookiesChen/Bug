#include "SceneLoginAndRegister.h"
#include "SimpleAudioEngine.h"
#include "LayerLogin.h"
#include "LayerRegister.h"
#include "LayerBackground.h"

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
    
    // 预加载图片资源
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("LogInScene.plist");

    // 添加层
    auto Login = LayerLogin::createLayer();
    auto Register = LayerRegister::createLayer();
    auto Background = LayerBackground::createLayer();

    Register->setVisible(false);

    this->addChild(Login, 10, "Login");
    this->addChild(Register, 10, "Register");
    this->addChild(Background, 9, "Background");
	return true;
}
