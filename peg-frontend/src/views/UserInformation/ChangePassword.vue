<template>
  <el-container class="demo-image">

    <el-aside width="200px" style="width: 100px;">
      <div class="block" v-for="fit in fits" :key="fit" style=" margin-top: 4vh;">

        <el-image style="width: 100px; height: 100px" :src="require('../../assets/user.png')" :fit="fit"></el-image>
      </div>
      <div class="userId">
        ID:{{ this.$store.getters['user/userName'] }}
      </div>
      <el-menu :default-active="this.$router.path" router>
        <el-menu-item index="/user">
          <template slot="title">个人信息</template>
        </el-menu-item>
        <el-menu-item index="/user/password">
          <template slot="title">修改密码</template>
        </el-menu-item>
      </el-menu>
    </el-aside>
    <el-container>
      <el-main>
        <el-card class="box-card">
          <div class="text item">
            <el-form :model="ruleForm" status-icon :rules="rules" ref="ruleForm" label-width="100px"
              class="demo-ruleForm">
              <el-form-item label="原密码" prop="userPassword">
                <el-input type="password" v-model="ruleForm.userPassword" v-bind:readonly="fixed"></el-input>
              </el-form-item>
              <el-form-item label="新密码" prop="newPassword">
                <el-input type="password" v-model="ruleForm.newPassword" v-bind:readonly="fixed"></el-input>
              </el-form-item>
              <el-form-item label="确认密码" prop="requirePassword">
                <el-input type="password" v-model="ruleForm.requirePassword" v-bind:readonly="fixed"></el-input>
              </el-form-item>

              <el-form-item>
                <el-button v-bind:type="buttonState" @click="FixInformation">{{ this.buttonInform }}</el-button>
                <el-button @click="Submit()" v-bind:disabled="buttonDisabled">提交</el-button>
              </el-form-item>
            </el-form>
          </div>

        </el-card>
      </el-main>
    </el-container>
  </el-container>
</template>
<script>
export default {
  name: "userInformation",
  //信息包括旧密码、新密码、确认密码
  data() {
    var validatePass = (rule, value, callback) => {
      if (value === '') {
        callback(new Error('请输入密码'))
      } else if (!/^(?![\d]+$)(?![a-zA-Z]+$)(?![^\da-zA-Z]+$).{6,20}$/.test(value)) {
        callback(new Error('密码需要6-10位，包含数字、密码'))
      } else {
        callback()
      }
    }
    var validatePass2 = (rule, value, callback) => {
      if (value === '') {
        callback(new Error('请再次输入密码'))
      } else if (value !== this.ruleForm.newPassword) {
        callback(new Error('两次输入密码不一致!'))
      } else {
        callback()
      }
    }
    return {
      fits: ['fill'],
      ruleForm: {
        userPassword: '',
        newPassword: '',
        requirePassword: ''
      },
      rules: {
        userPassword: [
          { required: true, message: '请输入原密码', trigger: 'blur' },
        ],
        newPassword: [
          { required: true, validator: validatePass, trigger: 'blur' },
        ],
        requirePassword: [
          { required: true, validator: validatePass2, trigger: 'blur' }
        ]
      },

      fixed: true,
      buttonInform: "修改",
      buttonState: "primary",
      buttonDisabled: true
    }
  },
  methods: {
    //按下按钮，将按钮内容改变，个人信息变得可修改，提交按钮禁用取消
    FixInformation() {
      if (this.buttonInform == '修改') {
        this.buttonState = 'danger';
        this.buttonInform = '取消';
        this.fixed = false;
        this.buttonDisabled = false;
      }
      else if (this.buttonInform == '取消') {
        this.buttonState = 'primary';
        this.buttonInform = '修改';
        this.fixed = true;
        this.buttonDisabled = true;
      }

    },
    //按下提交按钮，提交ruleForm给后端
    Submit() {
      this.$refs["ruleForm"].validate((valid) => {
        if (valid) {
          var passwordData = {
            old_password: this.ruleForm.userPassword,
            new_password: this.ruleForm.newPassword,
          };
          this.$http.post('/ChangePassword?user_id=' + this.$store.getters['user/userName'],
            JSON.stringify(passwordData)).then(resp => {
              if (resp.data.message == "success") {
                console.log(resp.data);
                this.$message({
                  message: '密码更改成功',
                  type: 'success'
                });
              }
              else {
                this.$message({
                  message: '更改失败',
                  type: 'warning'
                });
              }
            });
        }
        else {
          this.$message({
            message: '更改失败',
            type: 'warning'
          });
        }
      })
    }
  }
}
</script>

<style scoped>
.text {
  font-size: 14px;
}

.item {
  padding: 10px 0;
  width: 400px;
  text-align: center;
}

.box-card {
  width: 90%;
  min-height: 62vh;
  padding-top: 8vh;
  text-align: center;
  display: flex;
  align-items: center;
  justify-content: center;

}

.el-form-item {
  height: 35px;
}

.el-menu {
  border: solid;
  border-color: white;
}

.userId {
  font-size: 12px;
  line-height: 1.5;
  width: 100%;
  padding-bottom: 16px;
  color: rgba(110, 105, 105, 0.65);
  text-align: auto;
}
</style>