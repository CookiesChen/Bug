#ifndef __TAG_H__
#define __TAG_H__

enum Tag
{
    Null = 0,

    // SceneLoginAndRegister
    LayerFromLoginToRegister,
    LayerFromRegisterToLogin,
    LayerFromLoginOrRegisterToEmail,

    // SceneMenu
    LayerFromMenuToJoinRoom,
    LayerFromMenuToNewRoom,
    LayerFromJoinRoomOrNewRoomToMenu,
    LayerFromNewUserToMenu,
    LayerFromMenuToNewUser,

    LayerFromRoomToReady,
    LayerFromReadyToRoom,

    // Scene
    SceneFromLoginAndRegisterToMenu,
    SceneFromMenuToLoginAndRegister,
    SceneFromMenuToRoom,

    SceneFromRoomToMenu,
    SceneFromRoomToGame,



    Reversed = 9999
};

#endif // __TAG_H__
