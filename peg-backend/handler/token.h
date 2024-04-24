#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>

class Token
{
public:
    Token();
    inline std::string get_user_id_()
    {
        return this->user_id_;
    }
    inline std::string get_token_()
    {
        return this->token_;
    }
    inline std::string get_time_()
    {
        return this->time_;
    }
    inline void set_user_id_(const std::string &user_id)
    {
        this->user_id_ = user_id;
    }
    inline void set_token_(const std::string &token)
    {
        this->token_ = token;
    }
    inline void set_time_(const std::string &time)
    {
        this->time_ = time;
    }
    inline void Newtoken(const std::string &user_id, const std::string &token)
    {
        this->set_user_id_(user_id);
        this->set_token_(token);
    }

private:
    std::string user_id_;
    std::string token_;
    std::string time_;
};

#endif