#include "peglog.h"
//构造函数
peglog::PegLog::PegLog(){
    this->peg_user_id_="0";
    this->peg_time_="0";
    this->peg_things_="0";
}
/*****************************************************************
 * 函数名称： void peglog::PegLog::NewPegLog(const std::string &peguser_id, const std::string &peg_things)
 * 功能描述： 赋值peg日志项
 * 参数说明： 字符串类型的peg用户id,事件
 * 返回值：   无
 ******************************************************************/
void peglog::PegLog::NewPegLog(const std::string &peguser_id, const std::string &peg_things)
{
    this->peg_user_id_ = peguser_id;
    this->peg_things_ = peg_things;
    time_t now_time = time(NULL);
    tm *ltm = localtime(&now_time);
    std::string peg_time = std::to_string(ltm->tm_year + 1900) + "-" + std::to_string(ltm->tm_mon + 1) + "-";
    peg_time += std::to_string(ltm->tm_mday) + "-"+std::to_string(ltm->tm_hour) + "-" ;
    peg_time += std::to_string(ltm->tm_min) + "-" + std::to_string(ltm->tm_sec);
    this->peg_time_ = peg_time;
}
/*****************************************************************
 * 函数名称： std::vector<peglog::PegLog *> peglog::PegLogDisplayByUserid(const std::string &user_id, 
 *                                                                       std::vector<peglog::PegLog *> peglog_data)
 * 功能描述： 通过用户id查询日志
 * 参数说明： 字符串类型的peg用户id，vector类型的peg日志列表
 * 返回值：   查询后的peg日志列表
 ******************************************************************/
std::vector<peglog::PegLog *> peglog::PegLogDisplayByUserid(const std::string &user_id, 
                                                            std::vector<peglog::PegLog *> peglog_data)
{
    for (int i = 0; i < peglog_data.size(); i++)
    {
        if (peglog_data[i]->get_peg_user_id_() != user_id)
        {
            peglog_data.erase(peglog_data.begin() + i);
            i--;
        }
    }

    return peglog_data;
}
/*****************************************************************
 * 函数名称： std::vector<peglog::PegLog *> peglog::PegLogFuzzyFind(const std::string &strtofind, 
 *                                                                 std::vector<peglog::PegLog *> peglog_data)
 * 功能描述： 模糊查找
 * 参数说明： 字符串类型的查找元素，vector类型的peg日志列表
 * 返回值：   查询后的peg日志列表
 ******************************************************************/
std::vector<peglog::PegLog *> peglog::PegLogFuzzyFind(const std::string &strtofind, 
                                                      std::vector<peglog::PegLog *> peglog_data)
{
    for (int i = 0; i < peglog_data.size(); i++)
    {
        if (!tool::FuzzySearch(peglog_data[i]->get_peg_things_(), strtofind))
        {
            peglog_data.erase(peglog_data.begin() + i);
            i--;
        }
    }

    return peglog_data;
}