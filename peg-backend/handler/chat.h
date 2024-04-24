/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       chat.h
 * @brief      the Chat class
 * @descripition
 * 成员函数：
 *  bool CmpByTime(chat::ChatHistory *history1,chat::ChatHistory *history2);
    自定义排序规则，先根据id排序，id相同的根据时间排序
 *  std::vector<chat::ChatHistory *> GetChatHistory(const std::string &user_id,std::vector<chat::Chat *>chat_list);
    根据一个人的id获取他的所有聊天信息，按照id和发送时间排序
 *  std::vector<chat::ChatHistory *> GetLatelyChat(std::vector<chat::ChatHistory *> chat_history);
    获取每个用户发送的最新的一条消息
 *  std::vector<chat::Chat *> GetOneUserChat(const std::string &dest_id,std::vector<chat::ChatHistory *> chat_history);
    获得两个人全部的聊天记录
 *  int GetServer(const std::string &user_id,std::vector<peguser::PegUser *>peguser_list,std::vector<chat::ChatHistory *> chat_history);
    将该用户连接到服务器，用于接收信息
 *  int SendToDestServer(const std::string &source_user_id,const std::string &dest_user_id,const std::string &content,std::vector<peguser::PegUser *>peguser_list);
    发送某条消息
 * 成员变量：
 *  std::string source_user_id_    发送者账号
 *  std::string source_user_name_  发送者名字
 *  std::string dest_user_id_      接收者账号
 *  std::string dest_user_name_    接受者名字
 *  std::string content_           内容
 *  std::string send_time_         发送时间
 *  std::string read_flag_     //该标志应该是相对于对方来说的是否已读标志
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/

#ifndef CHAT_H_
#define CHAT_H_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>
#include "peguser.h"
#include "tool.h"

#define BUFFSIZE 1024
#define ERRORCODE -1
namespace chat
{
    class Chat
    {
    public:
        Chat();
        inline void set_source_user_id_(const std::string &source_user_id);
        inline void set_source_user_name_(const std::string &source_user_name);
        inline void set_dest_user_id_(const std::string &dest_user_id);
        inline void set_dest_user_name_(const std::string &dest_user_name);
        inline void set_content_(const std::string &content);
        inline void set_send_time_(const std::string &sent_time);
        inline void set_read_flag_(const std::string &flag);
        inline std::string get_source_user_id_();
        inline std::string get_source_user_name_();
        inline std::string get_dest_user_id_();
        inline std::string get_dest_user_name_();
        inline std::string get_content_();
        inline std::string get_send_time_();
        inline std::string get_read_flag_();
        void NewChat(const std::string &source_id, const std::string &dest_id, const std::string &content,
                     std::vector<peguser::PegUser *> peguser_list);

    private:
        std::string source_user_id_;
        std::string source_user_name_;
        std::string dest_user_id_;
        std::string dest_user_name_;
        std::string content_;
        std::string send_time_;
        std::string read_flag_; // 该标志应该是相对于对方来说的是否已读标志
    };

    struct SocketFd{
        std::string user_id;
        int fd;
    };

    struct ChatHistory
    {
        std::string role_id_; // 记录聊天对方id
        std::vector<Chat *> chat_list_;     // 记录与该人所有聊天记录
    };

    inline void Chat::set_source_user_id_(const std::string &source_user_id)
    {
        this->source_user_id_ = source_user_id;
    }
    inline void Chat::set_source_user_name_(const std::string &source_user_name)
    {
        this->source_user_name_ = source_user_name;
    }
    inline void Chat::set_dest_user_id_(const std::string &dest_user_id)
    {
        this->dest_user_id_ = dest_user_id;
    }
    inline void Chat::set_dest_user_name_(const std::string &dest_user_name)
    {
        this->dest_user_name_ = dest_user_name;
    }
    inline void Chat::set_content_(const std::string &content)
    {
        this->content_ = content;
    }
    inline void Chat::set_send_time_(const std::string &sent_time)
    {
        this->send_time_ = sent_time;
    }
    inline void Chat::set_read_flag_(const std::string &flag)
    {
        this->read_flag_ = flag;
    }
    inline std::string Chat::get_source_user_id_()
    {
        return this->source_user_id_;
    }
    inline std::string Chat::get_source_user_name_()
    {
        return this->source_user_name_;
    }
    inline std::string Chat::get_dest_user_id_()
    {
        return this->dest_user_id_;
    }
    inline std::string Chat::get_dest_user_name_()
    {
        return this->dest_user_name_;
    }
    inline std::string Chat::get_content_()
    {
        return this->content_;
    }
    inline std::string Chat::get_send_time_()
    {
        return this->send_time_;
    }
    inline std::string Chat::get_read_flag_()
    {
        return this->read_flag_;
    }
    bool CmpByTime(Chat* chat1, Chat* chat2);
    std::vector<ChatHistory *> GetChatHistory(const std::string &user_id, std::vector<chat::Chat *> chat_list);
    std::map<std::string, chat::Chat *> GetLatelyChat(std::vector<chat::ChatHistory *> chat_history);
    std::vector<Chat *> GetOneUserChat(const std::string &dest_id, std::vector<chat::ChatHistory *> chat_history);
    int GetServer(const std::string &user_id);
    int SendToServer(const std::string &source_user_id, const std::string &dest_user_id, 
                         const std::string &content,int &server_fd);
    void TellConnect(const std::string &user_id, int &server_fd);
    void TellCloseConnect(const std::string &user_id, int &server_fd);
    void RecvMessage(std::mutex &mtx, std::map<std::string, std::vector<ChatHistory *>> &user_chatlist, int &server_fd, std::vector<peguser::PegUser *> peguser_list);
    std::vector<chat::ChatHistory *> UpdateChatHistory(const std::string &user_id, std::vector<chat::ChatHistory *> chat_list, chat::Chat *chat);

}

#endif