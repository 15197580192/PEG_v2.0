/******************************************************************************
 * Copyright 2023-11-27 Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       tojson.h
 * @descripition  该头文件中包含将各个类数据转换成json格式的方法函数
 *
 * @author     袁永杰<1656113374@qq.com> 宋玉伟<2305129832@qq.com> 郑雨凡<1274502780@qq.com>
 * @date       2023/11/27
 * @history
 *****************************************************************************/
#ifndef TOJSON_H_
#define TOJSON_H_

#include <iostream>
#include <map>
#include <vector>
#include "../handler/json.hpp"
#include "../handler/node.h"
#include "../handler/peguser.h"
#include "../handler/database.h"
#include "../handler/dbbackup.h"
#include "../handler/dblog.h"
#include "../handler/peglog.h"
#include "../handler/support.h"
#include "../handler/post.h"
#include "../handler/question.h"
#include "../handler/comment.h"
#include "../handler/draft.h"
#include "../handler/chat.h"
#include "../handler/dbuser.h"
#include "../handler/notice.h"

namespace tojson
{
  nlohmann::json NodeToJson(std::vector<node::Node *> node_data);

  nlohmann::json DatabaseToJson(std::vector<database::Database *> database_data);

  nlohmann::json PEGUserToJson(peguser::PegUser *user);

  nlohmann::json PEGUserListToJson(std::vector<peguser::PegUser *> peguser_list);

  nlohmann::json ManagePEGUserListToJson(std::vector<peguser::PegUser *> peguser_list);

  nlohmann::json DatabaseJson(vector<database::Database *> databasevector);

  nlohmann::json DatabaseNameToJson(std::vector<std::string> database_name);

  nlohmann::json DbLogToJson(vector<dblog::DbLog *> dblog_vector);

  nlohmann::json PegLogToJson(vector<peglog::PegLog *> peglog_vector);

  nlohmann::json NodeIdDbIdToJson(vector<node::Node *> node_vector);

  // 将点赞转为json格式
  nlohmann::json UnreadSupportToJson(std::vector<support::Support *> support_list,
                                     std::vector<post::Post *> post_list,
                                     std::vector<question::Question *> question_list,
                                     std::vector<peguser::PegUser *> peguser_list);

  // 将评论转为json格式
  nlohmann::json UnreadCommentsToJson(std::vector<comment::Comment *> comments_list,
                                      std::vector<post::Post *> post_list,
                                      std::vector<question::Question *> question_list,
                                      std::vector<peguser::PegUser *> peguser_list);

  // 将post转为json格式
  nlohmann::json PostToJson(std::vector<post::Post *> post_list);

  // 将单个post转为json格式
  nlohmann::json OnePostToJson(post::Post *post);

  nlohmann::json OneFollowPostToJson(std::vector<post::Post *> post_list, const std::string &user_id, std::vector<support::Support *> support_list, std::vector<collection::Collection *> collection_list);
  // 将问答转为json格式
  nlohmann::json QuestionToJson(std::vector<question::Question *> question_list);

  // 将单个问答转为json格式
  nlohmann::json OneQuestionToJson(question::Question *question);

  // 将帖子数量、问答数量、注册人数转为json格式
  nlohmann::json PostQUestionEnrollNumToJson(const int &post_num, const int &question_num,
                                             const int &user_num);

  nlohmann::json FollowToJson(std::vector<peguser::UserInfor *> infor_list);

  // 将帖子评论转为json格式
  nlohmann::json PostCommentToJson(std::vector<comment::Comment *> comments_list);

  // 将问答评论转为json格式
  nlohmann::json QuestionCommentToJson(std::vector<comment::Comment *> comments_list);

  // 将草稿列表转为json格式
  nlohmann::json DraftToJson(std::vector<draft::Draft *> draft_list);

  // 将单个草稿转为json格式
  nlohmann::json OneDraftToJson(draft::Draft *draft);

  // 将最新的聊天记录转为json格式
  nlohmann::json ChatHistoryToJson(std::map<std::string, chat::Chat *> lately_chat);

  // 将具体聊天记录转为json格式
  nlohmann::json OneUserChatToJson(std::vector<chat::Chat *> chat_list);

  nlohmann::json DbUserToJson(vector<DbUser *> dbuser_list);

  nlohmann::json NoticeToJson(vector<Notice *> notice_vector);

  nlohmann::json BackupIdToJson(vector<dbbackup::DbBackup *> dbbackup_list);

  nlohmann::json BackupToJson(vector<dbbackup::DbBackup *> dbbackup_list);
}

#endif // TOJSON_H_