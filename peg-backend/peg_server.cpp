/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       main.cpp
 * @brief      主函数,包含开启网页路由的各个部分
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>

#include <pthread.h>

#include "util/FileTransfer.h"
#include "util/RemoteCmdInvoker.h"

#include "include/crow.h"
#include "crow/middlewares/cors.h"
#include "gStoreAPI/client.h"
#include "queryDecompose/Query/QueryTree.h"
#include "queryDecompose/Query/GeneralEvaluation.h"
#include "joiner/joiner.h"
#include "util/util.h"
#include "handler/user.h"
#include "handler/tool.h"
#include "tojson/tojson.h"
#include "dbUtil/dbutil.h"

int main()
{
    std::vector<GstoreConnector *> servers;
    std::vector<user::User *> userdata;
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .origin("*")
        .headers("origin, x-requested-with, accept, access-control-allow-origin, authorization, content-type")
        .methods("POST"_method, "GET"_method, "PUT"_method, "DELETE"_method, "PATCH"_method, "OPTIONS"_method);

    DB *db = new DB;
    // 接收get请求得到node表数据
    std::vector<node::Node *> node_list = db->NodeDisplay();
    std::vector<database::Database *> database_list = db->DatabaseDisplay();
    std::vector<std::map<std::string, std::string>> confJson = db->NodeDisplayMap();
    vector<dbbackup::DbBackup *> dbbackup_list = db->BackupDisplay();
    vector<dblog::DbLog *> dblog_list = db->DbLogDisplay();
    vector<peglog::PegLog *> peglog_list = db->PegLogDisplay();
    vector<dbnode::DbNode *> dbnode_list = db->DbNodeDisplay();
    vector<Notice *> notice_list = db->NoticeDisplay();
    std::vector<chat::Chat *> chat_list = db->ChatDisplay();
    std::vector<post::Post *> post_list = db->PostDisplay();
    std::vector<question::Question *> question_list = db->QuestionDisplay();
    std::vector<collection::Collection *> collection_list = db->CollectionDisplay();
    std::vector<follower::Follower *> follower_list = db->FollowerDisplay();
    std::vector<support::Support *> support_list = db->SupportDisplay();
    std::vector<comment::Comment *> comments_list = db->CommentDisplay();
    std::vector<draft::Draft *> draft_list = db->DraftDisplay();
    std::vector<DbUser *> dbuser_list = db->DBUserDisplay();
    std::vector<peguser::PegUser *> peguser_list = db->UserDisplay();
    std::vector<Token *> token_data = db->TokenDisplay();
    std::map<std::string, std::vector<chat::ChatHistory *>> chathistory_list;
    std::vector<chat::SocketFd *> socket_list;
    std::mutex mtx;
    std::map<std::string, std::thread> thread_list;
    for (int i = 0; i < confJson.size(); i++)
    {
        int port;
        std::stringstream ss;
        ss << confJson[i]["port"];
        ss >> port;
        ss.clear();
        servers.push_back(new GstoreConnector(
            confJson[i]["node_ip"],
            port,
            "POST",
            confJson[i]["gstore_user_id"],
            confJson[i]["gstore_user_password"]));
    }

    CROW_ROUTE(app, "/index")
    ([]
     {
        crow::mustache::context ctx;
        return crow::mustache::load("/index.html").render(); });

    // 显示节点信息
    CROW_ROUTE(app, "/api/ManageNode")
    ([&node_list, &db, &confJson, &servers](const crow::request &req)
     {
    nlohmann::json node_json=tojson::NodeToJson(node_list);
    std::string req_body=req.body;
    nlohmann::json retv;
    crow::response res;
    retv["status"] = "success";
    retv["message"] = "success";
    retv["data"] = node_json.dump();
    res.set_header("Content-Type","text/html;charset=utf-8");
    res.write((retv.dump()));
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    CROW_ROUTE(app, "/api/CheckNodeOnline").methods(crow::HTTPMethod::POST)([&node_list, &db, &servers](const crow::request &req)
                                                                            {
    std::string req_body=req.body;
    crow::json::rvalue data = crow::json::load(req_body);
    nlohmann::json retv;
    crow::response res;
    std::string node_ip=data["node_ip"].s();
    std::string node_port=data["node_port"].s();
    retv["data"]="success";
    if (!tool::CheckNode(servers, node_ip, node_port)) retv["data"] = "failed";
    res.set_header("Content-Type","text/html;charset=utf-8");
    res.write((retv.dump()));
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    CROW_ROUTE(app, "/api/Export").methods(crow::HTTPMethod::POST)([&db, &database_list,&dblog_list, &servers, &dbnode_list, &node_list](const crow::request &req)
                                                                   {
    std::string req_body = req.body;
    crow::json::wvalue retv;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string database_name = data["dbname"].s();
    std::string database_creator_id = data["database_cuid"].s();
    std ::string userid=data["dbuserid"].s();
    std::string dbid;
    std::string dbpassword;
    dbid=GetDatabaseId(database_name,database_creator_id,database_list);
    std::string path="/home/yyj/";
     std::vector<GstoreConnector *> newservers;
   std::string retstr;
    newservers = tool::DbIdGetNodes(servers,dbnode_list,dbid,node_list);
    for (int i=0;i<database_list.size();i++)
         {
            if(database_list[i]->get_database_id_() == dbid)
            {
               retstr= database_list[i]->DbExport(newservers,path);
            }
         }
   
    retv["data"]=retstr;
        dblog::DbLog *dblog=new dblog::DbLog;
        dblog->NewDbLog(userid,"export",dbid);
        db->DbLogInsert(dblog);
        dblog_list.push_back(dblog);
        crow::response res;
        res.set_header("Content-Type", "text/html;charset=utf-8");
        res.write((retv.dump()));
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 删除名称为id的节点
    CROW_ROUTE(app, "/api/ManageNode").methods(crow::HTTPMethod::POST)([&node_list, &db,&peglog_list](const crow::request &req)
       {
        nlohmann::json retv;
        retv["status"] = "success";
        retv["message"] = "success";
        crow::response res;
        res.set_header("Content-Type","text/html;charset=utf-8");
        std::string req_body=req.body;
        crow::json::rvalue data = crow::json::load(req_body);
        int n=data["node_id"].size();
        std::string user_id=data["user_id"].s();
        std::vector<std::string> node_id;
        for(int i=0;i<n;i++){
        node_id.push_back(data["node_id"][i].s());
        }
        if(db->NodeDelete(node_id)){
            node_list=node::DeleteNode(node_id,node_list);
            nlohmann::json node_json=tojson::NodeToJson(node_list);
            retv["data"]=node_json.dump();
            
            peglog::PegLog *peglog=new peglog::PegLog;
            peglog->NewPegLog(user_id,"删除节点");
            db->PegLogInsert(peglog);
            peglog_list.push_back(peglog);
        }
        else {
            retv["status"]="failed";
            retv["message"]="failed";
            retv["data"]=NULL;
        }
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 新建节点
    CROW_ROUTE(app, "/api/ManageNode/NewNode").methods(crow::HTTPMethod::POST)([&node_list, &db,&peglog_list](const crow::request &req)
                                                                               {
        nlohmann::json retv;//判断后返回前端的数据
        retv["status"] = "success";
        retv["message"] = "success";
        crow::response res;
        res.set_header("Content-Type","text/html;charset=utf-8");
        std::string req_body=req.body;
        crow::json::rvalue data = crow::json::load(req_body);
        std::vector<std::string> str_list;
        std::string node_id=data["node_id"].s();
        str_list.push_back(node_id);
        std::string node_ip=data["node_ip"].s();
        str_list.push_back(node_ip);
        std::string user_id = data["user_id"].s();
        str_list.push_back(user_id);
        std::string node_port=data["port"].s();
        std::string node_user_id=data["gstore_user_id"].s();
        str_list.push_back(node_user_id);
            std::string node_user_password = data["gstore_user_password"].s();
            str_list.push_back(node_user_password);
                std::string node_version = data["version"].s();
            std::string node_apitype = data["apitype"].s();
            std::string node_rootpath = data["rootpath"].s();
            str_list.push_back(node_rootpath);
            if(tool::CheckUnlawful(str_list)){
                retv["status"] = "unlawful";
                res.write(retv.dump());
                res.set_header("Content-Length", to_string(res.body.size()));
                return res;
            }
                // 将新增节点数据加入表
                bool flag = false;
            if (node::CheckNode(node_id, node_ip, node_list))
            {
                node::Node *new_node = new node::Node;
                new_node->new_nodedata(node_id, node_ip, user_id, node_port, node_user_id, node_user_password,
                                       node_version, node_apitype, node_rootpath);
                if (db->NodeInsert(new_node))
                {
                    node_list.push_back(new_node);
                    nlohmann::json node_json = tojson::NodeToJson(node_list);
                    retv["data"] = node_json.dump();
                    flag = true;
                    peglog::PegLog *peglog = new peglog::PegLog;
                    peglog->NewPegLog(user_id, "新建节点");
                    db->PegLogInsert(peglog);
                    peglog_list.push_back(peglog);
                }
        }
        if(!flag){
            retv["status"]="failed";
            retv["message"]="failed";
            retv["data"]=NULL; 
        }
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 修改节点
    CROW_ROUTE(app, "/api/ManageNode/ModifyNode").methods(crow::HTTPMethod::POST)([&node_list, &db,&peglog_list](const crow::request &req)
                                                                                  {
        nlohmann::json retv;//判断后返回前端的数据
        retv["status"] = "success";
        retv["message"] = "success";
        crow::response res;
        res.set_header("Content-Type","text/html;charset=utf-8");
        std::string req_body=req.body;
        crow::json::rvalue data = crow::json::load(req_body);
        std::vector<std::string> str_list;
        std::string node_id=data["node_id"].s();
        std::string node_ip=data["node_ip"].s();
        std::string user_id=data["user_id"].s();
        std::string node_port=data["port"].s();
        std::string node_user_id=data["gstore_user_id"].s();
        std::string node_user_password=data["gstore_user_password"].s();
        std::string node_version=data["version"].s();
        std::string node_apitype=data["apitype"].s();
        std::string node_rootpath=data["rootpath"].s();
        str_list.push_back(node_id);
        str_list.push_back(node_ip);
        str_list.push_back(user_id);
        str_list.push_back(node_user_id);
        str_list.push_back(node_user_password);
        str_list.push_back(node_rootpath);
        if (tool::CheckUnlawful(str_list))
        {
            retv["status"] = "unlawful";
            res.write(retv.dump());
            res.set_header("Content-Length", to_string(res.body.size()));
            return res;
        }
        node::Node *new_node=new node::Node;
        new_node->new_nodedata(node_id,node_ip,user_id,node_port,node_user_id,node_user_password,
                               node_version,node_apitype,node_rootpath);
        if(!db->NodeModify(new_node)){
        retv["status"]="failed";
        retv["message"] = "failed";
        retv["data"]=NULL;
        } else {
        node_list=node::NodeDataModify(node_list,new_node);
        peglog::PegLog *peglog=new peglog::PegLog;
            peglog->NewPegLog(user_id,"修改节点");
            db->PegLogInsert(peglog);
            peglog_list.push_back(peglog);
        }
        res.write((retv.dump()));
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 显示节点数量
    CROW_ROUTE(app, "/api/GetNodeNum")
    ([&node_list](const crow::request &req)
     {
    crow::json::wvalue retv;
    retv["message"] = to_string(node_list.size());
    crow::response res;
    res.write((retv.dump()));
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 显示PEG用户个人信息
    CROW_ROUTE(app, "/api/User")
    ([&peguser_list, &db](const crow::request &req)
     {
        nlohmann::json retv;//判断后返回前端的数据
        retv["status"] = "success";
        retv["message"] = "success";
        crow::response res;
        res.set_header("Content-Type","text/html;charset=utf-8");
        std::string user_id=req.url_params.get("user_id");
        peguser::PegUser *user=new peguser::PegUser;
        user=peguser::GetUserData(user_id,peguser_list);
        nlohmann::json peguser_json=tojson::PEGUserToJson(user);
        retv["data"]=peguser_json.dump();
        res.write((retv.dump()));
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 修改个人信息
    CROW_ROUTE(app, "/api/User").methods(crow::HTTPMethod::POST)([&peguser_list, &db, &post_list, &comments_list, &question_list, &chat_list, &chathistory_list,&peglog_list](const crow::request &req)
                                                                 {
    std::string req_body=req.body;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string user_id=data["user_id"].s();
    std::string user_name=data["user_name"].s();
    std::string tel=data["tel"].s();
    std::string introduction=data["introduction"].s();
    std::string birthday=data["birthday"].s();
    std::string location=data["location"].s();
    std::string mailbox=data["mailbox"].s();
    std::string sex=data["sex"].s();
    std::string adress=data["adress"].s();
    nlohmann::json retv;
    retv["status"] = "success";
    retv["message"] = "success";
    crow::response res;
    res.set_header("Content-Type","text/html;charset=utf-8");
    std::vector<std::string> str_list;
    str_list.push_back(user_name);
    str_list.push_back(tel);
    str_list.push_back(introduction);
    str_list.push_back(birthday);
    str_list.push_back(location);
    str_list.push_back(adress);
    if (tool::CheckUnlawful(str_list))
    {
        retv["status"] = "unlawful";
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res;
    }
    peglog::PegLog *peglog = new peglog::PegLog;
    peglog->NewPegLog(user_id, "修改个人信息");
    db->PegLogInsert(peglog);
    peglog_list.push_back(peglog);

    peguser::PegUser *user=new peguser::PegUser;
    user->UserModify(user_id,user_name,tel,introduction,birthday,location,mailbox,sex,adress);
    if(!db->UserModify(user)){
        retv["status"]="failed";
        retv["message"] = "failed";
        retv["data"]=NULL;
    } else {
    nlohmann::json peguser_json=tojson::PEGUserToJson(user);
    retv["data"]=peguser_json.dump();
    peguser_list=peguser::UserDataModify(peguser_list,user);
    }
    res.write((retv.dump()));
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 修改密码
    CROW_ROUTE(app, "/api/ChangePassword").methods(crow::HTTPMethod::POST)([&peguser_list, &db,&peglog_list](const crow::request &req)
                                                                           {
    std::string req_body=req.body;
    crow::response res;
    crow::json::wvalue retv; // 判断后返回前端的数据
    crow::json::rvalue data = crow::json::load(req_body);
    std::string user_id=req.url_params.get("user_id");
    std::string new_password=data["new_password"].s();
    std::string old_password=data["old_password"].s();
    std::vector<std::string> str_list;
    str_list.push_back(new_password);
    if (tool::CheckUnlawful(str_list))
    {
        retv["status"] = "unlawful";
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res;
    }
    peguser::PegUser *user = new peguser::PegUser;
    user=peguser::GetUserData(user_id,peguser_list);
    bool flag=false;
    if(user->UserChangePassword(new_password,old_password)){
        if(db->UserRecoverPassword(user)) {
            flag=true;
            peguser_list=peguser::UserDataModify(peguser_list,user);
        }
    }
    retv["status"] = "success";
    retv["message"] = "success";
    peglog::PegLog *peglog=new peglog::PegLog;
            peglog->NewPegLog(user_id,"修改密码");
            db->PegLogInsert(peglog);
            peglog_list.push_back(peglog);
    if(!flag){
    retv["status"]="failed";
    retv["message"] = "failed";
    }
    res.write((retv.dump()));
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 注册
    CROW_ROUTE(app, "/api/Enroll").methods(crow::HTTPMethod::POST)([&peguser_list, &db](const crow::request &req)
                                                                   {
    std::string req_body=req.body;
    crow::response res;
    crow::json::rvalue data = crow::json::load(req_body);
    std::vector<std::string> key=data.keys();
    std::map<std::string, std::string> key_value;
    peguser::PegUser *new_user=new peguser::PegUser;
    for (int i = 0; i < key.size(); i++)
    {
        std::string value;
        value = data[key[i]].s();
        std::cout<<key[i]<<std::endl;
        key_value[key[i]] = value;
        std::cout<<value<<std::endl;
    }
    if (key.size() > 1)
    {
        new_user = peguser::GetUserByMailbox(key_value["mailbox"],peguser_list);
    }
    bool flag=false;
    if(new_user->UserEnroll(key_value,peguser_list)){
        flag=true;
    }
    crow::json::wvalue retv;//判断后返回前端的数据
    retv["status"] = "failed";
    retv["message"] = "failed";
    if(flag){
        if (key.size() == 1)
        {
            peguser_list = NewUserList(new_user,peguser_list);
        } else {
            new_user->set_user_id_(NewUserId(peguser_list));
            peguser_list = new_user->SetUserId(peguser_list);
            db->UserInsert(new_user);
            retv["data"]=new_user->get_user_id_();
        }
    retv["status"] = "success";
    retv["message"] = "success";
    std::cout<<peguser_list.size()<<std::endl;
    }
    res.write((retv.dump()));
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 用户输入注册个人信息
    CROW_ROUTE(app, "/api/Enroll/Write").methods(crow::HTTPMethod::POST)([&peguser_list, &db](const crow::request &req)
                                                                         {
    std::string req_body=req.body;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string user_id=data["user_id"].s();
    std::string user_name=data["user_name"].s();
    std::string user_password=data["password"].s();
    std::string register_time=tool::GetTime();
    crow::json::wvalue retv;//判断后返回前端的数据
    crow::response res;
    std::vector<std::string> str_list;
    str_list.push_back(user_password);
    str_list.push_back(user_name);
    if (tool::CheckUnlawful(str_list))
    {
        retv["status"] = "unlawful";
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res;
    }
    retv["status"] = "failed";
    retv["message"] = "failed";
    if(db->UserSetNamePassword(user_id,user_name,user_password,register_time)) {
        peguser_list=peguser::SetUserNamePassword(user_id,user_name,user_password,register_time,peguser_list);
        retv["status"] = "success";
        retv["message"] = "success";
    }
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 用户重置密码
    CROW_ROUTE(app, "/api/RecoverPassword").methods(crow::HTTPMethod::POST)([&peguser_list, &db,&peglog_list](const crow::request &req)
                                                                            {
    std::string req_body=req.body;
    crow::response res;
    crow::json::wvalue retv; // 判断后返回前端的数据
    crow::json::rvalue data = crow::json::load(req_body);
    std::string mailbox;
    std::vector<std::string> key = data.keys();
    std::map<std::string,std::string> key_value;
    std::vector<std::string> str_list;
    for(int i=0;i<key.size();i++){
        std::string value;
        value=data[key[i]].s();
        key_value[key[i]]=value;
        str_list.push_back(value);
    }
    if (tool::CheckUnlawful(str_list))
    {
        retv["status"] = "unlawful";
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res;
    }
    peguser::PegUser *new_user=new peguser::PegUser;
    mailbox = data["mailbox"].s();
    std::cout<<mailbox<<std::endl;
    new_user=peguser::GetUserByMailbox(mailbox,peguser_list);
    std::cout<<new_user->get_user_id_()<<std::endl;
    if(new_user->get_user_id_()=="0"){
        retv["status"]="failed";
    } else {
    bool flag=false;
    retv["status"] = "success";
    retv["message"] = "success";
    if(key.size()>1){
        if(new_user->UserRecoverPassword(key_value)){
            if(db->UserRecoverPassword(new_user)){
                flag=true;
            }
        }
    } else {
        flag=new_user->UserRecoverPassword(key_value);
        peguser_list = NewUserList(new_user, peguser_list);
    }
    if(!flag){
        retv["status"]="failed";
        retv["message"] = "failed"; 
    }
    if (flag && key.size() > 1)
    {     
            peglog::PegLog *peglog=new peglog::PegLog;
            std::string user_id=peguser::GetUserIdAccordMailbox(mailbox,peguser_list);
            std::cout<<user_id<<std::endl;
            peglog->NewPegLog(user_id,"重置密码");
            db->PegLogInsert(peglog);
            peglog_list.push_back(peglog);
    }
    }
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 用户登录
    CROW_ROUTE(app, "/api/Login").methods(crow::HTTPMethod::POST)([&peguser_list, &db, &chat_list, &token_data, &chathistory_list, &socket_list, &mtx, &thread_list,&peglog_list](const crow::request &req)
                                                                  {
    nlohmann::json retv;
    crow::response res;
    std::string req_body = req.body;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string user_id=data["user_id"].s();
    std::string user_pass = data["user_password"].s();
    std::string header = req.get_header_value("Authorization");
     for (int j = 0; j < token_data.size(); j++)
    {
        if (token_data[j]->get_user_id_() == user_id)
        {
            if(token_data[j]->get_token_()==header){
                std::cout<<"success"<<std::endl;
                retv["state"] = "success";
                res.set_header("Content-Type", "textml;charset=utf-8");
                res.write((retv.dump()));
                res.set_header("Content-Length", to_string(res.body.size()));
                return res;
            }
        }
    }
    retv["state"] = "id no exist";
    for(int i=0;i<peguser_list.size();i++)
    {
       if(peguser_list[i]->get_user_id_()== user_id)
       {
          if(peguser_list[i]->get_user_password_() == user_pass)
          {
              if (peguser_list[i]->get_forbidden_() != "1")
              {
                  std::cout << user_id << std::endl;
                  chathistory_list.insert(std::pair<std::string, std::vector<chat::ChatHistory *>>(user_id, chat::GetChatHistory(user_id, chat_list))); // 拉取该用户的所有聊天记录
                  chat::SocketFd *socket = new chat::SocketFd;
                  socket->fd = chat::GetServer(user_id);
                  socket->user_id = user_id;
                  std::thread t(chat::RecvMessage, std::ref(mtx), std::ref(chathistory_list), std::ref(socket->fd), std::ref(peguser_list));
                  t.detach();
                  thread_list.emplace(user_id, std::move(t));
                  chat::TellConnect(user_id, socket->fd);
                  socket_list.push_back(socket);
                  retv["state"] = "success";
                  peglog::PegLog *peglog = new peglog::PegLog;
                  peglog->NewPegLog(user_id, "登录");
                  db->PegLogInsert(peglog);
                  peglog_list.push_back(peglog);
              }
              else
              {
                  retv["state"] = "in forbid";
              }
            std::string token_str = tool::EnCode();
            retv["state"] = "success";
            retv["token"] = token_str;
            Token *token = new Token;
            token->Newtoken(user_id,token_str);
            token_data.push_back(token);
            db->TokenInsert(token);
            continue;
          }
          else
          {
            retv["state"] = "pass error";
            continue;
          }
       }
    }
    res.set_header("Content-Type","text/html;charset=utf-8");
    
    res.write((retv.dump()));
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 用户退出登录
    CROW_ROUTE(app, "/api/LoginOut")
    ([&chathistory_list, &thread_list, &socket_list](const crow::request &req)
     {
        crow::response res;
        std::string user_id=req.url_params.get("user_id");
        crow::json::wvalue retv;
        retv["status"] = "success";
        std::this_thread::sleep_for(std::chrono::seconds(10));
        //向服务端发送消息，要求断开与该客户端的连接，终止线程
        for (auto i = socket_list.begin(); i != socket_list.end(); i++)
        {
            if ((*i)->user_id == user_id) {
                chat::TellCloseConnect(user_id, (*i)->fd);
                socket_list.erase(i);
                break;
            }
        }
        std::cout<<socket_list.size()<<std::endl;
        std::cout << thread_list.size() << std::endl;
        res.set_header("Content-Type","text/html;charset=utf-8");
    res.set_header("Content-Length", to_string(res.body.size()));
    res.write((retv.dump())); 
    return res; });

    // 管理用户
    // 得到所有用户信息
    CROW_ROUTE(app, "/api/ManagePegUser")
    ([&peguser_list](const crow::request &req)
     {
        nlohmann::json retv;
        retv["data"]=tojson::ManagePEGUserListToJson(peguser_list).dump();
        crow::response res;
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 禁用or解禁
    CROW_ROUTE(app, "/api/ManagePegUser/BanUser").methods(crow::HTTPMethod::POST)([&peguser_list, &db](const crow::request &req)
                                                                                  {
    nlohmann::json retv;
    retv["status"]="failed";
    std::string req_body=req.body;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string user_id=data["user_id"].s();
    std::string flag=data["flag"].s();
    if(db->UserForbidden(user_id,flag)){
        peguser_list=peguser::SetUserForbidden(user_id,flag,peguser_list);
        retv["status"]="success";
        retv["data"] = tojson::ManagePEGUserListToJson(peguser_list).dump();
    }
    crow::response res;
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 删除用户
    CROW_ROUTE(app, "/api/ManagePegUser/DeleteUser").methods(crow::HTTPMethod::POST)([&peguser_list, &db](const crow::request &req)
                                                                                     {
    nlohmann::json retv;
    retv["status"]="failed";
    std::string req_body=req.body;
    crow::json::rvalue data = crow::json::load(req_body);
    int n = data["user_id"].size();
    std::vector<std::string> userid_list;
    for(int i=0;i<n;i++){
        userid_list.push_back(data["user_id"][i].s());
    }
    for(int i=0;i<userid_list.size();i++){
    if(db->UserDelete(userid_list[i])){
        peguser_list=peguser::DeleteUser(userid_list[i],peguser_list);    
    }
    }
    retv["status"] = "success";
    retv["data"] = tojson::ManagePEGUserListToJson(peguser_list).dump();
    crow::response res;
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 新增用户
    CROW_ROUTE(app, "/api/ManagePegUser/NewUser").methods(crow::HTTPMethod::POST)([&peguser_list, &db](const crow::request &req)
                                                                                  {
    nlohmann::json retv;
    crow::response res;
    retv["status"]="failed";
    std::string req_body=req.body;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string user_name=data["user_name"].s();
    std::string user_password=data["user_password"].s();
    std::string mailbox=data["mailbox"].s();
    std::vector<std::string> str_list;
    str_list.push_back(user_name);
    str_list.push_back(user_password);
    str_list.push_back(mailbox);
    if (tool::CheckUnlawful(str_list))
    {
        retv["status"] = "unlawful";
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res;
    }
    peguser::PegUser *new_user = new peguser::PegUser;
    new_user->NewUser(user_name,user_password,peguser_list);
    new_user->set_mailbox_(mailbox);
    if(db->UserInsert(new_user)){
        peguser_list.push_back(new_user);
        retv["status"]="success";
        retv["data"] = tojson::ManagePEGUserListToJson(peguser_list).dump();
    }
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 重置密码
    CROW_ROUTE(app, "/api/ManagePegUser/RecoverPassword").methods(crow::HTTPMethod::POST)([&peguser_list, &db](const crow::request &req)
                                                                                          {
    nlohmann::json retv;
    retv["status"]="failed";
    std::string req_body=req.body;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string user_id=data["user_id"].s();
     if(db->UserResetPassword(user_id)){
        peguser_list=peguser::ResetUserPassword(user_id,peguser_list);
        retv["status"]="success";
        retv["data"] = tojson::ManagePEGUserListToJson(peguser_list).dump();
    }
    crow::response res;
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 数据库登录
    CROW_ROUTE(app, "/api/SqlLogin").methods(crow::HTTPMethod::POST)([&db, &dbuser_list,&dblog_list, &database_list,&dbnode_list,&node_list,&servers](const crow::request &requ)
     {
    crow::json::wvalue retv;
    crow::response res;
    std::string req_body=requ.body;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string database_name = data["db_name"].s();
    std::string database_creater_id = data["database_creater_id"].s();
    std::string dbuser_password = data["dbuser_password"].s();
    std::string dbuser_id=data["dbuser_id"].s();
    std::string dbid = database_creater_id + database_name;
    retv["state"]="fail";
    std::vector<GstoreConnector *> new_servers;
    new_servers = tool::DbIdGetNodes(servers, dbnode_list, dbid, node_list);
    for(int i=0;i<dbnode_list.size();i++)
    {
        if(!tool::CheckNode(new_servers,dbnode_list[i]->get_node_ip_(),dbnode_list[i]->get_node_port_()))
        {
            retv["state"] = "node put off";
            res.write(retv.dump());
            res.set_header("Content-Length", to_string(res.body.size()));
            tool::NewServersDelete(new_servers);
            return res;
        }
    }
    for(int i=0;i<dbuser_list.size();i++){
       if(dbuser_list[i]->DbLogin(dbid,dbuser_id,dbuser_password)){
        retv["state"] = "success";
          dblog::DbLog *dblog=new dblog::DbLog;
         dblog->NewDbLog(dbuser_id,"login",dbid);
         db->DbLogInsert(dblog);
         dblog_list.push_back(dblog);
       }
    }
    res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        tool::NewServersDelete(new_servers);
        return res; });
    // 显示数据库数量
    CROW_ROUTE(app, "/api/GetDatabaseNum")
    ([&database_list](const crow::request &req)
     {
    crow::json::wvalue retv;
    retv["message"] = to_string(database_list.size());
    crow::response res;
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 显示数据库列表
    CROW_ROUTE(app, "/api/GetDatabaseList")
    ([&database_list](const crow::request &req)
     {
        nlohmann::json  retv;
        retv["data"]=tojson::DatabaseJson(database_list).dump();
        crow::response res;  
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 获得该用户名下的数据库数量和列表
    CROW_ROUTE(app, "/api/GetDatabaseName")
    ([&database_list](const crow::request &req)
     {
    nlohmann::json retv;
    std::string user_id=req.url_params.get("user_id");
    std::vector<database::Database *> database_idlist;
    database_idlist = UserQueryDb(database_list,user_id);
    nlohmann::json database_data = tojson::DatabaseJson(database_idlist);
    retv["data"] = database_data.dump();
    crow::response res;
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 删除数据库
    CROW_ROUTE(app, "/api/Delete").methods(crow::HTTPMethod::POST)([&db, &database_list,&dblog_list, &servers, &node_list, &dbnode_list](const crow::request &req)
                                                                   {
                                                                       std::string req_body = req.body;
                                                                       crow::json::wvalue retv;
                                                                       crow::response res;
                                                                       crow::json::rvalue data = crow::json::load(req_body);
                                                                       std::string database_name = data["db_name"].s();
                                                                       std::string database_creater_id = data["database_creater_id"].s();
                                                                       std::string database_password = data["database_password"].s();
                                                                       std::string user_id = data["dbuser_id"].s();
                                                                       std::string db_password;
                                                                       std::vector<GstoreConnector *> new_servers;
                                                                       std::string dbid = GetDatabaseId(database_name, database_creater_id, database_list);
                                                                       db_password = GetDatabasePassword(database_name, database_creater_id, database_list);
                                                                       new_servers = tool::DbIdGetNodes(servers, dbnode_list, dbid, node_list);
                                                                       if (database_password != db_password)
                                                                       {
                                                                           retv["message"] = "password not true";
                                                                       }
                                                                       else
                                                                       {
                                                                           for (int i = 0; i < database_list.size(); i++)
                                                                           {
                                                                               int status = database_list[i]->DeleteDb(new_servers, dbid);
                                                                           }

                                                                           db->DatabaseDelete(dbid);
                                                                           for (int k = 0; k < database_list.size(); k++)
                                                                           {
                                                                               if (database_list[k]->get_database_id_() == dbid)
                                                                               {
                                                                                   database_list.erase(database_list.begin() + k);
                                                                               }
                                                                           }
                                                                           dblog::DbLog *dblog = new dblog::DbLog;
                                                                           dblog->NewDbLog(user_id, "delete", dbid);
                                                                           db->DbLogInsert(dblog);
                                                                           dblog_list.push_back(dblog);
                                                                           retv["message"] = "success";
                                                                       }
                                                                       tool::NewServersDelete(new_servers);
                                                                       res.write(retv.dump());
                                                                       res.set_header("Content-Length", to_string(res.body.size()));
                                                                       return res;
                                                                       //  }
                                                                   });

    // 新建数据库
    CROW_ROUTE(app, "/api/DbCreate").methods(crow::HTTPMethod::POST)([&node_list, &db, &dblog_list,&database_list, &confJson, &servers, &dbuser_list, &dbnode_list](const crow::request &req)
                                                                     { 
        nlohmann::json retv;
        crow::response res;
        auto file_data = req.body;
        std::string dbname=tool::Trim(tool::GetInf(file_data,"name=\"name\"","-----"));
        std::string division_number=tool::Trim(tool::GetInf(file_data,"name=\"divisionNumber\"","-----"));
        std::string user_id = tool::Trim(tool::GetInf(file_data, "name=\"user_id\"", "-----"));
        std::string db_password = tool::Trim(tool::GetInf(file_data, "name=\"dbpass\"", "-----"));
        std::string remarks = tool::Trim(tool::GetInf(file_data,"name=\"remarks\"","-----"));
        std::string ntfile_name = tool::Trim(tool::GetInf(file_data,"name=\"ntFilename\"","-----"));
        std::string txtfile_name = tool::Trim(tool::GetInf(file_data,"name=\"txtFilename\"","-----"));
        std::string nt_content = tool::Trim(tool::GetInf(file_data,"Content-Type: application/octet-stream","-----"));
        std::string txt_content = tool::Trim(tool::GetInf(file_data,"Content-Type: text/plain","-----"));
        std::string nodelist=tool::Trim(tool::GetInf(file_data,"name=\"nodeList\"","-----"));
        cout<<nodelist<<endl;
        crow::json::rvalue tes = crow::json::load(nodelist);
       
        std::string dbid = user_id + dbname;
        for(int i=0;i<database_list.size();i++)
        {
            if(dbid == database_list[i]->get_database_id_())
            {
                retv["data"] = "fail";
                res.write(retv.dump());
                res.set_header("Content-Length", to_string(res.body.size()));
                return res;
            }
        }
        tool::OutputToFile(ntfile_name, nt_content);
        tool::OutputToFile(txtfile_name, txt_content);
        
        std::string dbpath = ntfile_name;
        std::string divide_path = txtfile_name;
        std::vector<GstoreConnector *> new_servers = tool::CreateDbGetNode(tes, servers, node_list);
        cout<<"------"<<new_servers.size()<<endl;
        database::Database *newdb = new database::Database;
        newdb->NewDatabase(dbid,dbname,user_id,db_password,"1.0");
        newdb->DbBuild(confJson,new_servers,dbpath,divide_path);
        database_list.push_back(newdb);
        db->DatabaseInsert(newdb);
        DbUser *new_dbuser = new DbUser;
        new_dbuser->NewDbUser("1",dbid,"root","123456","0",user_id);
        db->DbUserInsert(new_dbuser);
        dbuser_list = db->DBUserDisplay();
        retv["message"] = "create success";
        dblog::DbLog *dblog=new dblog::DbLog;
        dblog->NewDbLog("root","build",dbid);
        db->DbLogInsert(dblog);
        dblog_list.push_back(dblog);
        for(int i=0;i<new_servers.size();i++)
        {
            dbnode::DbNode *newdbnode = new dbnode::DbNode;
            newdbnode->NewDbNode(dbid,new_servers[i]->serverIP,to_string(new_servers[i]->serverPort));
            db->DBnodeinsert(newdbnode);
            dbnode_list.push_back(newdbnode);
        }
       
        res.write(retv.dump());
        tool::NewServersDelete(new_servers);
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 数据库信息
    CROW_ROUTE(app, "/api/Monitor").methods(crow::HTTPMethod::POST)([&db, &servers,&dblog_list, &dbnode_list, &node_list, &database_list](const crow::request &req)
                                                                    {
    int part = servers.size();
    std::string req_body = req.body;
    nlohmann::json retv;
    nlohmann::json db_data;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string database_name = data["db_name"].s();
    std::string database_creater_id = data["database_creater_id"].s();
    std ::string user_id=data["dbuser_id"].s();
    std::string db_id;
    db_id = database_creater_id + database_name;
    dblog::DbLog *dblog=new dblog::DbLog;
    dblog->NewDbLog(user_id,"monitor",db_id);
    db->DbLogInsert(dblog);
    dblog_list.push_back(dblog);
    std::vector<GstoreConnector *> new_servers;
    new_servers = tool::DbIdGetNodes(servers,dbnode_list,db_id,node_list);
    for(int i=0;i<database_list.size();i++)
    {
        if(database_list[i]->get_database_id_()==db_id)
        {
            db_data =  database_list[i]->DbMonitor(new_servers);
        }
    }
    tool::NewServersDelete(new_servers);
    retv["data"] = db_data;
    retv["message"] = "success";
    crow::response res;
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 备份
    CROW_ROUTE(app, "/api/Backup").methods(crow::HTTPMethod::POST)([&db, &node_list, &dblog_list,&dbnode_list, &servers, &database_list, &dbbackup_list](const crow::request &requ)
                                                                   {
    std::string req_body = requ.body;
    crow::json::wvalue retv;
    crow::json::rvalue data = crow::json::load(req_body);
    std ::string database_name = data["dbname"].s();
    std ::string database_cuid = data["database_creater_id"].s();
    std ::string userid=data["dbuser_id"].s();
    std ::string version = data["version"].s();
    crow::response res;

    for(int j=0;j<dbbackup_list.size();j++)
    {
        if((database_cuid+database_name+version)==dbbackup_list[j]->get_backup_id_())
        {
            retv["message"]="this version already exists,please change one ";
            res.write(retv.dump());
            res.set_header("Content-Length", to_string(res.body.size()));
            return res;
        }
    }


    std::string path="/home/yyj/backup/";
    std ::string dbid;
    
    std::vector<GstoreConnector *> newservers;
    string dbpassword;
    dbid=database_cuid+database_name;
     newservers = tool::DbIdGetNodes(servers,dbnode_list,dbid,node_list);
     cout<<newservers.size();
    dblog::DbLog *dblog = new dblog::DbLog;
    dblog->NewDbLog(userid,"backup",dbid);
    db->DbLogInsert(dblog);
    dblog_list.push_back(dblog);
    retv["message"]="the database not exist";
    std::string flag;
    for(int i=0;i<database_list.size();i++)
    {
        if(database_list[i]->get_database_id_()==dbid)
        {
            if(database_list[i]->DbBackUp(newservers,path,version)!="fail")
            {
              
                flag=database_list[i]->DbBackUp(newservers,path,version);
                retv["message"]=flag;
            }
            else
            {
                
                retv["message"]="fail";
            }
            dbbackup::DbBackup *new_dbbackup = new dbbackup::DbBackup;
            std::string time;
            time=tool::extractAndFormatTimestamp(flag);
            new_dbbackup->NewDbBackup(dbid + version, dbid, version, path,time);
            db->BackupInsert(new_dbbackup);
            dbbackup_list.push_back(new_dbbackup);
        }
    }
   
    tool::NewServersDelete(newservers);

    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 恢复数据库
    CROW_ROUTE(app, "/api/Restore").methods(crow::HTTPMethod::POST)([&db, &database_list, &dblog_list,&servers, &node_list, &dbnode_list](const crow::request &requ)
                                                                    {
    std::string req_body = requ.body;
    crow::json::wvalue retv;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string database_name = data["dbname"].s();
    std::string database_creator_id = data["database_creater_id"].s();
    std::string datePath = data["datepath"].s();
    std ::string user_id=data["dbuserid"].s();
    std::string dbid;
    dbid = database_creator_id +database_name;
    dbid=GetDatabaseId(database_name,database_creator_id,database_list);
    dblog::DbLog *dblog=new dblog::DbLog;
    dblog->NewDbLog(user_id,"restore",dbid);
    db->DbLogInsert(dblog);
    dblog_list.push_back(dblog);
    std::vector<GstoreConnector *> newservers;
    newservers = tool::DbIdGetNodes(servers,dbnode_list,dbid,node_list);
    
    std::string path="/home/yyj/backup/"+dbid+".db_"+tool::ConvertDateTimeFormat(datePath);
    std::cout<<"&&&"<<path<<"&&&";
    std::string status;
    for(int i=0;i<database_list.size();i++)
    {
        if(database_list[i]->get_database_id_()==dbid)
        {
         status= database_list[i]->DbRestore(newservers,path);
        }
    }
    retv["data"]=status;
    tool::NewServersDelete(newservers);
    crow::response res;
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    CROW_ROUTE(app, "/api/DbQuery").methods(crow::HTTPMethod::POST)([&db, &database_list,&dblog_list, &servers, &dbnode_list, &node_list](const crow::request &req)
                                                                    {
    std::string req_body = req.body;
    nlohmann::json retv;
    crow::response res;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string database_name = data["db_name"].s();
    std::string database_creater_id = data["database_creater_id"].s();
    std::string entity = data["entity"].s();
    std::string inner_check = data["inner_check"].s();
    std ::string user_id=data["dbuser_id"].s();
    std::string db_id = database_creater_id + database_name;
    std::string query_sql = "select " + entity + " where\n{\n" + inner_check + "\n" + "}";
    dblog::DbLog *dblog=new dblog::DbLog;
    dblog->NewDbLog(user_id,"query",db_id);
    db->DbLogInsert(dblog);
    dblog_list.push_back(dblog);
    std::vector<GstoreConnector *> new_servers;
    new_servers = tool::DbIdGetNodes(servers,dbnode_list,db_id,node_list);
   // string dbid = database_name + database_creater_id;
     for (int i = 0; i < database_list.size(); i++)
    {
        if(database_list[i]->get_database_name_()==database_name&&database_list[i]->get_creater_id_()==database_creater_id)
        {
           retv =  database_list[i]->DbQuery(new_servers,query_sql);
        }
    }
    tool::NewServersDelete(new_servers);
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    res.set_header("Content-Type", "text/html;charset=utf-8");
    return res; });

    CROW_ROUTE(app, "/api/DbInsert").methods(crow::HTTPMethod::POST)([&db, &database_list,&dblog_list, &servers, &node_list, &dbnode_list](const crow::request &req)
                                                                     {
    std::string req_body = req.body;
    nlohmann::json retv;
    crow::response res;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string database_name = data["db_name"].s();
    std::string database_creater_id = data["database_creater_id"].s();
    std::string inner_check = data["inner_check"].s();
    std::string db_id = database_creater_id + database_name ;
    std ::string user_id=data["dbuser_id"].s();
    dblog::DbLog *dblog=new dblog::DbLog;
    dblog->NewDbLog(user_id,"insert",db_id);
    db->DbLogInsert(dblog);
    dblog_list.push_back(dblog);
    std::string insersql = "insert data\n{\n" + inner_check +"\n}";
    std::vector<GstoreConnector *> new_servers;
    new_servers = tool::DbIdGetNodes(servers,dbnode_list,db_id,node_list);
     for (int i = 0; i < database_list.size(); i++)
    {
        if(database_list[i]->get_database_name_()==database_name&&database_list[i]->get_creater_id_()==database_creater_id)
        {
           retv =  database_list[i]->DbInsert(new_servers,insersql);
        }
    }
    tool::NewServersDelete(new_servers);
    res.set_header("Content-Type", "text/html;charset=utf-8");
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    CROW_ROUTE(app, "/api/DbDelete").methods(crow::HTTPMethod::POST)([&db, &database_list, &servers,&dblog_list, &dbnode_list, &node_list](const crow::request &req)
                                                                     {
    std::string req_body = req.body;
    nlohmann::json retv;
    crow::response res;
    crow::json::rvalue data = crow::json::load(req_body);

    std::string database_name = data["db_name"].s();
    std::string database_creater_id = data["database_creater_id"].s();
    std::string inner_check = data["inner_check"].s();
    std ::string user_id=data["dbuser_id"].s();
    std::string db_id = database_creater_id+database_name;
    dblog::DbLog *dblog=new dblog::DbLog;
    dblog->NewDbLog(user_id,"deletedata",db_id);
    db->DbLogInsert(dblog);
    dblog_list.push_back(dblog);
    std::string deletesql = "delete where\n{\n" + inner_check +"\n}";
    std::vector<GstoreConnector *> new_servers;
    new_servers = tool::DbIdGetNodes(servers,dbnode_list,db_id,node_list);
   // string dbid = database_name + database_creater_id;
     for (int i = 0; i < database_list.size(); i++)
    {
        if(database_list[i]->get_database_name_()==database_name&&database_list[i]->get_creater_id_()==database_creater_id)
        {
           retv = database_list[i]->DbDelete(new_servers,deletesql);
        }
    }
    tool::NewServersDelete(new_servers);
    res.set_header("Content-Type", "text/html;charset=utf-8");
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    CROW_ROUTE(app, "/api/GetVersionToRestore")
    ([&dbbackup_list](const crow::request &req)
     {
      std::string database_id=req.url_params.get("database_id");
        nlohmann::json  retv;        
        retv["data"]=tojson::BackupIdToJson(BackupDisplayById(database_id,dbbackup_list)).dump(); 
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    CROW_ROUTE(app, "/api/GetDbLog")
    ([&dblog_list](const crow::request &req)
     {
         nlohmann::json retv;
         retv["data"]=tojson::DbLogToJson(dblog_list).dump();
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    CROW_ROUTE(app, "/api/GetPegLog")
    ([&peglog_list](const crow::request &req)
     {
         nlohmann::json retv;
         retv["data"] = tojson::PegLogToJson(peglog_list).dump();
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    CROW_ROUTE(app, "/api/GetDblogByDbuserId")
    ([&dblog_list, &db](const crow::request &req)
     {
         nlohmann::json retv;
         std::string dbuser_id = req.url_params.get("dbuser_id");
         retv["data"] = tojson::DbLogToJson(DbLogDisplayByDbuserId(dbuser_id, dblog_list)).dump();
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    CROW_ROUTE(app, "/api/GetDbLogByDbId")
    ([&dblog_list, &db](const crow::request &req)
     {
        nlohmann::json  retv;
        std::string db_name=req.url_params.get("db_name");
         std::string database_creater_id=req.url_params.get("database_creater_id");
      std::string db_id=database_creater_id+db_name;
        retv["data"]=tojson::DbLogToJson(DbLogDisplayByDbId(db_id,dblog_list)).dump();
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    CROW_ROUTE(app, "/api/GetPegLogByUserId")
    ([&peglog_list, &db](const crow::request &req)
     {
        nlohmann::json  retv;
        std::string user_id=req.url_params.get("user_id");
        retv["data"]=tojson::PegLogToJson(PegLogDisplayByUserid(user_id,peglog_list)).dump();
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });
    CROW_ROUTE(app, "/api/GetDatabaseNodeId").methods(crow::HTTPMethod::POST)([&db, &node_list, &dbnode_list](const crow::request &req)
                                                                              {
    nlohmann::json retv;
    std::string req_body = req.body;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string db_id = data["db_id"].s();
    std::vector<std::string> databasenode_id; 
    nlohmann::json dbnode_data = tojson::NodeIdDbIdToJson(tool::NodeDisplayByDbId(db_id,node_list,dbnode_list));
    retv["data"] = dbnode_data.dump();
    crow::response res;
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    CROW_ROUTE(app, "/api/GetPegLogFuzzyFind")
    ([&peglog_list, &db](const crow::request &req)
     {
         nlohmann::json retv;
         std::string fuzzy_str = req.url_params.get("fuzzy_str");
         retv["data"] = tojson::PegLogToJson(PegLogFuzzyFind(fuzzy_str, peglog_list)).dump();
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    CROW_ROUTE(app, "/api/IndexGetDatabase")
    ([&database_list, &db](const crow::request &req)
     {
        nlohmann::json  retv;
        std::string creater_id=req.url_params.get("user_id");
        std::vector<database::Database *> tmpdb;
        for(int i=0;i<database_list.size();i++)
        {
              if(database_list[i]->get_creater_id_() == creater_id)
              {
                  tmpdb.push_back(database_list[i]);
              }
        }
        nlohmann::json database_json = tojson::DatabaseToJson(tmpdb);
        retv["data"] = database_json;
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    CROW_ROUTE(app, "/api/IndexGetNode")
    ([&node_list, &servers](const crow::request &req)
     {
        nlohmann::json  retv;
        nlohmann::json node_json;
        for (int i = 0; i < node_list.size(); i++){
            node_json["data"][i]["id"] = node_list[i]->get_node_id_();
            node_json["data"][i]["ip"] = node_list[i]->get_node_ip_();
            node_json["data"][i]["port"] = node_list[i]->get_port_();
            node_json["data"][i]["version"] = node_list[i]->get_version_();
            node_json["data"][i]["rootpath"] = node_list[i]->get_rootpath_();
            bool flag=tool::CheckNode(servers,node_list[i]->get_node_ip_(),node_list[i]->get_port_());
            if(flag) node_json["data"][i]["status"]="t";
            else node_json["data"][i]["status"]="f";
        } 
        retv["data"] = node_json;
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });
    CROW_ROUTE(app, "/api/GetNode")
    ([&node_list, &db, &servers](const crow::request &req)
     {
        nlohmann::json  retv;
        nlohmann::json node_json= tojson::NodeToJson(node_list);
        retv["data"] = node_json;
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    // 显示论坛主页
    CROW_ROUTE(app, "/api/Forum")
    ([&post_list, &question_list, &peguser_list, &collection_list, &follower_list,
      &support_list, &comments_list, &chat_list](const crow::request &req)
     {
    //获得user_id
    std::string user_id=req.url_params.get("user_id");
    std::vector<std::string> user_postid=GetUserPostId(user_id,post_list);
    std::vector<std::string> user_questionid=question::GetUserQuestionId(user_id,question_list);
    int postlike_num=(support::GetUnreadPostSupportList(user_postid,support_list)).size();
    int questionlike_num=(support::GetUnreadQuestionSupportList(user_questionid,support_list)).size();
    int postcomments_num=(GetUnreadPostCommentsList(user_postid,comments_list)).size();
    int questioncomnents_num=(GetUnreadQuestionCommentsList(user_questionid,comments_list)).size();
    //nlohmann::json post_confJson=PostJson(post_list);
    //显示帖子数量、问答数量和人数
    nlohmann::json num=tojson::PostQUestionEnrollNumToJson(post_list.size(),question_list.size(),peguser_list.size());
    // 登录之后就应该一直处在连接状态，放在线程之中让它自己独立运行，直到收到信号停止

    //显示本人的关注数和收藏数
    nlohmann::json retv;
    crow::response res;
    retv["status"] = "success";
    retv["message"] = "success";
    retv["formData"]= num.dump();
    std::cout<<post_list.size()<<std::endl;
    retv["PostData"]= tojson::PostToJson(post_list).dump();
    retv["follow"] = GetConcernNum(follower_list,user_id);
    retv["favorites"]=collection::GetLovePostNum(user_id,collection_list);
    retv["unread_like"]=tool::AddTwo(postlike_num,questionlike_num);
    retv["unread_comments"]=tool::AddTwo(postcomments_num,questioncomnents_num);
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 查询帖子
    CROW_ROUTE(app, "/api/Forum").methods(crow::HTTPMethod::POST)([&post_list](const crow::request &req)
                                                                  {
        std::string req_body = req.body;
        nlohmann::json retv;
        crow::response res;
        crow::json::rvalue data = crow::json::load(req_body);
        std::string fuzzy_str=data["fuzzy_str"].s();
        std::vector<post::Post *> find_postlist=GetFuzzyFindPost(fuzzy_str,post_list);
        if(find_postlist.size()==0) {
            retv["status"]="failed";
        } else {
            retv["status"]="success";
            retv["data"] = tojson::PostToJson(find_postlist).dump();
        }
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 查看未读消息
    CROW_ROUTE(app, "/api/Forum/Unread")
    ([&db, &post_list, &question_list, &support_list, &comments_list, &peguser_list](const crow::request &req)
     {
        std::string user_id=req.url_params.get("user_id");
        nlohmann::json retv;
        std::vector<std::string> user_postid=GetUserPostId(user_id,post_list);
        std::vector<std::string> user_questionid=question::GetUserQuestionId(user_id,question_list);
        std::vector<comment::Comment *> unread_comments_list1=GetUnreadPostCommentsList(user_postid,comments_list);
        std::vector<comment::Comment *> unread_comments_list2=GetUnreadQuestionCommentsList(user_questionid,comments_list);
        unread_comments_list1.insert(unread_comments_list1.end(),unread_comments_list2.begin(),unread_comments_list2.end());
        std::vector<support::Support *> unread_support_list1=support::GetUnreadPostSupportList(user_postid,support_list);
        std::vector<support::Support *> unread_support_list2=support::GetUnreadQuestionSupportList(user_questionid,support_list);
        unread_support_list1.insert(unread_support_list1.end(),unread_support_list2.begin(),unread_support_list2.end());
        retv["support"]=tojson::UnreadSupportToJson(unread_support_list1,post_list,question_list,peguser_list).dump();
        retv["comments"]=tojson::UnreadCommentsToJson(unread_comments_list1,post_list,question_list,peguser_list).dump();
        if(db->SupportUpdate(unread_support_list1)){
            support_list=support::SetUnreadPostSupportList(user_postid,support_list);
            support_list=support::SetUnreadQuestionSupportList(user_questionid,support_list);
        }
        if(db->CommentUpdate(unread_comments_list1)){
            comments_list=SetUnreadPostCommentsList(user_postid,comments_list);
            comments_list=SetUnreadQuestionCommentsList(user_questionid,comments_list);
        }
        crow::response res;
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 显示论坛个人主页，包括关注、粉丝等信息
    CROW_ROUTE(app, "/api/Forum/Personal")
    ([&peguser_list, &follower_list, &post_list, &collection_list, &question_list](const crow::request &req)
     {
        std::string user_id=req.url_params.get("user_id");
        std::vector<post::Post *> user_post=GetUserPost(user_id,post_list);//获得个人所发布的帖子
        std::vector<collection::Collection *> user_collection=GetLovePostList(user_id,collection_list);
        std::vector<post::Post *> favorites_post = post::GetFavoritesPost(user_collection, post_list); // 个人收藏的帖子
        std::vector<question::Question *> user_question=GetUserQuestion(user_id,question_list);//个人所发出的问答
        nlohmann::json retv;
        crow::response res;
        retv["status"] = "success";
        retv["message"] = "success";
        if (peguser::GetUserName(user_id, peguser_list)=="null"){
            retv["data"]="null";
            res.write(retv.dump());
            res.set_header("Content-Length", to_string(res.body.size()));
            return res;
        }
        retv["name"] = peguser::GetUserName(user_id, peguser_list);
        retv["intro"]=peguser::GetUserIntroduction(user_id,peguser_list);
        retv["post_num"]=to_string(user_post.size());//帖子数量
        retv["question_num"]=to_string(user_question.size());
        retv["concern_num"]=GetConcernNum(follower_list,user_id);//关注数量
        retv["follower_num"]=GetFollowersNum(follower_list,user_id);//粉丝数量
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 论坛帖子主页
    CROW_ROUTE(app, "/api/Forum/UserInformation/Post")
    ([&post_list, &peguser_list](const crow::request &req)
     {
        bool delete_flag=true;
        std::string user_id=req.url_params.get("user_id");
        for(int i=0;i<peguser_list.size();i++){
            if(peguser_list[i]->get_user_id_()==user_id){
                delete_flag=false;
                break;
            }
        }
        nlohmann::json retv;
        crow::response res;
        retv["status"] = "success";
        retv["message"] = "success";
        if(!delete_flag){
        std::vector<post::Post *> user_post = post::GetUserPost(user_id, post_list); // 获得个人所发布的帖子
        nlohmann::json user_post_json=tojson::PostToJson(user_post);
        retv["post_data"]= user_post_json.dump();//该用户发布的帖子
        } else {
            retv["post_data"]="null";
        }
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 论坛问答主页
    CROW_ROUTE(app, "/api/Forum/UserInformation/Question")
    ([&question_list, &peguser_list](const crow::request &req)
     {
       bool delete_flag=true;
        std::string user_id=req.url_params.get("user_id");
        for(int i=0;i<peguser_list.size();i++){
            if(peguser_list[i]->get_user_id_()==user_id){
                delete_flag=false;
                break;
            }
        }
        nlohmann::json retv;
        crow::response res;
        retv["status"] = "success";
        retv["message"] = "success";
        if(!delete_flag){
        std::vector<question::Question *> user_question = GetUserQuestion(user_id, question_list); // 个人所发出的问答
        nlohmann::json user_question_json = tojson::QuestionToJson(user_question);
        retv["question_data"] = user_question_json.dump();
        } else {
            retv["question_data"] ="null";
        }
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 论坛个人收藏界面
    CROW_ROUTE(app, "/api/Forum/UserInformation/Favorites")
    ([&post_list, &collection_list, &peguser_list](const crow::request &req)
     {
        bool delete_flag=true;
        std::string user_id=req.url_params.get("user_id");
        for(int i=0;i<peguser_list.size();i++){
            if(peguser_list[i]->get_user_id_()==user_id){
                delete_flag=false;
                break;
            }
        }
        nlohmann::json retv;
        crow::response res;
        retv["status"] = "success";
        retv["message"] = "success";
        if(!delete_flag){
        std::vector<collection::Collection *> user_collection=GetLovePostList(user_id,collection_list);
        std::vector<post::Post *> favorites_post = GetFavoritesPost(user_collection, post_list); // 个人收藏的帖子
        nlohmann::json user_favorites_json=tojson::PostToJson(favorites_post);
        retv["favorites_data"]=user_favorites_json.dump();//该用户收藏的帖子
        } else {
            retv["favorites_data"] ="null";
        }
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 关注界面
    CROW_ROUTE(app, "/api/Forum/Follow")
    ([&peguser_list, &follower_list, &post_list, &collection_list, &support_list](const crow::request &req)
     {
        std::string user_id=req.url_params.get("user_id");
        std::vector<std::string> id_list=GetConcernList(follower_list,user_id);
        std::vector<peguser::UserInfor *> infor_list=peguser::GetUserInfor(id_list,peguser_list);
        std::vector<post::Post *> lately_postlist = GetLatelyUserPost(id_list, post_list);
        nlohmann::json retv;
        crow::response res;
        retv["user_infor"] = tojson::FollowToJson(infor_list).dump();
        retv["post_data"] = tojson::OneFollowPostToJson(lately_postlist,user_id,support_list,collection_list).dump();
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 点赞、收藏、关注，包括帖子详情页、取消点赞、取消收藏、取消关注
    CROW_ROUTE(app, "/api/Forum/Post/Details")
    ([&db, &post_list, &support_list, &collection_list, &comments_list,
      &follower_list](const crow::request &req)
     {
        nlohmann::json retv;
        crow::response res;
        retv["status"] = "success";
        retv["message"] = "success";
        std::string user_id=req.url_params.get("user_id");
        if(req.url_params.get("follow_id")==NULL){
        std::string post_id=req.url_params.get("post_id");
        if(req.url_params.get("like")!=NULL){//点赞
            //将点赞加1
            std::string support_str=req.url_params.get("like");
            post_list=ChangeSupport(post_id,support_str,post_list);
            post::Post *post = new post::Post;
            post=GetPost(post_id,post_list);
            db->PostSupportUpdate(post);
            //将点赞信息更新到点赞表中
            support::Support *support=new support::Support;
            if(support_str=="true"){
            support->NewSupport(post_id,user_id);
            db->SupportInsert(support);
            support_list.push_back(support);
            } else {
                support=GetSupportLog(user_id,post_id,support_list);
                db->SupportDelete(support);
                support_list=support::SupportDelete(user_id,post_id,support_list);
            }
        }
        else if(req.url_params.get("favorites")!=NULL){//收藏
        std::string collection_str=req.url_params.get("favorites");
           post_list=ChangeCollection(post_id,collection_str,post_list);
           post::Post *post = new post::Post;
           post = GetPost(post_id, post_list);
           db->PostCollectionUpdate(post);
           collection::Collection *collection = new collection::Collection;
           if (collection_str == "true")
           {
               collection->NewCollection(post_id, user_id);
               db->CollectionInsert(collection);
               collection_list.push_back(collection);
            } else {
               collection=collection::GetCollectionLog(user_id,post_id,collection_list);
                db->CollectionDelete(collection);
                collection_list=collection::CollectionDelete(user_id,post_id,collection_list); 
            }
        }
        else if(req.url_params.get("like")==NULL&&req.url_params.get("favorites")==NULL){
            post::Post *post = new post::Post;
            post=GetPost(post_id,post_list);//得到该帖子的具体内容
            std::vector<comment::Comment *> post_comments=GetPostComments(post_id,comments_list);
            std::string author_id=GetPostAuthorId(post_id,post_list);
            retv["data"]=(tojson::OnePostToJson(post)).dump();
            retv["comments"]=(tojson::PostCommentToJson(post_comments)).dump();
            retv["if_follow"]=IfFollowUser(user_id,author_id,follower_list);
            retv["if_liked"]=IfSupportPost(post_id,user_id,support_list);
            retv["if_collection"]=collection::IfCollectionPost(post_id,user_id,collection_list);
        }
        } else {
            std::string follow_str=req.url_params.get("follow");
            std::string follow_id=req.url_params.get("follow_id");
            follower::Follower *follower=new follower::Follower;
            if(follow_str=="true"){
            follower->NewFollow(follow_id,user_id);
            db->FollowInsert(follower);
            follower_list.push_back(follower);
            } else {
                follower=GetFollowLog(follow_id,user_id,follower_list);
                db->FollowDelete(follower);
                follower_list=FollowDelete(follow_id,user_id,follower_list);
            }
        }
        //crow::response res;
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 发评论（包括给帖子发评论和给问答发评论)
    CROW_ROUTE(app, "/api/Forum/Post").methods(crow::HTTPMethod::POST)([&db, &peguser_list, &comments_list, &post_list, &question_list](const crow::request &req)
                                                                       {
        std::string post_id=req.url_params.get("post_id");
        crow::json::wvalue retv;
        crow::response res;
        retv["status"]="failed";
        std::string req_body=req.body;
        crow::json::rvalue data=crow::json::load(req_body);
        std::string user_id=data["user_id"].s();
        std::string content=data["content"].s();
        std::vector<std::string> str_list;
        str_list.push_back(content);
        if (tool::CheckUnlawful(str_list))
        {
            retv["status"] = "unlawful";
            res.write(retv.dump());
            res.set_header("Content-Length", to_string(res.body.size()));
            return res;
        }
        comment::Comment *comment=new comment::Comment;
        std::string user_name=peguser::GetUserName(user_id,peguser_list);
        comment->NewComment(post_id,content,user_id,user_name);
        if(post_id.length()==7){
        post_list=AddComments(post_id,"true",post_list);
        post::Post *post = new post::Post;
        post=GetPost(post_id,post_list);
        if(db->PostCommentUpdate(post)){
        if(db->CommentInsert(comment)){
            comments_list.push_back(comment);
            retv["status"]="success";
        }
        }} else {
        question_list=AddComments(post_id,question_list);
        question::Question *question=new question::Question;
        question=GetNameQuestion(post_id,question_list);
        if(db->QuestionCommentUpdate(question)){
        if(db->CommentInsert(comment)){
            comments_list.push_back(comment);
            retv["status"]="success";
        }
        }
        }
        std::vector<comment::Comment *> post_comments=GetPostComments(post_id,comments_list);
        retv["comments_data"]=(tojson::PostCommentToJson(post_comments)).dump();
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 问答详情页,包括点赞
    CROW_ROUTE(app, "/api/Forum/Question/Detail")
    ([&db, &question_list, &comments_list, &support_list](const crow::request &req)
     {
        std::string question_id=req.url_params.get("questionId");
        nlohmann::json retv;
        crow::response res;
        retv["status"] = "success";
        retv["message"] = "success";
        std::string user_id=req.url_params.get("user");
        if(req.url_params.get("like")==NULL){
        question::Question *question=new question::Question;
        question=question::GetNameQuestion(question_id,question_list);//得到该问答的具体内容
        std::vector<comment::Comment *> question_comments=GetPostComments(question_id,comments_list);
        retv["data"]=(tojson::OneQuestionToJson(question)).dump();
        retv["comments"]=(tojson::QuestionCommentToJson(question_comments)).dump();
        retv["if_liked"] = IfSupportPost(question_id, user_id, support_list);
        } else {
            //将点赞加1
            std::string support_str=req.url_params.get("like");
            question_list=ChangeSupport(question_id,support_str,question_list);
            question::Question *question = new question::Question;
            question=GetNameQuestion(question_id,question_list);
            db->QuestionSupportUpdate(question);
            //将点赞信息更新到点赞表中
            support::Support *support=new support::Support;
            if(support_str=="true"){
            support->NewSupport(question_id,user_id);
            db->SupportInsert(support);
            support_list.push_back(support);
            } else {
                support=GetSupportLog(user_id,question_id,support_list);
                db->SupportDelete(support);
                support_list=support::SupportDelete(user_id,question_id,support_list);
            }
        }
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 设置最佳回答
    CROW_ROUTE(app, "/api/Forum/Question/Detail").methods(crow::HTTPMethod::POST)([&db, &question_list, &comments_list](const crow::request &req)
                                                                                  {
        std::string req_body=req.body;
        crow::json::rvalue data=crow::json::load(req_body);
        std::string question_id=data["question_id"].s();
        std::string commenter_id=data["user_id"].s();
        std::string comment_time=data["time"].s();
        comment::Comment *comment=new comment::Comment;
        comment=GetCommentAccordToIdTime(question_id,commenter_id,comment_time,comments_list);
        if(db->CommentUpdateBestAnswer(comment)) {
            comments_list=UpdateBestAnswer(comment,comments_list);
            db->QuestionResolvedUpdate(question_id);
            question_list=question::UpdateSolved(question_id,question_list);
        }
        nlohmann::json retv;
        crow::response res;
        retv["status"] = "success";
        retv["message"] = "success";
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 问答主页
    CROW_ROUTE(app, "/api/Forum/Question")
    ([&question_list](const crow::request &req)
     {
    nlohmann::json question_json=tojson::QuestionToJson(question_list);
    nlohmann::json retv;
    crow::response res;
    retv["status"] = "success";
    retv["message"] = "success";
    retv["question_data"]=question_json.dump();
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 发帖or发问答
    CROW_ROUTE(app, "/api/Forum/Creation/Editor").methods(crow::HTTPMethod::POST)([&db, &peguser_list, &post_list, &question_list, &draft_list](const crow::request req)
                                                                                  {
        std::string req_body=req.body;
        crow::json::rvalue data=crow::json::load(req_body);
        nlohmann::json retv;
        crow::response res;
        if(data.size()==5){
        std::string type=data["type"].s();//类型，帖子或问答
        std::string title=data["title"].s();//标题
        std::string content=data["content"].s();//内容
        std::vector<std::string> str_list;
        str_list.push_back(content);
        str_list.push_back(title);
        if (tool::CheckUnlawful(str_list))
        {
            retv["status"] = "unlawful";
            res.write(retv.dump());
            res.set_header("Content-Length", to_string(res.body.size()));
            return res;
        }
        std::string user_id=data["user_id"].s();
        std::string user_name=peguser::GetUserName(user_id,peguser_list);
        std::string choice=data["choice"].s();//该操作为保存还是直接发布
        bool flag=false;
        if(choice=="发布"){//直接发布
        if(type=="帖子"){//发布帖子
            post::Post *post = new post::Post;
            std::cout << title << content << user_id << user_name << std::endl;
            post->NewPost(user_id, user_name, title, content, post_list);
            if (db->PostInsert(post))
            {
                flag = true;
                post_list.push_back(post);
                std::cout<<post_list.size()<<std::endl;
        }
        } else {//发布问答
        question::Question *question=new question::Question;
        std::cout<<title<<content<<user_id<<user_name<<std::endl;
        question->NewQuestion(title,content,user_id,user_name,question_list);
        if(db->QuestionInsert(question)){
            flag=true;
            question_list.push_back(question);
        }
        }
        }
        else if(choice=="保存"){
            draft::Draft *draft=new draft::Draft;
            std::vector<draft::Draft *> certain_draft=draft::UserDraft(user_id,draft_list);
            draft->NewDraft(type,title,content,user_id);
            if(CheckDraft(title,certain_draft)){
                if(db->DraftInsert(draft)){
                    flag=true;
                    draft_list.push_back(draft);
                }
            }
        }
        if(flag==true){
        retv["status"] = "success";
        retv["message"] = "success";
        } else {
        retv["status"] = "failed";
        retv["message"] = "failed";
        }}
        else {
        std::string type=data["type"].s();
        std::string title=data["title"].s();
        std::string user_id=data["author_id"].s();
        std::vector<draft::Draft *> certain_draft=draft::UserDraft(user_id,draft_list);
        draft::Draft *draft=new draft::Draft;
        draft=GetDraftAccordIdTtile(type,title,certain_draft);
        if(db->DraftDelete(draft)) draft_list=draft::DraftDeleteCertain(draft,draft_list);
        retv["status"]="success";
        retv["data"]=tojson::OneDraftToJson(draft).dump();
        }
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res; });

    // 获取该用户草稿列表
    CROW_ROUTE(app, "/api/Forum/Creation/Editor")
    ([&draft_list](const crow::request &req)
     {
    std::string user_id=req.url_params.get("user_id");
    std::vector<draft::Draft *> certain_draft=draft::UserDraft(user_id,draft_list);
    nlohmann::json retv;
    retv["status"] = "success";
    if(certain_draft.size()==0){
        retv["status"]="null";
    } else {
    retv["data"]=tojson::DraftToJson(certain_draft).dump();
    }
    crow::response res;
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 进入聊天，返回所有关于这个人最新的聊天信息，显示在旁边的列表上
    // 给具体某一个人发消息，应该在获取到这个人id的时候，把他发给你的所有消息设置为已读
    CROW_ROUTE(app, "/api/Forum/Chat")
    ([&db, &chat_list, &peguser_list, &chathistory_list](const crow::request &req)
     {
     nlohmann::json retv;
     crow::response res;
     std::string user_id = req.url_params.get("user_id");
    //首先获取所有记录
    std::vector<chat::ChatHistory *> user_chathistory;
    for(auto it=chathistory_list.begin();it!=chathistory_list.end();it++){
        if(it->first==user_id){
            user_chathistory=it->second;
            std::cout<<"获取成功"<<std::endl;
            std::cout<<user_chathistory.size()<<std::endl;
            break;
        }
    }
    std::map<std::string, chat::Chat *> lately_chat = chat::GetLatelyChat(user_chathistory);
    retv["data"]=tojson::ChatHistoryToJson(lately_chat).dump();
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    CROW_ROUTE(app, "/api/Forum/Chat/Detail")
    ([&db, &chat_list, &peguser_list, &chathistory_list](const crow::request &req)
     {
     nlohmann::json retv;
     crow::response res;
     std::string user_id = req.url_params.get("user_id");
        std::string dest_id=req.url_params.get("dest_id");
        std::vector<chat::ChatHistory *> user_chathistory;
        for (auto it = chathistory_list.begin(); it != chathistory_list.end(); it++)
        {
            if (it->first == user_id)
            {
                user_chathistory = it->second;
                break;
            }
        }
        std::vector<chat::Chat *> thisuser_chat = chat::GetOneUserChat(dest_id, user_chathistory);
        db->ChatUpdateFlag(dest_id,user_id);
        retv["chat_data"]=tojson::OneUserChatToJson(thisuser_chat).dump();
        
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 发送消息到服务器
    CROW_ROUTE(app, "/api/Forum/Chat").methods(crow::HTTPMethod::POST)([&peguser_list, &chat_list, &db, &socket_list, &chathistory_list](const crow::request &req)
                                                                       {
        std::string req_body=req.body;
        crow::json::wvalue retv;
        crow::response res;
        crow::json::rvalue data=crow::json::load(req_body);
        std::string source_user_id=data["user_id"].s();
        std::string dest_user_id=data["dest_user_id"].s();
        std::string content=data["content"].s();
        std::vector<std::string> str_list;
        str_list.push_back(content);
        if (tool::CheckUnlawful(str_list) || content.find("client_connect") != content.npos ||
            content.find("message:") != content.npos || content.find("client_quit") != content.npos)
        {
            retv["status"] = "unlawful";
            res.write(retv.dump());
            res.set_header("Content-Length", to_string(res.body.size()));
            return res;
        }
        retv["status"]="success";
        //发送消息到服务器
        for(int i=0;i<socket_list.size();i++){
            if(socket_list[i]->user_id==source_user_id){
                if (chat::SendToServer(source_user_id, dest_user_id, content, socket_list[i]->fd) < 0)
                { // 发送消息到服务器失败
                    retv["status"] = "failed";
                }
                else
                {
                    chat::Chat *new_chat = new chat::Chat;
                    new_chat->NewChat(source_user_id, dest_user_id, content, peguser_list);
                    db->ChatInsert(new_chat);
                    chat_list.push_back(new_chat);
                    for (auto it = chathistory_list.begin(); it != chathistory_list.end(); it++)
                    {
                        if (it->first == source_user_id)//既要更新自己的聊天记录，也要更新别人的聊天记录
                        {
                            //返回一个vector<chathistory>
                            it->second = chat::UpdateChatHistory(dest_user_id,it->second,new_chat);
                        } else if (it->first==dest_user_id){
                            it->second=chat::UpdateChatHistory(source_user_id,it->second,new_chat);
                        }
                    }
                }
                break;
            }
        }
         res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    // 获取用户
    CROW_ROUTE(app, "/api/GetDbUser")
    ([&dbuser_list](const crow::request &req)
     {
        nlohmann::json  retv;

        std::string db_name = req.url_params.get("database_name");
        std::string creater_id = req.url_params.get("database_creater_id");
        std::string db_id = creater_id +db_name;
        std::vector<DbUser *> newDBuser;
        for(int i=0;i<dbuser_list.size();i++)
        {
            if(dbuser_list[i]->get_database_id_() == db_id)
            {
                newDBuser.push_back(dbuser_list[i]);
            }
        }
        nlohmann::json dbuser_json = tojson::DbUserToJson(newDBuser);
        retv["data"] = dbuser_json;
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    // 禁用用户
    CROW_ROUTE(app, "/api/BanDbUser")
    ([&dbuser_list, &db](const crow::request &req)
     {
        nlohmann::json  retv;
        std::string dbuser_id = req.url_params.get("dbuser_id");
        retv["state"] = "fail";
        for(int i=0;i<dbuser_list.size();i++)
        {
            if(dbuser_list[i]->get_dbuser_id_() == dbuser_id)
            {
                if(db->BanDbUser(dbuser_list[i]))
                {
                       retv["state"] = "success";
                }
                dbuser_list[i]->set_isban_("1");
            }
        }
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    // 启用用户
    CROW_ROUTE(app, "/api/ReuseDbUser")
    ([&dbuser_list, &db](const crow::request &req)
     {
        nlohmann::json  retv;
        std::string dbuser_id = req.url_params.get("dbuser_id");
        retv["state"] = "fail";
        for(int i=0;i<dbuser_list.size();i++)
        {
            if(dbuser_list[i]->get_dbuser_id_() == dbuser_id)
            {
                if (db->ReuseDbUser(dbuser_list[i]))
                {
                       retv["state"] = "success";
                }
                dbuser_list[i]->set_isban_("0");
            }
        }
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    // 改密码
    CROW_ROUTE(app, "/api/DbUserUpdatePassword")
    ([&dbuser_list, &db](const crow::request &req)
     {
        nlohmann::json retv;
        crow::response res;
        std::string dbuser_id = req.url_params.get("dbuser_id");
        std::string new_password = req.url_params.get("new_password");
        retv["state"] = "fail";
        std::vector<std::string> str_list;
        str_list.push_back(new_password);
        if (tool::CheckUnlawful(str_list))
        {
            retv["state"] = "unlawful";
            res.write(retv.dump());
            res.set_header("Content-Length", to_string(res.body.size()));
            return res;
        }
        for(int i=0;i<dbuser_list.size();i++)
        {
            if(dbuser_list[i]->get_dbuser_id_() == dbuser_id)
            {
                if (db->DbUserUpdatePassword(dbuser_list[i],new_password))
                {
                       retv["state"] = "success";
                }
                dbuser_list[i]->set_dbuser_pass_(new_password);
            }
        }
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    // 插入用户
    CROW_ROUTE(app, "/api/InsertDbUser")
    ([&dbuser_list, &db](const crow::request &req)
     {
        nlohmann::json  retv;
        crow::response res;
        std::string dbuser_id = req.url_params.get("dbuser_id");
        std::string database_name = req.url_params.get("database_name");
        std::string creater_id = req.url_params.get("creater_id");
        std::string dbuser_name = req.url_params.get("dbuser_name");
        std::string dbuser_pass = req.url_params.get("dbuser_pass");
        std::string database_id = creater_id + database_name;
        std::string isban = "0";
        bool flag =0;
        std::vector<std::string> str_list;
        str_list.push_back(dbuser_id);
        str_list.push_back(database_name);
        str_list.push_back(creater_id);
        str_list.push_back(dbuser_name);
        str_list.push_back(dbuser_pass);
            if (tool::CheckUnlawful(str_list))
        {
            retv["state"] = "unlawful";
            res.write(retv.dump());
            res.set_header("Content-Length", to_string(res.body.size()));
            return res;
        }
        for (int i = 0; i < dbuser_list.size(); i++)
        {
            if (dbuser_list[i]->get_dbuser_id_() == dbuser_id)
            {
                retv["state"] = "rebuild dbuser";
                flag = 1;
            }
        }
        if(!flag)
        {
         DbUser *newdbuser = new DbUser;
         newdbuser->NewDbUser(dbuser_id,database_id,dbuser_name,dbuser_pass,isban,creater_id);
        retv["state"] = "fail";
        if(db->DbUserInsert(newdbuser))
        {
            retv["state"] = "success";
        }
        }
        dbuser_list = db->DBUserDisplay();
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    CROW_ROUTE(app, "/api/UpdateNotice").methods(crow::HTTPMethod::POST)([&db, &notice_list](const crow::request &req)
                                                                         {
    std::string req_body = req.body;
    crow::json::wvalue retv;
    crow::response res;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string creater_id = data["creater_id"].s();
    std::string content = data["content"].s();
    std::string notice_topic = data["topic"].s();
    std::vector<std::string> str_list;
    str_list.push_back(content);
    str_list.push_back(content);
    if (tool::CheckUnlawful(str_list))
    {
        retv["state"] = "unlawful";
        res.write(retv.dump());
        res.set_header("Content-Length", to_string(res.body.size()));
        return res;
    }
    Notice *notice=new Notice;
    notice->NewNotice(creater_id,content,notice_topic);
    db->NoticeInsert(notice);
    notice_list.push_back(notice);
    retv["data"] = "success";
    res.write(retv.dump());
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });

    CROW_ROUTE(app, "/api/GetNotice")
    ([&notice_list](const crow::request &req)
     {
        nlohmann::json  retv;
        retv["data"]=tojson::NoticeToJson(notice_list).dump();
         crow::response res;
         
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    CROW_ROUTE(app, "/api/DeleteNotice").methods(crow::HTTPMethod::POST)([&db, &notice_list](const crow::request &req)
                                                                         {
    std::string req_body = req.body;
    crow::json::wvalue retv;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string notice_id = data["notice_id"].s();
    int notice_id_int=tool::StringToInt(notice_id);
    db->NoticeDelete(notice_id_int);
    for(int i=0;i<notice_list.size();i++)
    {
        if(notice_list[i]->get_notice_id_()==stoi(notice_id))
        {
            notice_list.erase(notice_list.begin()+i);
        }
    }
    retv["data"] = "success";
    crow::response res;
    res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    CROW_ROUTE(app, "/api/GetNoticeFuzzyFind")
    ([&notice_list, &db](const crow::request &req)
     {
         nlohmann::json retv;
         std::string fuzzy_str = req.url_params.get("fuzzy_str");

         std::vector<Notice *> notice_data = notice_list;
         for (int i = 0; i < notice_data.size(); i++)
         {
             if (!tool::FuzzySearch(notice_data[i]->get_notice_topic_(), fuzzy_str))
             {

                 notice_data.erase(notice_data.begin() + i);
                 i--;
             }
         }
         retv["data"] = tojson::NoticeToJson(notice_data).dump();
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });

    CROW_ROUTE(app, "/api/DbUserDelete")
    ([&dbuser_list, &db](const crow::request &req)
     {
        nlohmann::json  retv;
        std::string dbuser_id = req.url_params.get("dbuser_id");
        retv["state"] = "fail";
        for(int i=0;i<dbuser_list.size();i++)
        {
            if(dbuser_list[i]->get_dbuser_id_() == dbuser_id)
            {
                if (db->DbUserDelete(dbuser_list[i]))
                {
                       retv["state"] = "success";
                       dbuser_list.erase(dbuser_list.begin() + i);
                }
            }
        }
         crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });
    CROW_ROUTE(app, "/api/PegLogDelete").methods(crow::HTTPMethod::POST)([&db, &peglog_list](const crow::request &req)
                                                                         {

    std::string req_body = req.body;
    crow::json::wvalue retv;
    crow::json::rvalue data = crow::json::load(req_body);
    std::string peguser_id = data["peguser_id"].s();
     std::string peg_time = data["peg_time"].s();
    std::string peg_things = data["peg_things"].s();
    db->PegLogDelete(peguser_id,peg_time,peg_things);
    for(int i=0;i<peglog_list.size();i++)
    {
        if(peglog_list[i]->get_peg_user_id_()==peguser_id&&peglog_list[i]->get_peg_time_()==peg_time&&peglog_list[i]->get_peg_things_()==peg_things)
        {
            peglog_list.erase(peglog_list.begin()+i);
        }
    }

    retv["data"] = "success";

    crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });
    CROW_ROUTE(app, "/api/GetUserNum")
    ([&dbuser_list, &db, &peguser_list](const crow::request &req)
     {
        crow::json::wvalue retv;
    retv["message"] = to_string(peguser_list.size());
     crow::response res;
         res.write(retv.dump());
         res.set_header("Content-Length", to_string(res.body.size()));
         return res; });
    CROW_ROUTE(app, "/api/ManagerLogin").methods(crow::HTTPMethod::POST)([&node_list, &db, &servers](const crow::request &req)
                                                                         {
    std::string req_body=req.body;
    crow::json::rvalue data = crow::json::load(req_body);
    nlohmann::json retv;
    crow::response res;
    std::string manager_id=data["manager_id"].s();
    std::string manager_pass=data["manager_pass"].s();
    retv["data"]="fail";
    if(manager_id == "root"&& manager_pass == "root")
    {
        retv["data"] = "success";
    }
    res.set_header("Content-Type","text/html;charset=utf-8");
    res.write((retv.dump()));
    res.set_header("Content-Length", to_string(res.body.size()));
    return res; });
    app.port(18888).multithreaded().run();

    CROW_LOG_INFO << "Deleting GstoreConnector...";
    for (int i = 0; i < servers.size(); i++)
    {
        delete servers[i];
    }
    CROW_LOG_INFO << "Deleted GstoreConnector!";
    return 0;
}
