/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       peglog.h
 * @brief      the PegLog class
 * @descripition
 *
 *  名字空间内的成员函数：
 *  std::vector<PegLog *> PegLogDisplayByUserid(const std::string &user_id, std::vector<PegLog *> peglog_data)
    std::vector<PegLog *> PegLogFuzzyFind(const std::string &strtofind, std::vector<PegLog *> peglog_data)
    void NewPegLog(const std::string &peguser_id, const std::string &peg_things)
 *
 *
 *  成员变量：
 *  std ::string peg_user_id_  peg用户id
    std ::string peg_time_     时间
    std ::string peg_things_   事件
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef PEGLOG_H_
#define PEGLOG_H_
#include <iostream>
#include <vector>
#include "tool.h"

namespace peglog
{
    class PegLog
    {
    public:
        PegLog();
        inline void set_peg_user_id_(const std::string &peguserid)
        {
            this->peg_user_id_ = peguserid;
        }

        inline void set_peg_time_(const std::string &pegtime)
        {
            this->peg_time_ = pegtime;
        }

        inline void set_peg_things_(const std::string &pegthings)
        {
            this->peg_things_ = pegthings;
        }

        inline std::string get_peg_user_id_()
        {
            return this->peg_user_id_;
        }

        inline std::string get_peg_time_()
        {
            return this->peg_time_;
        }

        inline std::string get_peg_things_()
        {
            return this->peg_things_;
        }

        void NewPegLog(const std::string &peguser_id, const std::string &peg_things);

    private:
        std ::string peg_user_id_;
        std ::string peg_time_;
        std ::string peg_things_;
    };
    std::vector<PegLog *> PegLogDisplayByUserid(const std::string &user_id, std::vector<PegLog *> peglog_data);
    std::vector<PegLog *> PegLogFuzzyFind(const std::string &strtofind, std::vector<PegLog *> peglog_data);
}
#endif