#ifndef __USER_MODEL_H__
#define __USER_MODEL_H__

#include <string>
#include <stdio.h>

using namespace std;

class User final
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

    static string userId;
    static string nickname;
    // 头像
    static string avatar;
    // 0:man 1:women 3:gay
    static int gender;
    static int level;

};

#endif
