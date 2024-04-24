<template>
  <div class="login">
    <el-form class="login-container">
      <el-page-header @back="goBack">
      </el-page-header>
      <h1 class="title">忘记密码</h1>
      <!-- <el-form-item label="">
        <el-input type="text" v-model="userId" placeholder="输入用户名" autocomplete="off"></el-input>
      </el-form-item> -->
      <el-form-item label="">
        <el-input type="text" v-model="userName" placeholder="绑定的邮箱" autocomplete="off">
          <el-select v-model="select" slot="append" placeholder="请选择" style="width: 120px;">
            <el-option label="@qq.com" value="@qq.com"></el-option>
            <el-option label="@163.com" value="@163.com"></el-option>
            <el-option label="@126.com" value="@126.com"></el-option>
          </el-select>
        </el-input>
      </el-form-item>
      <el-form-item label="">
        <el-input type="text" v-model="verification" style="width: 200px" placeholder="验证码" autocomplete="off"></el-input>

        <el-button type="primary" style="width:40%;float: right;" @click="doSendVerfication()" :disabled="isSend">{{
          codeName }}</el-button>
      </el-form-item>
      <el-form-item label="">
        <el-input type="password" v-model="resetPassword" placeholder="重设密码" autocomplete="off"
          @focus="showMessage = true"></el-input>
      </el-form-item>
      <el-form-item label="">
        <el-input type="password" v-model="confirmPassword" placeholder="确认密码" autocomplete="off"></el-input>
      </el-form-item>
      <div style="font-size: 12px;color:rgb(206, 66, 66);" v-if="showMessage">请输入六位以上、包含数字字母密码</div>
      <el-form-item>
        <el-button type="primary" style="width:100%;" @click="doSubmit()">提交</el-button>
      </el-form-item>

    </el-form>
  </div>
</template>
 
<script>
export default {
  name: 'RecoverPassword',
  data() {
    return {
      showMessage: false,
      userId: '',
      select: '',
      userName: "",
      resetPassword: "",
      confirmPassword: "",
      verification: "",
      isSend: false,  //禁用
      codeName: "发送验证码",
      totalTime: 60, //一般是60
      timer: '', //定时器
    }

  },
  methods: {
    goBack() {
      this.$router.go(-1);
    },
    //返回登录界面
    gotoLogin() {
      this.$router.push('/login');
    },
    //提交表单给后台，用于发送验证码
    doSendVerfication() {
      if (this.userName == '' && this.userId == '') {
        this.$message({
          message: '输入不能为空',
          type: 'warning'
        });
        return;
      }
      if (this.select == '') {
        this.$message({
          message: '请选择后缀',
          type: 'warning'
        })
        return
      }
      if (this.userName.includes('.') || this.userName.includes('@')) {
        this.$message({
          message: '邮箱号不正确',
          type: 'warning'
        })
        return
      }

      else {
        var data = JSON.stringify({
          // user_id: this.userId,
          mailbox: this.userName + this.select,
        })
        console.log(data);
        //发送手机号用于接收验证码
        this.$http.post('/RecoverPassword', data, {
          headers: {
            "Content-Type": "application/json"
          }
        }).then(
          (resp) => {
            console.log(resp)
            var data = resp.data;
            if (data.status == 'success') {//需要自己定义success
              this.$message({
                message: '成功发送验证码',
                type: 'success'
              });
              if (this.isSend) return;
              this.isSend = true;
              this.codeName = this.totalTime + 's后重新发送';
              this.timer = setInterval(() => {
                this.totalTime--;
                this.codeName = this.totalTime + 's后重新发送';
                if (this.totalTime < 0) {
                  clearInterval(this.timer);
                  this.codeName = '重新发送验证码';
                  this.totalTime = 60;
                  this.isSend = false;
                }
              }, 1000);
            }
            else {
              this.$message({
                message: '发送失败',
                type: 'warning'
              });
            }
          }
        ).catch(err => {
          this.$message({
            message: '发送失败',
            type: 'warning'
          });
        })
        // console.log(data)
      }
    },
    //提交整个表单，重置密码
    doSubmit() {
      if (this.resetPassword == '' || this.confirmPassword == '' || this.verification == '') {
        this.$message({
          message: '输入不能为空',
          type: 'warning'
        });
        return;
      }
      if (this.confirmPassword != this.resetPassword) {
        this.$message({
          message: '两次密码不相同',
          type: 'warning'
        });
        return;
      }
      var params = this.resetPassword;
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
          mailbox: this.userName + this.select,
          password: this.resetPassword,
          verification: this.verification
        });
        console.log(data);
        //发送手机号，密码，和验证码
        this.$http.post('/RecoverPassword', data, {
          headers: {
            "Content-Type": "application/json"
          }
        }).then(
          (resp) => {
            var data = resp.data;
            if (data.message == "success") {//需要自己定义success
              this.return = {};
              this.$message({
                message: '密码重设成功',
                type: 'success'
              });
              console.log(data);
              this.$router.push('/login');
            }
            else {
              this.$message({
                message: '输入错误',
                type: 'warning'
              });
            }
          }
        )
      }
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
  background-image: url("../../../assets/background.jpg");
  /* background-color: #112346; */
  background-repeat: no-repeat;
  background-position: center;
  background-size: 100%;
}

.login-container {
  border-radius: 10px;
  margin: auto auto;
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


