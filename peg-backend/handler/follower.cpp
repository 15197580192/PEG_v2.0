#include "follower.h"

follower::Follower::Follower()
{
    this->user_id_ = "0";
    this->follower_id_ = "0";
    this->follow_time_ = "0";
}
/*****************************************************************
 * 函数名称： std::string follower::GetConcernNum(std::vector<follower::Follower *> follower_list, 
 *                                               const std::string &user_id)
 * 功能描述： 根据用户id获得关注者数量
 * 参数说明： vector类型的关注列表，字符串类型的用户id
 * 返回值：   返回字符串类型的数量
 ******************************************************************/
std::string follower::GetConcernNum(std::vector<follower::Follower *> follower_list, const std::string &user_id)
{
    int concern_num = 0;
    for (int i = 0; i < follower_list.size(); i++)
    {
        if (follower_list[i]->get_follower_id_() == user_id)
        {
            concern_num++;
        }
    }
    return tool::IntToString(concern_num);
}

/*****************************************************************
 * 函数名称： std::vector<std::string> follower::GetConcernList(std::vector<follower::Follower *> follower_list,
 *                                                             const std::string &user_id)
 * 功能描述： 根据用户id获得他关注人id
 * 参数说明： vector类型的关注列表，字符串类型的用户id
 * 返回值：   id列表
 ******************************************************************/
std::vector<std::string> follower::GetConcernList(std::vector<follower::Follower *> follower_list, 
                                                  const std::string &user_id)
{
    std::vector<std::string> id_list;
    for (int i = 0; i < follower_list.size(); i++)
    {
        if (follower_list[i]->get_follower_id_() == user_id)
        {
            id_list.push_back(follower_list[i]->get_user_id_());
        }
    }
    return id_list;
}

/*****************************************************************
 * 函数名称：  std::string follower::GetFollowersNum(std::vector<follower::Follower *> follower_list,
 *                                                  const std::string &user_id)
 * 功能描述： 根据用户id获得粉丝数量
 * 参数说明： vector类型的关注列表，字符串类型的用户id
 * 返回值：   字符串类型的粉丝数量
 ******************************************************************/
std::string follower::GetFollowersNum(std::vector<follower::Follower *> follower_list, const std::string &user_id)
{
    int followers_num = 0;
    for (int i = 0; i < follower_list.size(); i++)
    {
        if ((follower_list[i]->get_user_id_()) == user_id)
        {
            followers_num++;
        }
    }
    return tool::IntToString(followers_num);
}
/*****************************************************************
 * 函数名称： void Follower::NewFollow(const std::string &user_id,const std::string &follower_id)
 * 功能描述： 赋值关注项
 * 参数说明： 字符串类型的用户id，关注者id
 * 返回值：   无
 ******************************************************************/
void follower::Follower::NewFollow(const std::string &user_id, const std::string &follower_id)
{
    this->user_id_ = user_id;
    this->follower_id_ = follower_id;
    this->follow_time_ = tool::GetTime();
}
/*****************************************************************
 * 函数名称： Follower * GetFollowLog(const std::string &user_id,const std::string &follower_id, 
 *                                   std::vector<Follower *> follower_list)
 * 功能描述： 返回关注项
 * 参数说明： 字符串类型的用户id，关注者id，vector的关注列表
 * 返回值：   对应关注项
 ******************************************************************/
follower::Follower *follower::GetFollowLog(const std::string &user_id, const std::string &follower_id, 
                                           std::vector<follower::Follower *> follower_list)
{
    for (auto i = follower_list.begin(); i != follower_list.end(); i++)
    {
        if ((*i)->get_user_id_() == user_id && (*i)->get_follower_id_() == follower_id)
            return *i;
    }
}
/*****************************************************************
 * 函数名称： std::vector<Follower *> FollowDelete(const std::string &user_id,const std::string &follower_id,
 *                                                std::vector<Follower *> follower_list)
 * 功能描述： 删除关注项
 * 参数说明： 字符串类型的用户id，关注者id，vector的关注列表
 * 返回值：   对应关注项
 ******************************************************************/
std::vector<follower::Follower *> follower::FollowDelete(const std::string &user_id, 
                                                         const std::string &follower_id, std::vector<follower::Follower *> follower_list)
{
    for (auto i = follower_list.begin(); i != follower_list.end(); i++)
    {
        if ((*i)->get_user_id_() == user_id && (*i)->get_follower_id_() == follower_id)
        {
            follower_list.erase(i);
            break;
        }
    }
    return follower_list;
}

/*****************************************************************
 * 函数名称： std::string IfFollowUser(const std::string &user_id,const std::string &follow_id,
 *                                    std::vector<Follower *> follower_list)
 * 功能描述： 根据userid获取该人是否为本人的关注
 * 参数说明： 字符串类型的用户id，关注者id，vector的关注列表
 * 返回值：   判断值，是否关注
 ******************************************************************/
std::string follower::IfFollowUser(const std::string &user_id, const std::string &follow_id, 
                                   std::vector<follower::Follower *> follower_list)
{
    std::string flag = "false";
    for (auto i = follower_list.begin(); i != follower_list.end(); i++)
    {
        if ((*i)->get_user_id_() == follow_id && (*i)->get_follower_id_() == user_id)
        {
            flag = "true";
            break;
        }
    }
    return flag;
}