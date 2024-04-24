#include "FileTransfer.h"

FileTransfer::FileTransfer(std::string _itransfer_thread_args, std::string _user)
 : RemoteInfo(_itransfer_thread_args, _user)
{
}

FileTransfer::~FileTransfer()
{
}

int FileTransfer::Transfer(std::string localfile_path, std::string remotefile_path)
{
    std::string cmd = "scp " + localfile_path + " " + user_+"@"+ip_+":"+remotefile_path;
    // sctransfer_thread_args 传输成功返回0，不成功返回大于0的数
    std::cout << cmd << std::endl;
    
    int ret = system(cmd.c_str());
    return ret;
}

void *TransferThread(void *args)
{
    TransferThreadArgs *transfer_thread_args = (TransferThreadArgs*)args;
    int ret = transfer_thread_args->file_transfer_->Transfer(transfer_thread_args->localfile_path_, transfer_thread_args->remotefile_path_);
    std::cout << "Transfer " << transfer_thread_args->localfile_path_ << " to remote " << transfer_thread_args->remotefile_path_;
    if(ret == 0)
        std::cout << " successfully." << std::endl;
    else
        std::cout << " unsuccessfully." << std::endl;
    return nullptr;
}