#include "LayerEmail.h"

LayerBase* LayerEmail::createLayer()
{
    return LayerEmail::create();
}

bool LayerEmail::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    // todo 邮箱验证框
    // todo 提交按钮
    return true;
}
