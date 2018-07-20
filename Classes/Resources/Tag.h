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
};

#endif // __TAG_H__
