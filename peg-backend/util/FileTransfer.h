#ifndef FILETRANSFER
#define FILETRANSFER

#include <iostream>
#include <string>
#include <cstdlib>

#include "RemoteInfo.h"

/**
 * 先配置好免密登入
 */
class FileTransfer: public RemoteInfo
{
private:

public:
    FileTransfer(std::string _ip, std::string _user);
    ~FileTransfer();

    int Transfer(std::string localfile_path, std::string remotefile_path);
};

struct TransferThreadArgs
{
    FileTransfer *file_transfer_;
    std::string localfile_path_;
    std::string remotefile_path_;
};

void *TransferThread(void *args);

#endif