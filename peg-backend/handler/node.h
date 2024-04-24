/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       node.h
 * @brief      the Node class
 * @descripition
 *
 *  名字空间内的非成员函数：
 *  std::vector<Node *> DeleteNode(std::vector<std::string> node_id,std::vector<Node *> node_data) 删除节点
 *  bool CheckNode(std::string node_id,std::string node_ip,std::vector<Node *> node_data) 检查节点名称和ip是否重复
 *  std::vector<Node *> node_data_modify(std::vector<Node *> node_data,Node *node) 修改节点信息
 *
 *  成员变量：
 *  std::string node_id_ 节点id
 *  std::string node_ip_ 节点ip
 *  std::string user_id_ 用户id
 *  std::string port_ 节点端口号
 *  std::string gstore_user_id_ gstore用户id
 *  std::string gstore_user_password_ gstore用户密码
 *  std::string version_ gstore版本
 *  std::string apitype_ gstoreapi类型
 *  std::string rootpath_ gstore节点路径
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
namespace node
{
   class Node
   {
   public:
      Node();
      void new_nodedata(const std::string &node_id, const std::string &node_ip, const std::string &user_id,
                        const std::string &port, const std::string &gstore_user_id,
                        const std::string &gstore_user_password, const std::string &version,
                        const std::string &apitype, const std::string &rootpath);
      inline void set_node_id_(const std::string &node_id)
      {
         this->node_id_ = node_id;
      };
      inline void set_node_ip_(const std::string &node_ip)
      {
         this->node_ip_ = node_ip;
      };
      inline void set_user_id_(const std::string &user_id)
      {
         this->user_id_ = user_id;
      };
      inline void set_port_(const std::string &port)
      {
         this->port_ = port;
      };
      inline void set_gstore_user_id_(const std::string &gstore_user_id)
      {
         this->gstore_user_id_ = gstore_user_id;
      };
      inline void set_gstore_user_password_(const std::string &gstore_user_password)
      {
         this->gstore_user_password_ = gstore_user_password;
      };
      inline void set_version_(const std::string &version)
      {
         this->version_ = version;
      };
      inline void set_apitype_(const std::string &apitype)
      {
         this->apitype_ = apitype;
      };
      inline void set_rootpath_(const std::string &rootpath)
      {
         this->rootpath_ = rootpath;
      };

      inline std::string get_node_id_()
      {
         return this->node_id_;
      };
      inline std::string get_node_ip_()
      {
         return this->node_ip_;
      };
      inline std::string get_user_id_()
      {
         return this->user_id_;
      };
      inline std::string get_port_()
      {
         return this->port_;
      };
      inline std::string get_gstore_user_id_()
      {
         return this->gstore_user_id_;
      };
      inline std::string get_gstore_user_password_()
      {
         return this->gstore_user_password_;
      };
      inline std::string get_version_()
      {
         return this->version_;
      };
      inline std::string get_apitype_()
      {
         return this->apitype_;
      };
      inline std::string get_rootpath_()
      {
         return this->rootpath_;
      };

   private:
      std::string node_id_;
      std::string node_ip_;
      std::string user_id_;
      std::string port_;
      std::string gstore_user_id_;
      std::string gstore_user_password_;
      std::string version_;
      std::string apitype_;
      std::string rootpath_;
   };
   std::vector<Node *> DeleteNode(std::vector<std::string> node_id, std::vector<Node *> node_data);
   bool CheckNode(const std::string &node_id, const std::string &node_ip, std::vector<Node *> node_data);
   std::vector<Node *> NodeDataModify(std::vector<Node *> node_data, Node *node);
}

#endif // NODE_H_