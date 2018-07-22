#ifndef _LAYER_MAP_H__
#define _LAYER_MAP_H__

#include "LayerBase.h"
#include "ModelPlayer.h"

class LayerMap final : public LayerBase
{
public:
    static LayerBase* createLayer();

    virtual bool init() override;

    float maxWidth;
    float maxHeight;
    Sprite* player;
    experimental::TMXTiledMap * map;

    CREATE_FUNC(LayerMap);

};

#endif // !_LAYER_PLAYER_H
