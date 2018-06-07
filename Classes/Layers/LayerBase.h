#ifndef __LAYER_BASE_H__
#define __LAYER_BASE_H__

#include "cocos2d.h"

USING_NS_CC;

class LayerBase : public Layer
{
public:
    LayerBase();

    virtual bool getActive();
    virtual void setActive(bool active);

private:
    bool active;

protected:
    void updateLayer();
};

#endif // __LAYER_BASE_H__
