#ifndef __SCENE_MAP_H__
#define __SCENE_MAP_H__

#include "LayerBase.h"
#include "SceneBase.h"

class SceneMap final : public SceneBase
{
public:
    static SceneBase * createScene();

    virtual bool init() override;
    virtual void updateLayer(Tag tag) override;
    virtual void updateScene(Tag tag) override;

    CREATE_FUNC(SceneMap);
};

#endif // __SCENE_MAP_H__
