#include "ModelUser.h"

void ModelUser::setUserId(string userId)
{
    this->userId = userId;
}

void ModelUser::setNickName(string nickname)
{
    this->nickname = nickname;
}

// 头像暂不使用
void ModelUser::setAvatar(string avatar)
{
    this->avatar = avatar;
}

void ModelUser::setGender(int gender)
{
    this->gender = gender;
}

void ModelUser::setLevel(int level)
{
    this->level = level;
}


string ModelUser::getUserId()
{
    return userId;
}

string ModelUser::getNickName()
{
    return nickname;
}
string ModelUser::getAvatar()
{
    return avatar;
}
int ModelUser::getGender()
{
    return gender;
}
int ModelUser::getLevel()
{
    return level;
}
