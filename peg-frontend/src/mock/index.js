// import Mock from "mockjs";

// Mock.mock("/Login", "post", (item) => {
//   console.log(item);
//   return {
//     data: item.body,
//     state: "success",
//     token: "112",
//   };
// });

// Mock.mock("/ManagerLogin", "post", (item) => {
//   console.log(item);
//   return {
//     data: "success",
//     token: "112",
//   };
// });

// //首页数据库数量
// Mock.mock(RegExp("/GetDatabaseNum" + ".*"), "get", (item) => {
//   console.log(item);
//   return {
//     message: "8",
//   };
// });

// //管理员用户数量
// Mock.mock(RegExp("/GetUserNum"), "get", (item) => {
//   console.log(item);
//   return {
//     message: "8",
//   };
// });

// //数据库界面
// var database = [
//   {
//     database_name: "111",
//     database_id: "0",
//   },
//   {
//     database_name: "222",
//     database_id: "1",
//   },
//   {
//     database_name: "333",
//     database_id: "2",
//   },
//   {
//     database_name: "4444",
//     database_id: "3",
//   },
// ];
// // var dbcount = database.length;

// //数据库详细信息
// var dbData = {
//   StatusCode: 0,
//   StatusMsg: "success",
//   database: "nameabc",
//   creator: "222",
//   builtTime: "2023-11-30 11:43:37",
//   tripleNum: "80071",
//   entityNum: 21942,
//   literalNum: 2,
//   subjectNum: 14569,
//   predicateNum: 19,
//   connectionNum: 0,
//   diskUsed: 20,
//   subjectList: [
//     { name: "ub:University", value: 1 },
//     { name: "ub:TeachingAssistant", value: 407 },
//     { name: "ub:Department", value: 15 },
//     { name: "ub:Lecturer", value: 93 },
//     { name: "ub:ResearchGroup", value: 224 },
//     { name: "ub:ResearchAssistant", value: 532 },
//     { name: "ub:FullProfessor", value: 125 },
//     { name: "ub:AssociateProfessor", value: 176 },
//     { name: "ub:AssistantProfessor", value: 146 },
//     { name: "ub:GraduateStudent", value: 1874 },
//     { name: "ub:Course", value: 828 },
//     { name: "ub:GraduateCourse", value: 799 },
//   ],
// };
// var dbNode = [
//   {
//     id: "1",
//     ip: "ip",
//     port: "9000",
//     rootpath: "/data/gcluster/gStore0.8/gStore1",
//     version: "0.8",
//     status: "t",
//   },
//   {
//     id: "2",
//     ip: 2,
//     port: "/data/gcluster/gStore0.8/gStore2",
//     rootpath: "/data/gcluster/gStore0.8/gStore1",
//     version: "1",
//     status: "f",
//   },
//   {
//     id: "3",
//     ip: 4,
//     port: "/data/gcluster/gStore0.8/gStore1",
//     rootpath: "/data/gcluster/gStore0.8/gStore1",
//     version: "1",
//     status: "f",
//   },
//   {
//     id: "4",
//     ip: 3,
//     port: "/data/gcluster/gStore0.8/gStore1",
//     rootpath: "/data/gcluster/gStore0.8/gStore1",
//     version: "1",
//     status: "t",
//   },
// ];
// //数据库列表
// Mock.mock(RegExp("/GetDatabaseName" + ".*"), "get", (item) => {
//   console.log(item);
//   return {
//     data: JSON.stringify(database),
//   };
// });

// //数据库的节点拓扑图
// Mock.mock(RegExp("/IndexGetNode" + ".*"), "get", (item) => {
//   console.log(item);
//   return {
//     data: JSON.stringify(dbNode),
//   };
// });
// //详细信息
// Mock.mock(RegExp("/GetDatabaseInfo" + ".*"), "post", (item) => {
//   console.log(item);
//   return {
//     data: JSON.stringify(dbData),
//   };
// });

// //系统日志
// let log1 = {
//   peguserid: "123",
//   pegtime: "2022-12-4",
//   pegthings: "查看节点信息",
// };
// let log2 = {
//   peguserid: "246",
//   pegtime: "2023-12-4",
//   pegthings: "登录",
// };

// let log = [];
// log.push(log1);
// log.push(log2);
// log.push(log1);
// log.push(log2);
// log.push(log1);
// log.push(log2);

// Mock.mock("/GetPegLog", "get", (item) => {
//   console.log(item);
//   return {
//     data: JSON.stringify(log),
//   };
// });
// Mock.mock(RegExp("/PegLogDelete" + ".*"), "post", (item) => {
//   console.log(item);
//   return {
//     message: "success",
//   };
// });
// //模糊查找
// Mock.mock(RegExp("/GetPegLogFuzzyFind" + ".*"), "get", (item) => {
//   console.log(item);
//   return {
//     data: JSON.stringify(log2),
//   };
// });

// var notice1 = {
//   noticeid: "1",
//   noticetopic: "1111111111111111111111111好呀你好呀你好呀呀呀呀呀",
//   content:
//     "你好呀你好呀你好呀你好呀你好呀你好呀你好呀你好呀你好呀你好呀呀呀呀呀你好呀你好呀你好呀你好呀你好呀你好呀你好呀你好呀你好呀你好呀呀呀呀呀",
//   createrid: "111",
//   createtime: "2022/12/5 22:20:23",
// };
// var notice2 = {
//   noticeid: "2",
//   noticetopic:
//     "你好呀你好呀你好呀你好呀你好呀你好呀你好呀你好呀你好呀你好呀呀呀呀呀",
//   content: "啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊",
//   createrid: "222",
//   createtime: "2022/12/6 22:20:23",
// };
// let notice = [];
// notice.push(notice1);
// notice.push(notice2);

// Mock.mock("/GetNotice", "get", (item) => {
//   console.log(item);
//   return {
//     data: JSON.stringify(notice),
//   };
// });

// Mock.mock("/DeleteNotice", "post", (item) => {
//   console.log(item);
//   return {
//     message: "success",
//   };
// });

// var data = [
//   {
//     databaseid: "11111",
//     dbuserid: "22222",
//     operatetime: "222222",
//     operatetype: "1414",
//   },
//   {
//     databaseid: "11111",
//     dbuserid: "22222",
//     operatetime: "222222",
//     operatetype: "1414",
//   },
//   {
//     databaseid: "11111",
//     dbuserid: "22222",
//     operatetime: "222222",
//     operatetype: "1414",
//   },
//   {
//     databaseid: "11111",
//     dbuserid: "22222",
//     operatetime: "222222",
//     operatetype: "1414",
//   },
//   {
//     databaseid: "11111",
//     dbuserid: "22222",
//     operatetime: "222222",
//     operatetype: "1414",
//   },
//   {
//     databaseid: "11111",
//     dbuserid: "22222",
//     operatetime: "222222",
//     operatetype: "1414",
//   },
// ];
// Mock.mock("/GetDbLogByDbId", "get", (item) => {
//   console.log(item);
//   return {
//     data: JSON.stringify(data),
//   };
// });

// var user = [
//   {
//     creater_id: "11",
//     database_id: "2",
//     dbuser_id: "3",
//     dbuser_name: "111",
//     dbuser_pass: "2525",
//     isban: true,
//   },
//   {
//     creater_id: "11",
//     database_id: "2",
//     dbuser_id: "3",
//     dbuser_name: "111",
//     dbuser_pass: "2525",
//     isban: true,
//   },
//   {
//     creater_id: "11",
//     database_id: "2",
//     dbuser_id: "3",
//     dbuser_name: "111",
//     dbuser_pass: "2525",
//     isban: true,
//   },
//   {
//     creater_id: "11",
//     database_id: "2",
//     dbuser_id: "3",
//     dbuser_name: "111",
//     dbuser_pass: "2525",
//     isban: true,
//   },
//   {
//     creater_id: "11",
//     database_id: "2",
//     dbuser_id: "3",
//     dbuser_name: "111",
//     dbuser_pass: "2525",
//     isban: true,
//   },
// ];

// Mock.mock("/GetDbUser", "get", (item) => {
//   console.log(item);
//   return {
//     data: JSON.stringify(user),
//   };
// });

// Mock.mock("/SqlLogin", "post", (item) => {
//   console.log(item);
//   return {
//     state: "success",
//   };
// });
