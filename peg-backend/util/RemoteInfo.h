#ifndef REMOTEINFO
#define REMOTEINFO

#include <string>

class RemoteInfo
{
protected:
    std::string ip_;
    std::string user_;

public:
    RemoteInfo(std::string _ip, std::string _user);
    ~RemoteInfo();
};

#endif