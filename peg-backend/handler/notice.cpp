#include "notice.h"
//构造函数
Notice::Notice(){
    this->creater_id_="0";
    this->create_time_="0";
    this->content_="0";
    this->notice_topic_="0";
    this->notice_id_=0;
}
/*****************************************************************
 * 函数名称： void Notice::NewNotice(const std::string &creater_id, const std::string &content, 
 *                                  const std::string &notice_topic)
 * 功能描述： 赋值公告类
 * 参数说明： 字符串类型的创建者id,内容,公告标题
 * 返回值：   无
 ******************************************************************/
void Notice::NewNotice(const std::string &creater_id, const std::string &content, const std::string &notice_topic)
{
    this->creater_id_ = creater_id;
    this->content_ = content;
    this->notice_topic_ = notice_topic;
    this->create_time_ = tool::GetTime();
}