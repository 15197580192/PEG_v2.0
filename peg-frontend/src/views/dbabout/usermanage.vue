<template>
  <el-card class="box-card">
    <div slot="header" style="font-size: 20px; font-weight: 600">
      用户管理
    </div>
    <el-container>
      <el-main>
        <div style="margin-top:-5px;float: right;">
          <el-button type="primary" @click="usercontrol(1)">新增用户</el-button>
          <el-button type="primary" @click="usercontrol(2)">查看用户</el-button>
          <el-button type="primary" @click="usercontrol(3)">修改密码</el-button>
          <el-button type="danger" @click="deleteuser">删除用户</el-button>
        </div>
        <el-table v-loading="listLoading" :data="dataModel.slice((currentPage - 1) * pageSize, currentPage * pageSize)"
          style="width: 100%; margin-top: 100px;" border>
          <el-table-column fixed="left" label="操作" width="50" align="center">
            <template slot-scope="scope">
              <input @change="getmessage(scope.row)" type="radio" name="scope.row.HandleState" />
            </template>
          </el-table-column>
          <el-table-column prop="creater_id" label="创建者ID" width="150" align="center">
          </el-table-column>
          <el-table-column prop="database_id" label="数据库" width="150" align="center">
          </el-table-column>
          <el-table-column prop="dbuser_id" label="数据库用户ID" width="180" align="center">
          </el-table-column>
          <el-table-column prop="dbuser_name" label="用户名" width="180" align="center">
          </el-table-column>
          <el-table-column prop="dbuser_pass" label="密码" width="180" align="center">
          </el-table-column>
          <el-table-column prop="isban" label="状态" width="100" align="center" fixed="right">
            <template v-slot="scope">
              <div slot="reference" class="name-wrapper">
                <el-tag :type="scope.row.isban == '1' ? 'danger' : 'success'">{{
                  scope.row.isban == '1' ? '已禁用' : '正常'
                }}</el-tag>
              </div>
            </template>
          </el-table-column>
          <el-table-column prop="isban" label="操作" width="150" align="center" fixed="right">
            <template v-slot="scope">
              <div slot="reference" class="name-wrapper">
                <el-button type="danger" v-if="scope.row.isban == 0"
                  @click=" radio = scope.row; forbiddenuser();">禁用</el-button>
                <el-button type="danger" v-if="scope.row.isban == 1"
                  @click="radio = scope.row; unforbiddenuser();">解禁</el-button>
              </div>
            </template>
          </el-table-column>
          toggleRowSelection
        </el-table>
        <el-footer>
          <div class="block" style="margin-top:30px;">
            <el-pagination align='center' @current-change="handleCurrentChange" :current-page="currentPage"
              :page-size="pageSize" layout="total,  prev, pager, next, jumper" :total="dataModel.length">
            </el-pagination>
          </div>
        </el-footer>
      </el-main>
    </el-container>
  </el-card>
</template>

<script>

export default {
  data() {
    return {
      // 后台获取的数据放这
      dataModel: [],
      radio: '', //对应选择的用户
      flag: 0,
      flag1: 0,
      flag3: 0,
      currentPage: 1, // 当前页码
      total: 20, // 总条数
      pageSize: 5, // 每页的数据条数
      listLoading: false,
    }
  },
  created() {
    this.getData()
  },
  methods: {
    getData() {
      this.listLoading = true
      this.$http.get("/GetDbUser", {
        params:
        {
          database_name: this.$route.query.database_name,
          database_creater_id: this.$route.query.cuid,
        },
      }).then((resp) => {
        var result = JSON.stringify(resp.data.data);
        var data = JSON.parse(result);
        this.dataModel = data;
        this.listLoading = false
      }).catch((err) => {
        console.log(err);
      });
    },
    //当前页改变时触发 跳转其他页
    handleCurrentChange(val) {
      console.log(`当前页: ${val}`);
      this.currentPage = val;
    },
    getmessage(row) {
      this.radio = row;
    },
    usercontrol(item) {
      if (this.radio != '' && item == 2) {
        const t = this.$createElement;
        this.$msgbox({
          title: '查看',
          message: t('p', null, [
            t('span', null, '创建ID：'),
            t('input', {
              attrs: {
                id: 'input1',
                class: 'inputchange',
                value: this.radio.creater_id,
                disabled: true
              }
            }),
            t('span', null, '数据库：'),
            t('input', {
              attrs: {
                id: 'input2',
                class: 'inputchange',
                value: this.radio.database_id,
                disabled: true
              }
            }),
            t('br'),
            t('span', null, '创建人：'),
            t('input', {
              attrs: {
                class: 'inputchange',
                value: this.radio.dbuser_name,
                disabled: true
              }
            }),
            t('span', null, '密码：'),
            t('input', {
              attrs: {
                class: 'inputchange',
                value: this.radio.dbuser_pass,
                disabled: true
              }
            }),
            t('span', null, '状态：'),
            t('input', {
              attrs: {
                class: 'inputchange',
                value: this.radio.isban == 0 ? "正常" : "禁用",
                disabled: true
              }
            }),
          ]),
          showCancelButton: true,
        }).then(action => {
        }).catch(() => {
        });
      } else if (item == 1) {
        const t = this.$createElement;
        this.$msgbox({
          title: '新增用户',
          message: t('p', null, [
            t('span', null, '用户名：'),
            t('input', {
              attrs: {
                id: "input5",
                class: 'inputchange',
              }
            }),
            t('br'),
            t('span', null, '密码：'),
            t('input', {
              attrs: {
                id: 'input6',
                class: 'inputchange',
                type: 'password',
              }
            }),
            t('button', {
              attrs: {
                class: 'el-icon-view password1',
              },
              on: { click: () => this.handleClick2() }
            }),
          ]),
          showCancelButton: true,
          confirmButtonText: '确认',
          cancelButtonText: '取消',
        }).then(action => {
          var input5 = document.getElementById('input5').value;
          var input6 = document.getElementById('input6').value;
          if (input5 == "" || input6 == "") {
            this.$message({
              type: 'warning',
              message: '输入不能为空'
            });
            return;
          }
          this.$http.get("/InsertDbUser", {
            params: {
              dbuser_id: this.$route.query.dbuser_id,
              database_name: this.$route.query.database_name,
              creater_id: this.$route.query.cuid,
              dbuser_name: input5,
              dbuser_pass: input6,
            },
          })
            .then((result) => {
              this.$message({
                type: 'success',
                message: '创建成功'
              });
              this.$router.go(0);
            })
            .catch((err) => {
              this.$message({
                type: 'info',
                message: '创建失败'
              });
              console.log(err);
            });
        }).catch(() => {
          this.$message({
            type: 'info',
            message: '取消更改'
          });
          // this.$router.go(0);
        });
      } else if (this.radio != '' && item == 3) {
        const y = this.$createElement;
        this.$msgbox({
          title: '修改密码',
          message: y('p', null, [
            y('span', null, '新密码：'),
            y('input', {
              attrs: {
                id: 'newpassword',
                class: 'inputchange',
                type: 'password',
              }
            }),
            y('button', {
              attrs: {
                class: 'el-icon-view password2',
              },
              on: { click: () => this.handleClick() }
            }),
            y('span', null, '确认密码：'),
            y('input', {
              attrs: {
                id: 'againpassword',
                class: 'inputchange',
                type: 'password',
              }
            }),
            y('button', {
              attrs: {
                class: 'el-icon-view password3',
              },
              on: { click: () => this.handleClick1() }
            }),
          ]),
          showCancelButton: true,
          confirmButtonText: '确认',
          cancelButtonText: '取消',
        }).then(action => {
          var input1 = document.getElementById('newpassword').value;
          var input2 = document.getElementById('againpassword').value;
          if (input1 == "" || input2 == "") {
            this.$message({
              type: 'warning',
              message: '输入不能为空'
            });
            return;
          }
          if (input1 == input2) {
            this.$http.get("/DbUserUpdatePassword", {
              params: {
                dbuser_id: this.radio.dbuser_id,
                new_password: input1
              },
            })
              .then((result) => {
                this.$message({
                  type: 'success',
                  message: '成功'
                });
                // this.$router.go(0);
              })
              .catch((err) => {
                this.$message({
                  type: 'info',
                  message: '修改失败'
                });
                console.log(err);
              });
          } else {
            this.$message({
              type: 'info',
              message: '两次密码不一样，请重试'
            });
          }
        }).catch(() => {
          this.$message({
            type: 'info',
            message: '取消更改'
          });
          // this.$router.go(0);
        });
      } else {
        const h = this.$createElement;
        this.$message({
          message: h('p', null, [
            h('span', null, '必须选择一个用户'),
          ])
        });
      }
    },
    unforbiddenuser() {

      if (this.radio != '') {
        const t = this.$createElement;
        this.$msgbox({
          title: '取消禁用',
          message: t('p', null, [
            t('span', null, '是否取消禁用该用户？'),
          ]),
          showCancelButton: true,
          confirmButtonText: '确认',
          cancelButtonText: '取消',
        }).then(action => {
          this.$http.get("/ReuseDbUser", {
            params: {
              dbuser_id: this.radio.dbuser_id,
            },
          })
            .then((result) => {
              this.$message({
                type: 'success',
                message: '成功'
              });
              this.$router.go(0);
            })
            .catch((err) => {
              this.$message({
                type: 'info',
                message: '修改失败'
              });
              console.log(err);
            });
        }).catch(() => {
          this.$message({
            type: 'info',
            message: '取消更改'
          });
          this.radio = "";
        });
      } else {
        const h = this.$createElement;
        this.$message({
          message: h('p', null, [
            h('span', null, '必须选择一个'),
          ])
        });
      }
    },
    forbiddenuser() {
      if (this.radio != '') {
        const t = this.$createElement;
        this.$msgbox({
          title: '禁用',
          message: t('p', null, [
            t('span', null, '是否禁用用户？'),
          ]),
          showCancelButton: true,
          confirmButtonText: '确认',
          cancelButtonText: '取消',
        }).then(action => {
          console.log(this.radio.dbuser_id)
          this.$http.get("/BanDbUser", {
            params: {
              dbuser_id: this.radio.dbuser_id,
            },
          })
            .then((result) => {
              this.$message({
                type: 'success',
                message: '成功'
              });
              this.$router.go(0);
            })
            .catch((err) => {
              this.$message({
                type: 'info',
                message: '修改失败'
              });
              console.log(err);
            });
        }).catch(() => {
          this.$message({
            type: 'info',
            message: '取消更改'

          });
          this.radio = "";
        });
      } else {
        const h = this.$createElement;
        this.$message({
          message: h('p', null, [
            h('span', null, '必须选择一个'),
          ])
        });
      }
    },
    deleteuser() {
      if (this.radio != '') {
        const t = this.$createElement;
        this.$msgbox({
          title: '删除',
          message: t('p', null, [
            t('span', null, '是否删除该用户？'),
          ]),
          showCancelButton: true,
          confirmButtonText: '确认',
          cancelButtonText: '取消',
        }).then(action => {
          this.$http.get("/DbUserDelete", {
            params: {
              dbuser_id: this.radio.dbuser_id,
            },
          })
            .then((result) => {
              this.$message({
                type: 'success',
                message: '成功'
              });
              this.$router.go(0);
            })
            .catch((err) => {
              this.$message({
                type: 'info',
                message: '删除失败'
              });
              console.log(err);
            });
        }).catch(() => {
          this.$message({
            type: 'info',
            message: '取消更改'
          });
        });
      } else {
        const h = this.$createElement;
        this.$message({
          message: h('p', null, [
            h('span', null, '必须选择一个'),
          ])
        });
      }
    },
    handleClick() {
      var u = document.getElementById("newpassword");
      if (this.flag == 0 && u.value != '') {
        u.type = 'text';
        this.flag = 1;
      } else {
        u.type = 'password';
        this.flag = 0;
      }
    },
    handleClick1() {
      var u = document.getElementById("againpassword");
      if (this.flag1 == 0 && u.value != '') {
        u.type = 'text';
        this.flag1 = 1;
      } else {
        u.type = 'password';
        this.flag1 = 0;
      }
    },
    handleClick2() {
      var u = document.getElementById("input6");
      if (this.flag2 == 0 && u.value != '') {
        u.type = 'text';
        this.flag2 = 1;
      } else {
        u.type = 'password';
        this.flag2 = 0;
      }
    },
  },
}
</script>

<style lang ="less" scoped>
.password1 {
  width: 8%;
  height: 8%;
  border: 0;
  background-color: white;
  position: absolute;
  top: 78%;
  left: 92%;
  border-radius: 4px;
}

.password2 {
  width: 8%;
  height: 8%;
  border: 0;
  background-color: white;
  position: absolute;
  top: 27%;
  left: 92%;
  border-radius: 4px;
}

.password3 {
  width: 8%;
  height: 8%;
  border: 0;
  background-color: white;
  position: absolute;
  top: 78%;
  left: 92%;
  border-radius: 4px;
}

.inputchange {
  width: 100%;
  height: 30px;
  outline: none;
  border-radius: 5px;
  text-indent: 15px;
  font-size: 18px;
  margin: 10px 0;
  background-color: white;

}

.el-container {
  min-height: 500px;
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
    padding: 5px 20px 0 20px !important;
  }
}
</style>