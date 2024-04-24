#include "dblog.h"
/*****************************************************************
 * 函数名称： void dblog::DbLog::NewDbLog(std::string operate_userid,std::string operate_type,std::string operate_databaseid)
 * 功能描述： 赋值数据库日志项
 * 参数说明： 字符串类型的操作用户id,操作类型,操作数据库id
 * 返回值：   无返回值
 ******************************************************************/
void dblog::DbLog::NewDbLog(std::string operate_userid, std::string operate_type, std::string operate_databaseid)
{
    this->operate_user_id_ = operate_userid;
    this->operate_type_ = operate_type;
    time_t now_time = time(NULL);
    tm *ltm = localtime(&now_time);
    std::string operatetime = std::to_string(ltm->tm_year + 1900) + "-" + std::to_string(ltm->tm_mon + 1) + "-" + std::to_string(ltm->tm_mday) + "-";
    operatetime += std::to_string(ltm->tm_hour) + "-" + std::to_string(ltm->tm_min) + "-" + std::to_string(ltm->tm_sec);
    this->operate_time_ = operatetime;
    this->operate_database_id_ = operate_databaseid;
}
/*****************************************************************
 * 函数名称： std::vector<dblog::DbLog *> dblog::DbLogDisplayByDbuserId(const std::string &dbuser_id, std::vector<dblog::DbLog *> dblog_data)
 * 功能描述： 用户id得到数据库日志
 * 参数说明： 字符串类型的操作用户id，vector类型的日志列表
 * 返回值：   日志列表
 ******************************************************************/
std::vector<dblog::DbLog *> dblog::DbLogDisplayByDbuserId(const std::string &dbuser_id, std::vector<dblog::DbLog *> dblog_data)
{
    for (int i = 0; i < dblog_data.size(); i++)
    {
        if (dblog_data[i]->get_operate_user_id_() != dbuser_id)
        {
            dblog_data.erase(dblog_data.begin() + i);
            i--;
        }
    }
    return dblog_data;
}
/*****************************************************************
 * 函数名称： std::vector<dblog::DbLog *> dblog::DbLogDisplayByDbId(const std::string &db_id, std::vector<dblog::DbLog *> dblog_data)
 * 功能描述： 数据库id得到数据库日志
 * 参数说明： 字符串类型的数据库id，vector类型的日志列表
 * 返回值：   日志列表
 ******************************************************************/
std::vector<dblog::DbLog *> dblog::DbLogDisplayByDbId(const std::string &db_id, std::vector<dblog::DbLog *> dblog_data)
{
    for (int i = 0; i < dblog_data.size(); i++)
    {
        if (dblog_data[i]->get_operate_database_id_() != db_id)
        {
            dblog_data.erase(dblog_data.begin() + i);
            i--;
        }
    }
    return dblog_data;
}
