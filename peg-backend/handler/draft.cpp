#include "draft.h"

draft::Draft::Draft()
{
    this->type_ = "0";
    this->title_ = "0";
    this->content_ = "0";
    this->author_id_ = "0";
    this->time_ = "0";
}
/*****************************************************************
* 函数名称：  void draft::Draft::NewDraft(const std::string &type,const std::string &title,
                                         const std::string &content,
                                         const std::string author_id)
* 功能描述： 新建草稿（帖子或问答）
* 参数说明： 字符串类型的类型，标题，内容，作者id
* 返回值：   无返回值
******************************************************************/
void draft::Draft::NewDraft(const std::string &type, const std::string &title, const std::string &content,
                            const std::string author_id)
{
    this->type_ = type;
    this->title_ = title;
    this->content_ = content;
    this->author_id_ = author_id;
    this->time_ = tool::GetTime();
}
/*****************************************************************
 * 函数名称： bool draft::CheckDraft(const std::string &title,std::vector<draft::Draft *> draft_list)
 * 功能描述： 根据主题判断该草稿是否重复
 * 参数说明： 字符串类型的标题，vector类型的草稿列表
 * 返回值：   判断值
 ******************************************************************/
bool draft::CheckDraft(const std::string &title, std::vector<draft::Draft *> draft_list)
{
    for (auto i = draft_list.begin(); i != draft_list.end(); i++)
    {
        if ((*i)->get_title_() == title)
            return false;
    }
    return true;
}
/*****************************************************************
 * 函数名称： std::vector<draft::Draft *> draft::UserDraft(const std::string &user_id,
 *                                                        std::vector<draft::Draft *> draft_list)
 * 功能描述： 根据用户id找到属于这个用户的所有草稿
 * 参数说明： 字符串类型的用户id,vector类型的草稿列表
 * 返回值：   用户对应的草稿列表
 ******************************************************************/
std::vector<draft::Draft *> draft::UserDraft(const std::string &user_id, std::vector<draft::Draft *> draft_list)
{
    std::vector<draft::Draft *> user_draft;
    for (auto i = draft_list.begin(); i != draft_list.end(); i++)
    {
        if ((*i)->get_author_id_() == user_id)
            user_draft.push_back(*i);
    }
    return user_draft;
}
/*****************************************************************
 * 函数名称： draft::Draft * draft::GetDraftAccordIdTtile(const std::string &type,const std::string &title,
 *                                                       std::vector<draft::Draft *> draft_list)
 * 功能描述： 根据title和用户id找到该草稿
 * 参数说明： 字符串类型的类型，标题，vector类型的草稿列表
 * 返回值：   对应的草稿项
 ******************************************************************/
draft::Draft *draft::GetDraftAccordIdTtile(const std::string &type, const std::string &title, 
                                           std::vector<draft::Draft *> draft_list)
{
    for (auto i = draft_list.begin(); i != draft_list.end(); i++)
    {
        if ((*i)->get_type_() == type && (*i)->get_title_() == title)
            return *i;
    }
}
/*****************************************************************
 * 函数名称： std::vector<draft::Draft *> draft::DraftDeleteCertain(draft::Draft *draft,
 *                                                                 std::vector<draft::Draft *> draft_list)
 * 功能描述： 删除对应记录
 * 参数说明： 草稿项，vector类型的草稿列表
 * 返回值：   删除后的草稿列表
 ******************************************************************/
std::vector<draft::Draft *> draft::DraftDeleteCertain(draft::Draft *draft, std::vector<draft::Draft *> draft_list)
{
    for (auto i = draft_list.begin(); i != draft_list.end();)
    {
        if ((*i)->get_type_() == draft->get_type_() && (*i)->get_title_() == draft->get_title_() 
            && (*i)->get_author_id_() == draft->get_author_id_())
        {
            draft_list.erase(i);
            return draft_list;
        } else {
            i++;
        } 
    }
}