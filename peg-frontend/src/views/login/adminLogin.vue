<template>
  <div class="login">
    <el-form class="login-container">
      <h1 class="title">管理员登录</h1>
      <el-form-item label="">
        <el-input type="text" v-model="userName" placeholder="登录账号" autocomplete="off"></el-input>
      </el-form-item>
      <el-form-item label="">
        <el-input type="password" v-model="password" placeholder="登录密码" autocomplete="off" maxlength="20"></el-input>
      </el-form-item>

      <el-form-item>
        <el-button type="primary" style="width:100%;" @click="doSubmit()">提交</el-button>
      </el-form-item>
      <el-row style="text-align: center;margin-top:-10px">
        <router-link to="/login">用户登录</router-link>
      </el-row>
    </el-form>
  </div>
</template>
 
<script>
export default {
  name: 'AdminForm',
  data() {
    return {
      userName: '',
      password: '',
      MenuData: [
        {
          id: 1,
          parentid: "0",
          path: "/Adminhome",
          name: "AdminHome",
          lable: "首页",
          icon: "el-icon-s-home",
          url: "home/AdminHome.vue",
        },
        {
          id: 2,
          parentid: "0",
          path: "/databaseManage",
          lable: "数据库管理",
          icon: "el-icon-coin",
          children: [
            {
              id: 3,
              parentid: "2",
              path: "/databaseManage/Admindatabase",
              name: "Admindatabase",
              lable: "数据库",
              icon: "el-icon-s-order",
              url: "dbabout/Database.vue",
            },
            {
              id: 4,
              parentid: "2",
              path: "/databaseManage/node",
              name: "node",
              lable: "节点",
              icon: "el-icon-cloudy-and-sunny",
              url: "dbabout/node/Node.vue",
            },
          ],
        },
        {
          id: 5,
          parentid: "0",
          path: "/systemeManage",
          lable: "系统管理",
          icon: "el-icon-s-platform",
          children: [
            {
              id: 6,
              parentid: "5",
              path: "/systemeManage/user",
              name: "user",
              lable: "用户管理",
              icon: "el-icon-user",
              url: "Systemabout/User.vue",
            },
            {
              id: 7,
              parentid: "5",
              path: "/systemeManage/systemlog",
              name: "systemlog",
              lable: "系统日志",
              icon: "el-icon-document",
            },
          ],
        },
        {
          id: 8,
          parentid: "0",
          path: "/noticeManage",
          lable: "公告管理",
          icon: "el-icon-edit-outline",
          children: [
            {
              id: 9,
              parentid: "8",
              path: "/noticeManage/noticeList",
              name: "noticeList",
              lable: "公告列表",
              icon: "el-icon-message",
            },
            {
              id: 10,
              parentid: "8",
              path: "/noticeManage/sendNotice",
              name: "sendNotice",
              lable: "发布公告",
              icon: "el-icon-document-add",
            },
          ],
        },
        {
          id: 12,
          parentid: "0",
          path: "/introduction",
          name: "introduction",
          lable: "快速上手",
          icon: "el-icon-thumb",
          url: "Introuction/Introduction.vue",
        },
        {
          id: 13,
          parentid: "0",
          path: "/Personalization",
          name: "Personalization",
          lable: "个性化设置",
          icon: "el-icon-s-tools",
        },
      ],

      // tabList: [
      //   {
      //     path: "/Adminhome",
      //     name: "AdminHome",
      //     lable: "首页",
      //     icon: "el-icon-s-home",
      //     url: "home/AdminHome.vue",
      //   },
      // ]
    }

  },
  mounted() {//初始设置图形验证码
    console.log(localStorage.getItem('token'))
  },
  //页面跳转
  methods: {

    //实现登录，验证图形验证码
    doSubmit() {
      if (this.userName == '' || this.password == '') {
        this.$message({
          message: '输入不能为空',
          type: 'warning'
        });
        return;
      }
      var data1 = JSON.stringify({
        manager_id: this.userName,
        manager_pass: this.password
      });
      console.log(data1)
      
      this.$http.post('/ManagerLogin', data1,
        {
          headers: {
            "Content-Type": "application/json"
          }
        }
      ).then(
        (resp) => {
          var data = resp.data;
          console.log(resp.data);
          if (data.data == 'success') {//需要自己定义success
            this.return = {};//清空
            this.$store.dispatch('user/saveUserInfo',
              { username: this.userName, password: this.password, identity: 'administrator' });//存入本地缓存
            this.$store.dispatch('token/saveTokenInfo', 'administrator')
            this.$store.dispatch('user/setMenu', this.MenuData);
            this.$store.dispatch('tab/setTabList');

            //退出时要清空
            this.$message({
              message: '登陆成功',
              type: 'success'
            });
            this.$router.push({ name: 'AdminHome', query: { state: 'old' } });
          }
          else {
            this.$message({
              message: '管理员信息错误',
              type: 'warning'
            });
          }
        }
      )
    }

  }
}
</script>
 
 
<style scoped>
.login {
  box-sizing: border-box;
  width: 100%;
  height: 100vh;
  padding-top: 10%;
  background-image: url("../../assets/background2.jpg");
  /* background-color: #112346; */
  background-repeat: no-repeat;
  background-position: center;
  background-size: 100%;
}



.login-container {
  border-radius: 10px;
  margin: 10px auto;
  width: 350px;
  padding: 30px 35px 15px 35px;
  background: #fff;
  border: 1px solid #ffffff;
  text-align: left;
  box-shadow: 0 0 20px 2px rgba(255, 255, 255, 0.1);
}

.title {
  margin: 0px auto 40px auto;
  text-align: center;
  color: #505458;
}
</style>