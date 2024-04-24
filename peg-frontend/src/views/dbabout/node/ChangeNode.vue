<template>
  <div class="sidebar-container">
    <el-card>
      <el-scrollbar class="scrollbar-wrapper">
        <!-- 内部文本-->
        <el-form :inline="true" :model="ruleForm" :rules="rules" ref="ruleForm" label-width="100px" class="demo-ruleForm">
          <h1 class="title">{{ showChange }}节点<i class="el-icon-close" style="float: right;" @click="goBack"></i></h1>
          <el-row>
            <el-form-item label="节点名称" prop="nodeId">
              <el-input v-model="ruleForm.nodeId" :readonly="!showButtom"></el-input>
            </el-form-item>
            <el-form-item label="节点IP" prop="nodeIp">
              <el-input v-model="ruleForm.nodeIp" :readonly="!showButtom"></el-input>
            </el-form-item>
          </el-row>
          <el-row>
            <el-form-item label="Linux用户" prop="userId">
              <el-input v-model="ruleForm.userId" :readonly="!showButtom"></el-input>
            </el-form-item>
            <el-form-item label="gStore用户" prop="gstoreUserId">
              <el-input v-model="ruleForm.gstoreUserId" :readonly="!showButtom"></el-input>
            </el-form-item>
          </el-row>
          <el-row>
            <el-form-item label="gStore密码" prop="gstoreUserPassword">
              <el-input v-model="ruleForm.gstoreUserPassword" :readonly="!showButtom"></el-input>
            </el-form-item>
            <el-form-item label="gStore端口" prop="port">
              <el-input v-model="ruleForm.port" :readonly="!showButtom"></el-input>
            </el-form-item>
          </el-row>
          <el-row>
            <el-form-item label="根路径" prop="rootPath">
              <el-input v-model="ruleForm.rootPath" :readonly="!showButtom"></el-input>
            </el-form-item>

            <el-form-item label="gStore版本" prop="version">
              <el-select v-model="ruleForm.version" placeholder="请选择" style="width: 210px; " :disabled="!showButtom">
                <el-option label="0.8" value="0.8"></el-option>
                <el-option label="1.0" value="1.0"></el-option>
              </el-select>
            </el-form-item>
          </el-row>
          <el-row align="middle">
            <el-form-item label="接口类型" prop="apiType">
              <el-select v-model="ruleForm.apiType" placeholder="请选择" style="width: 210px; " :disabled="!showButtom">
                <el-option label="ghttp" value="ghttp"></el-option>
                <el-option label="1" value="1"></el-option>
              </el-select>
            </el-form-item>
            <el-form-item label="状态" prop="state">
              <el-select v-model="ruleForm.state" placeholder="请选择" :disabled="!showButtom">
                <el-option label="已开启" value="1"></el-option>
                <el-option label="已关闭" value="0"></el-option>
              </el-select>
            </el-form-item>

          </el-row>
          <el-form-item style="text-align:center">
            <el-button type="primary" @click="submitForm('ruleForm')" v-if="showButtom">立即修改</el-button>
            <el-button @click="resetForm('ruleForm')" v-if="showButtom">重置</el-button>
          </el-form-item>
        </el-form>

      </el-scrollbar>
    </el-card>
  </div>
</template>

<script>
export default {
  data() {
    return {
      ruleForm: {
        nodeId: '',
        nodeIp: '',
        userId: '',
        gstoreUserId: '',
        gstoreUserPassword: '',
        port: '',
        version: '',
        apiType: '',
        rootPath: '',
        state: ' '
      },
      showChange: '',
      showButtom: true,
      rules: {
        nodeId: [
          { required: true, message: '请输入节点名称', trigger: 'blur' },
        ],
        nodeIp: [
          { required: true, message: '请输入节点IP', trigger: 'blur' },
        ],
        userId: [
          { required: true, message: '请输入用户名', trigger: 'blur' },
        ],
        gstoreUserId: [
          { required: true, message: '请输入用户名', trigger: 'blur' },
        ],
        gstoreUserPassword: [
          { required: true, message: '请输入密码', trigger: 'blur' },
        ],
        port: [
          { required: true, message: '请输入端口', trigger: 'blur' },
        ],
        rootPath: [
          { required: true, message: '请输入根路径', trigger: 'blur' },
        ],
        version: [
          { required: true, message: '请输入版本', trigger: 'blur' },
        ],
        apiType: [
          { required: true, message: '请输入接口类型', trigger: 'blur' },
        ],

      }
    };
  },
  //钩子函数，预先处理节点管理通过路由传递的信息
  mounted() {
    console.log(this.$route.query);
    this.ruleForm = this.$route.query;
    this.showChange = this.$route.query.identity;
    this.showChange == '修改' ? this.showButtom = true : this.showButtom = false
    // this.ruleForm.apitype = this.$router.query.api_type
    console.log(this.showButtom)
  },
  methods: {
    //提交表单给后台
    submitForm(formName) {
      this.$refs[formName].validate((valid) => {
        if (valid) {
          var modify = {
            node_id: this.ruleForm.nodeId,
            node_ip: this.ruleForm.nodeIp,
            user_id: this.ruleForm.userId,
            gstore_user_id: this.ruleForm.gstoreUserId,
            gstore_user_password: this.ruleForm.gstoreUserPassword,
            port: this.ruleForm.port,
            version: this.ruleForm.version,
            apitype: this.ruleForm.apiType,
            rootpath: this.ruleForm.rootPath,

          };
          console.log(modify);
          this.$http.post('/ManageNode/ModifyNode', JSON.stringify(modify)
          ).then(resp => {
            console.log(resp);
            if (resp.data.message == 'success') {
              this.$message({
                message: '修改成功',
                type: 'success'
              });
              this.$router.go(-1);
            }
          })
        } else {
          this.$message({
            message: '修改失败',
            type: 'warning'
          });
          return false;
        }
      });

    },
    //重置表单，全部清空
    resetForm(formName) {
      this.$refs[formName].resetFields();
    },
    //返回节点管理
    goBack() {
      this.$confirm('是否退出' + this.showChange + '节点?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        this.$router.go(-1);
      }).catch(() => { })


    }
  }
}
</script>
<style scoped>
.sidebar-container {
  width: auto;
  height: 70vh;
  margin-top: 20px;
}

.el-form {
  border-radius: 10px;
  margin: auto auto;
  padding: 5px 35px 15px 35px;
  text-align: center;

}

.title {
  margin: 0px auto 40px auto;
  text-align: center;
  color: #505458;
}
</style>