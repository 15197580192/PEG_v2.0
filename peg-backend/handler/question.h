/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       question.h
 * @brief      the Question class
 * @descripition
 * 成员函数：
 *     void NewQuestion(const std::string &title,const std::string &content,const std::string &user_id,
                     const std::string &user_name,std::vector<Question *> question_list);
 *  创建新的问题

 * 非成员函数：
     std::string NewQuestionId(std::vector<Question *> question_list);
     随机生成questionid(question为5位id)

    std::vector<Question *> GetUserQuestion(const std::string &user_id,std::vector<Question *> question_list);
   获得个人发布的问答
    Question * GetNameQuestion(const std::string &question_id,std::vector<Question *> question_list);
    根据问答id获得某个问答的具体内容

   std::string GetQuestionTitle(const std::string &question_id,std::vector<Question *> question_list);
   根据问答id获得某个问答的标题

  std::vector<std::string> GetUserQuestionId(const std::string &user_id,std::vector<Question *> question_list);
  根据用户id获得问答id

   std::vector<Question *> AddSupport(const std::string &question_id,std::vector<Question *> question_list);
   将问答点赞数加一

std::vector<Question *> AddComments(const std::string &question_id,std::vector<Question *> question_list);
将问答评论数加1

 * 成员变量：
*    std::string question_id_;   问题id
*    std::string question_title_;   问题标题
*    std::string question_content_;   问题内容
*    std::string support_num_;    点赞数
*    std::string comments_num_;   评论数
*    std::string ques_time_;    问题提出的时间
*    std::string questioner_id_;   提问者的id
*    std::string questioner_name_;   提问者名字
*    std::string solved_;    是否被解决
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef QUESTION_H_
#define QUESTION_H_

#include <iostream>
#include "tool.h"
namespace question
{
    class Question
    {
    public:
        Question();
        inline void set_question_id_(const std::string &question_id);
        inline void set_question_title_(const std::string &question_title);
        inline void set_question_content_(const std::string &question_content);
        inline void set_support_num_(const std::string &support_num);
        inline void set_comments_num_(const std::string &comments_num);
        inline void set_ques_time_(const std::string &ques_time);
        inline void set_questioner_id_(const std::string &user_id);
        inline void set_questioner_name_(const std::string &user_name);
        inline void set_solved_(const std::string &flag);
        inline std::string get_question_id_();
        inline std::string get_question_title_();
        inline std::string get_question_content_();
        inline std::string get_support_num_();
        inline std::string get_comments_num_();
        inline std::string get_ques_time_();
        inline std::string get_questioner_id_();
        inline std::string get_questioner_name_();
        inline std::string get_solved_();
        void NewQuestion(const std::string &title, const std::string &content, const std::string &user_id,
                         const std::string &user_name, std::vector<Question *> question_list);

    private:
        std::string question_id_;
        std::string question_title_;
        std::string question_content_;
        std::string support_num_;
        std::string comments_num_;
        std::string ques_time_;
        std::string questioner_id_;
        std::string questioner_name_;
        std::string solved_;
    };

    inline void Question::set_question_id_(const std::string &question_id)
    {
        this->question_id_ = question_id;
    }
    inline void Question::set_question_title_(const std::string &question_title)
    {
        this->question_title_ = question_title;
    }
    inline void Question::set_question_content_(const std::string &question_content)
    {
        this->question_content_ = question_content;
    }
    inline void Question::set_support_num_(const std::string &support_num)
    {
        this->support_num_ = support_num;
    }
    inline void Question::set_comments_num_(const std::string &comments_num)
    {
        this->comments_num_ = comments_num;
    }
    inline void Question::set_ques_time_(const std::string &ques_time)
    {
        this->ques_time_ = ques_time;
    }
    inline void Question::set_questioner_id_(const std::string &user_id)
    {
        this->questioner_id_ = user_id;
    }
    inline void Question::set_questioner_name_(const std::string &user_name)
    {
        this->questioner_name_ = user_name;
    }
    inline void Question::set_solved_(const std::string &flag)
    {
        this->solved_ = flag;
    }
    inline std::string Question::get_question_id_()
    {
        return this->question_id_;
    }
    inline std::string Question::get_question_title_()
    {
        return this->question_title_;
    }
    inline std::string Question::get_question_content_()
    {
        return this->question_content_;
    }
    inline std::string Question::get_support_num_()
    {
        return this->support_num_;
    }
    inline std::string Question::get_comments_num_()
    {
        return this->comments_num_;
    }
    inline std::string Question::get_ques_time_()
    {
        return this->ques_time_;
    }
    inline std::string Question::get_questioner_id_()
    {
        return this->questioner_id_;
    }
    inline std::string Question::get_questioner_name_()
    {
        return this->questioner_name_;
    }
    inline std::string Question::get_solved_()
    {
        return this->solved_;
    }

    // 随机生成questionid(question为5位id)
    std::string NewQuestionId(std::vector<Question *> question_list);

    // 获得个人所发布的问答
    std::vector<Question *> GetUserQuestion(const std::string &user_id, std::vector<Question *> question_list);

    // 根据问答id获得某个问答的具体内容
    Question *GetNameQuestion(const std::string &question_id, std::vector<Question *> question_list);

    // 根据问答id获得某个问答的标题
    std::string GetQuestionTitle(const std::string &question_id, std::vector<Question *> question_list);

    // 根据用户id获得问答id
    std::vector<std::string> GetUserQuestionId(const std::string &user_id, std::vector<Question *> question_list);

    // 将问答点赞数加一
    std::vector<Question *> ChangeSupport(const std::string &question_id, const std::string &flag,std::vector<Question *> question_list);

    // 将问答评论数加1
    std::vector<Question *> AddComments(const std::string &question_id, std::vector<Question *> question_list);

    std::vector<question::Question *> UpdateSolved(const std::string &question_id,
                                                   std::vector<question::Question *> question_list);
}
#endif // QUESTION_H_