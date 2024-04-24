#ifndef CHATSERVER_H_
#define CHATSERVER_H_

#include <iostream>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPOLL_SIZE 5000

struct Client
{
    std::string user_id;
    int user_fd;
};

// 注册新的fd到epollfd中
// 参数enable_et表示是否启用ET模式，如果为True则启用，否则使用LT模式
static void addfd(int epollfd, int fd, bool enable_et)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if (enable_et)
        ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    // 设置socket为nonblocking模式
    // 执行完就转向下一条指令，不管函数有没有返回。
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK);
    printf("fd added to epoll!\n\n");
}

// 截取字符串信息
std::string StrSplitId(const std::string &str, const std::string &split)
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

// 服务器接收数据的线程函数
void ServerRececive()
{
    // epoll 事件队列
    static struct epoll_event events[EPOLL_SIZE];

    // 定义sockfd
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int epfd = 0;
    std::map<int, Client *> clients_list;
    // 定义sockaddr_in，初始化服务器和端口
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;                     // TCP/IP协议族
    server_sockaddr.sin_port = htons(8023);                   // 端口号
    server_sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ip地址，127.0.0.1是环回地址，相当于本机ip

    // bind，成功返回0，出错返回-1，绑定地址
    if (bind(server_sockfd, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1)
    {
        perror("bind"); // 输出错误原因
        exit(1);        // 结束程序
    }

    // listen，成功返回0，出错返回-1，监听
    if (listen(server_sockfd, 20) == -1)
    {
        perror("listen"); // 输出错误原因
        exit(1);          // 结束程序
    }

    // 在内核中创建事件表
    epfd = epoll_create(EPOLL_SIZE);
    if (epfd < 0)
    {
        perror("epfd error");
        exit(-1);
    }

    // 往事件表里添加监听事件
    addfd(epfd, server_sockfd, true);

    while (1)
    {
        char buffer[1024]; // 设置缓冲区
                           // epoll_events_count表示就绪事件的数目
        int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
        // 处理这epoll_events_count个就绪事件
        for (int i = 0; i < epoll_events_count; ++i)
        {
            int sockfd = events[i].data.fd;
            // 新用户连接，创建一个新的fd
            if (sockfd == server_sockfd)
            {
                struct sockaddr_in client_address;
                socklen_t client_addrLength = sizeof(struct sockaddr_in);
                int clientfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_addrLength);
                addfd(epfd, clientfd, true);
                // 创建一个新的client对象保存信息
                Client *client = new Client;
                client->user_fd = clientfd;
                clients_list[clientfd] = client;
            }
            else
            { // 接收来自客户端的信息
                int len = recv(sockfd, buffer, 1024, 0);
                std::string message = buffer;
                if(len==0){
                    close(sockfd);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    clients_list.erase(sockfd);
                    std::cout << "客户端已断开" << std::endl;
                } else {
                if (message.find("client_connect") != -1)
                {
                    // 接收到来自客户端的连接信息，发送自己的用户id
                    std::string user_id = StrSplitId(message, "id:");
                    clients_list[sockfd]->user_id = user_id;
                }
                else if (message.find("message:") != -1)
                {
                    int len = recv(sockfd, buffer, 1024, 0);
                    std::string message = buffer;
                    std::string dest_id = StrSplitId(message, "dest_id:");
                    // 遍历map，将消息发给指定客户端
                    for (auto it = clients_list.begin(); it != clients_list.end(); it++)
                    {
                        if (it->second->user_id == dest_id)
                            write(it->first, buffer, strlen(buffer));
                    }
                }
                else if (message.find("client_quit") != -1)
                {
                    close(sockfd);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL)
                    clients_list.erase(sockfd);
                    std::cout << "客户端已断开" << std::endl;
                }
                }
            }
        }
    }
    // 关闭epoll实例
    close(epfd);
    // 关闭socket描述符
    close(server_sockfd);
}
#endif