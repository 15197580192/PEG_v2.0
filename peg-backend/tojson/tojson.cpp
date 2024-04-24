#include "tojson.h"

/*****************************************************************
 * 函数名称： nlohmann::json NodeToJson(std::vector<node::Node *> node_data)
 * 功能描述： 格式转换函数，将node类的对象转换成json对象格式
 * 参数说明： node类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::NodeToJson(std::vector<node::Node *> node_data)
{
    nlohmann::json node;
    int i = 0;
    for (auto it = node_data.begin(); it != node_data.end(); it++)
    {
        node[i]["node_id"] = (*it)->get_node_id_();
        node[i]["node_ip"] = (*it)->get_node_ip_();
        node[i]["user_id"] = (*it)->get_user_id_();
        node[i]["port"] = (*it)->get_port_();
        node[i]["gstore_user_id"] = (*it)->get_gstore_user_id_();
        node[i]["gstore_user_password"] = (*it)->get_gstore_user_password_();
        node[i]["version"] = (*it)->get_version_();
        node[i]["apitype"] = (*it)->get_apitype_();
        node[i]["rootpath"] = (*it)->get_rootpath_();
        i++;
    }
    return node;
}

/*****************************************************************
 * 函数名称： nlohmann::json DatabaseToJson(std::vector<database::Database *> database_data)
 * 功能描述： 格式转换函数，将database类的对象转换成json对象格式
 * 参数说明： database类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::DatabaseToJson(std::vector<database::Database *> database_data)
{
    nlohmann::json database;
    for (int it = 0; it < database_data.size(); it++)
    {
        database[it]["database_id"] = database_data[it]->get_database_id_();
        database[it]["database_name"] = database_data[it]->get_database_name_();
        database[it]["create_user_id"] = database_data[it]->get_creater_id_();
        database[it]["database_passward"] = database_data[it]->get_database_password_();
        database[it]["databse_version"] = database_data[it]->get_database_version_();
    }
    return database;
}

/*****************************************************************
 * 函数名称： nlohmann::json PEGUserToJson(peguser::PEGUser *user)
 * 功能描述： 格式转换函数，将PEGUser类的对象转换成json对象格式
 * 参数说明： PEGUser类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::PEGUserToJson(peguser::PegUser *user)
{
    nlohmann::json peg_user;
    peg_user["user_id"] = user->get_user_id_();
    peg_user["user_name"] = user->get_user_name_();
    peg_user["tel"] = user->get_tel_();
    peg_user["register_time"] = user->get_register_time_();
    peg_user["forbidden"] = user->get_forbidden_();
    peg_user["birthday"] = user->get_birthday_();
    peg_user["introduction"] = user->get_introduction_();
    peg_user["location"] = user->get_location_();
    peg_user["mailbox"] = user->get_mailbox_();
    peg_user["sex"] = user->get_sex_();
    peg_user["adress"] = user->get_adress_();
    return peg_user;
}

/*****************************************************************
 * 函数名称： nlohmann::json PEGUserListToJson(std::vector<peguser::PegUser *> peguser_list)
 * 功能描述： 格式转换函数，将PEGUser类的对象列表转换成json对象格式
 * 参数说明： PEGUser类的列表
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::PEGUserListToJson(std::vector<peguser::PegUser *> peguser_list)
{
    nlohmann::json peguser_listjson;
    for (int i = 0; i < peguser_list.size(); i++)
    {
        peguser_listjson[i]["user_id"] = peguser_list[i]->get_user_id_();
        peguser_listjson[i]["user_name"] = peguser_list[i]->get_user_name_();
        peguser_listjson[i]["tel"] = peguser_list[i]->get_tel_();
        peguser_listjson[i]["register_time"] = peguser_list[i]->get_register_time_();
        peguser_listjson[i]["forbidden"] = peguser_list[i]->get_forbidden_();
        peguser_listjson[i]["birthday"] = peguser_list[i]->get_birthday_();
        peguser_listjson[i]["introduction"] = peguser_list[i]->get_introduction_();
        peguser_listjson[i]["location"] = peguser_list[i]->get_location_();
        peguser_listjson[i]["mailbox"] = peguser_list[i]->get_mailbox_();
        peguser_listjson[i]["sex"] = peguser_list[i]->get_sex_();
        peguser_listjson[i]["adress"] = peguser_list[i]->get_adress_();
    }
    return peguser_listjson;
}

/*****************************************************************
 * 函数名称： nlohmann::json ManagePEGUserListToJson(std::vector<peguser::PegUser *> peguser_list)
 * 功能描述： 格式转换函数，将PEGUser类的对象转换成json对象格式
 * 参数说明： PEGUser类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::ManagePEGUserListToJson(std::vector<peguser::PegUser *> peguser_list)
{
    nlohmann::json peguser_listjson;
    for (int i = 0; i < peguser_list.size(); i++)
    {
        peguser_listjson[i]["user_id"] = peguser_list[i]->get_user_id_();
        peguser_listjson[i]["user_name"] = peguser_list[i]->get_user_name_();
        peguser_listjson[i]["tel"] = peguser_list[i]->get_tel_();
        peguser_listjson[i]["register_time"] = peguser_list[i]->get_register_time_();
        peguser_listjson[i]["forbidden"] = peguser_list[i]->get_forbidden_();
        peguser_listjson[i]["birthday"] = peguser_list[i]->get_birthday_();
        peguser_listjson[i]["introduction"] = peguser_list[i]->get_introduction_();
        peguser_listjson[i]["location"] = peguser_list[i]->get_location_();
        peguser_listjson[i]["mailbox"] = peguser_list[i]->get_mailbox_();
        peguser_listjson[i]["sex"] = peguser_list[i]->get_sex_();
        peguser_listjson[i]["adress"] = peguser_list[i]->get_adress_();
        peguser_listjson[i]["password"] = peguser_list[i]->get_user_password_();
    }
    return peguser_listjson;
}

/*****************************************************************
 * 函数名称： nlohmann::json DatabaseJson(vector<database::Database *> databasevector)
 * 功能描述： 格式转换函数，将Database类的对象转换成json对象格式
 * 参数说明： Database类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::DatabaseJson(vector<database::Database *> databasevector)
{
    nlohmann::json databaseinf;
    for (int i = 0; i < databasevector.size(); i++)
    {
        databaseinf[i]["database_id"] = databasevector[i]->get_database_id_();
        databaseinf[i]["database_name"] = databasevector[i]->get_database_name_();
    }
    return databaseinf;
};

/*****************************************************************
 * 函数名称： nlohmann::json DatabaseNameToJson(
 *           std::vector<std::string>database_name)
 * 功能描述： 格式转换函数，将Databasename转换成json对象格式
 * 参数说明： 字符串
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::DatabaseNameToJson(std::vector<std::string> database_name)
{
    nlohmann::json database;
    for (int i = 0; i < database_name.size(); i++)
    {
        database[i] = database_name[i];
    }
    return database;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::DbLogToJson(vector<dblog::DbLog *> dblog_vector)
 * 功能描述： 格式转换函数，将DbLog类的对象转换成json对象格式
 * 参数说明： DbLog类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::DbLogToJson(vector<dblog::DbLog *> dblog_vector)
{
    nlohmann::json dblog_inf;
    for (int i = 0; i < dblog_vector.size(); i++)
    {
        dblog_inf[i]["dbuserid"] = dblog_vector[i]->get_operate_user_id_();
        dblog_inf[i]["operatetime"] = dblog_vector[i]->get_operate_time_();
        dblog_inf[i]["databaseid"] = dblog_vector[i]->get_operate_database_id_();
        dblog_inf[i]["operatetype"] = dblog_vector[i]->get_operate_type_();
    }
    return dblog_inf;
};

/*****************************************************************
 * 函数名称： nlohmann::json tojson::PegLogToJson(vector<peglog::PegLog *> peglog_vector)
 * 功能描述： 格式转换函数，将PegLog类的对象转换成json对象格式
 * 参数说明： PegLog类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::PegLogToJson(vector<peglog::PegLog *> peglog_vector)
{
    nlohmann::json peglog_inf;
    for (int i = 0; i < peglog_vector.size(); i++)
    {
        peglog_inf[i]["peguserid"] = peglog_vector[i]->get_peg_user_id_();
        peglog_inf[i]["pegtime"] = peglog_vector[i]->get_peg_time_();
        peglog_inf[i]["pegthings"] = peglog_vector[i]->get_peg_things_();
    }
    return peglog_inf;
};

/*****************************************************************
 * 函数名称： nlohmann::json tojson::NodeIdDbIdToJson(vector<node::Node *> node_vector)
 * 功能描述： 格式转换函数，将Node类的对象部分参数转换成json对象格式
 * 参数说明： Node类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::NodeIdDbIdToJson(vector<node::Node *> node_vector)
{
    nlohmann::json node_inf;
    for (int i = 0; i < node_vector.size(); i++)
    {
        node_inf[i]["id"] = node_vector[i]->get_node_id_();
        node_inf[i]["ip"] = node_vector[i]->get_node_ip_();
        node_inf[i]["port"] = node_vector[i]->get_port_();
    }
    return node_inf;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::UnreadSupportToJson(std::vector<support::Support *> support_list,
                                           std::vector<post::Post *> post_list,
                                           std::vector<question::Question *> question_list,
                                           std::vector<peguser::PegUser *> peguser_list)
 * 功能描述： 格式转换函数，将Support类的对象部分参数转换成json对象格式
 * 参数说明： Support类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::UnreadSupportToJson(std::vector<support::Support *> support_list,
                                           std::vector<post::Post *> post_list,
                                           std::vector<question::Question *> question_list,
                                           std::vector<peguser::PegUser *> peguser_list)
{
    nlohmann::json support_json;
    for (int i = 0; i < support_list.size(); i++)
    {
        std::string post_id = support_list[i]->get_post_id_();
        std::string user_id = support_list[i]->get_supporter_id_();
        support_json[i]["postId"] = post_id;
        if (post_id.size() == 7)
            support_json[i]["postTitle"] = post::GetPostTitle(post_id, post_list);
        else
            support_json[i]["postTitle"] = question::GetQuestionTitle(post_id, question_list);
        support_json[i]["name"] = peguser::GetUserName(user_id, peguser_list);
        support_json[i]["time"] = support_list[i]->get_support_time_();
    }
    return support_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::UnreadCommentsToJson(std::vector<comment::Comment *> comments_list,
                                            std::vector<post::Post *> post_list,
                                            std::vector<question::Question *> question_list,
                                            std::vector<peguser::PegUser *> peguser_list)
 * 功能描述： 格式转换函数，将Comment类的对象部分参数转换成json对象格式
 * 参数说明： Comment类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::UnreadCommentsToJson(std::vector<comment::Comment *> comments_list,
                                            std::vector<post::Post *> post_list,
                                            std::vector<question::Question *> question_list,
                                            std::vector<peguser::PegUser *> peguser_list)
{
    nlohmann::json comments_json;
    for (int i = 0; i < comments_list.size(); i++)
    {
        std::string post_id = comments_list[i]->get_post_id_();
        std::string user_id = comments_list[i]->get_commenter_id_();
        comments_json[i]["postId"] = post_id;
        if (post_id.size() == 7)
            comments_json[i]["postTitle"] = post::GetPostTitle(post_id, post_list);
        else
            comments_json[i]["postTitle"] = question::GetQuestionTitle(post_id, question_list);
         comments_json[i]["name"] = peguser::GetUserName(user_id, peguser_list);
        comments_json[i]["time"] = comments_list[i]->get_comment_time_();
    }
    return comments_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::PostToJson(std::vector<post::Post *> post_list)
 * 功能描述： 格式转换函数，将Post类的对象列表转换成json对象格式
 * 参数说明： Post类的对象列表
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::PostToJson(std::vector<post::Post *> post_list)
{
    nlohmann::json post_json;
    for (int i = 0; i < post_list.size(); i++)
    {
        post_json[i]["postId"] = post_list[i]->get_post_id_();
        post_json[i]["authorId"] = post_list[i]->get_poster_id_();
        post_json[i]["autherName"] = post_list[i]->get_poster_name_();
        post_json[i]["title"] = post_list[i]->get_post_title_();
        post_json[i]["intro"] = post_list[i]->get_post_content_();
        post_json[i]["like"] = post_list[i]->get_support_num_();
        post_json[i]["comments"] = post_list[i]->get_comments_num_();
        post_json[i]["favorites"] = post_list[i]->get_collection_num_();
        post_json[i]["time"] = post_list[i]->get_post_time_();
    }
    return post_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::OnePostToJson(post::Post *post)
 * 功能描述： 格式转换函数，将Post类的对象转换成json对象格式
 * 参数说明： Post类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::OnePostToJson(post::Post *post)
{
    nlohmann::json post_json;
    post_json["postId"] = post->get_post_id_();
    post_json["authorId"] = post->get_poster_id_();
    post_json["autherName"] = post->get_poster_name_();
    post_json["title"] = post->get_post_title_();
    post_json["intro"] = post->get_post_content_();
    post_json["like"] = post->get_support_num_();
    post_json["comments"] = post->get_comments_num_();
    post_json["favorites"] = post->get_collection_num_();
    post_json["time"] = post->get_post_time_();
    return post_json;
}

nlohmann::json tojson::OneFollowPostToJson(std::vector<post::Post *> post_list,const std::string &user_id,std::vector<support::Support *> support_list,std::vector<collection::Collection *> collection_list)
{
    nlohmann::json post_json;
    for(int i=0;i<post_list.size();i++){
    post_json[i]["postId"] = post_list[i]->get_post_id_();
    post_json[i]["authorId"] = post_list[i]->get_poster_id_();
    post_json[i]["autherName"] = post_list[i]->get_poster_name_();
    post_json[i]["title"] = post_list[i]->get_post_title_();
    post_json[i]["intro"] = post_list[i]->get_post_content_();
    post_json[i]["like"] = post_list[i]->get_support_num_();
    post_json[i]["comments"] = post_list[i]->get_comments_num_();
    post_json[i]["favorites"] = post_list[i]->get_collection_num_();
    post_json[i]["time"] = post_list[i]->get_post_time_();
    post_json[i]["if_liked"] = IfSupportPost(post_list[i]->get_post_id_(), user_id, support_list);
    post_json[i]["if_collection"] = collection::IfCollectionPost(post_list[i]->get_post_id_(), user_id, collection_list);
    }
    return post_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::QuestionToJson(std::vector<question::Question *> question_list
 * 功能描述： 格式转换函数，将Question类的对象列表转换成json对象格式
 * 参数说明： Question类列表
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::QuestionToJson(std::vector<question::Question *> question_list)
{
    nlohmann::json question_json;
    for (int i = 0; i < question_list.size(); i++)
    {
        question_json[i]["question_id"] = question_list[i]->get_question_id_();
        question_json[i]["question_title"] = question_list[i]->get_question_title_();
        question_json[i]["question_content"] = question_list[i]->get_question_content_();
        question_json[i]["support_num"] = question_list[i]->get_support_num_();
        question_json[i]["comments_num"] = question_list[i]->get_comments_num_();
        question_json[i]["questioner_id"] = question_list[i]->get_questioner_id_();
        question_json[i]["questioner_name"] = question_list[i]->get_questioner_name_();
        question_json[i]["ques_time"] = question_list[i]->get_ques_time_();
        question_json[i]["solved"] = question_list[i]->get_solved_();
    }
    return question_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::OneQuestionToJson(question::Question *question)
 * 功能描述： 格式转换函数，将Question类的对象转换成json对象格式
 * 参数说明： Question类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::OneQuestionToJson(question::Question *question)
{
    nlohmann::json question_json;
    question_json["questionId"] = question->get_question_id_();
    question_json["title"] = question->get_question_title_();
    question_json["content"] = question->get_question_content_();
    question_json["time"] = question->get_ques_time_();
    question_json["questioner_name"] = question->get_questioner_name_();
    question_json["questioner_id"] = question->get_questioner_id_();
    question_json["comments"] = question->get_comments_num_();
    question_json["like"] = question->get_support_num_();
    question_json["isResolve"] = question->get_solved_();
    return question_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::PostQUestionEnrollNumToJson(const int &post_num, const int &question_num, 
 *                                                              const int &user_num)
 * 功能描述： 格式转换函数，将三个数量转换成json对象格式
 * 参数说明： int
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::PostQUestionEnrollNumToJson(const int &post_num, const int &question_num,
                                                   const int &user_num)
{
    nlohmann::json num_json;
    num_json[0]["id"] = "主题";
    num_json[0]["number"] = to_string(post_num);
    num_json[1]["id"] = "问答";
    num_json[1]["number"] = to_string(question_num);
    num_json[2]["id"] = "人数";
    num_json[2]["number"] = to_string(user_num);
    return num_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::FollowToJson(std::vector<peguser::UserInfor *> infor_list)
 * 功能描述： 格式转换函数，将peguser类的对象部分参数转换成json对象格式
 * 参数说明： peguser类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::FollowToJson(std::vector<peguser::UserInfor *> infor_list)
{
    nlohmann::json follow_json;
    for (int i = 0; i != infor_list.size(); i++)
    {
        follow_json[i]["follow_user_name"] = infor_list[i]->name_;
        follow_json[i]["follow_user_id"] = infor_list[i]->id_;
        follow_json[i]["intro"] = infor_list[i]->introduction_;
    }
    return follow_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::PostCommentToJson(std::vector<comment::Comment *> comments_list)
 * 功能描述： 格式转换函数，将对应帖子评论的Comment类的对象转换成json对象格式
 * 参数说明： Comment类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::PostCommentToJson(std::vector<comment::Comment *> comments_list)
{
    nlohmann::json comment_json;
    for (int i = 0; i < comments_list.size(); i++)
    {
        comment_json[i]["comments_user_name"] = comments_list[i]->get_commenter_name_();
        comment_json[i]["comments_user_id"] = comments_list[i]->get_commenter_id_();
        comment_json[i]["comments_time"] = comments_list[i]->get_comment_time_();
        comment_json[i]["content"] = comments_list[i]->get_comment_content_();
        // comment_json[i]["read_flag"]=comments_list[i]->get_read_flag_();
    }
    return comment_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::QuestionCommentToJson(std::vector<comment::Comment *> comments_list)
 * 功能描述： 格式转换函数，将对应问答评论的Comment类的对象转换成json对象格式
 * 参数说明： Comment类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::QuestionCommentToJson(std::vector<comment::Comment *> comments_list)
{
    nlohmann::json comment_json;
    for (int i = 0; i < comments_list.size(); i++)
    {
        comment_json[i]["comments_user_name"] = comments_list[i]->get_commenter_name_();
        comment_json[i]["comments_user_id"] = comments_list[i]->get_commenter_id_();
        comment_json[i]["comments_time"] = comments_list[i]->get_comment_time_();
        comment_json[i]["content"] = comments_list[i]->get_comment_content_();
        // comment_json[i]["read_flag"]=comments_list[i]->get_read_flag_();
        comment_json[i]["bestAnswer"] = comments_list[i]->get_best_answer_();
    }
    return comment_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::DraftToJson(std::vector<draft::Draft *> draft_list)
 * 功能描述： 格式转换函数，将Draft类的对象列表转换成json对象格式
 * 参数说明： Draft类的列表
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::DraftToJson(std::vector<draft::Draft *> draft_list)
{
    nlohmann::json draft_json;
    for (int i = 0; i < draft_list.size(); i++)
    {
        draft_json[i]["type"] = draft_list[i]->get_type_();
        draft_json[i]["title"] = draft_list[i]->get_title_();
        draft_json[i]["content"] = draft_list[i]->get_content_();
        draft_json[i]["author_id"] = draft_list[i]->get_author_id_();
        draft_json[i]["time"] = draft_list[i]->get_time_();
    }
    return draft_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::OneDraftToJson(draft::Draft *draft)
 * 功能描述： 格式转换函数，将Draft类的对象转换成json对象格式
 * 参数说明： Draft类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::OneDraftToJson(draft::Draft *draft)
{
    nlohmann::json draft_json;
    draft_json["type"] = draft->get_type_();
    draft_json["title"] = draft->get_title_();
    draft_json["content"] = draft->get_content_();
    draft_json["author_id"] = draft->get_author_id_();
    draft_json["time"] = draft->get_time_();
    return draft_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::ChatHistoryToJson(std::vector<chat::ChatHistory *> lately_chat)
 * 功能描述： 格式转换函数，将ChatHistory类的对象转换成json对象格式
 * 参数说明： ChatHistory类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::ChatHistoryToJson(std::map<std::string, chat::Chat *> lately_chat)
{
    nlohmann::json chat;
    int i=0;
    for (auto it = lately_chat.begin(); it != lately_chat.end(); it++)
    {
        chat[i]["dest_user_id"] = it->first;
        chat[i]["content"] = it->second->get_content_();
        chat[i]["send_time"] = it->second->get_send_time_();
        // 最新消息是以自己结尾的，就不用管表中的已读标志
        if (it->first == it->second->get_dest_user_id_())
        {
            chat[i]["flag"] = "1";
            chat[i]["dest_user_name"] = it->second->get_dest_user_name_();
        }
        else
        {
            chat[i]["flag"] = it->second->get_read_flag_();
            chat[i]["dest_user_name"] = it->second->get_source_user_name_();
        }
        i++;
    }
    return chat;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::OneUserChatToJson(std::vector<chat::Chat *> chat_list)
 * 功能描述： 格式转换函数，将Chat类的对象转换成json对象格式
 * 参数说明： Chat类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::OneUserChatToJson(std::vector<chat::Chat *> chat_list)
{
    nlohmann::json user_chat;
    for (int i = 0; i < chat_list.size(); i++)
    {
        user_chat[i]["content"] = chat_list[i]->get_content_();
        user_chat[i]["source_id"] = chat_list[i]->get_source_user_id_();
        user_chat[i]["source_name"] = chat_list[i]->get_source_user_name_();
        user_chat[i]["dest_id"] = chat_list[i]->get_dest_user_id_();
        user_chat[i]["dest_name"] = chat_list[i]->get_dest_user_name_();
        user_chat[i]["send_time"] = chat_list[i]->get_send_time_();
    }
    return user_chat;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::DbUserToJson(vector<DbUser *> dbuser_list)
 * 功能描述： 格式转换函数，将DbUser类的对象转换成json对象格式
 * 参数说明： DbUser类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::DbUserToJson(vector<DbUser *> dbuser_list)
{
    nlohmann::json dbuser_json;
    for (int i = 0; i < dbuser_list.size(); i++)
    {
        dbuser_json[i]["dbuser_id"] = dbuser_list[i]->get_dbuser_id_();
        dbuser_json[i]["database_id"] = dbuser_list[i]->get_database_id_();
        dbuser_json[i]["dbuser_name"] = dbuser_list[i]->get_dbuser_name_();
        dbuser_json[i]["dbuser_pass"] = dbuser_list[i]->get_dbuser_password_();
        dbuser_json[i]["isban"] = dbuser_list[i]->get_isban_();
        dbuser_json[i]["creater_id"] = dbuser_list[i]->get_creater_id_();
    }
    return dbuser_json;
}

/*****************************************************************
 * 函数名称： nlohmann::json tojson::NoticeToJson(vector<Notice *> notice_vector)
 * 功能描述： 格式转换函数，将Notice类的对象转换成json对象格式
 * 参数说明： Notice类
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::NoticeToJson(vector<Notice *> notice_vector)
{
    nlohmann::json notice_inf;
    for (int i = 0; i < notice_vector.size(); i++)
    {
        notice_inf[i]["createrid"] = notice_vector[i]->get_creater_id_();
        notice_inf[i]["createtime"] = notice_vector[i]->get_create_time_();
        notice_inf[i]["content"] = notice_vector[i]->get_content_();
        notice_inf[i]["noticeid"] = notice_vector[i]->get_notice_id_();
        notice_inf[i]["noticetopic"] = notice_vector[i]->get_notice_topic_();
    }
    return notice_inf;
};

/*****************************************************************
 * 函数名称： nlohmann::json tojson::BackupIdToJson(vector<dbbackup::DbBackup *> dbbackup_list)
 * 功能描述： 格式转换函数，将DbBackup类的对象id转换成json对象格式
 * 参数说明： DbBackup类的id
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::BackupIdToJson(vector<dbbackup::DbBackup *> dbbackup_list)
{
    nlohmann::json backuplist_json;
    for (int i = 0; i < dbbackup_list.size(); i++)
    {
        backuplist_json[i]["backupid"] = dbbackup_list[i]->get_backup_id_();
        backuplist_json[i]["backuptime"] = dbbackup_list[i]->get_backup_time_();
        backuplist_json[i]["backupversion"] = dbbackup_list[i]->get_backup_version_();
    }
    return backuplist_json;
};

/*****************************************************************
 * 函数名称： nlohmann::json tojson::BackupToJson(vector<dbbackup::DbBackup *> dbbackup_list)
 * 功能描述： 格式转换函数，将DbBackup类的对象转换成json对象格式
 * 参数说明： DbBackup类的
 * 返回值：   json对象
 ******************************************************************/
nlohmann::json tojson::BackupToJson(vector<dbbackup::DbBackup *> dbbackup_list)
{
    nlohmann::json backuplist_json;
    for (int i = 0; i < dbbackup_list.size(); i++)
    {
        backuplist_json[i]["backupid"] = dbbackup_list[i]->get_backup_id_();
        backuplist_json[i]["backuptime"] = dbbackup_list[i]->get_backup_time_();
        backuplist_json[i]["backupversion"] = dbbackup_list[i]->get_backup_version_();
    }
    return backuplist_json;
};