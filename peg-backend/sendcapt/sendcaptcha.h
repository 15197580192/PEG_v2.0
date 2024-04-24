/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       sendcaptcha.h
 * @descripition  该头文件中包含使用邮箱发送验证码的方法函数
 *  
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef SENDCAPTCHA_H
#define SENDCAPTCHA_H

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>

#include <string>
#include "crow.h"
#include <sys/socket.h>

bool Base64Encode( const std::string & input, std::string * output );
bool Base64Decode( const std::string & input, std::string * output );
int sendEmail(const std::string& user_account, const std::string& user_password, 
              const std::string& dest_account, const std::string& content);
#endif // SENDCAPTCHA_H