/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       dbutil.h
 * @brief      the DB class
 * @descripition
 * 成员函数：
 *  std::vector<database::Database *> DatabaseDisplay() 拉取数据库表信息并存储在Database类中
 *  bool DatabaseInsert(database::Database *database) 在数据库表中插入一条数据
 *  void DatabaseDelete(const std::string &idtodelete, std::vector<database::Database *> dblist) 在数据库表中删除数据
 *  std::vector<peguser::PEGUser *> UserDisplay() 拉取用户表信息并存储  
 *  bool UserModify(peguser::PEGUser *user) 修改用户表记录
 *  bool UserInsert(peguser::PEGUser *user) 在用户表中插入一条数据
 *  bool UserRecoverPassword(peguser::PEGUser *user) 修改用户表中对应id的用户密码
 *  std::vector<UserNode *> UserAndNodeDisplay() 拉取用户节点表信息并存储
 *  std::vector<node::Node *> NodeDisplay() 拉取节点表信息并存储
 *  bool NodeDelete(std::vector<std::string> node_id) 删除节点表中某条记录
 *  bool NodeInsert(node::Node *node) 在节点表中新增一条记录
 *  bool NodeModify(node::Node *node) 修改节点表中某条记录
 *  std::vector<std::map<std::string,std::string>>  NodeDisplayMap() 拉取节点表信息并存储在map中 
 *  std::vector<Dbuser *> DBUserDisplay() 拉取数据库用户表的信息并存储
 *  std::vector<Dbrestore *> RestoreDisplay() 拉取数据库还原表的信息并存储
 *  bool RestoreInsert(Dbrestore *restore) 在数据库还原表中插入一条信息
 *  
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef DBUTIL_H_
#define DBUTIL_H_

#include <mysql/mysql.h> // mysql文件
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <map>
#include "crow.h"
#include "../handler/node.h"
#include "../handler/peguser.h"
#include "../handler/dbuser.h"
#include "../handler/database.h"
#include "../handler/usernode.h"
#include "../handler/dbrestore.h"
#include "../handler/dbbackup.h"
#include "../handler/dblog.h"
#include "../handler/peglog.h"
#include "../handler/dbnode.h"
#include "../handler/post.h"
#include "../handler/question.h"
#include "../handler/collection.h"
#include "../handler/comment.h"
#include "../handler/support.h"
#include "../handler/follower.h"
#include "../handler/chat.h"
#include "../handler/draft.h"
#include "../handler/notice.h"
#include "../handler/token.h"
using namespace std;

class DB
{
public:
	MYSQL mysql; // 数据库句柄
	MYSQL_RES *res;
	MYSQL_ROW row;

	DB();

public:
	std::vector<database::Database *> DatabaseDisplay();
	bool DatabaseInsert(database::Database *database);
	void DatabaseDelete(const std::string &id);
	std::vector<peguser::PegUser *> UserDisplay();
	bool UserModify(peguser::PegUser *user);
	bool UserInsert(peguser::PegUser *user);
	bool UserRecoverPassword(peguser::PegUser *user);
	bool UserForbidden(const std::string &user_id,const std::string &flag);
	bool UserDelete(const std::string &user_id);
	bool UserResetPassword(const std::string &user_id);
	bool UserSetNamePassword(const std::string &user_id, const std::string &user_name, const std::string &user_password, const std::string &register_time);
	std::vector<UserNode *> UserAndNodeDisplay();
	std::vector<node::Node *> NodeDisplay();
	bool NodeDelete(std::vector<std::string> node_id);
	bool NodeInsert(node::Node *node);
	bool NodeModify(node::Node *node);
	std::vector<std::map<std::string,std::string>>  NodeDisplayMap();
	std::vector<DbUser *> DBUserDisplay();
	bool DbUserInsert(DbUser *dbuser);
	bool BanDbUser(DbUser *dbuser);
	bool ReuseDbUser(DbUser *dbuser);
	void PegLogDelete(string peguserid, string pegtime, string pegthings);
	bool DbUserUpdatePassword(DbUser *dbuser,std::string newpass);
	bool RestoreInsert(DbRestore *restore);
	std::vector<DbRestore *> RestoreDisplay();
	std::vector<dbbackup::DbBackup *> BackupDisplay();
	void DbLogInsert(dblog::DbLog *dblog);
	void PegLogInsert(peglog::PegLog *peglog);
	std::vector<peglog::PegLog *> PegLogDisplay();
	std::vector<dblog::DbLog *> DbLogDisplay();
	std::vector<dbnode::DbNode *> DbNodeDisplay();
	bool DbUserDelete(DbUser *dbuser);
	std::vector<post::Post *> PostDisplay();
	bool PostInsert(post::Post *post);
	bool PostSupportUpdate(post::Post *post);
	bool PostCollectionUpdate(post::Post *post);
	bool PostCommentUpdate(post::Post *post);
	std::vector<question::Question *> QuestionDisplay();
	bool QuestionInsert(question::Question *question);
	bool QuestionSupportUpdate(question::Question *question);
	bool QuestionCommentUpdate(question::Question *question);
	bool QuestionResolvedUpdate(const std::string &question_id);
	std::vector<draft::Draft *> DraftDisplay();
	bool DraftInsert(draft::Draft *draft);
	bool DraftDelete(draft::Draft *draft);
	std::vector<collection::Collection *> CollectionDisplay();
	bool CollectionInsert(collection::Collection *collection);
	bool CollectionDelete(collection::Collection *collection);
	std::vector<comment::Comment *> CommentDisplay();
	bool CommentInsert(comment::Comment *comment);
	bool CommentUpdate(std::vector<comment::Comment *> comments_list);
	bool CommentUpdateBestAnswer(comment::Comment *comment);
	std::vector<support::Support *> SupportDisplay();
	bool SupportInsert(support::Support *support);
	bool SupportDelete(support::Support *support);
	bool SupportUpdate(std::vector<support::Support *> support_list);
	std::vector<follower::Follower *> FollowerDisplay();
	bool FollowInsert(follower::Follower *follow);
	bool FollowDelete(follower::Follower *follow);
	std::vector<chat::Chat *> ChatDisplay();
	bool ChatInsert(chat::Chat *chat);
	bool ChatUpdateFlag(const std::string &source_id,const std::string &dest_id);
	void BackupInsert(dbbackup::DbBackup *backup);
	void NoticeInsert(Notice *notice);
	std::vector<Notice *> NoticeDisplay();
	void NoticeDelete(int &id);
	std::vector<Token *> TokenDisplay();
	bool TokenInsert(Token *token);
	bool DBnodeinsert(dbnode::DbNode *dbnode);
};


#endif//DBUTIL_H_