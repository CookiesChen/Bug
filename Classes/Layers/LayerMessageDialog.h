#ifndef __LAYER_MESSAGE_DIALOG_H__
#define __LAYER_MESSAGE_DIALOG_H__

#include "cocos2d.h"

USING_NS_CC;

class LayerMessageDialog : public Layer
{
public:
    static Layer* createLayer();
    virtual bool init();

    CREATE_FUNC(LayerMessageDialog);
};

#endif //__LAYER_MESSAGE_DIALOG_H__
