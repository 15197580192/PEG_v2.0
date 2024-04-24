/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       follow.h
 * @brief      the Follow class
 * @descripition
 * 成员函数：
 *  void NewFollow(const std::string &user_id,const std::string &follower_id);
 *  构建关注项
 * 非成员函数：
 *  std::string GetConcernNum(std::vector<Follower *> follower_list,const std::string &user_id);
 *  根据用户id获得关注者数量
 *  std::vector<std::string> GetConcernList(std::vector<Follower *> follower_list,const std::string &user_id);
 *  根据用户id获得他关注人id
 *  std::string GetFollowersNum(std::vector<Follower *> follower_list,const std::string &user_id);
 *  根据用户id获得粉丝数量
 *  Follower * GetFollowLog(const std::string &user_id,const std::string &follower_id,
 *                          std::vector<Follower *> follower_list);
 *  获得一个关注记录
 *  std::vector<Follower *> FollowDelete(const std::string &user_id,const std::string &follower_id,
 *                                       std::vector<Follower *> follower_list);
 *  删除一个关注记录
 *  std::string IfFollowUser(const std::string &user_id,const std::string &follow_id,
 *                           std::vector<Follower *> follower_list);
 *  查询一个用户是否有关注

 * 成员变量：
 *  std::string user_id_      用户id
 *  std::string follower_id_  关注者id
 *  std::string follow_time_  关注时间
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef FOLLOWER_H_
#define FOLLOWER_H_

#include <iostream>
#include <vector>
#include <sstream>
#include "tool.h"

namespace follower
{
    class Follower
    {
    public:
        Follower();
        inline void set_user_id_(const std::string &user_id);
        inline void set_follower_id_(const std::string &follower_id);
        inline void set_follow_time_(const std::string &follow_time);
        inline std::string get_user_id_();
        inline std::string get_follower_id_();
        inline std::string get_follow_time_();
        void NewFollow(const std::string &user_id, const std::string &follower_id);
        // std::string GetConcernNum(std::vector<Follower *> follower_list);
        // std::string GetFollowersNum(std::vector<Follower *> follower_list);
    private:
        std::string user_id_;
        std::string follower_id_;
        std::string follow_time_;
    };
    inline void Follower::set_user_id_(const std::string &user_id)
    {
        this->user_id_ = user_id;
    }
    inline void Follower::set_follower_id_(const std::string &follower_id)
    {
        this->follower_id_ = follower_id;
    }
    inline void Follower::set_follow_time_(const std::string &follow_time)
    {
        this->follow_time_ = follow_time;
    }
    inline std::string Follower::get_user_id_()
    {
        return this->user_id_;
    }
    inline std::string Follower::get_follower_id_()
    {
        return this->follower_id_;
    }
    inline std::string Follower::get_follow_time_()
    {
        return this->follow_time_;
    }

    std::string GetConcernNum(std::vector<Follower *> follower_list, const std::string &user_id);
    std::vector<std::string> GetConcernList(std::vector<Follower *> follower_list, const std::string &user_id);
    std::string GetFollowersNum(std::vector<Follower *> follower_list, const std::string &user_id);
    Follower *GetFollowLog(const std::string &user_id, const std::string &follower_id, 
                           std::vector<Follower *> follower_list);
    std::vector<Follower *> FollowDelete(const std::string &user_id, const std::string &follower_id, 
                                         std::vector<Follower *> follower_list);
    std::string IfFollowUser(const std::string &user_id, const std::string &follow_id, 
                             std::vector<Follower *> follower_list);
}

#endif