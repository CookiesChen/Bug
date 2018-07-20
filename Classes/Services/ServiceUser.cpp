#include "ServiceUser.h"

string ServiceUser::GetEmail()
{
    return user.Email;
}

void ServiceUser::SetEmail(string email)
{
    user.Email = email;
}
