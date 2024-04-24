
/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       tools.h
 * @brief      the Tools
 * @descripition
 * 函数：
* std::string Trim(const std::string &str);
* 截取字符串
* void OutputToFile(const std::string &filename, const std::string &content);
* 输出文件
* std::string GetInf(const std::string &allstr, const std::string &beginstr, const std::string &endstr);
* 获取信息
* std::vector<GstoreConnector *> DbIdGetNodes(std::vector<GstoreConnector *> oldservers,
std::vector<dbnode::DbNode *> dbnode, std::string dbid,
std::vector<node::Node *> node);
* 选择节点
* std::vector<GstoreConnector *> CreateDbGetNode(crow::json::rvalue tes, std::vector<GstoreConnector *> servers,
std::vector<node::Node *> Node);
* 创建数据库时选择节点
* bool FuzzySearch(const std::string &text, const std::string &pattern);
* 模糊查询
* bool CheckNode(std::vector<GstoreConnector *> &servers,
               const std::string &node_ip, const std::string &node_port);
* 检查节点
* void NewServersDelete(std::vector<GstoreConnector *> servers);
* 删除节点
* bool isValidNumber(const std::string &str);
* 判断字符串合法性
* std::string ConvertDateTimeFormat(const std::string &input_date_time);
* 转换日期格式
* std::string EnCode();
* 编码
* std::vector<node::Node *> NodeDisplayByDbId(const std::string &db_id, std::vector<node::Node *> node_list,
std::vector<dbnode::DbNode *> dbnode_list);
* 根据数据库id展示相关节点
* std::string StrSplitId(const std::string &str, const std::string &split);
* 分割字符串得到id
* std::string StrSplitContent(const std::string &str);
* 分割字符串得到内容
* std::string IntToString(const int &num);
* int转为string
* int StringToInt(const std::string &str);
* string转为int
* std::string GetTime();
* 获取当前时间
* std::string AddTwo(int &num1, int &num2);
* 将两个整形相加
* tm *GetTimeStruct(const std::string &time_str);
* 获取tm格式的时间
* tm *GetThreeDaysAgoTime();
 *获取三天前时间
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef TOOLS_H_
#define TOOLS_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "crow.h"
#include "node.h"
#include "dbnode.h"
#include <sstream>
#include <string>

namespace tool
{
    std::string Trim(const std::string &str);

    void OutputToFile(const std::string &file_name, const std::string &content);

    std::string GetInf(const std::string &all_str, const std::string &begin_str, const std::string &end_str);

    std::vector<GstoreConnector *> DbIdGetNodes(std::vector<GstoreConnector *> old_servers,
                                                std::vector<dbnode::DbNode *> dbnode_list, const std::string &db_id,
                                                std::vector<node::Node *> node_list);

    std::vector<GstoreConnector *> CreateDbGetNode(crow::json::rvalue tes, std::vector<GstoreConnector *> servers,
                                                   std::vector<node::Node *> node_list);

    bool FuzzySearch(const std::string &text, const std::string &pattern);

    bool CheckNode(std::vector<GstoreConnector *> &servers,
                   const std::string &node_ip, const std::string &node_port);

    void NewServersDelete(std::vector<GstoreConnector *> servers);

    bool IsValidNumber(const std::string &str);

    std::string ConvertDateTimeFormat(const std::string &input_date_time);

    std::string EnCode();

    std::vector<node::Node *> NodeDisplayByDbId(const std::string &db_id, std::vector<node::Node *> node_list,
                                                std::vector<dbnode::DbNode *> dbnode_list);
    std::string StrSplitId(const std::string &str, const std::string &split);
    std::string StrSplitContent(const std::string &str);
    std::string IntToString(const int &num);
    int StringToInt(const std::string &str);
    std::string GetTime();
    std::string AddTwo(int &num1, int &num2);
    tm *GetTimeStruct(const std::string &time_str);
    tm *GetThreeDaysAgoTime();
    std::string extractAndFormatTimestamp(const std::string &input);
    bool CheckUnlawful(std::vector<std::string> str_list);
}
#endif // TOOLS_H_