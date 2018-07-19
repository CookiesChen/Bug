#ifndef __LAYER_BASE_H__
#define __LAYER_BASE_H__

#include "cocos2d.h"

#include "Tag.h"

using namespace cocos2d;


class LayerBase : public Layer
{
public:
    LayerBase();

    virtual void setActive(bool active);

    bool getActive();
    bool getVisible();
    void setVisible(bool visible) override;

private:
    bool active;
    bool visible;

protected:
    virtual void updateLayer(Tag tag = Tag::Null) final;
    virtual void updateScene(Tag tag = Tag::Null) final;
};

#endif // __LAYER_BASE_H__
