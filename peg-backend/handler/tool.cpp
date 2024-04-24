#include "tool.h"

/*****************************************************************
 * 函数名称： std::string Trim(const std::string &str)
 * 功能描述： 截取字符串
 * 参数说明： 字符串，整个字符串和划分头尾
 * 返回值：   string值，返回截取结果
 ******************************************************************/
std::string tool::Trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos)
    {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

/*****************************************************************
 * 函数名称： void OutputToFile(const std::string &filename, const std::string &content)
 * 功能描述： 将指定内容写入指定文件
 * 参数说明： 字符串，文件名和写入内容
 * 返回值：   void，无返回值
 ******************************************************************/
void tool::OutputToFile(const std::string &filename, const std::string &content)
{
    std::ofstream outfile;
    outfile.open(filename);
    if (outfile.is_open())
    {
        outfile << content;
        outfile.close();
    }
}

/*****************************************************************
 * 函数名称： std::string GetInf(const std::string &allstr, const std::string &beginstr, const std::string &endstr)
 * 功能描述： 截取字符串
 * 参数说明： 字符串，整个字符串和划分头尾
 * 返回值：   string值，返回截取结果
 ******************************************************************/
std::string tool::GetInf(const std::string &all_str, const std::string &begin_str, const std::string &end_str)
{
    std::string str = all_str;
    std::string start = begin_str;
    std::string end = end_str;

    size_t start_pos = str.find(start);
    if (start_pos != std::string::npos)
    {
        start_pos += start.length();
        size_t end_pos = str.find(end, start_pos);
        if (end_pos != std::string::npos)
        {
            std::string result = str.substr(start_pos, end_pos - start_pos);
            return result;
        }
    }
    return "can't find";
}

/*****************************************************************
 * 函数名称：std::vector<GstoreConnector *> DbIdGetNodes(std::vector<GstoreConnector *> oldservers,
 * std::vector<dbnode::DbNode *> dbnode, std::string dbid, std::vector<node::Node *> node)
 * 功能描述： 通过数据库id选取与数据库相关的节点
 * 参数说明： 全部节点的列表，数据库节点表，数据库id,节点表
 * 返回值：   vector，值为与数据库有关的节点
 ******************************************************************/

std::vector<GstoreConnector *> tool::DbIdGetNodes(std::vector<GstoreConnector *> old_servers,
                                                  std::vector<dbnode::DbNode *> dbnode_list,
                                                  const std::string &db_id,
                                                  std::vector<node::Node *> node_list)
{
    std::vector<GstoreConnector *> new_servers;
    for (int i = 0; i < dbnode_list.size(); i++)
    {
        if (dbnode_list[i]->get_database_id_() == db_id)
        {
            for (int j = 0; j < node_list.size(); j++)
            {
                if (node_list[j]->get_node_ip_() == dbnode_list[i]->get_node_ip_() &&
                    node_list[j]->get_port_() == dbnode_list[i]->get_node_port_())
                {
                    new_servers.push_back(new GstoreConnector(
                        node_list[j]->get_node_ip_(),
                        stoi(node_list[j]->get_port_()),
                        "POST",
                        node_list[j]->get_gstore_user_id_(),
                        node_list[j]->get_gstore_user_password_()));
                }
            }
        }
    }
    return new_servers;
}

/*****************************************************************
 * 函数名称：std::vector<GstoreConnector *> CreateDbGetNode(crow::json::rvalue tes,
 * std::vector<GstoreConnector *> servers, std::vector<node::Node *> Node)
 * 功能描述： 新建数据库时得到用户想要使用的节点的列表
 * 参数说明： json格式的tes，全部节点的列表，节点表
 * 返回值：   vector，值为用户选取的节点
 ******************************************************************/
std::vector<GstoreConnector *> tool::CreateDbGetNode(crow::json::rvalue tes,
                                                     std::vector<GstoreConnector *> servers,
                                                     std::vector<node::Node *> Node)
{
    std::vector<GstoreConnector *> new_servers;
    for (int i = 0; i < tes.size(); i++)
    {
        for (int j = 0; j < servers.size(); j++)
        {
            for (int k = 0; k < Node.size(); k++)
            {
                crow::json::wvalue t(tes[i]["id"]);
                std::string q = t.dump();
                int index1 = q.find_first_of("\"");
                int index2 = q.find_last_of("\"");
                std::string b(q, index1 + 1, index2 - index1 - 1);
                if (b == Node[k]->get_node_id_())
                {
                    if (servers[j]->serverIP == Node[k]->get_node_ip_() &&
                        servers[j]->serverPort == stoi(Node[k]->get_port_()))
                    {
                        new_servers.push_back(servers[j]);
                    }
                }
            }
        }
    }
    return new_servers;
}

/*****************************************************************
 * 函数名称：bool FuzzySearch(const std::string &text, const std::string &pattern)
 * 功能描述： 进行模糊查找
 * 参数说明：原字符串，准备与原字符串进行模糊匹配的字符串
 * 返回值：  bool类型，返回信息为两个字符串是否模糊匹配
 ******************************************************************/
bool tool::FuzzySearch(const std::string &text, const std::string &pattern)
{
    std::string lower_text = text;
    std::string lower_pattern = pattern;
    std::transform(lower_text.begin(), lower_text.end(), lower_text.begin(), towlower);
    std::transform(lower_pattern.begin(), lower_pattern.end(), lower_pattern.begin(), towlower);

    size_t pos = 0;
    for (wchar_t c : lower_pattern)
    {
        pos = lower_text.find(c, pos);
        if (pos == std::wstring::npos)
        {
            return false;
        }
        pos++;
    }
    return true;
}

/*****************************************************************
 * 函数名称：bool CheckNode(std::vector<GstoreConnector *> &servers,const std::string &node_ip,
 * const std::string &node_port)
 * 功能描述： 检查节点是否处于开启状态
 * 参数说明：节点列表，节点ip,节点端口
 * 返回值：  bool类型，返回信息为节点是否处于开启状态
 ******************************************************************/
bool tool::CheckNode(std::vector<GstoreConnector *> &servers,
                     const std::string &node_ip, const std::string &node_port)
{
    int part = servers.size();
    for (int i = 0; i < part; i++)
    {
        if (servers[i]->serverIP == node_ip && servers[i]->serverPort == stoi(node_port))
        {
            std::string result = servers[i]->check();
            if (result == "")
                return false;
            break;
        }
    }
    return true;
}

/*****************************************************************
 * 函数名称：void NewServersDelete(std::vector<GstoreConnector *> servers)
 * 功能描述： 删除节点
 * 参数说明：节点列表
 * 返回值：  void,无返回值
 ******************************************************************/
void tool::NewServersDelete(std::vector<GstoreConnector *> servers)
{
    for (int i = 0; i < servers.size(); i++)
    {
        delete servers[i];
    }
}

/*****************************************************************
 * 函数名称：bool isValidNumber(const std::string &str)
 * 功能描述： 检查是否含有非法字符
 * 参数说明：待检查的字符串
 * 返回值：  bool类型，返回是否含有非法字符
 ******************************************************************/
bool tool::IsValidNumber(const std::string &str)
{
    return !str.empty() && str.find_first_not_of("0123456789") == std::string::npos;
}

/*****************************************************************
 * 函数名称：std::string ConvertDateTimeFormat(const std::string &input_date_time)
 * 功能描述：转换日期格式
 * 参数说明：待转换的字符串
 * 返回值： string类型，返回转换后的字符串
 ******************************************************************/
std::string tool::ConvertDateTimeFormat(const std::string &input_date_time)
{
    std::stringstream ss(input_date_time);
    std::string year, month, day, hour, minute, second;
    std::getline(ss, year, '-');
    std::getline(ss, month, '-');
    std::getline(ss, day, '-');
    std::getline(ss, hour, '-');
    std::getline(ss, minute, '-');
    ss >> second;

    if (!IsValidNumber(year) || !IsValidNumber(month) || !IsValidNumber(day) ||
        !IsValidNumber(hour) || !IsValidNumber(minute) || !IsValidNumber(second))
    {
        return "Invalid input format";
    }

    int year_int, month_int, day_int, hour_int, minute_int, second_int;
    std::stringstream(year) >> year_int;
    std::stringstream(month) >> month_int;
    std::stringstream(day) >> day_int;
    std::stringstream(hour) >> hour_int;
    std::stringstream(minute) >> minute_int;
    std::stringstream(second) >> second_int;

    std::stringstream result;
    result << std::setw(2) << std::setfill('0') << (year_int % 100)
           << std::setw(2) << std::setfill('0') << month_int
           << std::setw(2) << std::setfill('0') << day_int
           << std::setw(2) << std::setfill('0') << hour_int
           << std::setw(2) << std::setfill('0') << minute_int
           << std::setw(2) << std::setfill('0') << second_int;

    return result.str();
}

/*****************************************************************
 * 函数名称：std::string EnCode()
 * 功能描述：进行编码
 * 参数说明：无
 * 返回值： string类型，返回编码后的token值
 ******************************************************************/
std::string tool::EnCode()
{
    srand(time(0));
    // 48-57 为 0-9  65-90 A-Z 97-122 a-z
    // 生成一个长度为12的字符串作为token。
    std::string token;
    for (int i = 0; i < 20; i++)
    {
        int choose = rand() % 3;
        int q = 0;
        char b;
        if (choose == 0)
        {
            q = rand() % 10;
            b = 48 + q;
            token.push_back(b);
        }
        if (choose == 1)
        {
            q = rand() % 26;
            b = 65 + q;
            token.push_back(b);
        }
        if (choose == 2)
        {
            q = rand() % 26;
            b = 97 + q;
            token.push_back(b);
        }
    }
    return token;
}

/*****************************************************************
 * 函数名称：std::vector<node::Node *> NodeDisplayByDbId(const std::string &db_id,
 * std::vector<node::Node *> node_list,
 * std::vector<dbnode::DbNode *> dbnode_list)
 * 功能描述：得到与数据库有关的节点
 * 参数说明：数据库id,节点列表，数据库节点表
 * 返回值：vector类型，返回节点列表
 ******************************************************************/
std::vector<node::Node *> tool::NodeDisplayByDbId(const std::string &db_id, std::vector<node::Node *> node_list,
                                                  std::vector<dbnode::DbNode *> dbnode_list)
{
    std::vector<node::Node *> specific_nodelist;
    for (int i = 0; i < dbnode_list.size(); i++)
    {
        if (dbnode_list[i]->get_database_id_() == db_id)
        {
            for (int j = 0; j < node_list.size(); j++)
            {
                if ((dbnode_list[i]->get_node_ip_() == node_list[j]->get_node_ip_())&&dbnode_list[i]->get_node_port_() == node_list[j]->get_port_())
                {
                    node::Node *node = new node::Node;
                    node->set_node_id_(node_list[j]->get_node_id_());
                    node->set_node_ip_(node_list[j]->get_node_ip_());
                    node->set_port_(node_list[j]->get_port_());
                    specific_nodelist.push_back(node);
                }
            }
        }
    }
    return specific_nodelist;
}

/*****************************************************************
 * 函数名称：std::string StrSplitId(const std::string &str, const std::string &split)
 * 功能描述：从发来的信息中找到id（包括from和to）,已知id为6位字符串
 * 参数说明：原字符串，要分割的字符串
 * 返回值：string类型，返回id
 ******************************************************************/
std::string tool::StrSplitId(const std::string &str, const std::string &split)
{
    std::string strs = str;
    size_t pos = strs.find(split); // 找到分割字符串的位置
    int step = split.size();
    if (pos != strs.npos)
    {
        std::string result = strs.substr(pos + step, 6);
        return result;
    }
}

/*****************************************************************
 * 函数名称：std::string StrSplitContent(const std::string &str)
 * 功能描述：从发来的信息中找到实际内容
 * 参数说明：原字符串
 * 返回值：string类型，返回实际内容
 ******************************************************************/
std::string tool::StrSplitContent(const std::string &str)
{
    std::string strs = str;
    std::string split = "value:";
    size_t pos = strs.find(split); // 找到分割字符串的位置
    int step = split.size();
    if (pos != strs.npos)
    {
        std::string result = strs.substr(pos + step);
        return result;
    }
}

/*****************************************************************
 * 函数名称：std::string IntToString(const int &num)
 * 功能描述：将int转为string
 * 参数说明：原int值
 * 返回值：string类型，返回转换后的字符串
 ******************************************************************/
std::string tool::IntToString(const int &num)
{
    std::string str;
    std::stringstream ss;
    ss << num;
    ss >> str;
    ss.clear();
    return str;
}

/*****************************************************************
 * 函数名称：int StringToInt(const std::string &str)
 * 功能描述：将string转为int
 * 参数说明：原string值
 * 返回值：int类型，返回转换后的整型
 ******************************************************************/
int tool::StringToInt(const std::string &str)
{
    int num;
    std::stringstream ss;
    ss << str;
    ss >> num;
    ss.clear();
    return num;
}

/*****************************************************************
 * 函数名称：std::string GetTime()
 * 功能描述：获取当前时间转换为字符串
 * 参数说明：无
 * 返回值：string类型，返回转换后的字符串
 ******************************************************************/
std::string tool::GetTime()
{
    time_t now_time = time(NULL);
    tm *ltm = localtime(&now_time);
    std::string local_time = std::to_string(ltm->tm_year + 1900) + "-" + std::to_string(ltm->tm_mon + 1) + "-";
    local_time += std::to_string(ltm->tm_mday) + "-" + std::to_string(ltm->tm_hour) + "-";
    local_time += std::to_string(ltm->tm_min) + "-" + std::to_string(ltm->tm_sec);
    return local_time;
}

/*****************************************************************
 * 函数名称：std::string AddTwo(int &num1, int &num2)
 * 功能描述：将两个int相加
 * 参数说明：两个int
 * 返回值：string类型，返回相加并转换后的字符串
 ******************************************************************/
std::string tool::AddTwo(int &num1, int &num2)
{
    return IntToString(num1 + num2);
}

/*****************************************************************
 * 函数名称：tm *GetTimeStruct(const std::string &time_str)
 * 功能描述：将传入的字符串分割成tm类型
 * 参数说明：要分割的字符串
 * 返回值：tm类型，分割后的值
 ******************************************************************/
tm *tool::GetTimeStruct(const std::string &time_str)
{
    struct tm *it_tm = new tm;
    std::string format = "%Y-%m-%d-%H-%M-%S";
    strptime(time_str.c_str(), format.c_str(), it_tm);
    it_tm->tm_isdst = 0;
    return it_tm;
}

/*****************************************************************
 * 函数名称：tm *GetThreeDaysAgoTime()
 * 功能描述：返回当前时间三天前的时间
 * 参数说明：无
 * 返回值：tm类型，三天前的时间
 ******************************************************************/
tm *tool::GetThreeDaysAgoTime()
{
    time_t now_time = time(NULL);
    tm *ltm = localtime(&now_time);
    struct tm *three_days_ago = new tm;
    if (ltm->tm_mon == 0 && ltm->tm_mday <= 3)
    { // 跨年
        three_days_ago->tm_year = ltm->tm_year - 1;
        three_days_ago->tm_mon = 11;
        three_days_ago->tm_mday = 31 - (3 - ltm->tm_mday);
    }
    else if (ltm->tm_mday <= 3)
    { // 跨月
        three_days_ago->tm_year = ltm->tm_year;
        three_days_ago->tm_mon = ltm->tm_mon;
        if (ltm->tm_mon == 1 || ltm->tm_mon == 3 || ltm->tm_mon == 5 || ltm->tm_mon == 7 || ltm->tm_mon == 8 || ltm->tm_mon == 10)
        {
            three_days_ago->tm_mday = 31 - (3 - ltm->tm_mday);
        }
        else if (ltm->tm_mon == 2)
        {
            // 判断该年是否为闰年
            if (((ltm->tm_year + 1900) % 4 == 0 && (ltm->tm_year + 1900) % 100 != 0) ||
                (ltm->tm_year + 1900) % 400 == 0)
                three_days_ago->tm_mday = 29 - (3 - ltm->tm_mday);
            else
                three_days_ago->tm_mday = 28 - (3 - ltm->tm_mday);
        }
        else
        {
            three_days_ago->tm_mday = 30 - (3 - ltm->tm_mday);
        }
    }
    else
    {
        three_days_ago->tm_year = ltm->tm_year;
        three_days_ago->tm_mon = ltm->tm_mon;
        three_days_ago->tm_mday = ltm->tm_mday - 3;
    }
    three_days_ago->tm_hour = ltm->tm_hour;
    three_days_ago->tm_min = ltm->tm_min;
    three_days_ago->tm_sec = ltm->tm_sec;
    return three_days_ago;
}

std::string tool::extractAndFormatTimestamp(const std::string &input)
{
    std::regex timestampRegex(R"(\d{12})"); // 匹配12位数字作为时间戳
    std::smatch match;

    if (std::regex_search(input, match, timestampRegex))
    {
        std::string timestamp = "20" + match.str(); // 在时间戳前面加上"20"
        // 将时间戳转换为指定格式
        std::string formattedTimestamp = timestamp.substr(0, 4) + "-" + timestamp.substr(4, 2) + "-" + timestamp.substr(6, 2) + "-" + timestamp.substr(8, 2) + "-" + timestamp.substr(10, 2) + "-" + timestamp.substr(12, 2);
        return formattedTimestamp;
    }
}

bool tool::CheckUnlawful(std::vector<std::string> str_list){
    for(int i=0;i<str_list.size();i++){
    size_t pos = str_list[i].find("'");
    if(pos!=str_list[i].npos) return true;
    }
    return false;
}