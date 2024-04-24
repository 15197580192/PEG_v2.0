/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       user.h
 * @brief      the User class
 * @descripition
 *
 * 成员变量：
 *   std::string usernode_id_ 节点用户id
 *   std::string user_id_ 用户id
 *   std::string node_id_ 节点id
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef USERNODE_H_
#define USERNODE_H_

#include <iostream>

class UserNode
{
public:
    UserNode();
    inline std::string get_usernode_id_();
    inline std::string get_user_id_();
    inline std::string get_node_id_();
    inline void set_usernode_id_(const std::string &usernode_id);
    inline void set_user_id_(const std::string &user_id);
    inline void set_node_id_(const std::string &node_id);

private:
    std::string usernode_id_;
    std::string user_id_;
    std::string node_id_;
};
inline std::string UserNode::get_usernode_id_()
{
    return this->usernode_id_;
}
inline std::string UserNode::get_user_id_()
{
    return this->user_id_;
}
inline std::string UserNode::get_node_id_()
{
    return this->node_id_;
}
inline void UserNode::set_usernode_id_(const std::string &usernode_id)
{
    this->usernode_id_ = usernode_id;
}
inline void UserNode::set_user_id_(const std::string &user_id)
{
    this->user_id_ = user_id;
}
inline void UserNode::set_node_id_(const std::string &node_id)
{
    this->node_id_ = node_id;
}

#endif // USERNODE_H_