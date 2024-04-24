#include "comment.h"

comment::Comment::Comment(){
    this->post_id_="0";
    this->comment_content_="0";
    this->commenter_id_="0";
    this->commenter_name_="0";
    this->comment_time_="0";
    this->read_flag_="0";
    this->best_answer_="0";
}
/*****************************************************************
 * 函数名称： void comment::Comment::NewComment(const std::string &post_id, const std::string &content, 
 *                                             const std::string &commenter_id, const std::string &commenter_name)
 * 功能描述： 新建评论
 * 参数说明： 字符串类型的用户id，帖子id
 * 返回值：   无返回值
 ******************************************************************/
void comment::Comment::NewComment(const std::string &post_id, const std::string &content, 
                                  const std::string &commenter_id, const std::string &commenter_name)
{
    this->post_id_ = post_id;
    this->comment_content_ = content;
    this->commenter_id_ = commenter_id;
    this->commenter_name_ = commenter_name;
    this->comment_time_ = tool::GetTime();
    this->read_flag_ = "0";
    this->best_answer_ = "0";
}
/*****************************************************************
 * 函数名称： std::vector<comment::Comment *> comment::GetPostComments(const std::string &post_id, 
 *                                                                    std::vector<comment::Comment *> comments_list)
 * 功能描述： 得到某个帖子下面的全部评论
 * 参数说明： 字符串类型的帖子id，vector类型的评论列表
 * 返回值：   vector类型的评论列表
 ******************************************************************/
std::vector<comment::Comment *> comment::GetPostComments(const std::string &post_id, 
                                                         std::vector<comment::Comment *> comments_list)
{
    std::vector<comment::Comment *> post_comments;
    for (auto i = comments_list.begin(); i != comments_list.end(); i++)
    {
        if ((*i)->get_post_id_() == post_id)
            post_comments.push_back(*i);
    }
    return post_comments;
}
/*****************************************************************
 * std::vector<comment::Comment *> comment::GetUnreadPostCommentsList(const std::vector<std::string> postid_list, 
 *                                                                    std::vector<comment::Comment *> comments_list)
 * 功能描述： 得到帖子下面的全部未读评论
 * 参数说明： vector类型的帖子id列表，vector类型的评论列表
 * 返回值：   vector类型的评论列表
 ******************************************************************/
std::vector<comment::Comment *> comment::GetUnreadPostCommentsList(const std::vector<std::string> postid_list, 
                                                                   std::vector<comment::Comment *> comments_list)
{
    std::vector<comment::Comment *> unread_comment_list;
    for (int i = 0; i < postid_list.size(); i++)
    {
        for (int j = 0; j < comments_list.size(); j++)
        {
            if (comments_list[j]->get_post_id_() == postid_list[i] && comments_list[j]->get_read_flag_() == "0")
                unread_comment_list.push_back(comments_list[j]);
        }
    }
    return unread_comment_list;
}
/*****************************************************************
 * 函数名称： std::vector<comment::Comment *> comment::GetUnreadQuestionCommentsList(
 *           const std::vector<std::string> questionid_list, 
 *           std::vector<comment::Comment *> comments_list)
 * 功能描述： 获取该人未读的问答评论列表
 * 参数说明： vector类型的问题id列表，评论列表
 * 返回值：   vector类型的评论列表
 ******************************************************************/
std::vector<comment::Comment *> comment::GetUnreadQuestionCommentsList(
    const std::vector<std::string> questionid_list, 
    std::vector<comment::Comment *> comments_list)
{
    std::vector<comment::Comment *> unread_comment_list;
    for (int i = 0; i < questionid_list.size(); i++)
    {
        for (int j = 0; j < comments_list.size(); j++)
        {
            if (comments_list[j]->get_post_id_() == questionid_list[i] && comments_list[j]->get_read_flag_() == "0")
                unread_comment_list.push_back(comments_list[j]);
        }
    }
    return unread_comment_list;
}
/*****************************************************************
 * 函数名称： std::vector<comment::Comment *> comment::SetUnreadPostCommentsList(
 *           const std::vector<std::string> postid_list, 
 *           std::vector<comment::Comment *> comment_list)
 * 功能描述： 将对应帖子下面所有未读评论设置为已读
 * 参数说明： vector类型的帖子id列表，评论列表
 * 返回值：   vector类型的评论列表
 ******************************************************************/
std::vector<comment::Comment *> comment::SetUnreadPostCommentsList(
    const std::vector<std::string> postid_list, 
    std::vector<comment::Comment *> comment_list)
{
    for (int i = 0; i < postid_list.size(); i++)
    {
        for (int j = 0; j < comment_list.size(); j++)
        {
            if (comment_list[j]->get_post_id_() == postid_list[i] && comment_list[j]->get_read_flag_() == "0")
                comment_list[j]->set_read_flag_("1");
        }
    }
    return comment_list;
}
/*****************************************************************
 * 函数名称： std::vector<comment::Comment *> comment::SetUnreadQuestionCommentsList(
 *           const std::vector<std::string> questionid_list,
 *           std::vector<comment::Comment *> comment_list)
 * 功能描述： 将将对应问答下面所有未读评论设置为已读
 * 参数说明： vector类型的问题id列表，评论列表
 * 返回值：   vector类型的评论列表
 ******************************************************************/
std::vector<comment::Comment *> comment::SetUnreadQuestionCommentsList(
    const std::vector<std::string> questionid_list, 
    std::vector<comment::Comment *> comment_list)
{
    for (int i = 0; i < questionid_list.size(); i++)
    {
        for (int j = 0; j < comment_list.size(); j++)
        {
            if (comment_list[j]->get_post_id_() == questionid_list[i] && comment_list[j]->get_read_flag_() == "0")
                comment_list[j]->set_read_flag_("1");
        }
    }
    return comment_list;
}
/*****************************************************************
 * 函数名称： comment::Comment * comment::GetCommentAccordToIdTime(const std::string &question_id, 
 *                                                                const std::string &user_id, 
 *                                                                const std::string &time,  
 *                                                                std::vector<comment::Comment *> comment_list)
 * 功能描述： 根据问题id、用户id和时间找到该条评论
 * 参数说明： 字符串类型的问题id,用户id,vector类型的评论列表
 * 返回值：   comment类型的评论
 ******************************************************************/
comment::Comment * comment::GetCommentAccordToIdTime(const std::string &question_id, const std::string &user_id,  
                                                     const std::string &time, 
                                                     std::vector<comment::Comment *> comment_list)
{
    for (auto i = comment_list.begin(); i != comment_list.end(); i++)
    {
        if ((*i)->get_post_id_() == question_id && (*i)->get_commenter_id_() == user_id && (*i)->get_comment_time_() == time)
            return *i;
    }
}
/*****************************************************************
 * 函数名称： std::vector<comment::Comment *> comment::UpdateBestAnswer(comment::Comment *comment, 
 *                                                                     std::vector<comment::Comment *> comment_list)
 * 功能描述： 设置最佳回答，返回列表
 * 参数说明： 评论类项，vector类型的评论列表
 * 返回值：   vector类型的评论列表
 ******************************************************************/
std::vector<comment::Comment *> comment::UpdateBestAnswer(comment::Comment *comment, 
                                                          std::vector<comment::Comment *> comment_list)
{
    for (auto i = comment_list.begin(); i != comment_list.end(); i++)
    {
        if ((*i)->get_post_id_() == comment->get_post_id_() && (*i)->get_commenter_id_() == comment->get_commenter_id_() && (*i)->get_comment_time_() == comment->get_comment_time_())
            (*i)->set_best_answer_("1");
    }
    return comment_list;
}