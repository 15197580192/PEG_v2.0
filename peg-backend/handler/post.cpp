#include "post.h"
// 构造函数
post::Post::Post()
{
    post_id_ = "0";
    poster_id_ = "0";
    poster_name_ = "0";
    post_title_ = "0";
    post_content_ = "0";
    support_num_ = "0";
    comments_num_ = "0";
    post_time_ = "0";
}

/*****************************************************************
 * 函数名称： void Post::NewPost(const std::string &user_id, const std::string &user_name, 
 *                              const std::string &post_title, const std::string &post_content, 
 *                              std::vector<Post *> post_list)
 * 功能描述：   新增帖子
 * 参数说明：userid,username,帖子标题，帖子内容，帖子列表
 * 返回值：无返回值
 ******************************************************************/
void post::Post::NewPost(const std::string &user_id, const std::string &user_name, const std::string &post_title, 
                         const std::string &post_content, std::vector<post::Post *> post_list)
{
    this->set_poster_id_(user_id);
    this->set_poster_name_(user_name);
    this->set_post_title_(post_title);
    this->set_post_content_(post_content);
    this->set_post_id_(NewPostId(post_list));
    time_t now_time = time(NULL);
    tm *ltm = localtime(&now_time);
    std::string post_time = std::to_string(ltm->tm_year + 1900) + "-" + std::to_string(ltm->tm_mon + 1) + "-" + std::to_string(ltm->tm_mday) + "-";
    post_time += std::to_string(ltm->tm_hour) + "-" + std::to_string(ltm->tm_min) + "-" + std::to_string(ltm->tm_sec);
    this->set_post_time_(post_time);
    this->set_support_num_("0");
    this->set_comments_num_("0");
    this->set_collection_num_("0");
    // post_list.push_back(post);
    // return post_list;
}

/*****************************************************************
 * 函数名称： std::vector<Post *> GetUserPost(const std::string &user_id, std::vector<Post *> post_list)
 * 功能描述：   根据用户id获得帖子内容
 * 参数说明：userid,username,帖子列表
 * 返回值：vector，返回帖子内容
 ******************************************************************/
std::vector<post::Post *> post::GetUserPost(const std::string &user_id, std::vector<post::Post *> post_list)
{
    std::vector<post::Post *> post_data;
    for (int i = 0; i < post_list.size(); i++)
    {
        if (post_list[i]->get_poster_id_() == user_id)
        {
            post_data.push_back(post_list[i]);
        }
    }
    return post_data;
}

/*****************************************************************
 * 函数名称：std::string NewPostId(std::vector<Post *> post_list)
 * 功能描述：   随机生成postid
 * 参数说明：帖子列表
 * 返回值：string,返回生成的帖子id
 ******************************************************************/
std::string post::NewPostId(std::vector<post::Post *> post_list)
{
    srand((unsigned int)time(0));
    bool flag = false;
    std::string id;
    while (!flag)
    {
        flag = true;
        id = "";
        for (int i = 0; i < 7; i++)
        {
            id += std::to_string((rand() % 10));
        }
        for (auto it = post_list.begin(); it != post_list.end(); it++)
        {
            if ((*it)->get_post_id_() == id)
                flag = false;
        }
    }
    return id;
}

/*****************************************************************
 * 函数名称： std::vector<std::string> GetUserPostId(const std::string &user_id, std::vector<Post *> post_list)
 * 功能描述：  根据用户id获得帖子id
 * 参数说明：userid,帖子列表
 * 返回值：vector，返回帖子id
 ******************************************************************/
std::vector<std::string> post::GetUserPostId(const std::string &user_id, std::vector<post::Post *> post_list)
{
    std::vector<std::string> postid_list;
    for (int i = 0; i < post_list.size(); i++)
    {
        if (post_list[i]->get_poster_id_() == user_id)
        {
            postid_list.push_back(post_list[i]->get_post_id_());
        }
    }
    return postid_list;
}

/*****************************************************************
 * 函数名称： Post *GetPost(const std::string &post_id, std::vector<Post *> post_list)
 * 功能描述：   根据帖子id获取帖子
 * 参数说明：帖子id，帖子列表
 * 返回值：返回帖子列表
 ******************************************************************/
post::Post *post::GetPost(const std::string &post_id, std::vector<post::Post *> post_list)
{
    for (int i = 0; i < post_list.size(); i++)
    {
        if (post_list[i]->get_post_id_() == post_id)
            return post_list[i];
    }
}

/*****************************************************************
 * 函数名称：std::string GetPostTitle(const std::string &post_id, std::vector<Post *> post_list)
 * 功能描述：   根据帖子id获取帖子标题
 * 参数说明：帖子id，帖子列表
 * 返回值：返回帖子标题
 ******************************************************************/
std::string post::GetPostTitle(const std::string &post_id, std::vector<post::Post *> post_list)
{
    for (int i = 0; i < post_list.size(); i++)
    {
        if (post_list[i]->get_post_id_() == post_id)
            return post_list[i]->get_post_title_();
    }
}

/*****************************************************************
 * 函数名称： std::string GetPostAuthorId(const std::string &post_id, std::vector<Post *> post_list)
 * 功能描述：   根据帖子id获得作者id
 * 参数说明：帖子id，帖子列表
 * 返回值：返回作者id
 ******************************************************************/
std::string post::GetPostAuthorId(const std::string &post_id, std::vector<post::Post *> post_list)
{
    for (int i = 0; i < post_list.size(); i++)
    {
        if (post_list[i]->get_post_id_() == post_id)
            return post_list[i]->get_poster_id_();
    }
}

/*****************************************************************
 * 函数名称： std::vector<Post *> GetFavoritesPost(std::vector<collection::Collection *> collection_list, std::vector<Post *> post_list)
 * 功能描述：  根据收藏帖子列表获取所有帖子数据
 * 参数说明：收藏列表，帖子列表
 * 返回值：返回帖子数据
 ******************************************************************/
std::vector<post::Post *> post::GetFavoritesPost(std::vector<collection::Collection *> collection_list, std::vector<post::Post *> post_list)
{
    std::vector<post::Post *> favorites_post;
    for (auto i = collection_list.begin(); i != collection_list.end(); i++)
    {
        favorites_post.push_back(GetPost((*i)->get_post_id_(), post_list));
    }
    return favorites_post;
}

/*****************************************************************
 * 函数名称： void Post::NewPost(const std::string &user_id, const std::string &user_name, 
 *                              const std::string &post_title, const std::string &post_content, 
 *                              std::vector<Post *> post_list)
 * 功能描述：   根据作者id获取近三天帖子
 * 参数说明：用户id列表，帖子列表
 * 返回值：返回近三天帖子
 ******************************************************************/
std::vector<post::Post *> post::GetLatelyUserPost(std::vector<std::string> userid_list, 
                                                  std::vector<post::Post *> post_list)
{
    std::vector<post::Post *> latelypost_list;
    tm *now_three_ago = tool::GetThreeDaysAgoTime();
    std::time_t time1 = std::mktime(now_three_ago);
    for (int i = 0; i < userid_list.size(); i++)
    {
        for (int j = 0; j < post_list.size(); j++)
        {
            if (post_list[j]->get_poster_id_() == userid_list[i])
            {
                tm *time = tool::GetTimeStruct(post_list[j]->get_post_time_());
                std::time_t time2 = std::mktime(time);
                if (time2 > time1)
                    latelypost_list.push_back(post_list[j]);
            }
        }
    }
    return latelypost_list;
}

/*****************************************************************
 * 函数名称： std::vector<Post *> ChangeSupport(const std::string &post_id, const std::string &flag, 
 *                                             std::vector<Post *> post_list)
 * 功能描述：  将该帖子的点赞数加一/减一
 * 参数说明：帖子id，帖子列表
 * 返回值：返回帖子列表
 ******************************************************************/
std::vector<post::Post *> post::ChangeSupport(const std::string &post_id, const std::string &flag, 
                                              std::vector<post::Post *> post_list)
{
    Post *post = new Post;
    for (auto i = post_list.begin(); i != post_list.end(); i++)
    {
        if ((*i)->get_post_id_() == post_id)
        {
            post = *i;
            post_list.erase(i);
            break;
        }
    }
    int support = tool::StringToInt(post->get_support_num_());
    if (flag == "true")
        support++;
    else
        support--;
    post->set_support_num_(tool::IntToString(support));
    post_list.push_back(post);
    return post_list;
}
//
/*****************************************************************
 * 函数名称： std::vector<Post *> ChangeCollection(const std::string &post_id, const std::string &flag, 
 *                                                std::vector<Post *> post_list)
 * 功能描述：   将该帖子收藏数加1/减一
 * 参数说明：帖子id，帖子列表
 * 返回值：返回帖子列表
 ******************************************************************/
std::vector<post::Post *> post::ChangeCollection(const std::string &post_id, const std::string &flag, 
                                                 std::vector<post::Post *> post_list)
{
    post::Post *post = new post::Post;
    for (auto i = post_list.begin(); i != post_list.end(); i++)
    {
        if ((*i)->get_post_id_() == post_id)
        {
            post = *i;
            post_list.erase(i);
            break;
        }
    }
    int collection = tool::StringToInt(post->get_collection_num_());
    if (flag == "true")
        collection++;
    else
        collection--;
    post->set_collection_num_(tool::IntToString(collection));
    post_list.push_back(post);
    return post_list;
}

/*****************************************************************
 * 函数名称： std::vector<Post *> AddComments(const std::string &post_id, const std::string &flag, 
 *                                           std::vector<Post *> post_list)
 * 功能描述： 将贴子评论数加1/减一
 * 参数说明：帖子id，帖子列表
 * 返回值：返回帖子列表
 ******************************************************************/
std::vector<post::Post *> post::AddComments(const std::string &post_id, const std::string &flag, 
                                            std::vector<post::Post *> post_list)
{
    post::Post *post = new post::Post;
    for (auto i = post_list.begin(); i != post_list.end(); i++)
    {
        if ((*i)->get_post_id_() == post_id)
        {
            post = *i;
            post_list.erase(i);
            break;
        }
    }
    int comments = tool::StringToInt(post->get_comments_num_());
    if (flag == "true")
        comments++;
    else
        comments--;
    post->set_comments_num_(tool::IntToString(comments));
    post_list.push_back(post);
    return post_list;
}

std::vector<post::Post *> post::GetFuzzyFindPost(const std::string &keyword, std::vector<post::Post *> post_list)
{
    std::vector<post::Post *> find_postlist;
    for (auto i = post_list.begin(); i != post_list.end(); i++)
    {
        if (tool::FuzzySearch((*i)->get_post_title_(), keyword))
            find_postlist.push_back(*i);
    }
    return find_postlist;
}