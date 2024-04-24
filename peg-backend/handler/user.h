/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       user.h
 * @brief      the User class
 * @descripition
 *
 * 成员变量：
 *   std::string dbuser_id_ 数据库用户id
 *   std::string db_id_ 数据库id
 *   std::string dbuser_name_ 数据库用户昵称
 *   std::string dbuser_password_ 数据库用户密码
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef USER_H_
#define USER_H_

#include <iostream>
namespace user
{
    class User
    {
    public:
        User();
        inline std::string get_dbuser_id_();
        inline std::string get_db_id_();
        inline std::string get_dbuser_name_();
        inline std::string get_dbuser_password_();
        inline void set_dbuser_id_(const std::string &dbuser_id);
        inline void set_db_id_(const std::string &db_id);
        inline void set_dbuser_name_(const std::string &dbuser_name);
        inline void set_dbuser_password_(const std::string &dbuser_password);

    private:
        std::string dbuser_id_;
        std::string db_id_;
        std::string dbuser_name_;
        std::string dbuser_password_;
    };
    inline std::string User::get_dbuser_id_()
    {
        return this->dbuser_id_;
    }
    inline std::string User::get_db_id_()
    {
        return this->db_id_;
    }
    inline std::string User::get_dbuser_name_()
    {
        return this->dbuser_name_;
    }
    inline std::string User::get_dbuser_password_()
    {
        return this->dbuser_password_;
    }
    inline void User::set_dbuser_id_(const std::string &dbuser_id)
    {
        this->dbuser_id_ = dbuser_id;
    }
    inline void User::set_db_id_(const std::string &db_id)
    {
        this->db_id_ = db_id;
    }
    inline void User::set_dbuser_name_(const std::string &dbuser_name)
    {
        this->dbuser_name_ = dbuser_name;
    }
    inline void User::set_dbuser_password_(const std::string &dbuser_password)
    {
        this->dbuser_password_ = dbuser_password;
    }
}

#endif // USER_H_