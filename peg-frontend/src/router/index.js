import Vue from "vue";
import Router from "vue-router";
import Main from "@/views/Main.vue";
import Login from "@/views/login/Login";
import Home from "@/views/home/Home.vue";

Vue.use(Router);

//路由信息 哪个属性key看到  this.$route.matched=[{一级路由信息},{二级路由信息},...{当前路由信息}]

const routes = [
  {
    path: "/login",
    name: "login",
    component: Login,
    meta: {
      title: "登录",
      requiresAuth: false,
    },
  },
  {
    path: "/adminster/login",
    name: "adminlogin",
    component: () => import("../views/login/adminLogin"),
    meta: {
      title: "管理员登录",
      requiresAuth: false,
    },
  },

  {
    path: "/recover/password",
    name: "recoverpassword",
    component: () => import("../views/login/recoverpassword/indexView.vue"),
    meta: {
      title: "忘记密码",
      requiresAuth: false,
    },
  },
  {
    path: "/Register",
    name: "register",
    component: () => import("../views/login/register/indexView.vue"),
    meta: {
      title: "注册",
      requiresAuth: false,
    },
  },
  {
    path: "/register/password",
    name: "register2",
    component: () =>
      import("../views/login/register/setpassword/indexView.vue"),
    meta: {
      title: "注册",
      requiresAuth: false,
    },
  },
  {
    path: "/", //这个表示的是根目录，即一进入的页面
    name: "main",
    component: Main,
    redirect: "/login", // 重定向 设置页面一进来就显示的页面，这里写的内容是对应组将的component的值
    children: [
      {
        path: "/home",
        name: "home",
        component: Home,
        meta: {
          title: "PEG首页",
          requiresAuth: false,
        },
      },
      {
        path: "/Adminhome",
        name: "AdminHome",
        component: () => import("../views/home/AdminHome.vue"),
        meta: {
          title: "管理员首页",
          requiresAuth: true,
        },
      },
      {
        path: "/databaseManage/database",
        name: "database",
        component: () => import("../views/dbabout/Database.vue"),
        meta: {
          title: "数据库管理",
          requiresAuth: false,
        },
      },
      {
        path: "/databaseManage/Admindatabase",
        name: "Admindatabase",
        component: () => import("../views/dbabout/AdminDatabase.vue"),
        meta: {
          title: "数据库管理",
          requiresAuth: false,
        },
      },
      {
        path: "/databaseManage/node",
        name: "node",
        component: () => import("../views/dbabout/node/Node.vue"),
        meta: {
          title: "节点管理",
          requiresAuth: false,
        },
      },
      {
        path: "/databaseManage/node/newnode",
        name: "newnode",
        component: () => import("../views/dbabout/node/NewNode.vue"),
        meta: {
          title: "新建节点",
          requiresAuth: true,
        },
      },
      {
        path: "/databaseManage/node/fixnode",
        name: "fixnode",
        component: () => import("../views/dbabout/node/ChangeNode.vue"),
        meta: {
          title: "修改节点",
          requiresAuth: false,
        },
      },
      {
        path: "/systemeManage/user",
        name: "user",
        component: () => import("../views/Systemabout/User.vue"),
        meta: {
          title: "用户管理",
          requiresAuth: true,
        },
      },
      {
        path: "/systemeManage/systemlog",
        name: "systemlog",
        component: () => import("../views/Systemabout/Systemlog.vue"),
        meta: {
          title: "系统日志",
          requiresAuth: true,
        },
      },
      {
        path: "/noticeManage/noticeList",
        name: "noticeList",
        component: () => import("../views/Notice/NoticeList.vue"),
        meta: {
          title: "公告列表",
          requiresAuth: true,
        },
      },
      {
        path: "/noticeManage/sendNotice",
        name: "sendNotice",
        component: () => import("../views/Notice/Notice.vue"),
        meta: {
          title: "发布公告",
          requiresAuth: true,
        },
      },
      {
        path: "/forum/editor",
        name: "post",
        component: () => import("../views/Forum/Post"),
        meta: {
          title: "论坛发布",
          requiresAuth: false,
        },
      },
      {
        path: "/forum/post",
        name: "post",
        component: () => import("../views/Forum/article/post"),
        meta: {
          title: "论坛帖子",
          requiresAuth: false,
        },
      },
      {
        path: "/forum/question/detail",
        name: "post",
        component: () => import("../views/Forum/article/question"),
        meta: {
          title: "论坛问答",
          requiresAuth: false,
        },
      },
      {
        path: "/forum/search",
        name: "search",
        component: () => import("../views/Forum/MyPost"),
        meta: {
          title: "搜索",
          requiresAuth: false,
        },
      },
      {
        path: "/forum/unread",
        name: "unread",
        component: () => import("../views/Forum/unread"),
        meta: {
          title: "未读消息",
          requiresAuth: false,
        },
      },
      {
        path: "/forum/message",
        name: "message",
        component: () => import("../views/Forum/Message"),
        meta: {
          title: "我的私信",
          requiresAuth: false,
        },
      },
      {
        path: "/forum/follow",
        name: "follow",
        component: () => import("../views/Forum/Follow"),
        meta: {
          title: "论坛关注",
          requiresAuth: false,
        },
      },
      {
        path: "/forum/question",
        name: "question",
        component: () => import("../views/Forum/Question"),
        meta: {
          title: "论坛问答",
          requiresAuth: false,
        },
      },
      {
        path: "/forum/userInformation",
        name: "information",
        component: () => import("../views/Forum/UserInfor"),
        meta: {
          title: "论坛个人主页",
          requiresAuth: false,
        },
      },
      {
        path: "/forum",
        name: "forum",
        component: () => import("../views/Forum/Forum"),
        meta: {
          title: "论坛首页",
          requiresAuth: false,
        },
      },
      {
        path: "/introduction",
        name: "introduction",
        component: () => import("../views/Introuction/Introduction.vue"),
        meta: {
          title: "快速上手",
          requiresAuth: false,
        },
      },

      {
        path: "/Personalization",
        name: "Personalization",
        component: () => import("../views/Settingsabout/Personalization.vue"),
        meta: {
          title: "个性化设置",
          requiresAuth: false,
        },
      },
      {
        path: "/user",
        name: "user",
        component: () => import("../views/UserInformation/User.vue"),
        meta: {
          title: "个人信息",
          requiresAuth: false,
        },
      },
      {
        path: "/user/password",
        name: "password",
        component: () => import("../views/UserInformation/ChangePassword"),
        meta: {
          title: "重设密码",
          requiresAuth: false,
        },
      },
    ],
  },
  {
    path: "/databaseinterface", //数据库管理界面
    name: "databaseinterface",
    component: () => import("../views/dbabout/databaseinterface.vue"),
    redirect: "/databaseinterface/databaseinterface-query",
    meta: {
      title: "数据库首页",
      requiresAuth: false,
    },
    children: [
      {
        path: "/databaseinterface/databaseinterface-query", //查询
        name: "databaseinterface-query",
        component: () => import("../views/dbabout/databaseinterface-query.vue"),
        meta: {
          title: "数据库查询",
          requiresAuth: false,
        },
      },
      {
        path: "/databaseinterface/databaseinterface-delete", //删除
        name: "databaseinterface-delete",
        component: () =>
          import("../views/dbabout/databaseinterface-delete.vue"),
        meta: {
          title: "数据库删除",
          requiresAuth: false,
        },
      },
      {
        path: "/databaseinterface/databaseinterface-increase", //增加
        name: "databaseinterface-increase",
        component: () =>
          import("../views/dbabout/databaseinterface-increase.vue"),
        meta: {
          title: "数据库增加",
          requiresAuth: false,
        },
      },
      {
        path: "/databaseinterface/systemlog",
        name: "querylog",
        component: () => import("../views/dbabout/querylog.vue"),
        meta: {
          title: "数据库日志",
          requiresAuth: false,
        },
      },
      {
        path: "/databaseinterface/user", //用户管理
        name: "usermanage",
        component: () => import("../views/dbabout/usermanage.vue"),
        meta: {
          title: "数据库用户管理",
          requiresAuth: false,
        },
      },
    ],
  },
  {
    path: "/404",
    name: "NotFound",
    meta: {
      title: "Page not found",
      isLogin: false,
      requiresAuth: false,
    },
    component: () => import("@/views/NotFound"),
  },
  // 所有未定义路由，全部重定向到404页
  {
    path: "*",
    redirect: "/404",
  },
];

// 解决重复点击导航时，控制台出现报错
const VueRouterPush = Router.prototype.push;
Router.prototype.push = function push(to) {
  return VueRouterPush.call(this, to).catch((err) => err);
};
const router = new Router({
  // mode: "history",
  base: process.env.BASE_URL,
  routes,
});

export default router;
