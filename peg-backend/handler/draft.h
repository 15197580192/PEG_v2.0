/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       draft.h
 * @brief      the Draft class
 * @descripition
 * 成员函数：
 *  void NewDraft(const std::string &type,const std::string &title,const std::string &content,
                  const std::string author_id);
 * 非成员函数：
 *  bool CheckDraft(const std::string &title,std::vector<Draft *> draft_list)
 *  根据主题判断该草稿是否重复
 *  std::vector<Draft *> UserDraft(const std::string &user_id,std::vector<Draft *> draft_list)
 *  根据用户id找到属于这个用户的所有草稿
 *  Draft * GetDraftAccordIdTtile(const std::string &type,const std::string &title,std::vector<Draft *> draft_list)
 *  根据title和用户id找到该草稿
 *  std::vector<Draft *> DraftDeleteCertain(Draft *draft,std::vector<Draft *> draft_list)
 *  删除对应记录
 * 成员变量：
 *  std::string type_       类型
    std::string title_      标题
    std::string content_    内容
    std::string author_id_  作者id
    std::string time_       时间
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef DRAFT_H_
#define DRAFT_H_

#include <iostream>
#include "tool.h"

namespace draft{
class Draft{
    public:
    Draft();
    inline void set_type_(const std::string &type);
    inline void set_title_(const std::string &title);
    inline void set_content_(const std::string &content);
    inline void set_author_id_(const std::string &author_id);
    inline void set_time_(const std::string &time);
    inline std::string get_type_();
    inline std::string get_title_();
    inline std::string get_content_();
    inline std::string get_author_id_();
    inline std::string get_time_();
    void NewDraft(const std::string &type,const std::string &title,const std::string &content,
                  const std::string author_id);
    private:
    std::string type_;
    std::string title_;
    std::string content_;
    std::string author_id_;
    std::string time_;
};
    inline void Draft::set_type_(const std::string &type){
        this->type_=type;
    }
    inline void Draft::set_title_(const std::string &title){
        this->title_=title;
    }
    inline void Draft::set_content_(const std::string &content){
        this->content_=content;
    }
    inline void Draft::set_author_id_(const std::string &author_id){
        this->author_id_=author_id;
    }
    inline void Draft::set_time_(const std::string &time){
        this->time_=time;
    }
    inline std::string Draft::get_type_(){
        return this->type_;
    }
    inline std::string Draft::get_title_(){
        return this->title_;
    }
    inline std::string Draft::get_content_(){
        return this->content_;
    }
    inline std::string Draft::get_author_id_(){
        return this->author_id_;
    }
    inline std::string Draft::get_time_(){
        return this->time_;
    }
    //根据主题判断该草稿是否重复
    bool CheckDraft(const std::string &title,std::vector<Draft *> draft_list);
    //根据用户id找到属于这个用户的所有草稿
    std::vector<Draft *> UserDraft(const std::string &user_id,std::vector<Draft *> draft_list);
     //根据title和用户id找到该草稿
    Draft * GetDraftAccordIdTtile(const std::string &type,const std::string &title,std::vector<Draft *> draft_list);
    //删除对应记录
    std::vector<Draft *> DraftDeleteCertain(Draft *draft,std::vector<Draft *> draft_list);
}
#endif//DRAFT_H_