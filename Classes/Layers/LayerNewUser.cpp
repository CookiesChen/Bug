#include "LayerNewUser.h"

LayerBase* LayerNewUser::createLayer()
{
    return LayerNewUser::create();
}

bool LayerNewUser::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    // todo 用户输入名字
    // todo 用户选择性别
    // todo 用户选择头像
    // todo 提交按钮
    return true;
}
