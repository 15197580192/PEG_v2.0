#include "node.h"

node::Node::Node()
{
   node_id_ = "0";
   node_ip_ = "0";
   user_id_ = "0";
   port_ = "0";
   gstore_user_id_ = "0";
   gstore_user_password_ = "0";
   version_ = "0";
   apitype_ = "0";
   rootpath_ = "0";
}

void node::Node::new_nodedata(const std::string &node_id, const std::string &node_ip, const std::string &user_id,
                              const std::string &port, const std::string &gstore_user_id,
                              const std::string &gstore_user_password, const std::string &version,
                              const std::string &apitype, const std::string &rootpath)
{
   this->node_id_ = node_id;
   this->node_ip_ = node_ip;
   this->user_id_ = user_id;
   this->port_ = port;
   this->gstore_user_id_ = gstore_user_id;
   this->gstore_user_password_ = gstore_user_password;
   this->version_ = version;
   this->apitype_ = apitype;
   this->rootpath_ = rootpath;
};

/*****************************************************************
 * 函数名称： std::vector<Node *> DeleteNode(std::vector<std::string> node_id,std::vector<Node *> node_data)
 * 功能描述： 根据节点id，在节点列表中删除某个节点
 * 参数说明： vector容器，为节点列表和节点id
 * 返回值：   更新后的节点列表
 ******************************************************************/
std::vector<node::Node *> node::DeleteNode(std::vector<std::string> node_id, std::vector<node::Node *> node_data)
{
   for (int i = 0; i < node_id.size(); i++)
   {
      for (auto j = node_data.begin(); j != node_data.end(); j++)
      {
         if (((*j)->get_node_id_()) == node_id[i])
         {
            node_data.erase(j);
            break;
         }
      }
   }
   return node_data;
}

/*****************************************************************
 * 函数名称： bool CheckNode(std::string node_id,std::string node_ip,std::vector<Node *> node_data)
 * 功能描述： 检查节点id和ip是否重复
 * 参数说明： vector容器，为节点列表；字符串，为节点id和ip
 * 返回值：   bool判断值
 ******************************************************************/
bool node::CheckNode(const std::string &node_id, const std::string &node_ip, std::vector<node::Node *> node_data)
{
   for (auto i = node_data.begin(); i != node_data.end(); i++)
   {
      if (((*i)->get_node_id_() == node_id) && ((*i)->get_node_ip_() == node_ip))
         return false;
   }
   return true;
}

/*****************************************************************
 * 函数名称： std::vector<Node *> node_data_modify(std::vector<Node *> node_data,Node *node)
 * 功能描述： 修改节点列表中某个节点
 * 参数说明： vector容器，为节点列表；Node对象，包含需要修改的所有信息
 * 返回值：   更新后的节点列表
 ******************************************************************/
std::vector<node::Node *> node::NodeDataModify(std::vector<node::Node *> node_data, node::Node *node)
{
   for (auto it = node_data.begin(); it != node_data.end(); it++)
   {
      if (((*it)->get_node_id_() == node->get_node_id_()) && (*it)->get_node_ip_() == node->get_node_ip_())
      {
         node_data.erase(it);
         break;
      }
   }
   node_data.push_back(node);
   return node_data;
}
