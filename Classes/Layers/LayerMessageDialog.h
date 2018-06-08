#ifndef __LAYER_MESSAGE_DIALOG_H__
#define __LAYER_MESSAGE_DIALOG_H__

#include "LayerBase.h"

class LayerMessageDialog final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    CREATE_FUNC(LayerMessageDialog);
};

#endif //__LAYER_MESSAGE_DIALOG_H__
