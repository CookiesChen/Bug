#include "ServiceUser.h"

string ServiceUser::GetEmail()
{
    return user.Email;
}

string ServiceUser::GetNikename()
{
    return user.Nikename;
}

void ServiceUser::SetEmail(string email)
{
    user.Email = email;
}

void ServiceUser::SetNikename(string nikename)
{
    user.Nikename = nikename;
}
