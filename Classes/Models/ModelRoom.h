#ifndef __MODEL_ROOM_H__
#define __MODEL_ROOM_H__
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

typedef struct {
  string userId;
  int gameId;
  string roleId;
  bool isReady;
  int team;
  string userName;
  string avatar;
  int gender;
} playerInfo;

class ModelRoom final
{
public:
  int Id;
  string OwnId;
  bool IsOwn;
  int Port;
  string Title;
  string GameMap;
  int MaxPalyer;
  string Mode;
  bool IsRandom;
  bool IsPublic;
  string Password;
  bool Playing;
  vector<playerInfo> players;
};

#endif
