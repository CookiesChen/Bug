#ifndef __LAYER_BASE_H__
#define __LAYER_BASE_H__

#include "cocos2d.h"

#include "Tag.h"

#include <string>

using namespace cocos2d;
using namespace std;

class LayerBase : public Layer
{
public:
    LayerBase();

    virtual bool init() override;
    virtual void setActive(bool active);

    bool getActive();
    bool getVisible();
    void setVisible(bool visible) override;

protected:
    virtual void dialog(const string& str) final;
    virtual void updateLayer(Tag tag = Tag::Null) final;
    virtual void updateScene(Tag tag = Tag::Null) final;

private:
    bool active;
    bool visible;
};

#endif // __LAYER_BASE_H__
