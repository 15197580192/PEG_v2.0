/*==============================================================*/
/* DBMS name:      MySQL 5.0                                    */
/* Created on:     2023/11/20 15:17:05                          */
/*==============================================================*/


drop table if exists Administrator;

drop table if exists "Database restore";

drop table if exists "Graph visualization";

drop table if exists "PEG record";

drop table if exists conversation;

drop table if exists "database";

drop table if exists "datebase and node";

drop table if exists dbuser;

drop table if exists forum;

drop table if exists friends;

drop table if exists "leave words";

drop table if exists node;

drop table if exists "personalized setting";

drop table if exists picture;

drop table if exists "user daily record";

drop table if exists "user messages";

drop table if exists user_node;

/*==============================================================*/
/* Table: Administrator                                         */
/*==============================================================*/
create table Administrator
(
   Administrator_id     varchar(20) not null,
   Administrator_passward varchar(20),
   primary key (Administrator_id)
);

/*==============================================================*/
/* Table: "Database restore"                                    */
/*==============================================================*/
create table "Database restore"
(
   restore_id           int not null,
   database_id          varchar(100),
   restore_time         time,
   restore_version      decimal,
   primary key (restore_id)
);

/*==============================================================*/
/* Table: "Graph visualization"                                 */
/*==============================================================*/
create table "Graph visualization"
(
   Lattice_distribution float,
   data_collection      varchar(100),
   grahpid              decimal not null,
   database_id          varchar(100),
   primary key (grahpid)
);

/*==============================================================*/
/* Table: "PEG record"                                          */
/*==============================================================*/
create table "PEG record"
(
   pegrecord_id         decimal not null,
   database_id          varchar(100),
   opertion             varchar(100),
   message              varchar(100),
   time                 time,
   username             varchar(100),
   primary key (pegrecord_id)
);

/*==============================================================*/
/* Table: conversation                                          */
/*==============================================================*/
create table conversation
(
   conversation_id      decimal not null,
   friends_id           varchar(100),
   chatting_records     longtext,
   chatting_time        varchar(100),
   chatting_value       varchar(100),
   sendperson_id        varchar(100),
   reciveperson_id      varchar(100),
   primary key (conversation_id)
);

/*==============================================================*/
/* Table: "database"                                            */
/*==============================================================*/
create table "database"
(
   database_id          varchar(100) not null,
   user_id              varchar(100),
   database_name        varchar(100),
   createuser_id        varchar(100),
   database_passward    decimal,
   databse_version      decimal,
   statusCode           int,
   statusMsg            longtext,
   builtTime            time,
   tripleNum            int,
   entityNum            int,
   literalNum           int,
   subjectNum           int,
   predicateNum         int,
   connectionNum        int,
   primary key (database_id)
);

/*==============================================================*/
/* Table: "datebase and node"                                   */
/*==============================================================*/
create table "datebase and node"
(
   dn_id                decimal(8) not null,
   node_id              varchar(100),
   database_id          varchar(100),
   value                varchar(100),
   primary key (dn_id)
);

/*==============================================================*/
/* Table: dbuser                                                */
/*==============================================================*/
create table dbuser
(
   dbuser_id            decimal not null,
   database_id          varchar(100),
   dbuser_name          varchar(20),
   dbuser_pass          varchar(20),
   primary key (dbuser_id)
);

/*==============================================================*/
/* Table: forum                                                 */
/*==============================================================*/
create table forum
(
   article_id           varchar(100) not null,
   user_id              varchar(100),
   article_info         longtext,
   supports             int,
   reports              int,
   primary key (article_id)
);

/*==============================================================*/
/* Table: friends                                               */
/*==============================================================*/
create table friends
(
   friends_id           varchar(100) not null,
   user_id              varchar(100),
   primary key (friends_id)
);

/*==============================================================*/
/* Table: "leave words"                                         */
/*==============================================================*/
create table "leave words"
(
   leave_id             bigint not null,
   article_id           varchar(100),
   user_id              varchar(100),
   leave_info           longtext,
   leave_value          varchar(100),
   person_id            varchar(100),
   primary key (leave_id)
);

/*==============================================================*/
/* Table: node                                                  */
/*==============================================================*/
create table node
(
   node_id              varchar(100) not null,
   node_ip              varchar(100),
   gStorev              varchar(100),
   creator              varchar(100),
   create_time          varchar(100),
   primary key (node_id)
);

/*==============================================================*/
/* Table: "personalized setting"                                */
/*==============================================================*/
create table "personalized setting"
(
   user_id              varchar(100),
   font                 float,
   color                float,
   background           double,
   apply                bool
);

/*==============================================================*/
/* Table: picture                                               */
/*==============================================================*/
create table picture
(
   picture_id           int not null,
   picture_URL          varchar(100),
   picture_attribute    longtext,
   primary key (picture_id)
);

/*==============================================================*/
/* Table: "user daily record"                                   */
/*==============================================================*/
create table "user daily record"
(
   record_id            bigint not null,
   user_id              varchar(100),
   operation            longtext,
   operate_time         time,
   login_info           longtext,
   primary key (record_id)
);

/*==============================================================*/
/* Table: "user messages"                                       */
/*==============================================================*/
create table "user messages"
(
   user_id              varchar(100) not null,
   user_name            varchar(100),
   user_password        varchar(100),
   tel                  varchar(100),
   register_time        time,
   forbidden            bool,
   birthday             time,
   introduction         varchar(100),
   location             longtext,
   "e-mail"             varchar(100),
   sex                  varchar(100),
   adress               varchar(100),
   primary key (user_id)
);

/*==============================================================*/
/* Table: user_node                                             */
/*==============================================================*/
create table user_node
(
   un_id                decimal not null,
   user_id              varchar(100),
   node_id              varchar(100),
   primary key (un_id)
);

alter table "Database restore" add constraint FK_Relationship_3 foreign key (database_id)
      references "database" (database_id) on delete restrict on update restrict;

alter table "Graph visualization" add constraint FK_Relationship_38 foreign key (database_id)
      references "database" (database_id) on delete restrict on update restrict;

alter table "PEG record" add constraint FK_Relationship_13 foreign key (database_id)
      references "database" (database_id) on delete restrict on update restrict;

alter table conversation add constraint FK_Relationship_18 foreign key (sendperson_id)
      references friends (friends_id) on delete restrict on update restrict;

alter table "database" add constraint FK_Relationship_22 foreign key (user_id)
      references "user messages" (user_id) on delete restrict on update restrict;

alter table "datebase and node" add constraint FK_Relationship_15 foreign key (database_id)
      references "database" (database_id) on delete restrict on update restrict;

alter table "datebase and node" add constraint FK_Relationship_16 foreign key (node_id)
      references node (node_id) on delete restrict on update restrict;

alter table dbuser add constraint FK_Relationship_24 foreign key (database_id)
      references "database" (database_id) on delete restrict on update restrict;

alter table forum add constraint FK_Relationship_14 foreign key (user_id)
      references "user messages" (user_id) on delete restrict on update restrict;

alter table friends add constraint FK_Relationship_26 foreign key (user_id)
      references "user messages" (user_id) on delete restrict on update restrict;

alter table "leave words" add constraint FK_Relationship_17 foreign key (person_id)
      references "user messages" (user_id) on delete restrict on update restrict;

alter table "leave words" add constraint FK_Relationship_19 foreign key (article_id)
      references forum (article_id) on delete restrict on update restrict;

alter table "personalized setting" add constraint FK_Relationship_27 foreign key (user_id)
      references "user messages" (user_id) on delete restrict on update restrict;

alter table "user daily record" add constraint FK_Relationship_23 foreign key (user_id)
      references "user messages" (user_id) on delete restrict on update restrict;

alter table user_node add constraint FK_Relationship_20 foreign key (user_id)
      references "user messages" (user_id) on delete restrict on update restrict;

alter table user_node add constraint FK_Relationship_21 foreign key (node_id)
      references node (node_id) on delete restrict on update restrict;

