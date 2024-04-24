#include "peguser.h"

peguser::PegUser::PegUser()
{
    user_id_ = "0";
    user_name_ = "0";
    user_password_ = "0";
    tel_ = "0";
    register_time_ = "0";
    forbidden_ = "0";
    birthday_ = "0";
    introduction_ = "0";
    location_ = "0";
    mailbox_ = "0";
    sex_ = "0";
    adress_ = "0";
    verification_ = "0";
    start_time = clock();
    end_time = clock();
}

/*****************************************************************
 * 函数名称： void PEGUser::UserModify(const std::string &user_id,const std::string &user_name,
 *                                    const std::string &tel,
 *                                    const std::string &introduction,const std::string &birthday,
 *                                    const std::string &location,const std::string &mailbox,
 *                                    const std::string &sex,const std::string &adress)
 * 功能描述： 修改用户信息函数，修改某个指定的用户id
 * 参数说明： 字符串，输入需要修改的用户信息，包括昵称、电话号码等
 * 返回值：   无返回值
 ******************************************************************/
void peguser::PegUser::UserModify(const std::string &user_id, const std::string &user_name, const std::string &tel,
                                  const std::string &introduction, const std::string &birthday,
                                  const std::string &location,
                                  const std::string &mailbox, const std::string &sex, const std::string &adress)
{
    this->user_name_ = user_name;
    this->user_id_ = user_id;
    this->tel_ = tel;
    this->introduction_ = introduction;
    this->birthday_ = birthday;
    this->location_ = location;
    this->mailbox_ = mailbox;
    this->sex_ = sex;
    this->adress_ = adress;
}

/*****************************************************************
 * 函数名称： std::vector<PEGUser *> UserDataModify(std::vector<PEGUser *> peguser_list,PEGUser *user)
 * 功能描述： 修改用户信息函数，将修改后的用户更新在用户列表中
 * 参数说明： vector容器，里面包含所有用户信息；PEGUser对象，待更新的用户对象
 * 返回值：   vector容器，更新后的用户列表
 ******************************************************************/
std::vector<peguser::PegUser *> peguser::UserDataModify(std::vector<peguser::PegUser *> peguser_list,
                                                        peguser::PegUser *user)
{
    for (auto it = peguser_list.begin(); it != peguser_list.end(); )
    {
        if ((*it)->get_user_id_() == user->get_user_id_())
        {
            user->set_forbidden_((*it)->get_forbidden_());
            user->set_user_password_((*it)->get_user_password_());
            user->set_register_time_((*it)->get_register_time_());
            peguser_list.erase(it);
            break;
        } else {
            it++;
        }
    }
    peguser_list.push_back(user);
    return peguser_list;
}

/*****************************************************************
 * 函数名称： void PEGUser::MakeEmailContent(const std::string &mailbox,const int &type)
 * 功能描述： 创建验证码函数
 * 参数说明： 字符串为要发送的邮箱地址，type为验证码类型（注册验证码或重置密码验证码）
 * 返回值：   无返回值
 ******************************************************************/
std::string peguser::PegUser::MakeEmailContent(const std::string &mailbox, const int &type)
{
    srand((unsigned int)time(0));
    std::string captcha = "";
    for (int i = 0; i < 6; i++)
    {
        captcha += std::to_string((rand() % 10));
    }
    std::string content;
    if (1 == type)
        content += "欢迎您注册本系统！";
    if (2 == type)
        content += "开始重置密码！";
    content += "本次验证码为：";
    content += captcha;
    content += "。请在60s内输入！";
    sendEmail("13735188055@163.com", "FWMAZPOAELTSSGFU", mailbox, content);
    return captcha;
}

/*****************************************************************
 * 函数名称： bool PEGUser::UserEnroll(const std::string &key,const std::string &value,
 *                                    std::vector<PEGUser *> peguser_list)
 * 功能描述： 用户注册函数，根据传入的参数值分为发送验证码和验证验证码两个部分
 * 参数说明： 字符串，分为邮箱和验证码
 * 返回值：   bool判断值
 ******************************************************************/
bool peguser::PegUser::UserEnroll(std::map<std::string, std::string> key_value,
                                  std::vector<peguser::PegUser *> peguser_list)
{
    if (key_value.size() == 1)
    {
        for (auto it = peguser_list.begin(); it != peguser_list.end(); it++)
        {
            if ((*it)->get_mailbox_() == key_value["mailbox"] && (*it)->get_user_id_() != "0")
                return false;
        }
        this->start_time = clock();
        this->verification_= MakeEmailContent(key_value["mailbox"], 1);
        // this->verification_=send_verification(value);
        this->mailbox_ = key_value["mailbox"];
        return true;
    }
    else
    {
        std::string value = key_value["verification"];
        std::cout<<value<<std::endl;
        this->end_time = clock();
        if (((double)((this->end_time) - (this->start_time))) > 60000)
            return false;
        if (this->verification_ == value){
            std::cout<<this->verification_<<std::endl;
            return true;
        }
            return false;
    }
}

/*****************************************************************
 * 函数名称： bool PEGUser::UserRecoverPassword(std::map<std::string,std::string> data)
 * 功能描述： 用户重置密码函数，根据传入的参数值分为发送验证码和更新重置密码两个部分
 * 参数说明： map类型，分为传入邮箱和传入验证码以及新密码两个部分
 * 返回值：   bool判断值
 ******************************************************************/
bool peguser::PegUser::UserRecoverPassword(std::map<std::string, std::string> data)
{
    int n = data.size();
    if (n == 1)
    {
        this->start_time=clock();
        this->verification_=MakeEmailContent(data["mailbox"], 2);
        // this->verification_=send_verification(data["tel"]);
        this->mailbox_ = data["mailbox"];
        return true;
    }
    else
    {
                this->end_time = clock();
                if (((double)((this->end_time) - (this->start_time))) > 60000)
                    return false;
                if (this->verification_ != data["verification"]){
                    std::cout<<"false"<<std::endl;
                    std::cout<<this->verification_<<std::endl;
                    std::cout << data["verification"] << std::endl;
                    return false;
                }
                std::cout << this->verification_ << std::endl;
                std::cout << data["verification"] << std::endl;
                this->user_password_ = data["password"];
                return true;
    }
}

/*****************************************************************
 * 函数名称： bool PEGUser::UserChangePassword(const std::string &new_password,const std::string &old_password)
 * 功能描述： 用户修改密码函数
 * 参数说明： 字符串，用户输入旧密码和新密码
 * 返回值：   bool判断值
 ******************************************************************/
bool peguser::PegUser::UserChangePassword(const std::string &new_password, const std::string &old_password)
{
    if (this->user_password_ != old_password)
        return false;
    this->user_password_ = new_password;
    return true;
}

/*****************************************************************
 * 函数名称： PEGUser * GetUserData(const std::string &user_id,std::vector<PEGUser *> peguser_list)
 * 功能描述： 根据用户id获得用户信息
 * 参数说明： 字符串，用户输入用户id；vector容器，为用户列表
 * 返回值：   PEGUser对象，与id对应的PEGUser对象
 ******************************************************************/
peguser::PegUser *peguser::GetUserData(const std::string &user_id, std::vector<peguser::PegUser *> peguser_list)
{
    for (auto it = peguser_list.begin(); it != peguser_list.end(); it++)
    {
        CROW_LOG_INFO << (*it)->get_user_name_();
        if ((*it)->get_user_id_() == user_id)
            return *it;
    }
}

peguser::PegUser *peguser::GetUserByMailbox(const std::string &mailbox, std::vector<peguser::PegUser *> peg_user)
{
    for (auto it = peg_user.begin(); it != peg_user.end(); it++)
    {
        if ((*it)->get_mailbox_() == mailbox){
            return *it;
        }
    }
}

/*****************************************************************
 * 函数名称： std::string NewUserId(std::vector<PEGUser *> peguser_list)
 * 功能描述： 生成新用户id函数
 * 参数说明： vector容器，为用户列表
 * 返回值：   string字符串，为生成的新用户id
 ******************************************************************/
std::string peguser::NewUserId(std::vector<peguser::PegUser *> peguser_list)
{
    srand((unsigned int)time(0));
    bool flag = false;
    std::string id;
    while (!flag)
    {
        flag = true;
        id = "";
        for (int i = 0; i < 6; i++)
        {
            id += std::to_string((rand() % 10));
        }
        for (auto it = peguser_list.begin(); it != peguser_list.end(); it++)
        {
            if ((*it)->get_user_id_() == id)
                flag = false;
        }
    }
    return id;
}

/*****************************************************************
* 函数名称： void PEGUser::NewUser(const std::string &user_name,const std::string &password,
                                  std::vector<PEGUser *> peguser_list)
* 功能描述： 将新用户加入用户列表
* 参数说明： vector容器，为用户列表；字符串，为新用户昵称和密码
* 返回值：   无返回值
******************************************************************/
void peguser::PegUser::NewUser(const std::string &user_name, const std::string &password,
                               std::vector<PegUser *> peguser_list)
{
    this->user_id_ = NewUserId(peguser_list);
    this->user_name_ = user_name;
    this->user_password_ = password;
    this->register_time_ = tool::GetTime();
}

/*****************************************************************
 * 函数名称： std::string peguser::GetUserName(const std::string &user_id,
 *                                            std::vector<peguser::PegUser *> peguser_list)
 * 功能描述：根据id获取该用户的用户名
 * 参数说明：用户id，用户列表
 * 返回值：   用户名
 ******************************************************************/
std::string peguser::GetUserName(const std::string &user_id, std::vector<peguser::PegUser *> peguser_list)
{
    for (int i = 0; i < peguser_list.size(); i++)
    {
        if (peguser_list[i]->get_user_id_() == user_id)
            return peguser_list[i]->get_user_name_();
    }
    return "null";
}

std::string peguser::GetUserIdAccordMailbox(const std::string &mailbox, std::vector<peguser::PegUser *> peguser_list){
    for (int i = 0; i < peguser_list.size(); i++)
    {
        if (peguser_list[i]->get_mailbox_() == mailbox)
            return peguser_list[i]->get_user_id_();
    }
}

    /*****************************************************************
     * 函数名称：std::string peguser::GetUserIntroduction(const std::string &user_id,
     *                                                   std::vector<peguser::PegUser *> peguser_list)
     * 功能描述： 获取用户介绍
     * 参数说明：用户id，用户列表
     * 返回值：   返回string，用户介绍
     ******************************************************************/
    std::string peguser::GetUserIntroduction(const std::string &user_id, std::vector<peguser::PegUser *> peguser_list)
{
    for (int i = 0; i < peguser_list.size(); i++)
    {
        if (peguser_list[i]->get_user_id_() == user_id)
            return peguser_list[i]->get_introduction_();
    }
    return "null";
}


/*****************************************************************
 * 函数名称： std::vector<peguser::UserInfor *> peguser::GetUserInfor(std::vector<std::string> user_list,
 *                                                                   std::vector<peguser::PegUser *> peguser_list)
 * 功能描述： 根据id返回个人简介
 * 参数说明：用户列表，peg用户列表
 * 返回值：  返回个人简介列表
 ******************************************************************/
std::vector<peguser::UserInfor *> peguser::GetUserInfor(std::vector<std::string> user_list,
                                                        std::vector<peguser::PegUser *> peguser_list)
{
    std::vector<peguser::UserInfor *> infor_list;
    for (int i = 0; i != user_list.size(); i++)
    {
        peguser::UserInfor *infor = new peguser::UserInfor;
        infor->id_ = user_list[i];
        infor->name_ = peguser::GetUserName(user_list[i], peguser_list);
        infor->introduction_ = peguser::GetUserIntroduction(user_list[i], peguser_list);
        infor_list.push_back(infor);
    }
    return infor_list;
}

/*****************************************************************
 * 函数名称：std::vector<peguser::PegUser *> peguser::SetUserForbidden(const std::string &user_id,
 *                                                                    const std::string &flag,
 *                                                                    std::vector<peguser::PegUser *> peguser_list)
 * 功能描述： 修改peguser列表中的禁用标识
 * 参数说明： 用户列表，peg用户列表
 * 返回值：   返回用户列表
 ******************************************************************/
std::vector<peguser::PegUser *> peguser::SetUserForbidden(const std::string &user_id, const std::string &flag,
                                                          std::vector<peguser::PegUser *> peguser_list)
{
    for (auto i = peguser_list.begin(); i != peguser_list.end(); i++)
    {
        if ((*i)->get_user_id_() == user_id)
        {
            (*i)->set_forbidden_(flag);
            break;
        }
    }
    return peguser_list;
}

/*****************************************************************
 * 函数名称： std::vector<peguser::PegUser *> peguser::DeleteUser(const std::string &user_id,
 *                                                               std::vector<peguser::PegUser *> peguser_list)
 * 功能描述：删除peguser列表中某个用户
 * 参数说明： 用户列表，peg用户列表
 * 返回值：   返回用户列表
 ******************************************************************/
std::vector<peguser::PegUser *> peguser::DeleteUser(const std::string &user_id,
                                                    std::vector<peguser::PegUser *> peguser_list)
{
    for (auto i = peguser_list.begin(); i != peguser_list.end(); i++)
    {
        if ((*i)->get_user_id_() == user_id)
        {
            peguser_list.erase(i);
            break;
        }
    }
    return peguser_list;
}

/*****************************************************************
 * 函数名称： std::vector<peguser::PegUser *> peguser::ResetUserPassword(
 *           const std::string &user_id,
 *           std::vector<peguser::PegUser *> peguser_list)
 * 功能描述： 重置用户密码
 * 参数说明： 用户id,用户列表
 * 返回值：   返回用户列表
 ******************************************************************/
std::vector<peguser::PegUser *> peguser::ResetUserPassword(const std::string &user_id,
                                                           std::vector<peguser::PegUser *> peguser_list)
{
    for (auto i = peguser_list.begin(); i != peguser_list.end(); i++)
    {
        if ((*i)->get_user_id_() == user_id)
        {
            (*i)->set_user_password_("111111");
            break;
        }
    }
    return peguser_list;
}

std::vector<peguser::PegUser *> peguser::PegUser::SetUserId(std::vector<PegUser *> peguser_list)
{
    for (auto i = peguser_list.begin(); i != peguser_list.end(); i++)
    {
        if ((*i)->get_mailbox_() == this->mailbox_)
        {
            (*i)->set_user_id_(this->user_id_);
            return peguser_list;
        }
    }
}

std::vector<peguser::PegUser *> peguser::PegUser::SetUserNameAndPaaword(std::vector<peguser::PegUser *> peguser_list)
{
    for (auto i = peguser_list.begin(); i != peguser_list.end(); i++)
    {
        if ((*i)->get_user_id_() == this->user_id_)
        {
            (*i)->set_user_name_(this->user_name_);
            (*i)->set_user_password_(this->user_password_);
            return peguser_list;
        }
    }
}

std::vector<peguser::PegUser *> peguser::SetUserNamePassword(const std::string &user_id, const std::string &user_name, const std::string &user_password, const std::string &register_time,std::vector<peguser::PegUser *> peguser_list)
{
    for (auto i = peguser_list.begin(); i != peguser_list.end(); i++)
    {
        if ((*i)->get_user_id_() == user_id)
        {
            (*i)->set_user_password_(user_password);
            (*i)->set_user_name_(user_name);
            (*i)->set_register_time_(tool::GetTime());
            break;
        }
    }
    return peguser_list;
}

std::vector<peguser::PegUser *> peguser::NewUserList(peguser::PegUser *user, std::vector<peguser::PegUser *> peguser_list)
{
    for(auto i=peguser_list.begin();i!=peguser_list.end();){
        if((*i)->get_mailbox_()==user->get_mailbox_()){
            peguser_list.erase(i);
            break;
        } else {
            i++;
        }
    }
    peguser_list.push_back(user);
    return peguser_list;
}