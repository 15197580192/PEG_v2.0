
/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       post.h
 * @brief      the Post class
 * @descripition
 * 成员函数：
 *    void NewPost(const std::string &user_id,const std::string &user_name,const std::string &post_title,const std::string &post_content,std::vector<Post *> post_list);
 *  创建新的帖子

 * 非成员函数：
    std::vector<Post *> GetUserPost(const std::string &user_id,std::vector<Post *> post_list);
   根据用户id获得帖子内容
    std::string NewPostId(std::vector<Post *> post_list);
    随机生成postid
    std::vector<std::string> GetUserPostId(const std::string &user_id,std::vector<Post *> post_list);
    根据用户id获得帖子id
    Post * GetPost(const std::string &post_id,std::vector<Post *> post_list);
    根据帖子id获取帖子
    std::string GetPostTitle(const std::string &post_id,std::vector<Post *> post_list);
    根据帖子id获取帖子标题
    std::string GetPostAuthorId(const std::string &post_id,std::vector<Post *> post_list);
    根据帖子id获得作者id
    std::vector<Post *> GetFavoritesPost(std::vector<collection::Collection *> collection_list,
                                         std::vector<Post *>post_list);
    根据收藏帖子列表获取所有帖子数据
    std::vector<Post *> GetLatelyUserPost(std::vector<std::string> userid_list,std::vector<Post *>post_list);
    根据作者id获取近三天帖子
    std::vector<Post *> ChangeSupport(const std::string &post_id,const std::string &flag,
                                      std::vector<Post *> post_list);
    将该帖子的点赞数加一/减一
    std::vector<Post *> ChangeCollection(const std::string &post_id,const std::string &flag,
                                         std::vector<Post *> post_list);
    将该帖子收藏数加1/减一
    std::vector<Post *> AddComments(const std::string &post_id,const std::string &flag,
                                    std::vector<Post *> post_list);
    将贴子评论数加1/减一
 * 成员变量：
*   std::string post_id_;   帖子id
*   std::string poster_id_;   发帖人id
*   std::string poster_name_;   发帖人name
*   std::string post_title_;   帖子标题
*    std::string post_content_;   帖子内容
*    std::string support_num_;   点赞数
*    std::string comments_num_;   评论数
*    std::string collection_num_;   收藏数
*    std::string post_time_;    发帖时间
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/

#ifndef POST_H_
#define POST_H_

#include <iostream>
#include <ctime>
#include "collection.h"

namespace post
{
    class Post
    {
    public:
        Post();
        inline void set_post_id_(const std::string &post_id);
        inline void set_poster_id_(const std::string &poster_id);
        inline void set_poster_name_(const std::string &poster_name);
        inline void set_post_title_(const std::string &post_title);
        inline void set_post_content_(const std::string &post_content);
        inline void set_support_num_(const std::string &support_num);
        inline void set_comments_num_(const std::string &comments_num);
        inline void set_collection_num_(const std::string &collection_num);
        inline void set_post_time_(const std::string &post_time);
        inline std::string get_post_id_();
        inline std::string get_poster_id_();
        inline std::string get_poster_name_();
        inline std::string get_post_title_();
        inline std::string get_post_content_();
        inline std::string get_support_num_();
        inline std::string get_comments_num_();
        inline std::string get_collection_num_();
        inline std::string get_post_time_();
        void NewPost(const std::string &user_id, const std::string &user_name, const std::string &post_title,
                     const std::string &post_content, std::vector<Post *> post_list);

    private:
        std::string post_id_;
        std::string poster_id_;
        std::string poster_name_;
        std::string post_title_;
        std::string post_content_;
        std::string support_num_;
        std::string comments_num_;
        std::string collection_num_;
        std::string post_time_;
    };
    inline void Post::set_post_id_(const std::string &post_id)
    {
        this->post_id_ = post_id;
    }
    inline void Post::set_poster_id_(const std::string &poster_id)
    {
        this->poster_id_ = poster_id;
    }
    inline void Post::set_poster_name_(const std::string &poster_name)
    {
        this->poster_name_ = poster_name;
    }
    inline void Post::set_post_title_(const std::string &post_title)
    {
        this->post_title_ = post_title;
    }
    inline void Post::set_post_content_(const std::string &post_content)
    {
        this->post_content_ = post_content;
    }
    inline void Post::set_support_num_(const std::string &support_num)
    {
        this->support_num_ = support_num;
    }
    inline void Post::set_comments_num_(const std::string &comments_num)
    {
        this->comments_num_ = comments_num;
    }
    inline void Post::set_collection_num_(const std::string &collection_num)
    {
        this->collection_num_ = collection_num;
    }
    inline void Post::set_post_time_(const std::string &post_time)
    {
        this->post_time_ = post_time;
    }
    inline std::string Post::get_post_id_()
    {
        return this->post_id_;
    }
    inline std::string Post::get_poster_id_()
    {
        return this->poster_id_;
    }
    inline std::string Post::get_poster_name_()
    {
        return this->poster_name_;
    }
    inline std::string Post::get_post_title_()
    {
        return this->post_title_;
    }
    inline std::string Post::get_post_content_()
    {
        return this->post_content_;
    }
    inline std::string Post::get_support_num_()
    {
        return this->support_num_;
    }
    inline std::string Post::get_comments_num_()
    {
        return this->comments_num_;
    }
    inline std::string Post::get_collection_num_()
    {
        return this->collection_num_;
    }
    inline std::string Post::get_post_time_()
    {
        return this->post_time_;
    }

    // 根据用户id获得帖子内容
    std::vector<Post *> GetUserPost(const std::string &user_id, std::vector<Post *> post_list);

    // 随机生成postid
    std::string NewPostId(std::vector<Post *> post_list);

    // 根据用户id获得帖子id
    std::vector<std::string> GetUserPostId(const std::string &user_id, std::vector<Post *> post_list);

    // 根据帖子id获取帖子
    Post *GetPost(const std::string &post_id, std::vector<Post *> post_list);

    // 根据帖子id获取帖子标题
    std::string GetPostTitle(const std::string &post_id, std::vector<Post *> post_list);

    // 根据帖子id获得作者id
    std::string GetPostAuthorId(const std::string &post_id, std::vector<Post *> post_list);

    // 根据收藏帖子列表获取所有帖子数据
    std::vector<Post *> GetFavoritesPost(std::vector<collection::Collection *> collection_list, 
                                         std::vector<Post *> post_list);

    // 根据作者id获取近三天帖子
    std::vector<Post *> GetLatelyUserPost(std::vector<std::string> userid_list, std::vector<Post *> post_list);

    // 将该帖子的点赞数加一/减一
    std::vector<Post *> ChangeSupport(const std::string &post_id, const std::string &flag, 
                                      std::vector<Post *> post_list);

    // 将该帖子收藏数加1/减一
    std::vector<Post *> ChangeCollection(const std::string &post_id, const std::string &flag, 
                                         std::vector<Post *> post_list);

    // 将贴子评论数加1/减一
    std::vector<Post *> AddComments(const std::string &post_id, const std::string &flag, 
                                    std::vector<Post *> post_list);

    std::vector<Post *> GetFuzzyFindPost(const std::string &keyword,
                                         std::vector<Post *> post_list);
}

#endif