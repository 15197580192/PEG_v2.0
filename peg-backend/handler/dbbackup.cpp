#include "dbbackup.h"
/*****************************************************************
 * 函数名称： void dbbackup::DbBackup::NewDbBackup(const std::string &backup_id,const std::string &database_id,
 *                                                const std::string &backup_version,const std::string &backup_path)
 * 功能描述： 赋值备份项
 * 参数说明： 字符串类型的备份id,数据库id,备份版本,备份路径
 * 返回值：   无返回值
 ******************************************************************/
void dbbackup::DbBackup::NewDbBackup(const std::string &backup_id, const std::string &database_id, const std::string &backup_version, const std::string &backup_path, const std::string &backup_time)
{
    this->backup_id_ = backup_id;
    this->database_id_ = database_id;

    this->backup_time_ = backup_time;
    this->backup_version_ = backup_version;
    this->backup_path_ = backup_path;
}
/*****************************************************************
 * 函数名称： std::vector<dbbackup::DbBackup *> dbbackup::BackupDisplayById(
 *           const std::string &id, 
 *           std::vector<dbbackup::DbBackup *> backup_data)
 * 功能描述： 赋值备份项
 * 参数说明： 字符串类型的查询id,vector类型的备份列表
 * 返回值：   查询后的备份列表
 ******************************************************************/
std::vector<dbbackup::DbBackup *> dbbackup::BackupDisplayById(const std::string &id, 
                                                              std::vector<dbbackup::DbBackup *> backup_data)
{
    std::vector<dbbackup::DbBackup *> tmpbackup_data = backup_data;
    for (int i = 0; i < tmpbackup_data.size(); i++)
    {
        if (tmpbackup_data[i]->get_database_id_() != id)
        {
            
            tmpbackup_data.erase(tmpbackup_data.begin() + i);
            i--;
        }
    }
    return tmpbackup_data;
}