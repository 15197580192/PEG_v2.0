#include "chat.h"

chat::Chat::Chat()
{
    this->source_user_id_ = "0";
    this->source_user_name_ = "0";
    this->dest_user_id_ = "0";
    this->dest_user_name_ = "0";
    this->content_ = "0";
    this->send_time_ = "0";
    this->read_flag_ = "0";
}
/*****************************************************************
 * 函数名称： bool chat::CmpByTime(chat::ChatHistory *history1, chat::ChatHistory *history2)
 * 功能描述： 自定义排序规则，先根据id排序，id相同的根据时间排序
 * 参数说明： 记录结构体
 * 返回值：   判断值
 ******************************************************************/
bool chat::CmpByTime(chat::Chat *chat1, chat::Chat *chat2)
{
    tm *time1 = tool::GetTimeStruct(chat1->get_send_time_());
    tm *time2 = tool::GetTimeStruct(chat2->get_send_time_());
    std::time_t time1_t = std::mktime(time1);
    std::time_t time2_t = std::mktime(time2);
    return time1_t > time2_t;
}

bool FindUserId(std::vector<chat::ChatHistory *> chat_history, const std::string &user_id)
{
    for (auto it = chat_history.begin(); it != chat_history.end(); it++)
    {
        if ((*it)->role_id_ == user_id)
            return true;
    }
    return false;
}

std::vector<chat::ChatHistory *> PushChatLog(chat::Chat *chat, const std::string &user_id, std::vector<chat::ChatHistory *> chat_history)
{
    for (auto it = chat_history.begin(); it != chat_history.end(); it++)
    {
        if ((*it)->role_id_ == user_id)
        {
            (*it)->chat_list_.push_back(chat);
            return chat_history;
        }
    }
}

/*****************************************************************
 * 函数名称： std::vector<chat::ChatHistory *> chat::GetChatHistory(const std::string &user_id,std::vector<chat::Chat *>chat_list)
 * 功能描述： 根据一个人的id获取他的所有聊天信息，按照id和发送时间排序
 * 参数说明： 字符串用户id，vector的聊天列表
 * 返回值：   返回vector类型的聊天记录结构体
 ******************************************************************/
std::vector<chat::ChatHistory *> chat::GetChatHistory(const std::string &user_id,
                                                      std::vector<chat::Chat *> chat_list)
{
    std::vector<chat::ChatHistory *> chat_history; // 获取所有聊天记录
    for (int i = 0; i < chat_list.size(); i++)
    {
        if (chat_list[i]->get_source_user_id_() == user_id) // user_id是登录者
        {
            if (!FindUserId(chat_history, chat_list[i]->get_dest_user_id_()))
            {
                chat::ChatHistory *chat_log = new chat::ChatHistory;
                chat_log->role_id_ = chat_list[i]->get_dest_user_id_();
                chat_log->chat_list_.push_back(chat_list[i]);
                chat_history.push_back(chat_log);
            }
            else
            {
                chat_history = PushChatLog(chat_list[i], chat_list[i]->get_dest_user_id_(), chat_history);
            }
        }
        else if (chat_list[i]->get_dest_user_id_() == user_id)
        {
            if (!FindUserId(chat_history, chat_list[i]->get_source_user_id_()))
            {
                chat::ChatHistory *chat_log = new chat::ChatHistory;
                chat_log->role_id_ = chat_list[i]->get_source_user_id_();
                chat_log->chat_list_.push_back(chat_list[i]);
                chat_history.push_back(chat_log);
            }
            else
            {
                chat_history = PushChatLog(chat_list[i], chat_list[i]->get_source_user_id_(), chat_history);
            }
        }
    }
    return chat_history;
}

/*****************************************************************
 * 函数名称： std::vector<chat::ChatHistory *> chat::GetLatelyChat(std::vector<chat::ChatHistory *> chat_history)
 * 功能描述： 获取每个用户发送的最新的一条消息
 * 参数说明： vector类型的的ChatHistory结构体
 * 返回值：   返回vector类型的聊天记录结构体
 ******************************************************************/
std::map<std::string, chat::Chat *> chat::GetLatelyChat(std::vector<chat::ChatHistory *> chat_history)
{
    std::map<std::string, chat::Chat *> lately_chat;
    std::string user_id;
    for (auto i = chat_history.begin(); i != chat_history.end(); i++)
    {
        std::vector<chat::Chat *> chat_temp = (*i)->chat_list_;
        sort(chat_temp.begin(), chat_temp.end(), CmpByTime);
        lately_chat.insert(std::pair<std::string, chat::Chat *>((*i)->role_id_, chat_temp[0]));
    }
    return lately_chat;
}

/*****************************************************************
 * 函数名称： std::vector<chat::Chat *> chat::GetOneUserChat(const std::string &dest_id,std::vector<chat::ChatHistory *> chat_history)
 * 功能描述： 获得两个人全部的聊天记录
 * 参数说明： 字符串类型的发送人id,vector类型的的ChatHistory结构体
 * 返回值：   返回vector类型的聊天记录
 ******************************************************************/
std::vector<chat::Chat *> chat::GetOneUserChat(const std::string &dest_id,
                                               std::vector<chat::ChatHistory *> chat_history)
{
    for (auto i = chat_history.begin(); i != chat_history.end(); i++)
    {
        if ((*i)->role_id_ == dest_id)
        {
            int chat_num = (*i)->chat_list_.size();
            std::vector<chat::Chat *> user_chat = (*i)->chat_list_;
            for (int j = 0; j < chat_num; j++)
            {
                if (user_chat[j]->get_source_user_id_() == dest_id)
                { // 这条消息是对方发过来的
                    if (user_chat[j]->get_read_flag_() == "0")
                    {
                        user_chat[j]->set_read_flag_("1"); // 将该条消息设置为已读
                    }
                }
            }
            return user_chat;
        }
    }
}

// 创建socket环境
int chat::GetServer(const std::string &user_id)
{
    struct sockaddr_in server_sockaddr;
    int server_sd;
    int con_rv;
    server_sd = socket(AF_INET, SOCK_STREAM, 0); // 定义sockfd
    if (server_sd == -1)
    {
        printf("socket create error:%s \n", strerror(errno));
        return ERRORCODE;
    }
    char buf[BUFFSIZE];
    memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    server_sockaddr.sin_port = htons(8023);                   // 为该服务端绑定端口
    server_sockaddr.sin_family = AF_INET;                     // 设置结构类型为TCP/IP
    server_sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 连接ip
    con_rv = connect(server_sd, (struct sockaddr *)&server_sockaddr,
                     sizeof(server_sockaddr)); // 连接到服务器
    if (con_rv == -1)
    {
        close(server_sd);
        printf("socket create error:%s \n", strerror(errno));
        exit(1);
        std::cout << "连接服务器失败" << std::endl;
        return -1;
    }
    else
    {
        return server_sd;
    }
}

// 发消息到服务器
int chat::SendToServer(const std::string &source_user_id, const std::string &dest_user_id,
                       const std::string &content, int &server_fd)
{
    std::string chat = "---type:message  fromid:";
    chat += source_user_id;
    chat += " toid:";
    chat += dest_user_id;
    chat += " value:";
    chat += content;
    // 发送信息内容到服务器
    send(server_fd, chat.c_str(), strlen(chat.c_str()), 0);
}

// 告诉服务器该用户上线了
void chat::TellConnect(const std::string &user_id, int &server_fd)
{
    std::string content = "client_connect-----";
    content += "id:";
    content += user_id;
    send(server_fd, content.c_str(), strlen(content.c_str()), 0);
}

void chat::TellCloseConnect(const std::string &user_id, int &server_fd)
{
    std::string content = "client_quit";
    send(server_fd, content.c_str(), strlen(content.c_str()), 0);
}

// 接收消息的线程
void chat::RecvMessage(std::mutex &mtx, std::map<std::string, std::vector<chat::ChatHistory *>> &user_chatlist, int &server_fd, std::vector<peguser::PegUser *> peguser_list)
{
    char buffer[1024];
    bool flag = true;
    while (flag)
    {
        int len = recv(server_fd, buffer, sizeof(buffer), 0);
        if (len == 0)
        {
            flag = false;
        }
        else
        {
            std::unique_lock<std::mutex> lock(mtx);
            std::string source_id = tool::StrSplitId(buffer, "fromid:");
            std::string dest_id = tool::StrSplitId(buffer, "toid:");
            std::string value = tool::StrSplitContent(buffer);
            chat::Chat *new_chat = new chat::Chat;
            new_chat->NewChat(source_id, dest_id, value, peguser_list);
            for (auto it = user_chatlist.begin(); it != user_chatlist.end(); it++)
            {  
                if (it->first == dest_id)//指该用户id，就是自己
                {
                    // 返回一个vector<chathistory>
                    it->second = chat::UpdateChatHistory(source_id, it->second, new_chat);
                    break;
                }
            }
            mtx.unlock();
        }
    }
    std::cout << "线程已结束" << std::endl;
}

/*****************************************************************
 * 函数名称：  void chat::Chat::NewChat(const std::string &source_id,const std::string &dest_id,const std::string &content,
               std::vector<peguser::PegUser *>peguser_list)
 * 功能描述： 新建一条信息，方便后续插入到表和vector
 * 参数说明： 字符串类型的发送者id和接收者id，内容，vector类型的peg用户列表
 * 返回值：   无返回值
 ******************************************************************/
void chat::Chat::NewChat(const std::string &source_id, const std::string &dest_id, const std::string &content,
                         std::vector<peguser::PegUser *> peguser_list)
{
    std::string source_name = peguser::GetUserName(source_id, peguser_list);
    std::string dest_name = peguser::GetUserName(dest_id, peguser_list);
    this->source_user_id_ = source_id;
    this->source_user_name_ = source_name;
    this->dest_user_id_ = dest_id;
    this->dest_user_name_ = dest_name;
    this->content_ = content;
    time_t now_time = time(NULL);
    tm *ltm = localtime(&now_time);
    std::string send_time = std::to_string(ltm->tm_year + 1900) + "-" + std::to_string(ltm->tm_mon + 1) + "-" + std::to_string(ltm->tm_mday) + "-";
    send_time += std::to_string(ltm->tm_hour) + "-" + std::to_string(ltm->tm_min) + "-" + std::to_string(ltm->tm_sec);
    this->send_time_ = send_time;
    this->read_flag_ = "0";
}

std::vector<chat::ChatHistory *> chat::UpdateChatHistory(const std::string &user_id, std::vector<chat::ChatHistory *> chat_list, chat::Chat *chat)
{
    for (auto i = chat_list.begin(); i != chat_list.end(); i++)
    {
        if ((*i)->role_id_ == user_id)
        {
            (*i)->chat_list_.push_back(chat);
            sort((*i)->chat_list_.begin(), (*i)->chat_list_.end(), chat::CmpByTime);
            return chat_list;
        }
    }
    chat::ChatHistory *new_chat=new chat::ChatHistory;
    new_chat->role_id_=user_id;
    new_chat->chat_list_.push_back(chat);
    chat_list.push_back(new_chat);
    return chat_list;
}
