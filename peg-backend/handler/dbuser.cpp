#include "dbuser.h"

DbUser::DbUser()
{
    dbuser_id_ = "0";
    db_id_ = "0";
    dbuser_name_ = "0";
    dbuser_password_ = "0";
    isban_ = "0";
    creater_id_ = "0";
}
/*****************************************************************
 * 函数名称： void DbUser::NewDbUser(const std::string &dbuserid, const std::string &db_id,
 *                                  const std::string &dbuser_name, const std::string &dbuser_password,
 *                                  const std::string &isban, const std::string &creater_id)
 * 功能描述： 赋值数据库用户项
 * 参数说明： 字符串类型的数据库用户id,数据库id,数据库用户名称，数据库用户密码，是否禁用，数据库创建者id
 * 返回值：   无返回值
 ******************************************************************/
void DbUser::NewDbUser(const std::string &dbuserid, const std::string &db_id, const std::string &dbuser_name,
                       const std::string &dbuser_password, const std::string &isban, const std::string &creater_id)
{
    this->set_dbuserid_(dbuserid);
    this->set_databaseid_(db_id);
    this->set_dbusername_(dbuser_name);
    this->set_dbuser_pass_(dbuser_password);
    this->set_isban_(isban);
    this->set_creater_id_(creater_id);
};

/*****************************************************************
 * 函数名称： int DbUser::DbLogin(std::string database_id, std::string dbuser_id, std::string dbuser_pass)
 * 功能描述： 数据库登录
 * 参数说明： 字符串类型的数据库id,数据库用户id,数据库用户密码
 * 返回值：   成功返回1，失败返回0
 ******************************************************************/
int DbUser::DbLogin(const std::string &database_id, const std::string &dbuser_id, const std::string &dbuser_pass)
{
    if (this->get_database_id_() == database_id && this->get_dbuser_name_() == dbuser_id && this->get_dbuser_password_() == dbuser_pass && this->get_isban_()=="0")
    {
        return 1;
    }
    return 0;
}