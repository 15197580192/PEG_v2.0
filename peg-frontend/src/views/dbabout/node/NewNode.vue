<template>
  <div class="sidebar-container">
    <el-card>
      <el-scrollbar class="scrollbar-wrapper">
        <!-- 内部文本-->
        <el-form :inline="true" :model="ruleForm" :rules="rules" ref="ruleForm" label-width="100px" class="demo-ruleForm">
          <h1 class="title">新建节点<i class="el-icon-close" style="float: right;" @click="goBack"></i></h1>

          <el-row>
            <el-form-item label="节点名称" prop="nodeId">
              <el-input v-model="ruleForm.nodeId"></el-input>
            </el-form-item>
            <el-form-item label="节点IP" prop="nodeIp">
              <el-input v-model="ruleForm.nodeIp"></el-input>
            </el-form-item>
          </el-row>
          <el-row>
            <el-form-item label="Linux用户" prop="userId">
              <el-input v-model="ruleForm.userId"></el-input>
            </el-form-item>
            <el-form-item label="gStore用户" prop="gstoreUserId">
              <el-input v-model="ruleForm.gstoreUserId"></el-input>
            </el-form-item>
          </el-row>
          <el-row>
            <el-form-item label="gStore密码" prop="gstoreUserPassword">
              <el-input v-model="ruleForm.gstoreUserPassword"></el-input>
            </el-form-item>
            <el-form-item label="gStore端口" prop="port">
              <el-input v-model="ruleForm.port"></el-input>
            </el-form-item>
          </el-row>
          <el-row>
            <el-form-item label="根路径" prop="rootPath">
              <el-input v-model="ruleForm.rootPath"></el-input>
            </el-form-item>
            <el-form-item label="gStore版本" prop="version">
              <el-select v-model="ruleForm.version" placeholder="请选择" style="width: 210px; ">
                <el-option label="0.8" value="0.8"></el-option>
                <el-option label="1.0" value="1.0"></el-option>
              </el-select>
            </el-form-item>
          </el-row>
          <el-row>
            <el-form-item label="接口类型" prop="apiType">
              <el-select v-model="ruleForm.apiType" placeholder="请选择" style="width: 210px; ">
                <el-option label="ghttp" value="ghttp"></el-option>
              </el-select>
            </el-form-item>
            <el-form-item style="width: 310px;">
              <span></span>
            </el-form-item>
          </el-row>
          <el-form-item style="text-align:center">
            <el-button type="primary" @click="submitForm('ruleForm')">立即创建</el-button>
            <el-button @click="resetForm('ruleForm')">重置</el-button>
          </el-form-item>
        </el-form>

      </el-scrollbar>
    </el-card>
  </div>
</template>

<script>
export default {
  data() {
    var validatePass = (rule, value, callback) => {
      if (value === '') {
        callback(new Error('请输入端口号'))
      } else if (!(/^\d+$/.test(value))) {
        callback(new Error('端口号为纯数字'))
      } else {
        callback()
      }
    }
    //新建节点信息
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

      },
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
        rootPath: [
          { required: true, message: '请输入根路径', trigger: 'blur' },
        ],
        port: [
          { required: true, validator: validatePass, trigger: 'blur' },
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
  methods: {
    //提交给后台处理
    submitForm(formName) {
      this.$refs[formName].validate((valid) => {
        if (valid) {
          var addNode = JSON.stringify(
            {
              node_id: this.ruleForm.nodeId,
              node_ip: this.ruleForm.nodeIp,
              user_id: this.ruleForm.userId,
              gstore_user_id: this.ruleForm.gstoreUserId,
              gstore_user_password: this.ruleForm.gstoreUserPassword,
              port: this.ruleForm.port,
              version: this.ruleForm.version,
              apitype: this.ruleForm.apiType,
              rootpath: this.ruleForm.rootPath,
            }
          );
          console.log(addNode);
          this.$http.post('/ManageNode/NewNode', addNode
          ).then(resp => {
            console.log(resp.data)
            if (resp.data.message == 'success') {
              this.$message({
                message: '新增成功',
                type: 'success'
              });
              this.$router.go(-1);
            }
            else if (resp.data.status == 'unlawful') {
              this.$message({
                message: '不能输入非法单引号',
                type: 'waring'
              });
            }
            else {
              this.$message({
                message: '新增失败',
                type: 'warning'
              });
            }
          }
          )
        } else {
          this.$message({
            message: '新增失败',
            type: 'warning'
          });
        }
      });

    },
    //重置表格，全部清空
    resetForm(formName) {
      this.$refs[formName].resetFields();
    },
    //返回节点管理
    goBack() {
      this.$confirm('是否退出新建节点?', '提示', {
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