#include "collection.h"

collection::Collection::Collection(){
    this->post_id_="0";
    this->fans_id_="0";
}
/*****************************************************************
 * 函数名称：  void collection::Collection::NewCollection(const std::string &post_id, const std::string &user_id)
 * 功能描述： 设置新的帖子类属性
 * 参数说明： 字符串类型的文章id和用户id
 * 返回值：   无返回值
 ******************************************************************/
void collection::Collection::NewCollection(const std::string &post_id, const std::string &user_id)
{
    this->post_id_ = post_id;
    this->fans_id_ = user_id;
}

/*****************************************************************
 * 函数名称：  std::vector<collection::Collection *> collection::GetLovePostList(const std::string &user_id, std::vector<collection::Collection *> collection_list)
 * 功能描述： 根据id获得他的收藏列表
 * 参数说明： 字符串类型的用户id和vector类型的帖子
 * 返回值：   无返回值
 ******************************************************************/
std::vector<collection::Collection *> collection::GetLovePostList(
    const std::string &user_id, 
    std::vector<collection::Collection *> collection_list)
{
    std::vector<collection::Collection *> love_list;
    for (auto i = collection_list.begin(); i != collection_list.end(); i++)
    {
        if ((*i)->get_fans_id_() == user_id)
            love_list.push_back(*i);
    }
    return love_list;
}

/*****************************************************************
 * 函数名称： std::string collection::IfCollectionPost(const std::string &post_id, const std::string &user_id, std::vector<collection::Collection *> collection_list)
 * 功能描述： 根据postid和userid获取该帖子是否为该人收藏过
 * 参数说明： 字符串类型的发送者id,用户id,收藏列表
 * 返回值：   是否被收藏过
 ******************************************************************/
std::string collection::IfCollectionPost(const std::string &post_id, const std::string &user_id,               
                                         std::vector<collection::Collection *> collection_list)
{
    std::string flag = "false";
    for (auto i = collection_list.begin(); i != collection_list.end(); i++)
    {
        if ((*i)->get_post_id_() == post_id && (*i)->get_fans_id_() == user_id)
        {
            flag = "true";
            break;
        }
    }
    return flag;
}
/*****************************************************************
 * 函数名称： std::string collection::GetLovePostNum(const std::string &user_id, std::vector<collection::Collection *> collection_list)
 * 功能描述： 根据id获得他收藏的帖子数量
 * 参数说明： 字符串类型的用户id，帖子列表
 * 返回值：   字符串类型的帖子数量
 ******************************************************************/
std::string collection::GetLovePostNum(const std::string &user_id, 
                                       std::vector<collection::Collection *> collection_list)
{
    int num = 0;
    for (auto i = collection_list.begin(); i != collection_list.end(); i++)
    {
        if ((*i)->get_fans_id_() == user_id)
            num++;
    }
    return tool::IntToString(num);
}
/*****************************************************************
 * 函数名称： collection::Collection * collection::GetCollectionLog(
 *              const std::string &user_id, 
 *              const std::string &post_id,
 *              std::vector<collection::Collection *> collection_list)
 * 功能描述： 根据user_id和post_id获得收藏列表中对应记录
 * 参数说明： 字符串类型的用户id，帖子id，收藏列表
 * 返回值：   对应收藏记录
 ******************************************************************/
collection::Collection * collection::GetCollectionLog(const std::string &user_id, const std::string &post_id, 
                                                      std::vector<collection::Collection *> collection_list)
{
    for (auto i = collection_list.begin(); i != collection_list.end(); i++)
    {
        if ((*i)->get_fans_id_() == user_id && (*i)->get_post_id_() == post_id)
            return *i;
    }
}
/*****************************************************************
 * 函数名称： std::vector<collection::Collection *> collection::CollectionDelete(
 *           const std::string &user_id, 
 *           const std::string &post_id, 
 *           std::vector<collection::Collection *> collection_list)
 * 功能描述： 删除收藏列表中某条记录
 * 参数说明： 字符串类型的用户id，帖子id，收藏列表
 * 返回值：   vector类型的收藏列表
 ******************************************************************/
std::vector<collection::Collection *> collection::CollectionDelete(
    const std::string &user_id, const std::string &post_id, 
    std::vector<collection::Collection *> collection_list)
{
    for (auto i = collection_list.begin(); i != collection_list.end(); i++)
    {
        if ((*i)->get_fans_id_() == user_id && (*i)->get_post_id_() == post_id)
        {
            collection_list.erase(i);
            break;
        }
    }
    return collection_list;
}