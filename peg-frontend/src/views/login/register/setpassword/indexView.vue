<template>
  <div class="login">
    <el-form class="login-container">
      <el-page-header @back="goBack">
      </el-page-header>
      <h1 class="title">用户注册</h1>
      <el-form-item label="">
        <el-input type="text" v-model="userName" placeholder="用户名" autocomplete="off">
        </el-input>
      </el-form-item>
      <el-form-item label="">
        <el-input type="password" v-model="setPassword" placeholder="设置密码" autocomplete="off"
          @focus="showMessage = true"></el-input>

      </el-form-item>
      <el-form-item label="">
        <el-input type="password" v-model="confirmPassword" placeholder="确认密码" autocomplete="off"></el-input>
      </el-form-item>
      <div style="font-size: 12px;color:rgb(206, 66, 66);" v-if="showMessage">请输入六位以上、包含数字字母密码</div>
      <el-form-item>
        <el-button type="primary" style="width:100%;" @click="doSubmit()" :disabled='state'>注册</el-button>
      </el-form-item>

    </el-form>
  </div>
</template>
 
<script>
// import { stringify } from 'querystring'
export default {
  name: 'SetPassword',
  data() {
    return {
      showMessage: false,
      userName: "",
      setPassword: "",
      confirmPassword: "",
      userId: "",
      state: false,
    }
  },
  mounted() {
    this.userId = this.$route.params.id;
    console.log(this.$route.params);
    if (this.userId === undefined) {
      this.$router.go(-1);
    }
    this.$store.dispatch('user/saveUserInfo',
      { username: this.userId, password: "111111", identity: 'normal' });
  },
  methods: {
    goBack() {
      this.$router.go(-1);
    },
    //返回登录
    gotoLogin() {
      this.$router.push('/login');
    },
    //提交表单信息，设置用户名密码
    doSubmit() {
      if (this.setPassword == '' || this.confirmPassword == '' || this.userName == '') {
        this.$message({
          message: '输入不能为空',
          type: 'warning'
        });
        return;
      }
      if (this.confirmPassword != this.setPassword) {
        this.$message({
          message: '两次密码不相同',
          type: 'warning'
        });
        return;
      }
      var params = this.setPassword
      if (!/^(?![\d]+$)(?![a-zA-Z]+$)(?![^\da-zA-Z]+$).{6,20}$/.test(params)) {
        this.$message({
          message: '密码强度不够',
          type: 'warning'
        });
        return;
      }
      else {
        this.showMessage = false;
        var data = JSON.stringify({
          user_id: this.userId,
          user_name: this.userName,
          password: this.setPassword,
        });
        this.state = true;
        //发送用户名和密码
        this.$http.post('/Enroll/Write', data, {
          headers: {
            "Content-Type": "application/json"
          }
        }).then(
          (resp) => {//根据返回码是否重名
            var data = (resp.data);
            if (data.status == 'success') {//需要自己定义success
              this.return = {}
              this.$message({
                message: '密码设置成功',
                type: 'success'
              });
              console.log(data);
              this.$store.dispatch('user/saveUserInfo',
                { username: this.userId, password: this.setPassword, identity: 'normal' });
              this.$router.push({ path: '/login', query: { state: 'new' } });
            }
            else {
              this.state = false;
              console.log('fail');
            }
          }
        )
      }
    },
  }
}



</script>
 
 
<style scoped>
.login {
  box-sizing: border-box;
  width: 100%;
  height: 100vh;
  padding-top: 10%;
  background-image: url("../../../../assets/background.jpg");
  /* background-color: #112346; */
  background-repeat: no-repeat;
  background-position: center;
  background-size: 100%;
}

.login-container {
  border-radius: 10px;
  margin: -30px auto;
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