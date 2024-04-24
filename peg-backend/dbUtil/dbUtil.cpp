#include "dbutil.h"

// 构造函数
DB::DB()
{
    // 初始化数据库
    mysql_init(&mysql);

    // 设置字符编码
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

    // 连接数据库
    if (mysql_real_connect(&mysql, "localhost", "root", "123456", "PEGdb", 3306, NULL, 0) == NULL)
    // localhost为服务器，root为用户名和密码，school为数据库名，3306为端口
    {
        printf("错误原因:%s\n", mysql_error(&mysql));
        printf("连接失败！\n");
        exit(-1);
    }
}

// database
// 得到数据库表中所有数据
std::vector<database::Database *> DB::DatabaseDisplay()
{
    std::vector<database::Database *> database_data;

    std::string sql = "select * from `database`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        database::Database *database = new database::Database;
        database->set_database_id_(row[0]);
        database->set_database_name_(row[1]);
        database->set_creater_id_(row[2]);
        database->set_database_password_(row[3]);
        database->set_database_version_(row[4]);
        database_data.push_back(database);
    }
    mysql_free_result(res);
    return database_data;
};

// 在数据库表中新增数据
bool DB::DatabaseInsert(database::Database *database)
{
    std::string sql = "insert into `database` values('";
    sql += database->get_database_id_();
    sql += "','";
    sql += database->get_database_name_();
    sql += "','";
    sql += database->get_creater_id_();
    sql += "','";
    sql += database->get_database_password_();
    sql += "','";
    sql += database->get_database_version_();
    sql += "');";
    if (mysql_query(&mysql, sql.c_str()))
    {
        cerr << "[ERR] mysql insert error: " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}

// 在数据库表中删除对应数据
void DB::DatabaseDelete(const std::string &id)
{
    std::string delete_str = "delete from `database` where database_id='";
    delete_str += id;
    delete_str += "';";
    mysql_query(&mysql, "SET NAMES utf8");
    mysql_query(&mysql, delete_str.c_str());
}

// userinfor
// 得到peg用户表中所有数据
std::vector<peguser::PegUser *> DB::UserDisplay()
{
    vector<peguser::PegUser *> peg_user;
    std::string sql = "select * from `user_messages`";
    mysql_query(&mysql, "SET NAMES utf8");
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        peguser::PegUser *user = new peguser::PegUser;
        user->set_user_id_(row[0]);
        user->set_user_name_(row[1]);
        user->set_user_password_(row[2]);
        user->set_tel_(row[3]);
        user->set_register_time_(row[4]);
        user->set_forbidden_(row[5]);
        user->set_birthday_(row[6]);
        user->set_introduction_(row[7]);
        user->set_location_(row[8]);
        user->set_mailbox_(row[9]);
        user->set_sex_(row[10]);
        user->set_adress_(row[11]);
        peg_user.push_back(user);
    }
    mysql_free_result(res);
    return peg_user;
}

// 更新peg用户表中某个用户对应的个人信息
bool DB::UserModify(peguser::PegUser *user)
{
    string update_str = "update `user_messages` set user_name='";
    update_str += user->get_user_name_();
    update_str += "',tel='";
    update_str += user->get_tel_();
    update_str += "',birthday='";
    update_str += user->get_birthday_();
    update_str += "',introduction='";
    update_str += user->get_introduction_();
    update_str += "',location='";
    update_str += user->get_location_();
    update_str += "',`e-mail`='";
    update_str += user->get_mailbox_();
    update_str += "',sex='";
    update_str += user->get_sex_();
    update_str += "',adress='";
    update_str += user->get_adress_();
    update_str += "' where user_id='";
    update_str += user->get_user_id_();
    update_str += "';";
    std::cout<<update_str<<std::endl;
    mysql_query(&mysql, "SET NAMES utf8");
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

// 在peg用户表中新增数据
bool DB::UserInsert(peguser::PegUser *user)
{
    std::string insert_sql = "insert into `user_messages`(user_id,user_name,user_password,tel,register_time,forbidden,birthday,introduction,location,`e-mail`,sex,adress) values('";
    insert_sql += user->get_user_id_();
    insert_sql += "','";
    insert_sql += user->get_user_name_();
    insert_sql += "','";
    insert_sql += user->get_user_password_();
    insert_sql += "','";
    insert_sql += user->get_tel_();
    insert_sql += "','";
    insert_sql += user->get_register_time_();
    insert_sql += "','";
    insert_sql += user->get_forbidden_();
    insert_sql += "','";
    insert_sql += user->get_birthday_();
    insert_sql += "','";
    insert_sql += user->get_introduction_();
    insert_sql += "','";
    insert_sql += user->get_location_();
    insert_sql += "','";
    insert_sql += user->get_mailbox_();
    insert_sql += "','";
    insert_sql += user->get_sex_();
    insert_sql += "','";
    insert_sql += user->get_adress_();
    insert_sql += "');";
    CROW_LOG_INFO << insert_sql;
    if (mysql_query(&mysql, insert_sql.c_str()))
        return false;
    return true;
}

// 修改peg用户表中某个用户的密码
bool DB::UserRecoverPassword(peguser::PegUser *user)
{
    std::string update_str = "update `user_messages` set user_password='";
    update_str += user->get_user_password_();
    update_str += "' where `e-mail`='";
    update_str += user->get_mailbox_();
    update_str += "';";
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

// 修改peg用户表中某个用户的禁用标识
bool DB::UserForbidden(const std::string &user_id, const std::string &flag)
{
    std::string update_str = "update user_messages set forbidden='";
    update_str += flag;
    update_str += "' where user_id='";
    update_str += user_id;
    update_str += "';";
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

// 删除peg用户表中某个用户
bool DB::UserDelete(const std::string &user_id)
{
    std::string delete_str = "delete from user_messages where user_id='";
    delete_str += user_id;
    delete_str += "';";
    if (mysql_query(&mysql, delete_str.c_str()))
        return false;
    return true;
}

// 重置peg用户表中某个用户的密码为“111111”
bool DB::UserResetPassword(const std::string &user_id)
{
    std::string update_str = "update user_messages set user_password='111111' where user_id='";
    update_str += user_id;
    update_str += "';";
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

bool DB::UserSetNamePassword(const std::string &user_id, const std::string &user_name, const std::string &user_password, const std::string &register_time)
{
    std::string update_str = "update user_messages set user_name='";
    update_str += user_name;
    update_str += "',user_password='";
    update_str += user_password;
    update_str+="',register_time='";
    update_str+=register_time;
    update_str += "' where user_id='";
    update_str += user_id;
    update_str += "';";
    std::cout << update_str << std::endl;
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

// usernode
// 得到usernode表中所有数据
std::vector<UserNode *> DB::UserAndNodeDisplay()
{
    std::vector<UserNode *> usernode_data;
    string sql = "select * from `user_node`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        UserNode *usernode = new UserNode;
        usernode->set_usernode_id_(row[0]);
        usernode->set_user_id_(row[1]);
        usernode->set_node_id_(row[2]);
        usernode_data.push_back(usernode);
    }
    mysql_free_result(res);
    return usernode_data;
}

// node
// 得到node表中的所有数据
std::vector<node::Node *> DB::NodeDisplay()
{
    std::vector<node::Node *> node_data;
    std::string query_node = "select * from node";
    mysql_query(&mysql, "SET NAMES utf8");
    int ret = mysql_query(&mysql, query_node.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        node::Node *node = new node::Node;
        node->set_node_id_(row[0]);
        node->set_node_ip_(row[1]);
        node->set_user_id_(row[2]);
        node->set_port_(row[3]);
        node->set_gstore_user_id_(row[4]);
        node->set_gstore_user_password_(row[5]);
        node->set_version_(row[6]);
        node->set_apitype_(row[7]);
        node->set_rootpath_(row[8]);
        node_data.push_back(node);
    }
    return node_data;
}

// 删除node表中的某条记录
bool DB::NodeDelete(std::vector<std::string> node_id)
{
    bool flag = true;
    int node_number = node_id.size();
    for (int i = 0; i < node_number; i++)
    {
        std::string delete_str = "delete from node where node_id='";
        delete_str += node_id[i];
        delete_str += "';";
        mysql_query(&mysql, "SET NAMES utf8");
        if (mysql_query(&mysql, delete_str.c_str()))
            flag = false;
    }
    return flag;
}

// 在node表中新增一条记录
bool DB::NodeInsert(node::Node *node)
{
    std::string insert_str = "insert into node(node_id,node_ip,user_id,port,gstore_user_id,gstore_user_password,version,apitype,rootpath) values('";
    insert_str += node->get_node_id_();
    insert_str += "','";
    insert_str += node->get_node_ip_();
    insert_str += "','";
    insert_str += node->get_user_id_();
    insert_str += "','";
    insert_str += node->get_port_();
    insert_str += "','";
    insert_str += node->get_gstore_user_id_();
    insert_str += "','";
    insert_str += node->get_gstore_user_password_();
    insert_str += "','";
    insert_str += node->get_version_();
    insert_str += "','";
    insert_str += node->get_apitype_();
    insert_str += "','";
    insert_str += node->get_rootpath_();
    insert_str += "');";
    if (mysql_query(&mysql, insert_str.c_str()))
        return false;
    return true;
}

// 修改node表中某条记录
bool DB::NodeModify(node::Node *node)
{
    std::string update_str = "update node set user_id='";
    update_str += node->get_user_id_();
    update_str += "',port='";
    update_str += node->get_port_();
    update_str += "',gstore_user_id='";
    update_str += node->get_gstore_user_id_();
    update_str += "',gstore_user_password='";
    update_str += node->get_gstore_user_password_();
    update_str += "',version='";
    update_str += node->get_version_();
    update_str += "',apitype='";
    update_str += node->get_apitype_();
    update_str += "',rootpath='";
    update_str += node->get_rootpath_();
    update_str += "' where node_id='";
    update_str += node->get_node_id_();
    update_str += "' and node_ip='";
    update_str += node->get_node_ip_();
    update_str += "';";
    CROW_LOG_INFO << update_str;
    mysql_query(&mysql, "SET NAMES utf8");
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

// 得到node表中所有信息，存储成map形式
std::vector<std::map<std::string, std::string>> DB::NodeDisplayMap()
{
    vector<map<string, string>> node_data;
    std::string query_node = "select * from node";
    mysql_query(&mysql, "SET NAMES utf8");
    int ret = mysql_query(&mysql, query_node.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        map<string, string> node;
        node["node_id"] = row[0];
        node["node_ip"] = row[1];
        node["user_id"] = row[2];
        node["port"] = row[3];
        node["gstore_user_id"] = row[4];
        node["gstore_user_password"] = row[5];
        node["version"] = row[6];
        node["apitype"] = row[7];
        node["rootpath"] = row[8];
        node_data.push_back(node);
    }
    return node_data;
}

// dbuser
// 得到dbuser表中所有数据
std::vector<DbUser *> DB::DBUserDisplay()
{
    std::vector<DbUser *> dbuser_data;
    std::string query_node = "select * from dbuser";
    mysql_query(&mysql, "SET NAMES utf8");
    int ret = mysql_query(&mysql, query_node.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        DbUser *dbuser = new DbUser;
        dbuser->set_dbuserid_(row[0]);
        dbuser->set_databaseid_(row[1]);
        dbuser->set_dbusername_(row[2]);
        dbuser->set_dbuser_pass_(row[3]);
        dbuser->set_isban_(row[4]);
        dbuser->set_creater_id_(row[5]);
        dbuser_data.push_back(dbuser);
    }
    return dbuser_data;
}

// 在dbuser表中新增一条记录
bool DB::DbUserInsert(DbUser *dbuser)
{
    std::string insert_str = "insert into dbuser (database_id,dbuser_name,dbuser_pass,isban,creater_id) values  ('";
    insert_str += dbuser->get_database_id_();
    insert_str += "','";
    insert_str += dbuser->get_dbuser_name_();
    insert_str += "','";
    insert_str += dbuser->get_dbuser_password_();
    insert_str += "','";
    insert_str += dbuser->get_isban_();
    insert_str += "','";
    insert_str += dbuser->get_creater_id_();
    insert_str += "');";
    if (mysql_query(&mysql, insert_str.c_str()))
    {
        cerr << "[ERR] mysql insert error: " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}

// 修改dbuser表中某条记录的禁用字段为1，即禁用
bool DB::BanDbUser(DbUser *dbuser)
{
    std::string sql = "update dbuser set isban = '1' where dbuser_id = ";
    sql += "'";
    sql += dbuser->get_dbuser_id_();
    sql += "';";
    if (mysql_query(&mysql, sql.c_str()))
    {
        cerr << "[ERR] mysql insert error: " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}

// 修改dbuser表中某条记录的禁用字段为0，即解禁
bool DB::ReuseDbUser(DbUser *dbuser)
{
    std::string sql = "update dbuser set isban = '0' where dbuser_id = ";
    sql += "'";
    sql += dbuser->get_dbuser_id_();
    sql += "';";
    if (mysql_query(&mysql, sql.c_str()))
    {
        cerr << "[ERR] mysql insert error: " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}

// 删除peglog表中的某条记录
void DB::PegLogDelete(string peguserid, string pegtime, string pegthings)
{
    std::string delete_str = "delete from `peglog` where peguserid='";
    delete_str += peguserid;
    delete_str += "' and pegtime= '";
    delete_str += pegtime;
    delete_str += "' and pegthings= '";
    delete_str += pegthings;
    delete_str += "';";
    mysql_query(&mysql, "SET NAMES utf8");
    mysql_query(&mysql, delete_str.c_str());
}

// 修改dbuser表中某条记录的密码字段
bool DB::DbUserUpdatePassword(DbUser *dbuser, std::string newpass)
{
    std::string sql = "update dbuser set dbuser_pass =";
    sql += "'";
    sql += newpass;
    sql += "'";
    sql += " where dbuser_id = ";
    sql += "'";
    sql += dbuser->get_dbuser_id_();
    sql += "';";
    if (mysql_query(&mysql, sql.c_str()))
    {
        cerr << "[ERR] mysql insert error: " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}

// 在dbrestore表中新增一条记录
bool DB::RestoreInsert(DbRestore *restore)
{
    std::string insert_str = "insert into dbrestore(restore_id,database_id,restore_time,restore_version) values ('";
    insert_str += restore->get_restore_id_();
    insert_str += "','";
    insert_str += restore->get_database_id_();
    insert_str += "','";
    insert_str += restore->get_restore_time_();
    insert_str += "','";
    insert_str += restore->get_restore_version_();
    insert_str += "');";
    if (mysql_query(&mysql, insert_str.c_str()))
    {
        cerr << "[ERR] mysql insert error: " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}

// 获得dbrestore表中的所有数据
std::vector<DbRestore *> DB::RestoreDisplay()
{
    std::vector<DbRestore *> restore_data;
    std::string sql = "select * from `dbrestore`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        DbRestore *restore = new DbRestore;
        restore->set_restore_id_(row[0]);
        restore->set_database_id_(row[1]);
        restore->set_restore_time_(row[2]);
        restore->set_restore_version_(row[3]);
        restore_data.push_back(restore);
    }
    return restore_data;
}

// 获得dbbackup表中的所有数据
std::vector<dbbackup::DbBackup *> DB::BackupDisplay()
{
    std::vector<dbbackup::DbBackup *> backup_data;
    std::string sql = "select * from `dbbackup`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        dbbackup::DbBackup *backup = new dbbackup::DbBackup;
        backup->set_backup_id_(row[0]);
        backup->set_database_id_(row[1]);
        backup->set_backup_time_(row[2]);
        backup->set_backup_version_(row[3]);
        backup->set_backup_path_(row[4]);
        backup_data.push_back(backup);
    }
    return backup_data;
}

// 在dblog表中新增一条记录
void DB::DbLogInsert(dblog::DbLog *dblog)
{
    std::string insert_str = "insert into dblog(operateuserid,operatetime,operatedbid,operatetype) values ('";
    insert_str += dblog->get_operate_user_id_();
    insert_str += "','";
    insert_str += dblog->get_operate_time_();
    insert_str += "','";
    insert_str += dblog->get_operate_database_id_();
    insert_str += "','";
    insert_str += dblog->get_operate_type_();
    insert_str += "');";
    mysql_query(&mysql, insert_str.c_str());
}

// 在peglog表中新增一条记录
void DB::PegLogInsert(peglog::PegLog *peglog)
{
    std::string insert_str = "insert into peglog(peguserid,pegtime,pegthings) values ('";
    insert_str += peglog->get_peg_user_id_();
    insert_str += "','";
    insert_str += peglog->get_peg_time_();
    insert_str += "','";
    insert_str += peglog->get_peg_things_();
    insert_str += "');";
    mysql_query(&mysql, insert_str.c_str());
}

// 获得peglog表中的所有数据
std::vector<peglog::PegLog *> DB::PegLogDisplay()
{
    std::vector<peglog::PegLog *> peglog_data;
    std::string sql = "select * from `peglog`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        peglog::PegLog *peglog = new peglog::PegLog;
        peglog->set_peg_user_id_(row[0]);
        peglog->set_peg_time_(row[1]);
        peglog->set_peg_things_(row[2]);
        peglog_data.push_back(peglog);
    }
    return peglog_data;
}

// 获得dblog表中的所有数据
std::vector<dblog::DbLog *> DB::DbLogDisplay()
{
    std::vector<dblog::DbLog *> dblog_data;
    std::string sql = "select * from `dblog`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        dblog::DbLog *dblog = new dblog::DbLog;
        dblog->set_operate_user_id_(row[0]);
        dblog->set_operate_time_(row[1]);
        dblog->set_operate_database_id_(row[2]);
        dblog->set_operate_type_(row[3]);
        dblog_data.push_back(dblog);
    }
    return dblog_data;
}

// 获得dbnode表中的所有数据
std::vector<dbnode::DbNode *> DB::DbNodeDisplay()
{
    std::vector<dbnode::DbNode *> dbnode_data;
    std::string sql = "select * from `database_node`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        dbnode::DbNode *dbnode = new dbnode::DbNode;
        dbnode->set_database_id_(row[0]);
        dbnode->set_node_ip_(row[1]);
        dbnode->set_node_port_(row[2]);
        dbnode_data.push_back(dbnode);
    }
    return dbnode_data;
}

// 删除dbuser表中的某条记录
bool DB::DbUserDelete(DbUser *dbuser)
{
    std::string sql = "delete from dbuser where dbuser_id =";
    sql += "'";
    sql += dbuser->get_dbuser_id_();
    sql += "';";
    if (mysql_query(&mysql, sql.c_str()))
    {
        cerr << "[ERR] mysql insert error: " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}

// forum
// post
// 获得post表中的所有数据
std::vector<post::Post *> DB::PostDisplay()
{
    std::vector<post::Post *> post_list;
    std::string sql = "select * from `post`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        post::Post *post = new post::Post;
        post->set_post_id_(row[0]);
        post->set_poster_id_(row[1]);
        post->set_poster_name_(row[2]);
        post->set_post_title_(row[3]);
        post->set_post_content_(row[4]);
        post->set_support_num_(row[5]);
        post->set_comments_num_(row[6]);
        post->set_collection_num_(row[7]);
        post->set_post_time_(row[8]);
        post_list.push_back(post);
    }
    return post_list;
}

// 在post表中新增一条记录
bool DB::PostInsert(post::Post *post)
{
    std::string insert_sql = "insert into `post`(post_id,poster_id,poster_name,post_title,post_content,support_num,comments_num,collection_num,post_time) values('";
    insert_sql += post->get_post_id_();
    insert_sql += "','";
    insert_sql += post->get_poster_id_();
    insert_sql += "','";
    insert_sql += post->get_poster_name_();
    insert_sql += "','";
    insert_sql += post->get_post_title_();
    insert_sql += "','";
    insert_sql += post->get_post_content_();
    insert_sql += "','";
    insert_sql += post->get_support_num_();
    insert_sql += "','";
    insert_sql += post->get_comments_num_();
    insert_sql += "','";
    insert_sql += post->get_collection_num_();
    insert_sql += "','";
    insert_sql += post->get_post_time_();
    insert_sql += "');";
    std::cout<<insert_sql<<std::endl;
    if (mysql_query(&mysql, insert_sql.c_str()))
        return false;
    return true;
}

// 修改post表中某条记录的support（点赞）字段
bool DB::PostSupportUpdate(post::Post *post)
{
    std::string update_str = "update post set support_num='";
    update_str += post->get_support_num_();
    update_str += "' where post_id='";
    update_str += post->get_post_id_();
    update_str += "';";
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

// 修改post表中某条记录的collection（收藏）字段
bool DB::PostCollectionUpdate(post::Post *post)
{
    std::string update_str = "update post set collection_num='";
    update_str += post->get_collection_num_();
    update_str += "' where post_id='";
    update_str += post->get_post_id_();
    update_str += "';";
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

// 修改post表中某条记录的comment（评论）字段
bool DB::PostCommentUpdate(post::Post *post)
{
    std::string update_str = "update post set comments_num='";
    update_str += post->get_comments_num_();
    update_str += "' where post_id='";
    update_str += post->get_post_id_();
    update_str += "';";
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

// question
// 获取question表的所有信息
std::vector<question::Question *> DB::QuestionDisplay()
{
    std::vector<question::Question *> question_list;
    std::string sql = "select * from question";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        question::Question *question = new question::Question;
        question->set_question_id_(row[0]);
        question->set_question_content_(row[1]);
        question->set_support_num_(row[2]);
        question->set_comments_num_(row[3]);
        question->set_questioner_id_(row[4]);
        question->set_questioner_name_(row[5]);
        question->set_ques_time_(row[6]);
        question->set_solved_(row[7]);
        question->set_question_title_(row[8]);
        question_list.push_back(question);
    }
    return question_list;
}

// 在question表中插入一条记录
bool DB::QuestionInsert(question::Question *question)
{
    std::string insert_str = "insert into question(question_id,question_content,support_num,comments_num,questioner_id,questioner_name,ques_time,solved,question_title) values('";
    insert_str += question->get_question_id_();
    insert_str += "','";
    insert_str += question->get_question_content_();
    insert_str += "',";
    insert_str += question->get_support_num_();
    insert_str += ",";
    insert_str += question->get_comments_num_();
    insert_str += ",'";
    insert_str += question->get_questioner_id_();
    insert_str += "','";
    insert_str += question->get_questioner_name_();
    insert_str += "','";
    insert_str += question->get_ques_time_();
    insert_str += "',";
    insert_str += question->get_solved_();
    insert_str += ",'";
    insert_str += question->get_question_title_();
    insert_str += "');";
    if (mysql_query(&mysql, insert_str.c_str()))
        return false;
    return true;
}

// 修改question表中某条记录的support（点赞）字段
bool DB::QuestionSupportUpdate(question::Question *question)
{
    std::string update_str = "update question set support_num='";
    update_str += question->get_support_num_();
    update_str += "' where question_id='";
    update_str += question->get_question_id_();
    update_str += "';";
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

// 修改question表中某条记录的comment（评论）字段
bool DB::QuestionCommentUpdate(question::Question *question)
{
    std::string update_str = "update question set comments_num='";
    update_str += question->get_comments_num_();
    update_str += "' where question_id='";
    update_str += question->get_question_id_();
    update_str += "';";
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

//修改question表中的解决字段
bool DB::QuestionResolvedUpdate(const std::string &question_id){
    std::string update_str = "update question set solved=1";
    update_str += " where question_id='";
    update_str += question_id;
    update_str += "';";
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}
// draft
// 获得draft表的所有数据
std::vector<draft::Draft *> DB::DraftDisplay()
{
    std::vector<draft::Draft *> draft_list;
    std::string sql = "select * from draft";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        draft::Draft *draft = new draft::Draft;
        draft->set_type_(row[0]);
        draft->set_title_(row[1]);
        draft->set_content_(row[2]);
        draft->set_author_id_(row[3]);
        draft->set_time_(row[4]);
        draft_list.push_back(draft);
    }
    return draft_list;
}

// 在draft表中插入一条记录
bool DB::DraftInsert(draft::Draft *draft)
{
    std::string insert_str = "insert into draft(type,title,content,author_id,time) values('";
    insert_str += draft->get_type_();
    insert_str += "','";
    insert_str += draft->get_title_();
    insert_str += "','";
    insert_str += draft->get_content_();
    insert_str += "','";
    insert_str += draft->get_author_id_();
    insert_str += "','";
    insert_str += draft->get_time_();
    insert_str += "');";
    if (mysql_query(&mysql, insert_str.c_str()))
        return false;
    return true;
}

// 删除draft表中某条记录
bool DB::DraftDelete(draft::Draft *draft)
{
    std::string delete_str = "delete from draft where type='";
    delete_str += draft->get_type_();
    delete_str += "' and title='";
    delete_str += draft->get_title_();
    delete_str += "' and author_id='";
    delete_str += draft->get_author_id_();
    delete_str += "';";
    if (mysql_query(&mysql, delete_str.c_str()))
        return false;
    return true;
}

// collection
// 获得collection表中的所有记录
std::vector<collection::Collection *> DB::CollectionDisplay()
{
    std::vector<collection::Collection *> collection_list;
    std::string sql = "select * from collection";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        collection::Collection *collection = new collection::Collection;
        collection->set_post_id_(row[0]);
        collection->set_fans_id_(row[1]);
        collection_list.push_back(collection);
    }
    return collection_list;
}

// 在collection表中插入一条记录
bool DB::CollectionInsert(collection::Collection *collection)
{
    std::string insert_str = "insert into collection(post_id,fans_id) values('";
    insert_str += collection->get_post_id_();
    insert_str += "','";
    insert_str += collection->get_fans_id_();
    insert_str += "');";
    if (mysql_query(&mysql, insert_str.c_str()))
        return false;
    return true;
}

// 删除collection表中的某条记录
bool DB::CollectionDelete(collection::Collection *collection)
{
    std::string delete_str = "delete from collection where post_id='";
    delete_str += collection->get_post_id_();
    delete_str += "' and fans_id='";
    delete_str += collection->get_fans_id_();
    delete_str += "';";
    if (mysql_query(&mysql, delete_str.c_str()))
        return false;
    return true;
}

// comments
// 获得comment表中的所有记录
std::vector<comment::Comment *> DB::CommentDisplay()
{
    std::vector<comment::Comment *> comment_list;
    std::string sql = "select * from `comment`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        comment::Comment *comment = new comment::Comment;
        comment->set_post_id_(row[0]);
        comment->set_comment_content_(row[1]);
        comment->set_commenter_id_(row[2]);
        comment->set_commenter_name_(row[3]);
        comment->set_comment_time_(row[4]);
        comment->set_read_flag_(row[5]);
        comment->set_best_answer_(row[6]);
        comment_list.push_back(comment);
    }
    return comment_list;
}

// 在comment表中插入一条记录
bool DB::CommentInsert(comment::Comment *comment)
{
    std::string insert_str = "insert into comment(post_id,comment_content,commenter_id,commenter_name,comment_time,if_read,best_answer) values('";
    insert_str += comment->get_post_id_();
    insert_str += "','";
    insert_str += comment->get_comment_content_();
    insert_str += "','";
    insert_str += comment->get_commenter_id_();
    insert_str += "','";
    insert_str += comment->get_commenter_name_();
    insert_str += "','";
    insert_str += comment->get_comment_time_();
    insert_str += "',";
    insert_str += comment->get_read_flag_();
    insert_str += ",";
    insert_str += comment->get_best_answer_();
    insert_str += ");";
    std::cout<<insert_str<<std::endl;
    if (mysql_query(&mysql, insert_str.c_str()))
        return false;
    return true;
}

// 将comment表中对应多条记录的未读字段设置为已读
bool DB::CommentUpdate(std::vector<comment::Comment *> comments_list)
{
    for (auto i = comments_list.begin(); i != comments_list.end(); i++)
    {
        std::string update_str = "update comment set if_read=1 where post_id='";
        update_str += (*i)->get_post_id_();
        update_str += "' and commenter_id='";
        update_str += (*i)->get_commenter_id_();
        update_str += "';";
        if (mysql_query(&mysql, update_str.c_str()))
            return false;
    }
    return true;
}

// 设置comment表中对应某条记录的最佳回答字段
bool DB::CommentUpdateBestAnswer(comment::Comment *comment)
{
    std::string update_str = "update comment set best_answer=1 where post_id='";
    update_str += comment->get_post_id_();
    update_str += "' and commenter_id='";
    update_str += comment->get_commenter_id_();
    update_str += "' and comment_time='";
    update_str += comment->get_comment_time_();
    update_str += "';";
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

// support
// 获取support表的所有记录
std::vector<support::Support *> DB::SupportDisplay()
{
    std::vector<support::Support *> support_list;
    std::string sql = "select * from `support`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        support::Support *support = new support::Support;
        support->set_post_id_(row[0]);
        support->set_supporter_id_(row[1]);
        support->set_support_time_(row[2]);
        support->set_read_flag_(row[3]);
        support_list.push_back(support);
    }
    return support_list;
}

// 在support表中插入一条新纪录
bool DB::SupportInsert(support::Support *support)
{
    std::string insert_str = "insert into support(post_id,supporter_id,support_time,if_read) values('";
    insert_str += support->get_post_id_();
    insert_str += "','";
    insert_str += support->get_supporter_id_();
    insert_str += "','";
    insert_str += support->get_support_time_();
    insert_str += "',";
    insert_str += support->get_read_flag_();
    insert_str += ");";
    if (mysql_query(&mysql, insert_str.c_str()))
        return false;
    return true;
}

// 删除support表中某条记录
bool DB::SupportDelete(support::Support *support)
{
    std::string delete_str = "delete from support where post_id='";
    delete_str += support->get_post_id_();
    delete_str += "' and supporter_id='";
    delete_str += support->get_supporter_id_();
    delete_str += "';";
    if (mysql_query(&mysql, delete_str.c_str()))
        return false;
    return true;
}

// 将support表中对应多条记录的未读字段设置为已读
bool DB::SupportUpdate(std::vector<support::Support *> support_list)
{
    for (auto i = support_list.begin(); i != support_list.end(); i++)
    {
        std::string update_str = "update support set if_read=1 where post_id='";
        update_str += (*i)->get_post_id_();
        update_str += "' and supporter_id='";
        update_str += (*i)->get_supporter_id_();
        update_str += "';";
        if (mysql_query(&mysql, update_str.c_str()))
            return false;
    }
    return true;
}

// follower
// 获取follower表中的所有记录
std::vector<follower::Follower *> DB::FollowerDisplay()
{
    std::vector<follower::Follower *> follower_list;
    std::string sql = "select * from `follower`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        follower::Follower *follower = new follower::Follower;
        follower->set_user_id_(row[0]);
        follower->set_follower_id_(row[1]);
        follower->set_follow_time_(row[2]);
        follower_list.push_back(follower);
    }
    return follower_list;
}

// 在follower表中插入一条新纪录
bool DB::FollowInsert(follower::Follower *follow)
{
    std::string insert_str = "insert into follower(user_id,follower_id,follow_time) values('";
    insert_str += follow->get_user_id_();
    insert_str += "','";
    insert_str += follow->get_follower_id_();
    insert_str += "','";
    insert_str += follow->get_follow_time_();
    insert_str += "');";
    if (mysql_query(&mysql, insert_str.c_str()))
        return false;
    return true;
}

// 删除follower表中某条记录
bool DB::FollowDelete(follower::Follower *follow)
{
    std::string delete_str = "delete from follower where user_id='";
    delete_str += follow->get_user_id_();
    delete_str += "' and follower_id='";
    delete_str += follow->get_follower_id_();
    delete_str += "';";
    if (mysql_query(&mysql, delete_str.c_str()))
        return false;
    return true;
}

// chat
// 获得chat表的所有记录
std::vector<chat::Chat *> DB::ChatDisplay()
{
    std::vector<chat::Chat *> chat_data;
    std::string query_chat = "select * from chat";
    mysql_query(&mysql, "SET NAMES utf8");
    int ret = mysql_query(&mysql, query_chat.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        chat::Chat *log = new chat::Chat;
        log->set_source_user_id_(row[0]);
        log->set_source_user_name_(row[1]);
        log->set_dest_user_id_(row[2]);
        log->set_dest_user_name_(row[3]);
        log->set_content_(row[4]);
        log->set_send_time_(row[5]);
        log->set_read_flag_(row[6]);
        chat_data.push_back(log);
    }
    return chat_data;
}

// 在chat表中插入一条记录
bool DB::ChatInsert(chat::Chat *chat)
{
    std::string insert_str = "insert into chat(source_user_id,source_user_name,dest_user_id,dest_user_name,content,send_time,if_read) values('";
    insert_str += chat->get_source_user_id_();
    insert_str += "','";
    insert_str += chat->get_source_user_name_();
    insert_str += "','";
    insert_str += chat->get_dest_user_id_();
    insert_str += "','";
    insert_str += chat->get_dest_user_name_();
    insert_str += "','";
    insert_str += chat->get_content_();
    insert_str += "','";
    insert_str += chat->get_send_time_();
    insert_str += "',";
    insert_str += chat->get_read_flag_();
    insert_str += ");";
    if (mysql_query(&mysql, insert_str.c_str()))
        return false;
    return true;
}

// 将chat表中对应记录的未读字段设置为1，标记为已读
bool DB::ChatUpdateFlag(const std::string &source_id, const std::string &dest_id)
{
    std::string update_str = "update chat set if_read=1 where source_user_id='";
    update_str += source_id;
    update_str += "' and dest_user_id='";
    update_str += dest_id;
    update_str += "';";
    if (mysql_query(&mysql, update_str.c_str()))
        return false;
    return true;
}

// 在dbbackup表中插入一条记录
void DB::BackupInsert(dbbackup::DbBackup *backup)
{
    std::string insert_str = "insert into dbbackup(backup_id,database_id,backup_time,backup_version,backup_path) values ('";
    insert_str += backup->get_backup_id_();
    insert_str += "','";
    insert_str += backup->get_database_id_();
    insert_str += "','";
    insert_str += backup->get_backup_time_();
    insert_str += "','";
    insert_str += backup->get_backup_version_();
    insert_str += "','";
    insert_str += backup->get_backup_path_();
    insert_str += "');";
    mysql_query(&mysql, insert_str.c_str());
}

// 在notice表中插入一条记录
void DB::NoticeInsert(Notice *notice)
{
    std::string insert_str = "insert into notice(createrid,createtime,content,noticetopic) values ('";
    insert_str += notice->get_creater_id_();
    insert_str += "','";
    insert_str += notice->get_create_time_();
    insert_str += "','";
    insert_str += notice->get_content_();
    insert_str += "','";
    insert_str += notice->get_notice_topic_();
    insert_str += "');";
    mysql_query(&mysql, insert_str.c_str());
}

// 获取notice表的所有信息
std::vector<Notice *> DB::NoticeDisplay()
{
    std::vector<Notice *> notice_data;
    std::string sql = "select * from `notice`";
    int ret = mysql_query(&mysql, sql.c_str());
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        Notice *notice = new Notice;
        notice->set_creater_id_(row[0]);
        notice->set_create_time_(row[1]);
        notice->set_content_(row[2]);
        notice->set_notice_id_(row[3]);
        notice->set_notice_topic_(row[4]);
        notice_data.push_back(notice);
    }
    return notice_data;
}

// 删除notice表中某条记录
void DB::NoticeDelete(int &id)
{
    std::string delete_str = "delete from `notice` where noticeid='";
    delete_str += to_string(id);
    delete_str += "';";

    mysql_query(&mysql, "SET NAMES utf8");
    mysql_query(&mysql, delete_str.c_str());
}

// 获得token表中所有信息
std::vector<Token *> DB::TokenDisplay()
{
    std::vector<Token *> token_data;
    std::string sql = "select * from `token`";

    if (mysql_query(&mysql, sql.c_str()))
    {
        cerr << "[ERR] mysql insert error: " << mysql_error(&mysql) << endl;
    }
    res = mysql_store_result(&mysql);
    while (row = mysql_fetch_row(res))
    {
        Token *token = new Token;
        token->set_user_id_(row[0]);
        token->set_token_(row[1]);
        token->set_time_(row[2]);
        token_data.push_back(token);
    }
    return token_data;
}

// 在token表中新增一条记录
bool DB::TokenInsert(Token *token)
{
    std::string insert_str = "insert into token values ('";
    insert_str += token->get_user_id_();
    insert_str += "','";
    insert_str += token->get_token_();
    insert_str += "',";
    insert_str += "now()";
    insert_str += ");";
    if (mysql_query(&mysql, insert_str.c_str()))
    {
        cerr << "[ERR] mysql insert error: " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}
bool DB::DBnodeinsert(dbnode::DbNode *dbnode)
{
    string insert_str = "insert into `database_node` values('";
    insert_str += dbnode->get_database_id_();
    insert_str += "','";
    insert_str += dbnode->get_node_ip_();
    insert_str += "','";
    insert_str += dbnode->get_node_port_();
    insert_str += "');";
    if (mysql_query(&mysql, insert_str.c_str()))
    {
        cerr << "[ERR] mysql insert error: " << mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}