<template>
  <div class="login">
    <el-form class="login-container">
      <el-page-header @back="goBack">
      </el-page-header>
      <h1 class="title">用户注册</h1>
      <el-form-item label="">
        <el-input type="text" v-model="userName" placeholder="邮箱号" autocomplete="off">
          <el-select v-model="select" slot="append" placeholder="请选择" style="width: 120px;">
            <el-option label="@qq.com" value="@qq.com"></el-option>
            <el-option label="@163.com" value="@163.com"></el-option>
            <el-option label="@126.com" value="@126.com"></el-option>
          </el-select>
        </el-input>
      </el-form-item>
      <el-form-item label="">
        <el-input type="text" v-model="verification" style="width: 200px" placeholder="验证码" autocomplete="off"></el-input>
        <el-button type="primary" style="width:40%;float: right;" :disabled="isSend" @click="doSendVerfication()">{{
          codeName
        }}</el-button>
      </el-form-item>

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
      select: '',
      userName: "",
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
      // this.$router.push({ name: "register2", params: { id: '1234' } })
    },
    //提交手机号给后台，发送验证码
    doSendVerfication() {//手机登录，唯一标识
      if (this.userName == '') {
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
      var data = JSON.stringify({
        mailbox: this.userName + this.select,
      });
      //发送手机号
      this.$http.post('/Enroll', data, {
        headers: {
          "Content-Type": "application/json"
        }
      }).then((resp) => {
        console.log(resp);
        var data = resp.data;
        if (data.status == 'success') {//需要自己定义success
          this.$message({
            message: '成功发送验证码',
            type: 'success'
          });
          //发送到后台
          if (this.isSend)
            return;
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
            message: '邮箱已注册',
            type: 'fail'
          });
        }
      })
      console.log(data);


    },
    //提交表单，用于验证注册信息
    doSubmit() {

      if (this.userName == '' || this.verification == '') {
        this.$message({
          message: '输入不能为空',
          type: 'warning'
        });
        return;
      }
      var data = JSON.stringify({
        verification: this.verification,
        mailbox: this.userName + this.select
      });
      console.log(data)
      //发送验证码
      this.$http.post('/Enroll', data, {
        headers: {
          "Content-Type": "application/json"
        }
      }).then(
        (resp) => {
          console.log(resp)
          var data = resp.data;
          if (data.status == 'success') {//需要自己定义success
            this.return = {};
            this.$message({
              message: '验证成功',
              type: 'success'
            });
            console.log(data.data);
            this.$router.push({ name: "register2", params: { id: data.data } });
          }
          else {
            this.$message({
              message: '验证失败',
              type: 'warning'
            });
          }
        }
      )

      //console.log(data)

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
  margin: 30px auto;
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