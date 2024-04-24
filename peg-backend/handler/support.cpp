#include "support.h"

support::Support::Support()
{
    this->post_id_ = "0";
    this->supporter_id_ = "0";
    this->support_time_ = "0";
    this->read_flag_ = "0";
}
/*****************************************************************
 * 函数名称： void support::Support::NewSupport(const std::string &post_id, const std::string &user_id)
 * 功能描述： 赋予点赞类数据
 * 参数说明： 字符串类型的文章id,用户id
 * 返回值：   无返回值
 ******************************************************************/
void support::Support::NewSupport(const std::string &post_id, const std::string &user_id)
{
    this->post_id_ = post_id;
    this->supporter_id_ = user_id;
    time_t now_time = time(NULL);
    tm *ltm = localtime(&now_time);
    std::string support_time = std::to_string(ltm->tm_year + 1900) + "-" + std::to_string(ltm->tm_mon + 1) + "-";
    support_time += std::to_string(ltm->tm_mday) + "-" + std::to_string(ltm->tm_hour) + "-";
    support_time += std::to_string(ltm->tm_min) + "-" + std::to_string(ltm->tm_sec);
    this->support_time_ = support_time;
    this->read_flag_ = "0";
}

/*****************************************************************
 * 函数名称： std::string support::IfSupportPost(const std::string &post_id,const std::string &user_id,std::vector<support::Support *> support_list)
 * 功能描述： 根据postid和userid获取该帖子是否为该人点赞过
 * 参数说明： 字符串类型的文章id,用户id，点赞列表
 * 返回值：   返回标志位
 ******************************************************************/
std::string support::IfSupportPost(const std::string &post_id, const std::string &user_id,
                                   std::vector<support::Support *> support_list)
{
    std::string flag = "false";
    for (auto i = support_list.begin(); i != support_list.end(); i++)
    {
        if ((*i)->get_post_id_() == post_id && (*i)->get_supporter_id_() == user_id)
        {
            flag = "true";
            break;
        }
    }
    return flag;
}

/*****************************************************************
 * 函数名称： std::vector<support::Support *> support::GetUnreadPostSupportList(const std::vector<std::string> postid_list,std::vector<support::Support *> support_list)
 * 功能描述： 获取该人未读的帖子点赞数目
 * 参数说明： vector类型的文章列表，点赞列表
 * 返回值：   未读的文章列表
 ******************************************************************/
std::vector<support::Support *> support::GetUnreadPostSupportList(const std::vector<std::string> postid_list,
                                                                  std::vector<support::Support *> support_list)
{
    std::vector<support::Support *> unread_support_list;
    for (int i = 0; i < postid_list.size(); i++)
    {
        for (int j = 0; j < support_list.size(); j++)
        {
            if (support_list[j]->get_post_id_() == postid_list[i] && support_list[j]->get_read_flag_() == "0")
                unread_support_list.push_back(support_list[j]);
        }
    }
    return unread_support_list;
}
/*****************************************************************
 * 函数名称： std::vector<support::Support *> support::GetUnreadPostSupportList(const std::vector<std::string> postid_list,std::vector<support::Support *> support_list)
 * 功能描述： 获取该人未读的问答点赞列表
 * 参数说明： vector类型的提问列表，点赞列表
 * 返回值：   未读的提问点赞列表
 ******************************************************************/
std::vector<support::Support *> support::GetUnreadQuestionSupportList(
    const std::vector<std::string> questionid_list,
    std::vector<support::Support *> support_list)
{
    std::vector<support::Support *> unread_support_list;
    for (int i = 0; i < questionid_list.size(); i++)
    {
        for (int j = 0; j < support_list.size(); j++)
        {
            if (support_list[j]->get_post_id_() == questionid_list[i] && support_list[j]->get_read_flag_() == "0")
                unread_support_list.push_back(support_list[j]);
        }
    }
    return unread_support_list;
}
/*****************************************************************
 * 函数名称： std::vector<support::Support *> support::GetUnreadPostSupportList(const std::vector<std::string> postid_list,std::vector<support::Support *> support_list)
 * 功能描述： 将未读文章点赞设置为已读
 * 参数说明： vector类型的文章列表，点赞列表
 * 返回值：   标志位改变后的点赞列表
 ******************************************************************/
std::vector<support::Support *> support::SetUnreadPostSupportList(const std::vector<std::string> postid_list,
                                                                  std::vector<support::Support *> support_list)
{
    for (int i = 0; i < postid_list.size(); i++)
    {
        for (int j = 0; j < support_list.size(); j++)
        {
            if (support_list[j]->get_post_id_() == postid_list[i] && support_list[j]->get_read_flag_() == "0")
                support_list[j]->set_read_flag_("1");
        }
    }
    return support_list;
}
/*****************************************************************
 * 函数名称： std::vector<support::Support *> support::SetUnreadQuestionSupportList(const std::vector<std::string> questionid_list,std::vector<support::Support *> support_list)
 * 功能描述： 将未读问题点赞设置为已读
 * 参数说明： vector类型的文章列表，点赞列表
 * 返回值：   标志位改变后的点赞列表
 ******************************************************************/
std::vector<support::Support *> support::SetUnreadQuestionSupportList(
    const std::vector<std::string> questionid_list,
    std::vector<support::Support *> support_list)
{
    for (int i = 0; i < questionid_list.size(); i++)
    {
        for (int j = 0; j < support_list.size(); j++)
        {
            if (support_list[j]->get_post_id_() == questionid_list[i] && support_list[j]->get_read_flag_() == "0")
                support_list[j]->set_read_flag_("1");
        }
    }
    return support_list;
}
/*****************************************************************
 * 函数名称： support::Support * support::GetSupportLog(const std::string &user_id,const std::string &post_id,std::vector<support::Support *> support_list)
 * 功能描述： 得到点赞项
 * 参数说明： 字符串类型的用户id,文章id,vector类型的点赞列表
 * 返回值：   点赞项
 ******************************************************************/
support::Support *support::GetSupportLog(const std::string &user_id, const std::string &post_id,
                                         std::vector<support::Support *> support_list)
{
    for (auto i = support_list.begin(); i != support_list.end(); i++)
    {
        if ((*i)->get_supporter_id_() == user_id && (*i)->get_post_id_() == post_id)
            return *i;
    }
}
/*****************************************************************
 * 函数名称： std::vector<support::Support *> support::SupportDelete(const std::string &user_id,const std::string &post_id,std::vector<support::Support *> support_list)
 * 功能描述： 删除点赞项
 * 参数说明： 字符串类型的用户id,文章id,vector类型的点赞列表
 * 返回值：   删除后的点赞列表
 ******************************************************************/
std::vector<support::Support *> support::SupportDelete(const std::string &user_id, const std::string &post_id,
                                                       std::vector<support::Support *> support_list)
{
    for (auto i = support_list.begin(); i != support_list.end(); i++)
    {
        if ((*i)->get_supporter_id_() == user_id && (*i)->get_post_id_() == post_id)
        {
            support_list.erase(i);
            break;
        }
    }
    return support_list;
}