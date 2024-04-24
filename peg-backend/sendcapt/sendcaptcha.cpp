#include "sendcaptcha.h"

/*****************************************************************
* 函数名称： bool Base64Encode( const std::string & input, std::string * output )
* 功能描述： 将字符串进行base64编码
* 参数说明： 字符串，需要编码的字符串和编码后的字符串
* 返回值：   bool判断值
******************************************************************/
bool Base64Encode( const std::string & input, std::string * output )
{
	typedef boost::archive::iterators::base64_from_binary<boost::archive::iterators::transform_width<std::string::const_iterator, 6, 8>> Base64EncodeIterator;
	std::stringstream result;
	try {
		copy( Base64EncodeIterator( input.begin() ), Base64EncodeIterator( input.end() ), std::ostream_iterator<char>( result ) );
	} catch ( ... ) {
		return false;
	}
	size_t equal_count = (3 - input.length() % 3) % 3;
	for ( size_t i = 0; i < equal_count; i++ )
	{
		result.put( '=' );
	}
	*output = result.str();
    std::cout<<output<<std::endl;
	return output->empty() == false;
}

/*****************************************************************
* 函数名称： bool Base64Decode( const std::string & input, std::string * output )
* 功能描述： 将字符串进行base64解码
* 参数说明： 字符串，需要解码的字符串和解码后的字符串
* 返回值：   bool判断值
******************************************************************/
bool Base64Decode( const std::string & input, std::string * output )
{
	typedef boost::archive::iterators::transform_width<boost::archive::iterators::binary_from_base64<std::string::const_iterator>, 8, 6> Base64DecodeIterator;
	std::stringstream result;
	try {
		copy( Base64DecodeIterator( input.begin() ), Base64DecodeIterator( input.end() ), std::ostream_iterator<char>( result ) );
	} catch ( ... ) {
		return false;
	}
	*output = result.str();
    std::cout<<output<<std::endl;
	return output->empty() == false;
}

/*****************************************************************
* 函数名称： int sendEmail(const std::string& user_account, const std::string& user_password, 
*                         const std::string& dest_account, const std::string& content)
* 功能描述： 发送邮件
* 参数说明： 字符串，发送方邮箱、发送发授权码、接收方邮箱，发送内容
* 返回值：   int判断值
******************************************************************/
int sendEmail(const std::string& user_account, const std::string& user_password, 
              const std::string& dest_account, const std::string& content)
{
    std::string smtp_url;
    int smtp_port = 25;

    //获取smtp服务器地址
    std::string::size_type pos = user_account.find('@');
    if (pos != std::string::npos)
    {
        smtp_url = "smtp." + user_account.substr(pos + 1);
        CROW_LOG_DEBUG << "smtp_url:" << smtp_url << ", port:" << smtp_port ;
    }
    else
    {
        CROW_LOG_ERROR << "get smtp_url error, user_account:" << user_account;
        return -1;
    }

    int sock = ::socket(AF_INET, SOCK_STREAM, 0);
    hostent* he = ::gethostbyname(smtp_url.c_str());
    if (he == NULL)
    {
        CROW_LOG_ERROR << "get host error, smtp_url:" << smtp_url;
        return -1;
    }

    struct sockaddr_in addr;
    memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(smtp_port);

    if (::connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        CROW_LOG_ERROR << "connect error\n" ;
        return -1;
    }

    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    if (setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                sizeof(timeout)) < 0)
    {
        CROW_LOG_ERROR << "set recv timeout error";
        return 0;
    }

    if (setsockopt (sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                sizeof(timeout)) < 0)
    {
        CROW_LOG_ERROR << "set send timeout error";
        return 0;
    }

    char buff[1024] = {0};
    size_t len = sizeof(buff);    

    //step 1: connect
    int recv_len = ::recv(sock, buff, len, 0);//copy数据
    //SMTP_LOG(1);

    //step 2: EHLO 和服务器打招呼
    std::string send("HELO ");
    send += smtp_url;
    send += "\r\n";

    ::send(sock, send.data(), send.size(), 0);
    recv_len = ::recv(sock, buff, len, 0);
    std::cout<<"1"<<std::endl;
    CROW_LOG_ERROR << buff;

    //SMTP_LOG(2);

    //step 3: AUTH LOGIN 一般登陆模式
    send = "AUTH LOGIN\r\n";

    ::send(sock, send.data(), send.size(), 0);
    recv_len = ::recv(sock, buff, len, 0);
    std::cout<<"2"<<std::endl;
    CROW_LOG_ERROR << buff;
    //std::cout<<recv_len<<std::endl;
    //SMTP_LOG(3);

    //step 4: account_name
    std::string account_name;
    pos = user_account.find("@");
    if (pos != std::string::npos)
    {
        account_name = user_account.substr(0, pos);
    }

    Base64Encode(user_account,&send);
    send+="\r\n";
    ::send(sock, send.data(), send.size(), 0);
    recv_len = ::recv(sock, buff, len, 0);
    std::cout<<"3"<<std::endl;
    CROW_LOG_ERROR << buff;
    //SMTP_LOG(4);

    //step 5: account_pwd
    Base64Encode(user_password,&send);
    send += "\r\n";
    ::send(sock, send.data(), send.size(), 0);
    recv_len = ::recv(sock, buff, len, 0);
    std::cout<<"4"<<std::endl;
    CROW_LOG_ERROR << buff;
    //SMTP_LOG(5);

    if (std::string(buff, recv_len).find("235") == std::string::npos)
    {
        CROW_LOG_ERROR << "account password error";
        return -1;
    }

    //step 6: MAIL FROM
    send = "MAIL FROM: ";
    send += "<" + user_account + ">";
    send += "\r\n";

    ::send(sock, send.data(), send.size(), 0);
    recv_len = ::recv(sock, buff, len, 0);
    //SMTP_LOG(6);

    //step 7: RCPT TO
        send = "RCPT TO: ";
        send += "<" + dest_account + ">";
        send += "\r\n";

        ::send(sock, send.data(), send.size(), 0);
        recv_len = ::recv(sock, buff, len, 0);
        //SMTP_LOG(7);

    //step 8: DATA
    send = "DATA";
    send += "\r\n";

    ::send(sock, send.data(), send.size(), 0);
    recv_len = ::recv(sock, buff, len, 0);
    //SMTP_LOG(8);

    //step 9: content
    send = "";
    send += "FROM: " + user_account;
    send += "\r\n";

    send += "TO: ";
    for (size_t i = 0; i != dest_account.size(); ++i)
    {
        if (i != 0)
        {
            send += ",";
        }
        send += dest_account[i];
    }
    send += "\r\n";

    send += "SUBJECT: 系统注册";
    send += "\r\n\r\n";

    send += content;
    send += "\r\n\r\n";

    send += ".";
    send += "\r\n";

    CROW_LOG_DEBUG << "email:" << send ;

    ::send(sock, send.data(), send.size(), 0);
    recv_len = ::recv(sock, buff, len, 0);
    //long send_time=Util::get_cur_time();
    //SMTP_LOG(9);
    //return send_time;
}