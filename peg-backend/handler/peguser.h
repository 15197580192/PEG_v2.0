/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       peguser.h
 * @brief      the PEGUser class
 * @descripition
 *
 *  名字空间内的成员函数：
 *  void UserModify(const std::string &user_id,const std::string &user_name,const std::string &tel,
                     const std::string &introduction,const std::string &birthday,const std::string &location,
                     const std::string &mailbox,const std::string &sex,const std::string &adress);
 *   修改某个用户信息函数
 *   bool UserEnroll(const std::string &key,const std::string &value,std::vector<PEGUser *> peg_user);
 *   用户注册函数，分为发送验证码和验证验证码两个分支
 *   void NewUser(const std::string &user_name,const std::string &password,std::vector<PEGUser *> peg_user);
 *   新建用户函数
 *   void MakeEmailContent(const std::string &mailbox,const int &type);
 *   生成验证码函数
 *   bool UserRecoverPassword(std::map<std::string,std::string> data);
 *   用户重置密码函数
 *   bool UserChangePassword(const std::string &new_password,const std::string &old_password);
 *   用户修改密码函数
 *
 *
 * 非成员函数：
 * std::vector<PegUser *> UserDataModify(std::vector<PegUser *> peg_user,PegUser *user);
 * 修改用户信息函数，将修改后的用户更新在用户列表中
 * PegUser * GetUserData(const std::string &user_id,std::vector<PegUser *> peg_user);
 * 获取用户数据
 * std::string NewUserId(std::vector<PegUser *> peg_user);
 * 生成新用户id函数
 * std::string GetUserName(const std::string &user_id,std::vector<PegUser *> peg_user);
 * 获取用户名字
 * std::string GetUserIntroduction(const std::string &user_id,std::vector<PegUser *> peg_user);
 * 获取用户介绍
 * IpPort * GetIpPort(const std::string &user_id, std::vector<PegUser *> peguser_list);
 * 获取IP端口
 * std::vector<UserInfor *> GetUserInfor(std::vector<std::string> user_list,std::vector<PegUser *> peguser_list);
 * 获取用户信息
 * std::vector<PegUser *> SetUserForbidden(const std::string &user_id,const std::string &flag,
 *                                         std::vector<PegUser *> peguser_list);
 * 设置用户禁用
 * std::vector<PegUser *> DeleteUser(const std::string &user_id,std::vector<PegUser *> peguser_list);
 * 删除用户
 * std::vector<PegUser *> ResetUserPassword(const std::string &user_id,std::vector<PegUser *> peguser_list);
 * 重置密码

 *  成员变量：
 *   std::string user_id_ 用户id
 *   std::string user_name_ 用户昵称
 *   std::string user_password_ 用户密码
 *   std::string tel_ 用户电话号码
 *   std::string register_time_ 用户注册时间
 *   std::string forbidden_ 用户权限（是否被禁用）
 *   std::string birthday_ 用户生日
 *   std::string introduction_ 用户个人简介
 *   std::string location_ 用户所属国家地区
 *   std::string mailbox_ 用户邮箱
 *   std::string sex_ 用户性别
 *   std::string adress_ 用户地址
 *   std::string verification_ 用户注册验证码
 *   clock_t start_time 用户注册时发送验证码时间
 *   clock_t end_time 用户注册时输入验证码时间
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef PEGUSER_H_
#define PEGUSER_H_

#include <iostream>
#include <string>
#include <vector>
#include "../sendcapt/sendcaptcha.h"
#include "tool.h"

namespace peguser
{
    class PegUser
    {
    public:
        PegUser();
        inline std::string get_user_id_();
        inline std::string get_user_name_();
        inline std::string get_user_password_();
        inline std::string get_tel_();
        inline std::string get_register_time_();
        inline std::string get_forbidden_();
        inline std::string get_birthday_();
        inline std::string get_introduction_();
        inline std::string get_location_();
        inline std::string get_mailbox_();
        inline std::string get_sex_();
        inline std::string get_adress_();
        inline std::string get_delete_();
        inline void set_user_id_(const std::string &user_id);
        inline void set_user_name_(const std::string &user_name);
        inline void set_user_password_(const std::string &user_password);
        inline void set_tel_(const std::string &tel);
        inline void set_register_time_(const std::string &register_time);
        inline void set_forbidden_(const std::string &forbidden);
        inline void set_birthday_(const std::string &birthday);
        inline void set_introduction_(const std::string &introduction);
        inline void set_location_(const std::string &location);
        inline void set_mailbox_(const std::string &mailbox);
        inline void set_sex_(const std::string &sex);
        inline void set_adress_(const std::string &adress);
        inline void set_delete_(const std::string &flag);

        void UserModify(const std::string &user_id, const std::string &user_name, const std::string &tel,
                        const std::string &introduction, const std::string &birthday, const std::string &location,
                        const std::string &mailbox, const std::string &sex, const std::string &adress);
        bool UserEnroll(std::map<std::string, std::string> key_value, std::vector<PegUser *> peguser_list);
        void NewUser(const std::string &user_name, const std::string &password, std::vector<PegUser *> peg_user);
        std::string MakeEmailContent(const std::string &mailbox, const int &type);
        bool UserRecoverPassword(std::map<std::string, std::string> data);
        bool UserChangePassword(const std::string &new_password, const std::string &old_password);
        std::vector<PegUser *> SetUserId(std::vector<PegUser *> peguser_list);
        std::vector<PegUser *> SetUserNameAndPaaword(std::vector<PegUser *> peguser_list);

    private:
        std::string user_id_;
        std::string user_name_;
        std::string user_password_;
        std::string tel_;
        std::string register_time_;
        std::string forbidden_;
        std::string birthday_;
        std::string introduction_;
        std::string location_;
        std::string mailbox_;
        std::string sex_;
        std::string adress_;
        std::string verification_;
        clock_t start_time;
        clock_t end_time;
    };

    struct UserInfor
    {
        std::string id_;
        std::string name_;
        std::string introduction_;
    };

    inline std::string PegUser::get_user_id_()
    {
        return this->user_id_;
    }
    inline std::string PegUser::get_user_name_()
    {
        return this->user_name_;
    }
    inline std::string PegUser::get_user_password_()
    {
        return this->user_password_;
    }
    inline std::string PegUser::get_tel_()
    {
        return this->tel_;
    }
    inline std::string PegUser::get_register_time_()
    {
        return this->register_time_;
    }
    inline std::string PegUser::get_forbidden_()
    {
        return this->forbidden_;
    }
    inline std::string PegUser::get_birthday_()
    {
        return this->birthday_;
    }
    inline std::string PegUser::get_introduction_()
    {
        return this->introduction_;
    }
    inline std::string PegUser::get_location_()
    {
        return this->location_;
    }
    inline std::string PegUser::get_mailbox_()
    {
        return this->mailbox_;
    }
    inline std::string PegUser::get_sex_()
    {
        return this->sex_;
    }
    inline std::string PegUser::get_adress_()
    {
        return this->adress_;
    }
    inline void PegUser::set_user_id_(const std::string &user_id)
    {
        this->user_id_ = user_id;
    }
    inline void PegUser::set_user_name_(const std::string &user_name)
    {
        this->user_name_ = user_name;
    }
    inline void PegUser::set_user_password_(const std::string &user_password)
    {
        this->user_password_ = user_password;
    }
    inline void PegUser::set_tel_(const std::string &tel)
    {
        this->tel_ = tel;
    }
    inline void PegUser::set_register_time_(const std::string &register_time)
    {
        this->register_time_ = register_time;
    }
    inline void PegUser::set_forbidden_(const std::string &forbidden)
    {
        this->forbidden_ = forbidden;
    }
    inline void PegUser::set_birthday_(const std::string &birthday)
    {
        this->birthday_ = birthday;
    }
    inline void PegUser::set_introduction_(const std::string &introduction)
    {
        this->introduction_ = introduction;
    }
    inline void PegUser::set_location_(const std::string &location)
    {
        this->location_ = location;
    }
    inline void PegUser::set_mailbox_(const std::string &mailbox)
    {
        this->mailbox_ = mailbox;
    }
    inline void PegUser::set_sex_(const std::string &sex)
    {
        this->sex_ = sex;
    }
    inline void PegUser::set_adress_(const std::string &adress)
    {
        this->adress_ = adress;
    }
    std::vector<PegUser *> UserDataModify(std::vector<PegUser *> peg_user, PegUser *user);
    PegUser *GetUserData(const std::string &user_id, std::vector<PegUser *> peg_user);
    peguser::PegUser *GetUserByMailbox(const std::string &mailbox, std::vector<peguser::PegUser *> peg_user);
    std::string NewUserId(std::vector<PegUser *> peg_user);
    std::string GetUserName(const std::string &user_id, std::vector<PegUser *> peg_user);
    std::string GetUserIdAccordMailbox(const std::string &mailbox, std::vector<PegUser *> peguser_list);
    std::string GetUserIntroduction(const std::string &user_id, std::vector<PegUser *> peg_user);
    std::vector<UserInfor *> GetUserInfor(std::vector<std::string> user_list, std::vector<PegUser *> peguser_list);
    std::vector<PegUser *> SetUserForbidden(const std::string &user_id, const std::string &flag,
                                            std::vector<PegUser *> peguser_list);
    std::vector<PegUser *> DeleteUser(const std::string &user_id, std::vector<PegUser *> peguser_list);
    std::vector<PegUser *> ResetUserPassword(const std::string &user_id, std::vector<PegUser *> peguser_list);
    std::vector<PegUser *> SetUserNamePassword(const std::string &user_id, const std::string &user_name, const std::string &user_password, const std::string &register_time,std::vector<PegUser *> peguser_list);
    std::vector<PegUser *> NewUserList(PegUser *user, std::vector<PegUser *> peguser_list);
}
#endif // PEGUSER_H_