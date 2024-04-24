/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       database.h
 * @brief      the Database class
 * @descripition
 * 成员函数：
 *  int DbBuild(vector<map<string, string>> confJson, std::vector<GstoreConnector *> &servers,
                const std::string &db_path, const std::string &divfile_path)
 *  创建数据库函数
 *  查询函数，划分输入的sparql语句，分解查询，组合结果
 *  nlohmann::json DbInsert(std::vector<GstoreConnector *> &servers,std::string insert_sql)
 *  数据库增
 *  nlohmann::json DbDelete(std::vector<GstoreConnector *> &servers, std::string delete_sql)
 *  数据库删
 *  nlohmann::json DbMonitor(std::vector<GstoreConnector *> &servers)
 *  监控数据库
 *  int DbBackUp(std::vector<GstoreConnector*> &servers,const std::string &path,const std::string version)
 *  备份数据库
 *  int DbRestore(std::vector<GstoreConnector *> &servers,const std::string &path)
 *  还原数据库
 *  int DbExport(std::vector<GstoreConnector *> &servers,const std::string &path)
 *  导出数据库
 *  int DeleteDb(std::vector<GstoreConnector *> &servers, const std::string &db_name)
 *  删除数据库
 *  非成员函数：
    std::vector<Database *> UserQueryDb(std::vector<Database *> db_list, const std::string &creater_id);
    得到该用户id下的所有数据库
    Database * DatabaseIdGetData(const std::string &database_id, std::vector<Database *> db_list);
    根据数据库id获得该数据库信息
    std::string GetDatabaseId(const std::string &database_name, const std::string &database_creater_id,
                              std::vector<Database *> db_list);
    根据数据库名称和创建者id获得数据库id
    std::string GetDatabasePassword(const std::string &database_name, const std::string &database_creater_id,
                                    std::vector<Database *> db_list);
    根据数据库名称和创建者id获得数据库密码
    int Divide(const std::string &ntfile, const std::string &divide_file);
    数据库划分
 * 成员变量：
 *  std::string database_id_  数据库id
 *  std::string database_name_  数据库名称
 *  std::string creater_id_  创建者id
 *  std::string database_password_ 创建者密码
 *  std::string database_version_ 数据库版本
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <string>
#include <vector>
#include "crow/json.h"
#include "../util/FileTransfer.h"
#include "../util/RemoteCmdInvoker.h"
#include "../queryDecompose/Query/QueryTree.h"
#include "../queryDecompose/Query/GeneralEvaluation.h"
#include "../joiner/joiner.h"

namespace database
{
    class Database
    {
    public:
        Database();
        void NewDatabase(std::string database_id, std::string database_name, std::string creater_id,
                         std::string database_password, std::string database_version);
        inline void set_database_id_(const std::string &database_id)
        {
            this->database_id_ = database_id;
        }
        inline void set_database_name_(const std::string &database_name)
        {
            this->database_name_ = database_name;
        }
        inline void set_creater_id_(const std::string &creater_id)
        {
            this->creater_id_ = creater_id;
        }
        inline void set_database_password_(const std::string &database_password)
        {
            this->database_password_ = database_password;
        }
        inline void set_database_version_(const std::string &database_version)
        {
            this->database_version_ = database_version;
        }

        inline std::string get_database_id_()
        {
            return this->database_id_;
        }
        inline std::string get_database_name_()
        {
            return this->database_name_;
        };
        inline std::string get_creater_id_()
        {
            return this->creater_id_;
        };
        inline std::string get_database_password_()
        {
            return this->database_password_;
        };
        inline std::string get_database_version_()
        {
            return this->database_version_;
        };

        int DbBuild(vector<map<string, string>> confJson, std::vector<GstoreConnector *> &servers,
                    const std::string &db_path, const std::string &divfile_path);
        nlohmann::json DbQuery(std::vector<GstoreConnector *> &servers, std::string query);
        nlohmann::json DbInsert(std::vector<GstoreConnector *> &servers, std::string insert_sql);
        nlohmann::json DbDelete(std::vector<GstoreConnector *> &servers, std::string delete_sql);
        nlohmann::json DbMonitor(std::vector<GstoreConnector *> &servers);
        std::string DbBackUp(std::vector<GstoreConnector *> &servers, const std::string &path, const std::string version);
        std::string DbRestore(std::vector<GstoreConnector *> &servers, const std::string &path);
        std::string DbExport(std::vector<GstoreConnector *> &servers, const std::string &path);
        int DeleteDb(std::vector<GstoreConnector *> &servers, const std::string &db_name);

    private:
        std::string database_id_;
        std::string database_name_;
        std::string creater_id_;
        std::string database_password_;
        std::string database_version_;
    };

    std::vector<Database *> UserQueryDb(std::vector<Database *> db_list, const std::string &creater_id);

    Database *DatabaseIdGetData(const std::string &database_id, std::vector<Database *> db_list);

    std::string GetData(vector<map<string, string>> &confJson, std::vector<GstoreConnector *> &servers);
    // 根据数据库名称和创建者id获得数据库id
    std::string GetDatabaseId(const std::string &database_name, const std::string &database_creater_id,
                              std::vector<Database *> db_list);
    std::string GetDatabasePassword(const std::string &database_name, const std::string &database_creater_id,
                                    std::vector<Database *> db_list);

    int Divide(const std::string &ntfile, const std::string &divide_file);
}

#endif // DATABASE_H_
