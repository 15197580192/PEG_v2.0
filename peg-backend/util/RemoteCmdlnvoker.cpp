#include "RemoteCmdInvoker.h"

RemoteCmdInvoker::RemoteCmdInvoker(std::string _ip, std::string _user)
 : RemoteInfo(_ip, _user)
{
}

RemoteCmdInvoker::~RemoteCmdInvoker()
{
}

int RemoteCmdInvoker::Execute(std::string _cmd)
{
    std::string cmd = "ssh " + user_+"@"+ip_+" \"" + _cmd + "\"";
    std::cout << cmd << std::endl;
    
    int ret = system(cmd.c_str());
    return ret;
}

/*****************************************************************
* 函数名称： void *MonitorThread(void *args)
* 功能描述： 监视数据库线程函数
* 参数说明： 无
* 返回值：   无
******************************************************************/
void *MonitorThread(void *args)
{
    MNV *vars = (MNV *)args;
    GstoreConnector &server_ = *vars->server_;
    server_.load(vars->db_name_);
    vars->res_ = server_.monitor(vars->db_name_);
    server_.unload(vars->db_name_);
    return NULL;
}

/*****************************************************************
* 函数名称： void *BuildThread(void *args)
* 功能描述： 创建数据库线程函数
* 参数说明： 无
* 返回值：   无
******************************************************************/
void *BuildThread(void *args)
{
    BuildThreadArgs *thread_args = (BuildThreadArgs*) args;
    std::cout << "ip: " 
              << thread_args->server_->serverIP << " 255.255.255.0"
              << " port: " 
              << thread_args->server_->serverPort 
              << " dbuser: " 
              << thread_args->server_->username 
              << " dbpasswd: " 
              << thread_args->server_->password 
              << " db_name_: "
              << thread_args->db_name_
              << " nt_path_: "
              << thread_args->nt_path_
              << std::endl;
    std::cout << thread_args->server_->build(thread_args->db_name_, thread_args->nt_path_) << std::endl
              << thread_args->server_->load(thread_args->db_name_) << std::endl;
    return nullptr;
}

/*****************************************************************
* 函数名称： void *LoadThread(void *args)
* 功能描述： 新建数据库线程函数
* 参数说明： 无
* 返回值：   无
******************************************************************/
void *LoadThread(void *args)
{
    BuildThreadArgs *thread_args = (BuildThreadArgs*) args;
    std::cout << thread_args->server_->load(thread_args->db_name_) << std::endl;
    return nullptr;
}

/*****************************************************************
* 函数名称： void *UnloadThread(void *args)
* 功能描述： 卸载数据库线程函数
* 参数说明： 无
* 返回值：   无
******************************************************************/
void *UnloadThread(void *args)
{
    BuildThreadArgs *thread_args = (BuildThreadArgs*) args;
    std::cout << thread_args->server_->unload(thread_args->db_name_) << std::endl;
    return nullptr;
}

/*****************************************************************
* 函数名称： void *DeleteThread(void *args)
* 功能描述： 删除数据库线程函数
* 参数说明： 无
* 返回值：   无
******************************************************************/
void *DeleteThread(void *args)
{
    BuildThreadArgs *thread_args = (BuildThreadArgs*) args;
    thread_args->server_->unload(thread_args->db_name_);
    std::cout << thread_args->server_->drop(thread_args->db_name_, false) << std::endl;
    return nullptr;
}

/*****************************************************************
* 函数名称： void *QueryThread(void *args)
* 功能描述： 查询数据库线程函数
* 参数说明： 无
* 返回值：   无
******************************************************************/
void *QueryThread(void *args)
{
    long begin = Util::get_cur_time(), cost_time;
    QNV *vars = (QNV *)args;
    GstoreConnector &server_ = *vars->server_;
    vars->res_ = server_.query(vars->db_name_, vars->format_, vars->query_);
    cost_time = Util::get_cur_time() - begin;
    cout << "query " << vars->query_id_ << " has finished on server_ " << vars->server_id_ << ". Take " << cost_time << "ms." << endl;
    cout << vars->query_ << endl;
    vars -> cost_time_ = cost_time;
    // cout << vars -> cost_time << endl;
    return NULL;
}

/*****************************************************************
* 函数名称： void *BackupThread(void *args)
* 功能描述： 备份数据库线程函数
* 参数说明： 无
* 返回值：   无
******************************************************************/
void *BackupThread(void *args)
{

    BackRestoreThreadArgs *thread_args = (BackRestoreThreadArgs *)args;
    thread_args->server_->load(thread_args->db_name_);

    std::string directory = thread_args->path_;
    std::string folderName = thread_args->server_->serverIP;
    thread_args->res_ = thread_args->server_->backup(thread_args->db_name_, thread_args->path_);

    return nullptr;
}

/*****************************************************************
 * 函数名称： void *RestoreThread(void *args)
 * 功能描述： 还原数据库线程函数
 * 参数说明： 无
 * 返回值：   无
 ******************************************************************/
void *RestoreThread(void *args)
{
    BackRestoreThreadArgs *thread_args = (BackRestoreThreadArgs *)args;
    // std::cout << thread_args->server->restore(thread_args->db_name, thread_args->path) << std::endl;
    thread_args->res_ = thread_args->server_->restore(thread_args->db_name_, thread_args->path_);
    return nullptr;
}

void *ExportThread(void *args)
{
    ExportThreadArgs *thread_args = (ExportThreadArgs *)args;
    thread_args->server_->load(thread_args->db_name_);
    // std::cout << thread_args->server->exportDB(thread_args->db_name, thread_args->path) << std::endl;
    thread_args->res_ = thread_args->server_->exportDB(thread_args->db_name_, thread_args->path_);
}