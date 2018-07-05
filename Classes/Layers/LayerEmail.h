#ifndef __LAYER_EMAIL_H__
#define __LAYER_EMAIL_H__

#include "LayerBase.h"

class LayerEmail final : public LayerBase
{
public:
    static LayerBase* createLayer();



    virtual bool init() override;

    CREATE_FUNC(LayerEmail);

private:
};

#endif // __LAYER_EMAIL_H__
