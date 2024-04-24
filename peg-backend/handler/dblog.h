/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       dblog.h
 * @brief      the DbLog class
 * @descripition
 * 成员函数：
 *   void NewDbLog(std::string operate_userid,std::string operate_type,std::string operate_databaseid)
 *  赋值备份类
 * 非成员函数：
 *  std::vector<DbLog *> DbLogDisplayByDbuserId(const std::string &dbuser_id, std::vector<DbLog *> dbLog_data)
 * 通过dbuserid查询数据库日志
 *  std::vector<DbLog *> DbLogDisplayByDbId(const std::string &db_id, std::vector<DbLog *> dbLog_data)
 * 通过id查询备份列表
 * 成员变量：
 *   std::string operate_user_id_     操作者id
 *   std::string operate_time_        操作时间
 *   std::string operate_type_        操作类型
 *   std::string operate_database_id_ 操作数据库id
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef DBLOG_H_
#define DBLOG_H_

#include <iostream>
#include <vector>

namespace dblog
{
    class DbLog
    {
    private:
        std::string operate_user_id_;
        std::string operate_time_;
        std::string operate_type_;
        std::string operate_database_id_;

    public:
        inline void set_operate_user_id_(const std::string &operateuserid)
        {
            this->operate_user_id_ = operateuserid;
        }
        inline void set_operate_time_(const std::string &operatetime)
        {
            this->operate_time_ = operatetime;
        }
        inline void set_operate_type_(const std::string &operatetype)
        {
            this->operate_type_ = operatetype;
        }
        inline void set_operate_database_id_(const std::string &operatedatabaseid)
        {
            this->operate_database_id_ = operatedatabaseid;
        }
        inline std::string get_operate_user_id_()
        {
            return this->operate_user_id_;
        }
        inline std::string get_operate_time_()
        {
            return this->operate_time_;
        }
        inline std::string get_operate_type_()
        {
            return this->operate_type_;
        }
        inline std::string get_operate_database_id_()
        {
            return this->operate_database_id_;
        }
        void NewDbLog(std::string operate_userid, std::string operate_type, std::string operate_databaseid);
    };
    std::vector<DbLog *> DbLogDisplayByDbuserId(const std::string &dbuser_id, std::vector<DbLog *> dbLog_data);
    std::vector<DbLog *> DbLogDisplayByDbId(const std::string &db_id, std::vector<DbLog *> dbLog_data);
}
#endif