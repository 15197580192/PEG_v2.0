/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       dbnode.h
 * @brief      the DbNode class
 * @descripition
 * 成员函数：
 *   void void NewDbNode(const std::string &database_id, const std::string &node_ip, const std::string &node_port);
 *  赋值备份类
 * 非成员函数：
 *  bool JudgeNoAboutNodes(const std::string &db_id, GstoreConnector *server, std::vector<DbNode *> dbnode_list);
 * 通过id查询备份列表
 * 成员变量：
 *  std::string database_id_   数据库id
 *  std::string node_ip_       节点ip
 *  std::string node_port_     节点Port
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef DBNODE_H_
#define DBNODE_H_
#include <iostream>
#include <vector>
#include "../gStoreAPI/client.h"

namespace dbnode
{
    class DbNode
    {
    private:
        std::string database_id_;
        std::string node_ip_;
        std::string node_port_;

    public:
        inline void set_database_id_(const std::string &databaseid)
        {
            this->database_id_ = databaseid;
        }

        inline void set_node_ip_(const std::string &nodeip)
        {
            this->node_ip_ = nodeip;
        }

        inline void set_node_port_(const std::string &nodeport)
        {
            this->node_port_ = nodeport;
        }

        inline std::string get_database_id_()
        {
            return this->database_id_;
        }

        inline std::string get_node_ip_()
        {
            return this->node_ip_;
        }

        inline std::string get_node_port_()
        {
            return this->node_port_;
        }
        void NewDbNode(const std::string &database_id, const std::string &node_ip, const std::string &node_port);
    };
    bool JudgeNoAboutNodes(const std::string &db_id, GstoreConnector *server, std::vector<DbNode *> dbnode_list);
}
#endif