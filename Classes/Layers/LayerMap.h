#ifndef _LAYER_MAP_H__
#define _LAYER_MAP_H__

#include "LayerBase.h"

class LayerMap final : public LayerBase
{
public:
    void movemap();
private:
    TMXTiledMap * map;
};

#endif // !_LAYER_PLAYER_H
