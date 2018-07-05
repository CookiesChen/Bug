#ifndef __LAYER_NEW_USER_H__
#define __LAYER_NEW_USER_H__

#include "LayerBase.h"

class LayerNewUser final : public LayerBase
{
public:
    static LayerBase* createLayer();



    virtual bool init() override;

    CREATE_FUNC(LayerNewUser);

private:
};

#endif // __LAYER_NEW_USER_H__
