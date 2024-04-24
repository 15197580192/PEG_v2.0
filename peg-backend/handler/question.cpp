
#include "question.h"
// 构造函数
question::Question::Question()
{
    this->question_id_ = "0";
    this->question_title_ = "0";
    this->question_content_ = "0";
    this->support_num_ = "0";
    this->comments_num_ = "0";
    this->ques_time_ = "0";
    this->questioner_id_ = "0";
    this->questioner_name_ = "0";
    this->solved_ = "0";
}

/*****************************************************************
 * 函数名称： std::string question::NewQuestionId(std::vector<question::Question *> question_list)
 * 功能描述： 随机生成questionid(question为5位id)
 * 参数说明： 问题列表
 * 返回值：   string值，返回生成的id
 ******************************************************************/
std::string question::NewQuestionId(std::vector<question::Question *> question_list)
{
    srand((unsigned int)time(0));
    bool flag = false;
    std::string id;
    while (!flag)
    {
        flag = true;
        id = "";
        for (int i = 0; i < 5; i++)
        {
            id += std::to_string((rand() % 10));
        }
        for (auto it = question_list.begin(); it != question_list.end(); it++)
        {
            if ((*it)->get_question_id_() == id)
                flag = false;
        }
    }
    return id;
}

/*****************************************************************
 * 函数名称：  void question::Question::NewQuestion(const std::string &title,const std::string &content,const       
 *                                                 std::string &user_id,const std::string &user_name,
 *                                                 std::vector<question::Question *> question_list)
 * 功能描述：   新建question
 * 参数说明： 标题，内容，userid,username,问题列表
 * 返回值： 无返回值
 ******************************************************************/
void question::Question::NewQuestion(const std::string &title, const std::string &content, 
                                     const std::string &user_id,const std::string &user_name, std::vector<question::Question *> question_list)
{
    this->set_question_id_(NewQuestionId(question_list));
    this->question_title_ = title;
    this->question_content_ = content;
    this->questioner_id_ = user_id;
    this->questioner_name_ = user_name;
    this->support_num_ = "0";
    this->comments_num_ = "0";
    this->ques_time_ = tool::GetTime();
    this->solved_ = "0";
}

/*****************************************************************
 * 函数名称： std::vector<question::Question *> question::GetUserQuestion(const std::string &user_id,std::vector<question::Question *> question_list)
 * 功能描述：   获得个人所发布的问答
 * 参数说明：userid,问题列表
 * 返回值： 返回vector,问题列表
 ******************************************************************/
std::vector<question::Question *> question::GetUserQuestion(const std::string &user_id, 
                                                            std::vector<question::Question *> question_list)
{
    std::vector<question::Question *> user_question;
    for (auto i = question_list.begin(); i != question_list.end(); i++)
    {
        if ((*i)->get_questioner_id_() == user_id)
            user_question.push_back(*i);
    }
    return user_question;
}

/*****************************************************************
 * 函数名称：  question::Question * question::GetNameQuestion(const std::string &question_id,
 *                                                           std::vector<question::Question *> question_list)
 * 功能描述：根据问答id获得某个问答的具体内容
 * 参数说明：问题id,问题列表
 * 返回值： 返回vector,问题列表
 ******************************************************************/
question::Question *question::GetNameQuestion(const std::string &question_id, 
                                              std::vector<question::Question *> question_list)
{
    for (int i = 0; i < question_list.size(); i++)
    {
        if (question_list[i]->get_question_id_() == question_id)
            return question_list[i];
    }
}

/*****************************************************************
 * 函数名称：  std::string question::GetQuestionTitle(const std::string &question_id,
 *                                                   std::vector<question::Question *> question_list)
 * 功能描述：根据问答id获得某个问答的标题
 * 参数说明：问题id,问题列表
 * 返回值： 返回string，问答标题
 ******************************************************************/
std::string question::GetQuestionTitle(const std::string &question_id, 
                                       std::vector<question::Question *> question_list)
{
    for (int i = 0; i < question_list.size(); i++)
    {
        if (question_list[i]->get_question_id_() == question_id)
            return question_list[i]->get_question_title_();
    }
}

/*****************************************************************
 * 函数名称：  std::vector<std::string> question::GetUserQuestionId(const std::string &user_id,
 *                                                                 std::vector<question::Question *> question_list)
 * 功能描述：根据用户id获得问答id
 * 参数说明：用户id,问题列表
 * 返回值： 返回vector，问答id
 ******************************************************************/
std::vector<std::string> question::GetUserQuestionId(const std::string &user_id, 
                                                     std::vector<question::Question *> question_list)
{
    std::vector<std::string> questionid_list;
    for (int i = 0; i < question_list.size(); i++)
    {
        if (question_list[i]->get_questioner_id_() == user_id)
        {
            questionid_list.push_back(question_list[i]->get_question_id_());
        }
    }
    return questionid_list;
}
/*****************************************************************
 * 函数名称：   std::vector<question::Question *> question::AddSupport(
 *             const std::string &question_id,
 *             std::vector<question::Question *> question_list)
 * 功能描述：将问答点赞数加一
 * 参数说明：问题id,问题列表
 * 返回值： 返回vector，问答列表
 ******************************************************************/
std::vector<question::Question *> question::ChangeSupport(const std::string &question_id, const std::string &flag,
                                                          std::vector<question::Question *> question_list)
{
    question::Question *question = new question::Question;
    for (auto i = question_list.begin(); i != question_list.end(); i++)
    {
        if ((*i)->get_question_id_() == question_id)
        {
            question = *i;
            question_list.erase(i);
            break;
        }
    }
    int support = tool::StringToInt(question->get_support_num_());
    if (flag == "true")
        support++;
    else
        support--;
    question->set_support_num_(tool::IntToString(support));
    question_list.push_back(question);
    return question_list;
}
/*****************************************************************
 * 函数名称：  std::vector<question::Question *> question::AddComments(
 *            const std::string &question_id,
 *            std::vector<question::Question *> question_list)
 * 功能描述：将问答评论数加1
 * 参数说明：问题id,问题列表
 * 返回值： 返回vector，问答列表
 ******************************************************************/
std::vector<question::Question *> question::AddComments(const std::string &question_id, 
                                                        std::vector<question::Question *> question_list)
{
    question::Question *question = new question::Question;
    for (auto i = question_list.begin(); i != question_list.end(); i++)
    {
        if ((*i)->get_question_id_() == question_id)
        {
            question = *i;
            question_list.erase(i);
            break;
        }
    }
    int comments = tool::StringToInt(question->get_comments_num_());
    comments++;
    question->set_comments_num_(tool::IntToString(comments));
    question_list.push_back(question);
    return question_list;
}

std::vector<question::Question *> question::UpdateSolved(const std::string &question_id,
                                                             std::vector<question::Question *> question_list)
{
    for (auto i = question_list.begin(); i != question_list.end(); i++)
    {
        if ((*i)->get_question_id_() == question_id){
            (*i)->set_solved_("1");
            break;
        }
    }
    return question_list;
}
