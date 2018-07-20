#ifndef __SERVICE_USER_H__
#define __SERVICE_USER_H__

#include "ModelUser.h"

class ServiceUser final
{
public:
    string GetEmail();
    void SetEmail(string email);

private:
    ModelUser user;
};

#endif // __SERVICE_USER_H__
