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

    LayerEmail = 1000,
    LayerJoinRoom,
    LayerLogin,
    LayerMenu,
    LayerMessageDialog,
    LayerNewRoom,
    LayerNewUser,
    LayerRegister,
    LayerRole,
    LayerRoom,

    SceneGameRoom = 2000,
    SceneLoginAndRegister,
    SceneMenu,
    SceneRoom
};

#endif // __TAG_H__
