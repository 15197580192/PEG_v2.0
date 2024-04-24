/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       collection.h
 * @brief      the Collection class
 * @descripition
 * 成员函数：
 *  std::vector<Collection *> GetLovePostList(const std::string &user_id,
 *                                            std::vector<Collection *> collection_list)
 *  根据id获得他收藏的帖子列表
 *  std::string IfCollectionPost(const std::string &post_id,const std::string &user_id,
 *                               std::vector<Collection *> collection_list)
 *  根据postid和userid获取该帖子是否为该人收藏过
 *  std::string GetLovePostNum(const std::string &user_id,std::vector<Collection *> collection_list)
 *  根据id获得他收藏的帖子数量
 *  Collection * GetCollectionLog(const std::string &user_id,const std::string &post_id,
 *                                std::vector<Collection *> collection_list)
 *  根据id获得某条收藏记录
 *  std::vector<Collection *> CollectionDelete(const std::string &user_id,const std::string &post_id,               
 *                                             std::vector<Collection *> collection_list)
 *  取消收藏，删除对应记录
 *  成员变量：
 *   std::string post_id_ 关注的账号
 *   std::string fans_id_ 粉丝账号
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef COLLECTION_H_
#define COLLECTION_H_

#include <iostream>
#include <vector>
#include "tool.h"

namespace collection{
class Collection{
    public:
    Collection();
    inline void set_post_id_(const std::string &post_id);
    inline void set_fans_id_(const std::string &fans_id);
    inline std::string get_post_id_();
    inline std::string get_fans_id_();
    void NewCollection(const std::string &post_id,const std::string &user_id);
    private:
    std::string post_id_;
    std::string fans_id_;
};
    inline void Collection::set_post_id_(const std::string &post_id){
        this->post_id_=post_id;
    }
    inline void Collection::set_fans_id_(const std::string &fans_id){
        this->fans_id_=fans_id;
    }
    inline std::string Collection::get_post_id_(){
        return this->post_id_;
    }
    inline std::string Collection::get_fans_id_(){
        return this->fans_id_;
    }
    std::vector<Collection *> GetLovePostList(const std::string &user_id,std::vector<Collection *> collection_list);
    std::string IfCollectionPost(const std::string &post_id,const std::string &user_id,
                                 std::vector<Collection *> collection_list);
    std::string GetLovePostNum(const std::string &user_id,std::vector<Collection *> collection_list);
    Collection * GetCollectionLog(const std::string &user_id,const std::string &post_id,
                                  std::vector<Collection *> collection_list);
    std::vector<Collection *> CollectionDelete(const std::string &user_id,const std::string &post_id, 
                                               std::vector<Collection *> collection_list);
}
#endif