#ifndef __LAYER_BASE_H__
#define __LAYER_BASE_H__

#include "cocos2d.h"

USING_NS_CC;

class LayerBase : public Layer
{
public:
    LayerBase();

    virtual void setActive(bool active);

    bool getActive();
    bool getVisible();
    void setVisible(bool visible) override;
    int targetLayer;

private:
    bool active;
    bool visible;

protected:
    virtual void updateLayer() final;
    virtual void updateScene() final;
};

#endif // __LAYER_BASE_H__
