/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       dbbackup.h
 * @brief      the DbBackup class
 * @descripition
 * 成员函数：
 *  void NewDbBackup(const std::string &backup_id,const std::string &database_id,const std::string &backup_version,
 *                   const std::string &backup_path);
 *  赋值备份类
 * 非成员函数：
 *  std::vector<DbBackup *> BackupDisplayById(const std::string &id, std::vector<DbBackup *> backup_data);
 * 通过id查询备份列表
 * 成员变量：
 *  std::string backup_id_       备份id
 *  std::string database_id_     数据库id
 *  std::string backup_time_     备份时间
 *  std::string backup_version_  备份版本
 *  std::string backup_path_;    备份路径
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef DBBACKEUP_H_
#define DBBACKEUP_H_

#include <iostream>
#include <vector>

namespace dbbackup
{
    class DbBackup
    {
    private:
        std::string backup_id_;
        std::string database_id_;
        std::string backup_time_;
        std::string backup_version_;
        std::string backup_path_;

    public:
        inline std::string get_backup_id_();
        inline std::string get_database_id_();
        inline std::string get_backup_time_();
        inline std::string get_backup_version_();
        inline std::string get_backup_path_();
        inline void set_backup_id_(const std::string &backup_id);
        inline void set_database_id_(const std::string &database_id);
        inline void set_backup_time_(const std::string &backup_time);
        inline void set_backup_version_(const std::string &backup_version);
        inline void set_backup_path_(const std::string &backup_path_);
        void NewDbBackup(const std::string &backup_id, const std::string &database_id, const std::string &backup_version, const std::string &backup_path, const std::string &backup_time);
    };
    inline std::string DbBackup::get_backup_id_()
    {
        return this->backup_id_;
    }
    inline std::string DbBackup::get_database_id_()
    {
        return this->database_id_;
    }
    inline std::string DbBackup::get_backup_time_()
    {
        return this->backup_time_;
    }
    inline std::string DbBackup::get_backup_version_()
    {
        return this->backup_version_;
    }
    inline std::string DbBackup::get_backup_path_()
    {
        return this->backup_path_;
    }
    inline void DbBackup::set_backup_path_(const std::string &backup_path_)
    {
        this->backup_path_ = backup_path_;
    }
    inline void DbBackup::set_backup_id_(const std::string &backup_id)
    {
        this->backup_id_ = backup_id;
    }
    inline void DbBackup::set_database_id_(const std::string &database_id)
    {
        this->database_id_ = database_id;
    }
    inline void DbBackup::set_backup_time_(const std::string &backup_time)
    {
        this->backup_time_ = backup_time;
    }
    inline void DbBackup::set_backup_version_(const std::string &backup_version)
    {
        this->backup_version_ = backup_version;
    }
    std::vector<DbBackup *> BackupDisplayById(const std::string &id, std::vector<DbBackup *> backup_data);
}

#endif
