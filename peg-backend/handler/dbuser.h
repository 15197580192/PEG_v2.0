/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       dbuser.h
 * @brief      the DBUser class
 * @descripition
 *
 * 成员函数：
 * void NewDbUser(const std::string &dbuserid, const std::string &db_id, const std::string &dbuser_name,
 *                const std::string &dbuser_password, const std::string &isban, const std::string &creater_id)
 * 赋值数据库用户项
 * int DbLogin(const std::string &database_id, const std::string &dbuser_id, const std::string &dbuser_pass)
 * 数据库登录
 * 成员变量：
 *  std::string dbuser_id_ 数据库用户id
 *  std::string db_id_ 数据库id
 *  std::string dbuser_name_ 数据库用户名称
 *  std::string dbuser_password_ 数据库用户密码
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef DBUSER_H_
#define DBUSER_H_

#include <iostream>

class DbUser
{
public:
   DbUser();
   void NewDbUser(const std::string &dbuserid, const std::string &db_id, const std::string &dbuser_name, 
                  const std::string &dbuser_password, const std::string &isban, const std::string &creater_id);
   int DbLogin(const std::string &database_id, const std::string &dbuser_id, const std::string &dbuser_pass);

   inline void set_dbuserid_(const std::string &dbuserid)
   {
      this->dbuser_id_ = dbuserid;
   };
   inline void set_databaseid_(const std::string &databaseid)
   {
      this->db_id_ = databaseid;
   };
   inline void set_dbusername_(const std::string &dbusername)
   {
      this->dbuser_name_ = dbusername;
   };
   inline void set_dbuser_pass_(const std::string &dbuserpassword)
   {
      this->dbuser_password_ = dbuserpassword;
   };
   inline void set_isban_(const std::string &isban)
   {
      this->isban_ = isban;
   };
   inline void set_creater_id_(const std::string &creater_id)
   {
      this->creater_id_ = creater_id;
   };

   inline std::string get_dbuser_id_()
   {
      return this->dbuser_id_;
   };
   inline std::string get_database_id_()
   {
      return this->db_id_;
   };
   inline std::string get_dbuser_name_()
   {
      return this->dbuser_name_;
   };
   inline std::string get_dbuser_password_()
   {
      return this->dbuser_password_;
   };
   inline std::string get_isban_()
   {
      return this->isban_;
   };
   inline std::string get_creater_id_()
   {
      return this->creater_id_;
   };

private:
   std::string dbuser_id_;
   std::string db_id_;
   std::string dbuser_name_;
   std::string dbuser_password_;
   std::string isban_;
   std::string creater_id_;
};

#endif // DBUSER_H_