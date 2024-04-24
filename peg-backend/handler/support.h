/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       support.h
 * @brief      the Support class
 * @descripition
 * 成员函数：
 *  std::string IfSupportPost(const std::string &post_id,const std::string &user_id,
 * std::vector<Support *> support_list);
    根据postid和userid获取该帖子是否为该人点赞过
    std::vector<Support *> GetUnreadPostSupportList(const std::vector<std::string> postid_list,
                                                    std::vector<Support *> support_list);
    获取该人未读的帖子点赞数目
    std::vector<Support *> GetUnreadQuestionSupportList(const std::vector<std::string> questionid_list,
                                                        std::vector<Support *> support_list);
    获取该人未读的问答点赞列表
    std::vector<Support *> SetUnreadPostSupportList(const std::vector<std::string> postid_list,
                                                    std::vector<Support *> support_list);
    将未读文章点赞设置为已读
    std::vector<Support *> SetUnreadQuestionSupportList(const std::vector<std::string> questionid_list,             
                                                        std::vector<Support *> support_list);
    将未读问题点赞设置为已读
    Support * GetSupportLog(const std::string &user_id,const std::string &post_id,
                            std::vector<Support *> support_list);
    得到点赞项
    std::vector<Support *> SupportDelete(const std::string &user_id,const std::string &post_id,
                                         std::vector<Support *> support_list);
    删除点赞项
 * 成员变量：
   std::string post_id_      文章id
   std::string supporter_id_ 点赞id
   std::string support_time_ 点赞时间
   std::string read_flag_    是否已读
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef SUPPORT_H_
#define SUPPORT_H_

#include <iostream>
#include <vector>

namespace support
{
    class Support
    {
    public:
        Support();
        inline void set_post_id_(const std::string &post_id);
        inline void set_supporter_id_(const std::string &supporter_id);
        inline void set_support_time_(const std::string &support_time);
        inline void set_read_flag_(const std::string &flag);
        inline std::string get_post_id_();
        inline std::string get_supporter_id_();
        inline std::string get_support_time_();
        inline std::string get_read_flag_();
        void NewSupport(const std::string &post_id, const std::string &user_id);

    private:
        std::string post_id_;
        std::string supporter_id_;
        std::string support_time_;
        std::string read_flag_;
    };
    inline void Support::set_post_id_(const std::string &post_id)
    {
        this->post_id_ = post_id;
    }
    inline void Support::set_supporter_id_(const std::string &supporter_id)
    {
        this->supporter_id_ = supporter_id;
    }
    inline void Support::set_support_time_(const std::string &support_time)
    {
        this->support_time_ = support_time;
    }
    inline void Support::set_read_flag_(const std::string &flag)
    {
        this->read_flag_ = flag;
    }
    inline std::string Support::get_post_id_()
    {
        return this->post_id_;
    }
    inline std::string Support::get_supporter_id_()
    {
        return this->supporter_id_;
    }
    inline std::string Support::get_support_time_()
    {
        return this->support_time_;
    }
    inline std::string Support::get_read_flag_()
    {
        return this->read_flag_;
    }
    // 根据postid和userid获取该帖子是否为该人点赞过
    std::string IfSupportPost(const std::string &post_id, const std::string &user_id,
                              std::vector<Support *> support_list);
    // 获取该人未读的帖子点赞数目
    std::vector<Support *> GetUnreadPostSupportList(const std::vector<std::string> postid_list,
                                                    std::vector<Support *> support_list);
    // 获取该人未读的问答点赞数目
    std::vector<Support *> GetUnreadQuestionSupportList(const std::vector<std::string> questionid_list,
                                                        std::vector<Support *> support_list);
    // 将未读点赞设置为已读
    std::vector<Support *> SetUnreadPostSupportList(const std::vector<std::string> postid_list,
                                                    std::vector<Support *> support_list);
    std::vector<Support *> SetUnreadQuestionSupportList(const std::vector<std::string> questionid_list,
                                                        std::vector<Support *> support_list);

    Support *GetSupportLog(const std::string &user_id, const std::string &post_id,
                           std::vector<Support *> support_list);

    std::vector<Support *> SupportDelete(const std::string &user_id, const std::string &post_id,
                                         std::vector<Support *> support_list);
}
#endif