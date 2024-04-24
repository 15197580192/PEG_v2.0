#include "dbnode.h"
/*****************************************************************
 * 函数名称： void dbnode::DbNode::NewDbNode(const std::string &database_id, const std::string &node_ip, 
 *                                          const std::string &node_port)
 * 功能描述： 赋值数据库节点项
 * 参数说明： 字符串类型的数据库id,节点ip,节点port
 * 返回值：   无返回值
 ******************************************************************/
void dbnode::DbNode::NewDbNode(const std::string &database_id, const std::string &node_ip, 
                               const std::string &node_port)
{
    this->database_id_ = database_id;
    this->node_ip_ = node_ip;
    this->node_port_ = node_port;
}
/*****************************************************************
 * 函数名称： void dbnode::DbNode::NewDbNode(const std::string &database_id, const std::string &node_ip, 
 *                                          const std::string &node_port)
 * 功能描述： 判断是否是相关节点
 * 参数说明： 字符串类型的数据库id,节点项，vector类型的节点列表
 * 返回值：   无返回值
 ******************************************************************/
bool dbnode::JudgeNoAboutNodes(const std::string &db_id, GstoreConnector *server, 
                               std::vector<dbnode::DbNode *> dbnode_list)
{
    bool flag = false;
    for (int i = 0; i < dbnode_list.size(); i++)
    {
        if (dbnode_list[i]->get_database_id_() == db_id && dbnode_list[i]->get_node_ip_() == server->serverIP && dbnode_list[i]->get_node_port_() == std::to_string(server->serverPort))
        {
            flag = true;
        }
    }
}