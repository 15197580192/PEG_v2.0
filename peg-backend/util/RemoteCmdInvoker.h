/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Informat_ion.
 *
 * @file       RemoteCmdlnvoker.h
 * @descripition  该头文件中包含数据库增删查和备份还原的线程函数实现
 *  
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef REMOTECMDINVOKER
#define REMOTECMDINVOKER

#include <cstdlib>
#include <string>
#include <iostream>

#include "RemoteInfo.h"
#include "../gStoreAPI/client.h"

#include "../queryDecompose/Util/Util.h"

using namespace std;

class RemoteCmdInvoker : public RemoteInfo
{
private:

public:
    RemoteCmdInvoker(std::string _ip, std::string _user);
    ~RemoteCmdInvoker();

    int Execute(std::string _cmd);
};

struct BuildThreadArgs
{
    GstoreConnector *server_;
    std::string db_name_;
    std::string nt_path_;
};

struct BackRestoreThreadArgs
{
    GstoreConnector *server_;
    std::string db_name_;
    std::string path_;
    std::string version_;
    std::string res_;
};

typedef struct MonitorNeedVars
{
    GstoreConnector *server_;
    std::string db_name_;
    std::string res_;
} MNV;

typedef struct QueryNeedVars
{
    int query_id_, server_id_;
    GstoreConnector *server_;
    std::string db_name_;
    std::string format_;
    std::string query_;
    std::string res_;
    long cost_time_;
} QNV;

struct ExportThreadArgs
{
    GstoreConnector *server_;
    std::string db_name_;
    std::string path_;
    std::string res_;
};

void *MonitorThread(void *args);
void *BuildThread(void *args);
void *LoadThread(void *args);
void *UnloadThread(void *args);
void *DeleteThread(void *args);
void *QueryThread(void *args);
void *BackupThread(void *args);
void *RestoreThread(void *args);
void *ExportThread(void *args);

#endif