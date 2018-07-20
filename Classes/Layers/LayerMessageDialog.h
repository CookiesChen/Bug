#ifndef __LAYER_MESSAGE_DIALOG_H__
#define __LAYER_MESSAGE_DIALOG_H__

#include <string>

#include "LayerBase.h"

using namespace std;

class LayerMessageDialog final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    void setString(const string& str);

    CREATE_FUNC(LayerMessageDialog);

private:
    void back(Ref* pSender);

    Label* label;
};

#endif //__LAYER_MESSAGE_DIALOG_H__
