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
            <el-form :inline="true" :model="ruleForm" status-icon :rules="rules" ref="ruleForm" label-width="100px"
              class="demo-ruleForm">
              <el-row>
                <el-form-item label="用户名" prop="user_name">
                  <el-input v-model="ruleForm.user_name" readonly></el-input>
                </el-form-item>
                <el-form-item label="电话" prop="tel">
                  <el-input v-model="ruleForm.tel" v-bind:readonly="fixed"></el-input>
                </el-form-item></el-row>
              <el-row>

                <el-form-item label="性别" prop="sex">
                  <el-select v-model="ruleForm.sex" v-bind:disabled="fixed" style="width: 210px;">
                    <el-option label="男" value="男"></el-option>
                    <el-option label="女" value="女"></el-option>
                  </el-select>

                </el-form-item>
                <el-form-item label="生日" prop="birthday">

                  <el-date-picker type="date" placeholder="选择日期" value-format="yyyy-MM-dd" v-bind:disabled="fixed"
                    v-model="ruleForm.birthday" style="width: 210px;"></el-date-picker>
                </el-form-item></el-row>
              <el-row>
                <el-form-item label="注册时间" prop="registerTime">
                  <el-input v-model="ruleForm.registerTime" readonly></el-input>
                </el-form-item>
                <el-form-item label="状态" prop="forbidden">
                  <!-- 是否禁用 -->
                  <el-input v-model="ruleForm.forbidden" readonly></el-input>
                </el-form-item>

              </el-row><el-row>
                <el-form-item label="简介" prop="introduction">
                  <el-input v-model="ruleForm.introduction" v-bind:readonly="fixed"></el-input>
                </el-form-item>
                <el-form-item label="地区" prop="location">
                  <el-input v-model.number="ruleForm.location" v-bind:readonly="fixed"></el-input>
                </el-form-item></el-row>
              <el-row>

                <el-form-item label="电子邮箱" prop="email">
                  <el-input v-model.number="ruleForm.mailbox" readonly></el-input>
                </el-form-item>

                <el-form-item label="地址" prop="adress">
                  <el-input v-model.number="ruleForm.adress" v-bind:readonly="fixed"></el-input>
                </el-form-item></el-row>
              <el-row style="text-align: center;">
                <el-form-item>
                  <el-button v-bind:type="buttonState" @click="FixInformation(); getData();">{{ this.buttonInform
                  }}</el-button>
                  <el-button @click="Submit()" v-bind:disabled="buttonDisabled">提交</el-button>
                </el-form-item></el-row>
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
  //用户信息，包括姓名、性别等
  data() {
    return {
      fits: ['fill'],
      ruleForm: {
        userId: this.$store.getters['user/userName'],
        user_name: '',
        sex: '',
        tel: '',
        registerTime: '',
        forbidden: '',
        birthday: '',
        introduction: '',
        location: '',
        email: '',
        adress: ''
      },
      rules: {
        sex: [
          { required: true, message: '请输入性别', trigger: 'blur' },
        ],
        tel: [
          { required: true, message: '请输入电话号码', trigger: 'blur' },
        ],
        birthday: [
          { required: true, message: '请输入生日', trigger: 'blur' },
        ],
        location: [
          { required: true, message: '请输入地区', trigger: 'blur' },
        ],
        adress: [
          { required: true, message: '请输入地址', trigger: 'blur' },
        ],
      },
      fixed: true,
      buttonInform: "修改",
      buttonState: "primary",
      buttonDisabled: true
    }
  },
  //钩子函数，预先向后端获取用户信息
  mounted() {
    this.getData();
  },
  methods: {
    getData() {
      var url = '/User?user_id=' + this.$store.getters['user/userName'];
      console.log(url);
      this.$http.get(url).then(resp => {
        console.log(resp.data.data);//statussuccess
        var data = JSON.parse(resp.data.data);
        this.ruleForm = data;
        this.ruleForm.user_name = data.user_name;
        this.ruleForm.forbidden = data.forbidden == 1 ? '禁用' : '未禁用';
        this.ruleForm.registerTime = data.register_time;
        if (this.ruleForm.birthday == ' ') {
          this.ruleForm.birthday = '';
        }
        console.log(this.ruleForm)
        // this.ruleForm = JSON.parse(resp.data)
      });
    },
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
          if (this.ruleForm.introduction == "") {
            this.ruleForm.introduction == " ";
          }
          console.log(this.ruleForm);
          var getForm = JSON.stringify({
            user_id: this.$store.getters['user/userName'],
            user_name: this.ruleForm.user_name,
            sex: this.ruleForm.sex,
            tel: this.ruleForm.tel,
            birthday: this.ruleForm.birthday,
            introduction: this.ruleForm.introduction,
            location: this.ruleForm.location,
            mailbox: this.ruleForm.mailbox,
            adress: this.ruleForm.adress
          });
          console.log((getForm))
          this.$http.post('/User',
            (getForm)
          ).then(resp => {
            console.log(resp)
            if (resp.data.message == 'success') {
              // this.ruleForm = JSON.parse(resp.data.data)
              this.$message({
                message: '更改成功',
                type: 'success'
              });
              this.getData();
              this.FixInformation();
            }
            else {
              this.$message({
                message: '更改失败',
                type: 'warning'
              });
            }
          })
        }
        else {
          this.$message({
            message: '请提交规范格式',
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
}

.el-menu {
  border: solid;
  border-color: white;
}


.box-card {
  width: 90%;
  padding-top: 8vh;
  min-height: 62vh;
  display: flex;
  align-items: center;
  justify-content: center;
}

.el-form-item {
  height: 35px;
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