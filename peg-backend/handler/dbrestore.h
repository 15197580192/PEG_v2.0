/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       dbrestore.h
 * @brief      the DBRestore class
 * @descripition
 *
 * 成员变量：
 *  std::string restore_id_ 还原id，唯一标识
 *  std::string database_id_ 数据库id
 *  std::string restore_time_ 还原时间
 *  std::string restore_version_ 还原版本
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef DBRESTORE_H_
#define DBRESTORE_H_

#include <iostream>

class DbRestore
{
public:
   DbRestore();
   inline void set_restore_id_(const std::string &restoreid)
   {
      this->restore_id_ = restoreid;
   };
   inline void set_database_id_(const std::string &databaseid)
   {
      this->database_id_ = databaseid;
   };

   inline void set_restore_time_(const std ::string &restoretime)
   {
      this->restore_time_ = restoretime;
   };
   inline void set_restore_version_(const std ::string &restoreversion)
   {
      this->restore_version_ = restoreversion;
   };

   inline std::string get_restore_id_()
   {
      return this->restore_id_;
   };

   inline std::string get_database_id_()
   {
      return this->database_id_;
   };

   inline std::string get_restore_time_()
   {
      return this->restore_time_;
   };

   inline std::string get_restore_version_()
   {
      return this->restore_version_;
   };

private:
   std::string restore_id_;
   std::string database_id_;
   std::string restore_time_;
   std::string restore_version_;
};

#endif // DBRESTORE_H_