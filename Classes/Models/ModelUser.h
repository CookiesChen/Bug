#ifndef __USER_MODEL_H__
#define __USER_MODEL_H__

#include <string>
#include <stdio.h>

using namespace std;

class ModelUser final
{
public:

    void setUserId(string userId);
    void setNickName(string nickname);
    // 头像暂不使用
    void setAvatar(string avatar);
    void setGender(int gender);
    void setLevel(int level);

    string getUserId();
    string getNickName();
    // 头像暂不使用
    string getAvatar();
    int getGender();
    int getLevel();

private:
    string userId;
    string nickname;
    string avatar;
    int gender; // 0:man 1:women
    int level;
};

#endif
