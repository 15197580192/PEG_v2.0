<template>
  <div class="login">
    <el-form class="login-container">
      <h1 class="title">用户登录</h1>
      <el-form-item label="">
        <el-input type="text" v-model="userName" placeholder="登录账号" autocomplete="off"></el-input>
      </el-form-item>
      <el-form-item label="">
        <el-input type="password" v-model="password" placeholder="登录密码" autocomplete="off" maxlength="20"></el-input>
      </el-form-item>

      <el-form-item>
        <!-- 图形验证码 -->
        <el-input type="text" v-model="verifyInput" style="width: 200px" placeholder="验证码" autocomplete="off"></el-input>
        <span id="v_container" @click="btncode" style="float: right"></span>
      </el-form-item>
      <el-form-item>
        <el-button type="primary" style="width:100%;" @click="doSubmit()">提交</el-button>
      </el-form-item>
      <el-row style="text-align: center;margin-top:-10px">
        <router-link to="/recover/password" style="float: left;">忘记密码</router-link>
        <router-link to="/Register" style="float: auto;">用户注册</router-link>
        <router-link to="/adminster/login" style="float: right;">管理员登录</router-link>
      </el-row>
    </el-form>
  </div>
</template>
 
<script>
// import http from "@/utils/request"
import { GVerify } from "../../components/gVerify"


export default {
  name: 'LoginForm',
  data() {
    return {
      MenuData: [
        {
          id: 1,
          parentid: "0",
          path: "/home",
          name: "home",
          lable: "首页",
          icon: "el-icon-s-home",
          url: "home/Home.vue",
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
              path: "/databaseManage/database",
              name: "database",
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
          path: "/forum",
          name: "forum",
          lable: "论坛",
          icon: "el-icon-chat-dot-round",
          url: "Forum/Forum.vue",
        },
        {
          id: 6,
          parentid: "0",
          path: "/introduction",
          name: "introduction",
          lable: "快速上手",
          icon: "el-icon-thumb",
          url: "Introuction/Introduction.vue",
        },
        {
          id: 7,
          parentid: "0",
          path: "/Personalization",
          name: "Personalization",
          lable: "个性化设置",
          icon: "el-icon-s-tools",
        },
      ],
      // tabList: [
      //   {
      //     path: "/home",
      //     name: "home",
      //     lable: "首页",
      //     icon: "el-icon-s-home",
      //     url: "home/Home.vue",
      //   },
      // ],

      userName: '',
      password: '',
      verifyInput: '',
      index2: 0,// 验证码 提示
      verifyCode: "",
      imgData: "", //验证码
    }

  },
  mounted() {//初始设置图形验证码
    if (this.$store.getters['user/userName'] != '' && this.$store.getters['user/password'] != "" && this.$store.getters['user/idntity'] == 'normal' && localStorage.getItem('token') != "") {
      this.$message({
        message: '用户' + this.$store.getters['user/userName'] + "，已经为您自动输入登录信息",
        type: 'success'
      });
      this.userName = this.$store.getters['user/userName'];
      this.password = this.$store.getters['user/password'];
    }
    this.verifyCode = new GVerify("v_container");
    this.imgData = this.verifyCode.options.code;
    console.log(localStorage.getItem('token'))
    if (this.$route.query.state == 'new') {
      this.$alert('新用户您好,您的id是' + this.$store.getters['user/userName'], '欢迎来到PEG系统', {
        confirmButtonText: '确定',
      });
    }
  },
  //页面跳转
  methods: {
    btncode() {//验证码
      this.imgData = this.verifyCode.options.code.substring(
        this.verifyCode.options.code.length - 4
      );
      console.log(this.imgData);
    },

    //实现登录，验证图形验证码
    doSubmit() {
      if (this.userName == '' || this.password == '') {
        this.$message({
          message: '输入不能为空',
          type: 'warning'
        });
        return;
      }
      if (this.verifyInput != this.imgData) {
        this.$message({
          message: '验证码不正确',
          type: 'warning'
        });
        return;
      }
      var data1 = JSON.stringify({
        user_id: this.userName,
        user_password: this.password
      });
      if (this.userName != this.$store.getters['user/userName']) {
        console.log(localStorage.getItem("token"))
        this.$store.dispatch('token/removeToken')
        console.log(localStorage.getItem("token"))
      }
      
      this.$http.post('/Login', data1,
        {
          headers: {
            "Content-Type": "application/json"
          }
        }
      ).then(
        (resp) => {
          var data = resp.data;
          // var data = {};
          // data.token = '2113ejiewjf'
          console.log(resp);
          if (data.state == 'success') {//需要自己定义successdata.statu == 'success'
            this.return = {};//清空
            this.$store.dispatch('user/saveUserInfo',
              { username: this.userName, password: this.password, identity: 'normal' });//存入本地缓存
            this.$store.dispatch('token/saveTokenInfo', data.token)
            this.$store.dispatch('user/setMenu', this.MenuData);
            // this.$store.dispatch('tab/setTabList', this.tabList);
            this.$store.dispatch('tab/setTabList');

            //退出时要清空
            this.$message({
              message: '登陆成功',
              type: 'success'
            });
            this.$router.push({ name: 'home', query: { state: 'old' } });
          }
          else if (data.state == 'id no exist') {
            this.$message({
              message: '用户不存在',
              type: 'warning'
            });
          }
          else if (data.state == 'inforbid') {
            this.$message({
              message: '用户被禁用',
              type: 'warning'
            });
          }
          else {
            this.$message({
              message: '用户信息错误',
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
  background-image: url("../../assets/background.jpg");
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

