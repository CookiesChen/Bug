#ifndef __TAG_H__
#define __TAG_H__

enum Tag
{
    Null = 0,

    // SceneLoginAndRegister
    LayerFromLoginToRegister,
    LayerFromRegisterToLogin,

    // SceneMenu
    LayerFromMenuToJoinRoom,
    LayerFromMenuToNewRoom,
    LayerFromJoinRoomOrNewRoomToMenu,

    // Scene
    SceneFromLoginAndRegisterToMenu,

    Reversed = 9999
};

#endif // __TAG_H__
