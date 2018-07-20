#ifndef __SERVICE_USER_H__
#define __SERVICE_USER_H__

#include "ModelUser.h"

class ServiceUser final
{
public:
    string GetEmail();
    string GetNikename();
    void SetEmail(string email);
    void SetNikename(string nikename);
    bool RefreshInfo();

private:
    ModelUser user;
};

#endif // __SERVICE_USER_H__
