/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       comment.h
 * @brief      the Comment class
 * @descripition
 * 成员函数：
 *  std::vector<Comment *> GetPostComments(const std::string &post_id, std::vector<Comment *> comments_list)
 *  获得该帖子的评论列表
 *  std::vector<Comment *> GetUnreadPostCommentsList(const std::vector<std::string> postid_list, 
 *                                                   std::vector<Comment *> comments_list)
 *  获取该人未读的帖子评论列表
 *  std::vector<Comment *> GetUnreadQuestionCommentsList(const std::vector<std::string> questionid_list, 
 *                                                       std::vector<Comment *> comments_list)
 *  获取该人未读的问答评论列表
 *  std::vector<Comment *> SetUnreadPostCommentsList(const std::vector<std::string> postid_list, 
 *                                                   std::vector<Comment *> comment_list)
 *  将未读帖子评论设置为已读
 *  std::vector<Comment *> SetUnreadQuestionCommentsList(const std::vector<std::string> questionid_list,  
 *                                                       std::vector<Comment *> comment_list)
 *  将未读问答评论设置为已读
 *  Comment * GetCommentAccordToIdTime(const std::string &question_id, const std::string &user_id, 
 *                                     const std::string &time, std::vector<Comment *> comment_list)
 *  根据问题id、用户id和时间找到该条评论
 *  std::vector<Comment *> UpdateBestAnswer(Comment *comment, std::vector<Comment *> comment_list)
 *  设置最佳回答
 * 成员变量：
 *  std::string post_id_           帖子id
 *  std::string comment_content_   评论内容
 *  std::string commenter_id_      评论人id
 *  std::string commenter_name_    评论人名字
 *  std::string comment_time_      评论时间
 *  std::string read_flag_         是否已读
 *  std::string best_answer_       最优答案
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef COMMENT_H_
#define COMMENT_H_

#include <iostream>
#include "tool.h"

namespace comment{
class Comment{
    public:
    Comment();
    inline void set_post_id_(const std::string &post_id);
    inline void set_comment_content_(const std::string &comment_content);
    inline void set_commenter_id_(const std::string &commenter_id);
    inline void set_commenter_name_(const std::string &commenter_name);
    inline void set_comment_time_(const std::string &comment_time);
    inline void set_read_flag_(const std::string &flag);
    inline void set_best_answer_(const std::string &flag);
    inline std::string get_post_id_();
    inline std::string get_comment_content_();
    inline std::string get_commenter_id_();
    inline std::string get_commenter_name_();
    inline std::string get_comment_time_();
    inline std::string get_read_flag_();
    inline std::string get_best_answer_();
    void NewComment(const std::string &post_id,const std::string &content,const std::string &commenter_id,
                    const std::string &commenter_name);
    private:
    std::string post_id_;
    std::string comment_content_;
    std::string commenter_id_;
    std::string commenter_name_;
    std::string comment_time_;
    std::string read_flag_;
    std::string best_answer_;
};

    inline void Comment::set_post_id_(const std::string &post_id){
        this->post_id_=post_id;
    }
    inline void Comment::set_comment_content_(const std::string &comment_content){
        this->comment_content_=comment_content;
    }
    inline void Comment::set_commenter_id_(const std::string &commenter_id){
        this->commenter_id_=commenter_id;
    }
    inline void Comment::set_commenter_name_(const std::string &commenter_name){
        this->commenter_name_=commenter_name;
    }
    inline void Comment::set_comment_time_(const std::string &comment_time){
        this->comment_time_=comment_time;
    }
    inline void Comment::set_read_flag_(const std::string &flag){
        this->read_flag_=flag;
    }
    inline void Comment::set_best_answer_(const std::string &flag){
        this->best_answer_=flag;
    }
    inline std::string Comment::get_post_id_(){
        return this->post_id_;
    }
    inline std::string Comment::get_comment_content_(){
        return this->comment_content_;
    }
    inline std::string Comment::get_commenter_id_(){
        return this->commenter_id_;
    }
    inline std::string Comment::get_commenter_name_(){
        return this->commenter_name_;
    }
    inline std::string Comment::get_comment_time_(){
        return this->comment_time_;
    }
    inline std::string Comment::get_read_flag_(){
        return this->read_flag_;
    }
    inline std::string Comment::get_best_answer_(){
        return this->best_answer_;
    }
    std::vector<Comment *> GetPostComments(const std::string &post_id, std::vector<Comment *> comments_list);
    std::vector<Comment *> GetUnreadPostCommentsList(const std::vector<std::string> postid_list, 
                                                     std::vector<Comment *> comments_list);
    std::vector<Comment *> GetUnreadQuestionCommentsList(const std::vector<std::string> questionid_list,  
                                                         std::vector<Comment *> comments_list);
    std::vector<Comment *> SetUnreadPostCommentsList(const std::vector<std::string> postid_list, 
                                                     std::vector<Comment *> comment_list);
    std::vector<Comment *> SetUnreadQuestionCommentsList(const std::vector<std::string> questionid_list, 
                                                         std::vector<Comment *> comment_list);
    Comment * GetCommentAccordToIdTime(const std::string &question_id, const std::string &user_id, 
                                       const std::string &time, std::vector<Comment *> comment_list);
    std::vector<Comment *> UpdateBestAnswer(Comment *comment, std::vector<Comment *> comment_list);
}
#endif