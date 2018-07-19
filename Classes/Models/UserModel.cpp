#include "UserModel.h"
using namespace std;

string User::userId = "";
string User::nickname = "";
string User::avatar = "";
int User::gender = 0;
int User::level = 0;


void User::setUserId(string userId)
{
    this->userId = userId;
}

void User::setNickName(string nickname)
{
    this->nickname = nickname;
}

// 头像暂不使用
void User::setAvatar(string avatar)
{
    this->avatar = avatar;
}

void User::setGender(int gender)
{
    this->gender = gender;
}

void User::setLevel(int level)
{
    this->level = level;
}


string User::getUserId()
{
    return userId;
}

string User::getNickName()
{
    return nickname;
}
string User::getAvatar()
{
    return avatar;
}
int User::getGender()
{
    return gender;
}
int User::getLevel()
{
    return level;
}
