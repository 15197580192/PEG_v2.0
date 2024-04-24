/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       notice.h
 * @brief      the Notice class
 * @descripition
 *
 *  名字空间内的成员函数：
 *  void NewNotice(const std::string &creater_id, const std::string &content, const std::string &notice_topic);
 *    赋值公告项
 *
 *  成员变量：
 *  std::string creater_id_  创建者id
    std::string create_time_ 创建时间
    std::string content_     内容
    std::string notice_topic_ 公告标题
    int notice_id_;           公告id
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef NOTICE_H_
#define NOTICE_H_
#include <iostream>
#include "tool.h"

class Notice
{
public:
    Notice();
    inline void set_creater_id_(const std::string &createrid)
    {
        this->creater_id_ = createrid;
    }
    inline void set_create_time_(const std::string &createtime)
    {
        this->create_time_ = createtime;
    }
    inline void set_content_(const std::string &content)
    {
        this->content_ = content;
    }
    inline void set_notice_topic_(const std::string &noticetopic)
    {
        this->notice_topic_ = noticetopic;
    }
    inline void set_notice_id_(const std::string &noticeid)
    {
        this->notice_id_ = tool::StringToInt(noticeid);
    }

    inline std::string get_creater_id_()
    {
        return this->creater_id_;
    }

    inline std::string get_create_time_()
    {
        return this->create_time_;
    }

    inline std::string get_content_()
    {
        return this->content_;
    }

    inline std::string get_notice_topic_()
    {
        return this->notice_topic_;
    }
    inline int get_notice_id_()
    {
        return this->notice_id_;
    }
    void NewNotice(const std::string &creater_id, const std::string &content, const std::string &notice_topic);

private:
    std::string creater_id_;
    std::string create_time_;
    std::string content_;
    std::string notice_topic_;
    int notice_id_;
};
#endif
