#include "ServiceUser.h"
#include "Helpers.h"
#include "ServiceAPI.h"

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

bool ServiceUser::RefreshInfo()
{
    auto d = Singleton<ServiceAPI>::GetInstance()->GetUserInfo();
    if (!d.HasParseError() && d.IsObject() && d.HasMember("status"))
    {
        if (strcmp(d["status"].GetString(), "success") == 0)
        {
            this->user.Nikename = d["nikeName"].GetString();
            this->user.avatar = d["avatar"].GetString();
            this->user.gender = d["gender"].GetInt();
            this->user.level = d["level"].GetInt();
            return true;
        }
        else
        {
            return false;
        }
    }
    else {
        return false;
    }
}
