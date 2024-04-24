<template>
  <el-card class="box-card">
    <!-- 设置标题公告管理 -->
    <div slot="header" class="clearfix">
      <span style="font-size:25px">用户列表</span>
    </div>
    <el-container>
      <el-main>
        <!-- v-model="input2" -->
        <el-input placeholder="请输入内容" prefix-icon="el-icon-search" style="width: 30%;" v-model="searchData" clearable
          @clear="getData" @keyup.enter.native="searchTable">
        </el-input>
        <el-button type="primary" icon="el-icon-search" style="margin-left:10px;" @click="searchTable">搜索</el-button>
        <el-button type="danger" icon="el-icon-delete" style="float: right;" @click="delete_box">删除</el-button>
        <el-button type="primary" icon="el-icon-refresh" style="float: right;" @click="getmessage">刷新</el-button>
        <el-button type="primary" icon="el-icon-circle-plus-outline" style="float: right;"
          @click="SetNewUser">新增</el-button>
        <el-dialog title="新建用户" :visible.sync="dialogVisible" width="30%">
          <el-form ref="form" :model="form" label-width="80px" :rules="rules">
            <el-form-item label="姓名" prop="user_name">
              <el-input v-model="form.user_name"></el-input>
            </el-form-item>
            <el-form-item label="邮箱" prop="mailbox">
              <el-input v-model="form.mailbox"></el-input>
            </el-form-item>
            <el-form-item label="密码" prop="user_password">
              <el-input type="password" v-model="form.user_password"></el-input>
            </el-form-item>
            <el-form-item label="确认密码">
              <el-input type="password" v-model="confirmPassword"></el-input>
            </el-form-item>
          </el-form>
          <span slot="footer" class="dialog-footer">
            <el-button @click="dialogVisible = false">取 消</el-button>
            <el-button type="primary" @click="dialogVisible == false; submitUser();">确 定</el-button>
          </span>
        </el-dialog>
        <el-table :data="tableData.slice((currentPage - 1) * pageSize, currentPage * pageSize)" border
          style="width: 100%; margin-top: 20px; " @selection-change="handleSelectionChange" v-loading="listLoading">
          <!-- @row-click="textRowClick" -->
          <el-table-column type="selection" width="40" align="center">
          </el-table-column>
          <el-table-column fixed prop="user_id" label="用户ID" width="120">
          </el-table-column>
          <el-table-column prop="user_name" label="用户名" width="150">
          </el-table-column>
          <el-table-column prop="password" label="用户密码" width="120">
          </el-table-column>
          <el-table-column prop="tel" label="电话" width="120">
          </el-table-column>
          <el-table-column prop="register_time" label="注册时间" width="220">
          </el-table-column>
          <!-- <el-table-column prop="forbidden" label="状态" width="120">
          </el-table-column> -->
          <el-table-column prop="birthday" label="生日" width="120">
          </el-table-column>
          <el-table-column prop="introduction" :show-overflow-tooltip="true" label="简介" width="120">
          </el-table-column>
          <el-table-column prop="location" label="地区" width="120">
          </el-table-column>
          <el-table-column prop="mailbox" :show-overflow-tooltip="true" label="电子邮箱" width="220">
          </el-table-column>
          <el-table-column prop="sex" label="性别" width="120">
          </el-table-column>
          <el-table-column prop="adress" :show-overflow-tooltip="true" label="地址" width="120">
          </el-table-column>
          <el-table-column fixed="right" label="操作" width="200">
            <template v-slot="scope">
              <el-button @click="resetPassword(scope.row)" type="primary" size="small"
                class="table-buttom">重置密码</el-button>
              <el-button @click="forbidden(scope.row)" type="danger" size="small" class="table-buttom">{{
                scope.row.forbidden == '0' ? '禁用' : '解禁'
              }}</el-button>

            </template>
          </el-table-column>
          toggleRowSelection
        </el-table>
      </el-main>
      <el-footer>
        <div class="block" style="margin-top:15px;">
          <el-pagination align='center' @current-change="handleCurrentChange" :current-page="currentPage"
            :page-size="pageSize" layout="total,  prev, pager, next, jumper" :total="tableData.length">
          </el-pagination>
        </div>
      </el-footer>
    </el-container>
  </el-card>
</template>
<!-- rootpath -->
<script>
export default {

  // created() {
  //   this.getmessage();
  // },
  data() {
    var validatePass = (rule, value, callback) => {
      if (value === '') {
        callback(new Error('请输入密码'))
      } else if (!/^(?![\d]+$)(?![a-zA-Z]+$)(?![^\da-zA-Z]+$).{6,20}$/.test(value)) {
        callback(new Error('密码需要6-10位，包含数字、密码'))
      } else if (value !== this.confirmPassword) {
        callback(new Error('两次输入密码不一致!'))
      } else {
        callback()
      }
    }
    return {
      dialogVisible: false,
      form: {
        user_name: '',
        mailbox: '',
        user_password: ''
      },
      rules: {
        user_name: [
          { required: true, message: '请输入用户名', trigger: 'blur' },
        ],
        mailbox: [
          { required: true, message: '请输入邮箱号', trigger: 'blur' },
        ],
        user_password: [
          { required: true, validator: validatePass, trigger: 'blur' },
        ],
      },
      confirmPassword: '',
      tableData: [],//表格数据
      currentPage: 1, // 当前页码
      total: 20, // 总条数
      pageSize: 4, // 每页的数据条数
      multipleSelection: [],
      multiple: false,
      searchData: "",
      isForbidden: "禁用",
      listLoading: true,
    }
  },
  mounted() {
    this.getData()
  },
  methods: {
    getData() {
      this.listLoading = true
      this.$http.get('/ManagePegUser').then(resp => {
        console.log(resp);
        this.tableData = JSON.parse(resp.data.data);
        this.listLoading = false
      })
    },

    //当前页改变时触发 跳转其他页
    handleCurrentChange(val) {
      console.log(`当前页: ${val}`);
      this.currentPage = val;
    },
    //刷新时得到节点信息，请求
    getmessage() {
      const loading = this.$loading({
        lock: true,
        text: '刷新成功！',
        spinner: 'el-icon-loading',
        background: 'rgba(0, 0, 0, 0.7)'
      });
      setTimeout(() => {
        this.getData();
        loading.close()
      }, 1000);
    },
    //多选触发事件
    handleSelectionChange(val) {
      this.multipleSelection = val;
    },
    //删除用户、在多选之后
    delete_box() {
      console.log(this.multipleSelection)
      if (!this.multipleSelection.length) {
        this.$message({
          message: '请选择要删除的用户',
          type: 'warning'
        });
        return
      };
      var text = "";
      var params = [];
      this.multipleSelection.forEach((item) => {
        text = text + '用户' + item.user_id + ' ';
        params.push(item.user_id);
      })
      //text得到节点名显示在弹窗
      this.$confirm("是否确认删除" + text, '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        var data = JSON.stringify({ user_id: params });
        console.log(data);
        this.$http.post('/ManagePegUser/DeleteUser',
          data).then((resp) => {
            var dataNode = resp.data;
            if (dataNode) {
              console.log(dataNode);
              this.multipleSelection.forEach((item) => {
                var newtableData = this.tableData;
                this.tableData = newtableData.filter((it) => { return it != item });
              })//返回新的数据库内容
            }
          })
        this.$message({
          type: 'success',
          message: '删除成功!'
        });
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除'
        });
      });
    },
    SetNewUser() {
      this.dialogVisible = true;
    },
    submitUser() {
      if (this.form.user_password == "" || this.form.mailbox == "" || this.form.user_name == "") {
        this.$message({
          message: '内容不能为空',
          type: 'warning'
        });
        return;
      }

      // if (!/^(?![\d]+$)(?![a-zA-Z]+$)(?![^\da-zA-Z]+$).{6,20}$/.test(this.form.user_password)) {
      //   this.$message({
      //     message: '密码强度不够',
      //     type: 'warning'
      //   });
      // }
      // if (this.form.user_password != this.confirmPassword) {
      //   this.$message({
      //     message: '两次密码不一样',
      //     type: 'warning'
      //   });
      // }
      console.log(this.form)
      this.$refs["form"].validate((valid) => {
        if (valid) {
          this.$http.post('/ManagePegUser/NewUser', JSON.stringify(this.form)).then(resp => {
            console.log(resp);
            if (resp.data.status == 'success') {
              this.$message({
                type: 'success',
                message: '新增成功'
              });
              this.dialogVisible = false;
              this.tableData = JSON.parse(resp.data.data)
            }
            else {
              this.$message({
                type: 'warning',
                message: '新增失败'
              });
            }
          }
          )
        }
        else {
          this.$message({
            type: 'warning',
            message: '新增失败'
          });
        }
      })
    },
    //根据信息查询节点
    searchTable() {
      if (this.searchData == null || this.searchData === '') {
        this.$message({
          type: 'info',
          message: '查找内容为空'
        });
        return;
      }
      var newtableData = this.tableData;
      this.tableData = newtableData.filter((item) => {

        if (item.user_id == this.searchData || item.user_name == this.searchData) {
          console.log(item)
          return item;
        }
      })
    },
    //重置密码
    resetPassword(row) {
      this.$confirm('重置用户' + row.user_id + '密码为111111, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        this.$http.post('/ManagePegUser/RecoverPassword', JSON.stringify({
          user_id: row.user_id,
        })).then(resp => {
          console.log(resp);
          if (resp.data.status == 'success') {
            this.tableData = JSON.parse(resp.data.data)
          }
          else {
            this.$message({
              type: 'info',
              message: '重置失败'
            });
          }
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消'
        });
      });
    },
    forbidden(row) {
      this.$confirm((row.forbidden == '0' ? '禁用' : '解禁') + '用户' + row.user_id + ', 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        this.$http.post('/ManagePegUser/BanUser', { user_id: row.user_id, flag: row.forbidden == "0" ? "1" : "0" }).then(resp => {
          console.log(resp)
          if (resp.data.status == 'success') {
            this.tableData = JSON.parse(resp.data.data)
            console.log(this.tableData);
            this.$message({
              type: 'success',
              message: '修改成功!'
            });
            this.getData();
          }
        })
      }).catch(() => {
        return
      })
    }
  },
}
</script>

<style lang="less" scoped>
.table-buttom {
  width: 80px;
}

.el-container {
  min-height: 500px;
}

.text-id {
  font-size: large;
}

.box-card {
  width: 99%;
  height: 600px;
}

.clearfix:before,
.clearfix:after {
  display: table;
  content: "";
}

.clearfix:after {
  clear: both
}

.clearfix span {
  font-weight: 600;
}

.el-card {

  ::v-deep .el-card__header {
    padding: 10px 20px !important;
  }

  ::v-deep .el-card__body {
    padding: 10px 20px 0 20px !important;
  }
}
</style>