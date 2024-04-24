<template>
  <div style="height:100%;width:99.9%;">
    <div class="container1">
      <el-page-header @back="goBack" class="fangkuang">
      </el-page-header>
      <p class="jiantou">{{ a }}</p>
    </div>
    <div class="container2">
      <el-container>
        <el-aside width="200px">
          <el-menu class="el-menu-vertical-demo" background-color="#304156" text-color="#fff" active-text-color="#409BFF"
            :collapse-transition="false" :unique-opened="true" :default-active="onRoutes" :router="true" ref="menu">
            <template v-for="item in menuListForAdmin">
              <el-submenu :key="item.name" :index="item.path" v-if="item.children">
                <template slot="title">
                  <i :class="item.icon"></i>
                  <span slot="title">{{ item.lable }}</span>
                </template>
                <el-menu-item-group v-for="child in item.children" :key="child.lable">
                  <el-menu-item @click="clickItem(child)" :index="child.path">
                    <i :class="child.icon"></i>
                    <span slot="title">{{ child.lable }}</span>
                  </el-menu-item>
                </el-menu-item-group>
              </el-submenu>

              <el-menu-item @click="clickItem(item)" :key="item.lable" :index="item.path" v-else>
                <i :class="item.icon"></i>
                <span slot="title">{{ item.lable }}</span>
              </el-menu-item>

            </template>
          </el-menu>
        </el-aside>
        <el-container class="content">
          <el-header class="header">
            <div class="header-container">
              <el-row style="padding-top: 10px;">
                <el-col @click.native="copy" :span="2" style=" font-size: 18px;color: rgb(9, 47, 108); cursor: pointer;">
                  <i class="el-icon-document-copy" style="font-size:20px;margin-left:25px;"></i>
                  备份</el-col>
                <el-col :span="2" @click.native="reduction"
                  style="font-size: 18px; color: rgb(9, 47, 108); cursor: pointer;"><i class="el-icon-folder-checked"
                    style="font-size:20px;margin-left:25px;"></i>还原</el-col>
                <el-col :span="2" style="font-size: 18px; color: rgb(9, 47, 108);cursor: pointer; "
                  @click.native="refresh"><i class="el-icon-refresh-right"
                    style="font-size:20px;margin-left:25px;"></i>刷新</el-col>
              </el-row>
            </div>
          </el-header>
          <el-main>
            <router-view></router-view>
          </el-main>
        </el-container>
      </el-container>
    </div>
  </div>
</template>

<script>
import {
  mapState
} from 'vuex'
export default {
  data() {
    return {
      a: this.$route.query.database_name,
      b: this.$route.query.cuid,
      c: this.$route.query.dbuser_id,
      user: '',
      password: '',
      datamodel: [],
      menuListForAdmin: [{
        id: "0xe67b",
        parentid: "0",
        lable: "操作",
        icon: "el-icon-s-home",
        children: [{
          id: "0xe473",
          parentid: "0xe67b",
          path: "/databaseinterface/databaseinterface-query",
          name: "databaseinterface-query",
          lable: "数据库查询",
          icon: "el-icon-search",
          url: "../views/dbabout/databaseinterface-query.vue",
        },
        {
          id: "0xe693",
          parentid: "0xe67b",
          path: "/databaseinterface/databaseinterface-increase",
          name: "databaseinterface-increase",
          lable: "数据库增加",
          icon: "el-icon-circle-plus-outline",
          url: "../views/dbabout/databaseinterface-increase.vue",
        },
        {
          id: "0xe736",
          parentid: "0xe67b",
          path: "/databaseinterface/databaseinterface-delete",
          name: "databaseinterface-delete",
          lable: "数据库删除",
          icon: "el-icon-remove-outline",
          url: "../views/dbabout/databaseinterface-delete.vue",
        }
        ]
      },
      {
        id: "0xe636",
        parentid: "0",
        path: "/databaseinterface/systemlog",
        name: "querylog",
        lable: "数据库日志",
        icon: "el-icon-document",
      },

      ],
      onRoutes: "/databaseinterface/databaseinterface-query", //查询
    }
  },

  created() {
    this.setCurrentRoute();
    this.setUserMenu()
    this.getData()

  },
  // 检测路由变化
  watch: {
    $route() {
      this.setCurrentRoute();
    }
  },
  methods: {
    setCurrentRoute() {
      this.onRoutes = this.$route.path; // 通过他就可以监听到当前路由状态并激活当前菜单
    },
    refresh() {
      location.reload();
    },
    setUserMenu() {
      var dbuser_id = this.$route.query.dbuser_id
      var userMenu = {
        id: "0xe812",
        parentid: "0",
        path: "/databaseinterface/user",
        name: "usermanage",
        lable: "用户管理",
        icon: "el-icon-user",
      }
      if (dbuser_id == "root") {
        this.menuListForAdmin.push(userMenu)
      }
    },
    clickItem(item) {
      console.log(item)
      // 防止自己跳自己的报错
      if (
        this.$route.path !== item.path && !(this.$route.path === '/databaseinterface/databaseinterface-query')
      ) {
        this.$router.push(item.path)
      }

      // 面包屑
      this.$store.commit('tab/SelectdatabaseMenu', item)
      this.$router.push({
        name: item.name,
        query: {
          database_name: this.a,
          cuid: this.b,
          dbuser_id: this.c,
        }
      })
      localStorage.setItem('temp', JSON.stringify(item));
    },
    handleClose(item, index) {
      // 删除面包屑数据
      this.$store.commit('closedatabaseTag', item)
      // 如果删除的刚好是自己
      if (item.name === this.$route.name) {
        const length = this.tags.length
        // 如果删除的是最后一个:跳到前一个
        if (length === index) {
          this.$router.push({
            name: this.tags[index - 1].name
          })
        }
        // 不是最后一个:往后一个
        else {
          this.$router.push({
            name: this.tags[index].name
          })
        }
      }
    },
    goBack() {
      if (this.$store.getters['user/identity'] == 'normal') {
        this.$router.push({ name: "database" })
      }
      else if (this.$store.getters['user/identity'] == "administrator") {
        this.$router.push({ name: "Admindatabase" })
      }
    },
    getData() {
      this.$http.get("/GetVersionToRestore", {
        //带参数时  ————若无参数时直接省略params对象不写
        params: {
          // database_id: "123nameabc",
          // dbname: 'nameabc',
          database_id: this.$route.query.cuid + this.$route.query.database_name, //"123nameabc"
          dbname: this.$route.query.database_name, //'nameabc'
        },
      })
        .then((result) => {
          this.datamodel = JSON.parse(result.data.data);
        })
        .catch((err) => {
          console.log(err);
        });
      if (localStorage.getItem("temp") != null)
        this.$store.commit('SelectdatabaseMenu', JSON.parse(localStorage.getItem('temp')));
    },
    copy() {
      const t = this.$createElement;
      var P1 = [],
        i;
      if (this.datamodel != null) {
        for (i = 0; i < this.datamodel.length; i++) {
          var sonP1 = this.$createElement('option', null, this.datamodel[i].id);
          P1.push(sonP1);
        }
      }

      this.$msgbox({
        title: '备份',
        message: t('p', null, [
          t('input', {
            attrs: {
              id: 'input2',
              class: 'inputchange',
              placeholder: "请输入版本号"
            }
          }),
        ]),
        showCancelButton: true,
        confirmButtonText: '确认',
        cancelButtonText: '取消',
      }).then(action => {
        if (action === 'confirm') {
          // 用户点击了确认按钮
          const inputContent = document.getElementById('input2').value;
          if (inputContent.trim() === '') {
            // 输入为空，不执行后续操作
            this.$message({
              type: 'danger',
              message: "输入不能为空"

            });
            return;
          }
          var version = document.getElementById("input2").value;
          this.$http.post('/Backup', JSON.stringify({
            dbname: this.$route.query.database_name, //"nameabc"
            database_creater_id: this.$route.query.cuid, //"123"
            dbuser_id: this.$route.query.dbuser_id,//"11"
            version: version
          })).then(resp => {
            console.log(resp.data);
            this.$message({
              type: 'info',
              message: resp.data.message
            })

          })
        }
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '取消更改'
        });
      });
    },
    reduction() {
      const t = this.$createElement;
      var P1 = [],
        i;
      if (this.datamodel != null) {
        for (i = 0; i < this.datamodel.length; i++) {

          var sonP1 = this.$createElement('option', null, this.datamodel[i].backupversion);
          P1.push(sonP1);
        }
      }
      this.$msgbox({
        title: '还原数据库',
        message: t('p', null, [
          t('span', null, '数据库：'),
          t('form', null, [
            t('select', {
              attrs: {
                id: 'myselect',
                placeholder: "请选择版本号"
              },
              style: 'width: 100%',
            }, [P1])
          ]),
        ]),
        showCancelButton: true,
        confirmButtonText: '确认',
        cancelButtonText: '取消',
      }).then(action => {
        if (action === 'confirm') {
          var tempselect = document.getElementById('myselect').value;
          if (tempselect.trim() === '') {
            // 如果没有选择有效的版本号，阻止进一步操作
            this.$message({
              type: 'danger',
              message: "选择不能为空"

            });
            return;
          }
          for (i = 0; i < this.datamodel.length; i++) {
            if (tempselect == this.datamodel[i].backupversion) {
              tempselect = this.datamodel[i].backuptime;
              break;
            }
          }
          this.$http.post('/Restore', JSON.stringify({
            //   dbname: "nameabc", //this.datamodel.dbname,
            //   database_creater_id: "123", //this.datamodel.database_id,
            //   datepath: tempselect,
            //   dbuserid: "11"
            dbname: this.a,
            database_creater_id: this.b,
            datepath: tempselect,
            dbuserid: this.c,
          })).then(resp => {
            console.log(resp.data)
            this.$message({
              type: 'info',
              message: resp.data.data
            })
          })
        }
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '取消更改'
        });
      });
    },
    exports() {
      const t = this.$createElement;
      this.$msgbox({
        title: '导出',
        message: t('p', null, [
          t('span', null, '是否导出到本地？'),
        ]),
        showCancelButton: true,
        confirmButtonText: '确认',
        cancelButtonText: '取消',
      }).then(action => {
        var fileUrl; // 文件的URL地址
        this.$http.post('/Export', JSON.stringify({
          dbname: this.$route.query.database_name, //this.datamodel.dbname,
          database_cuid: this.$route.query.cuid, //this.datamodel.database_id,
          dbuserid: this.$route.query.dbuser_id
        })).then(resp => {
          resp = JSON.parse(resp.data.data);
          var fileUrl = resp.filepath;
          window.open(fileUrl)
          // this.$http.get(fileUrl, {
          //   responseType: 'blob'
          // })
          //   .then(response => {
          //     const url = window.URL.createObjectURL(new Blob([response.data]));
          //     const link = document.createElement('a');
          //     link.href = url;
          //     link.setAttribute('download', fileName);
          //     document.body.appendChild(link);
          //     link.click();
          //     this.$message({
          //       type: 'info',
          //       message: '成功'
          //     });
          //   })
          //   .catch(error => {
          //     this.$message({
          //       type: 'info',
          //       message: '导出失败'
          //     });
          //     console.error(error);
          //   });
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '取消更改'
        });
      });
    },
  },
  computed: {
    ...mapState({
      tags: state => state.tab.otherList
    }),
  },
}
</script>


<style lang="less" scoped>
.fangkuang {
  left: 47px;
  top: 5px;
  width: 100px;
  height: 28px;
  color: rgba(255, 255, 255, 1);
  font-size: 18px;
  text-align: right;
  font-family: SourceHanSansSC-regular;
  margin-top: 6px;
  margin-left: 15px;
}

.jiantou {
  left: 18px;
  top: 15px;
  width: 300px;
  height: 22px;
  color: rgba(255, 255, 255, 1);
  margin-top: 10px;
}

.container1 {
  //left: -1px;
  top: 0px;
  width: 100%;
  height: 45px;
  line-height: 20px;
  background-color: rgba(5, 32, 62, 1);
  color: rgba(16, 16, 16, 1);
  font-size: 14px;
  font-family: Roboto;
  border: 1px solid rgba(187, 187, 187, 1);
  display: flex;
}

.container2 {
  height: 100%-50px;
}

.el-menu-vertical-demo:not(.el-menu--collapse) {
  width: 200px;
  min-height: 400px;
}

.el-menu {
  height: calc(100vh - 50px);
  border-right: none;
}

::v-deep .el-submenu__title {
  min-width: 0;
}

.content {
  height: calc(100vh - 50px);
  width: 98%;
}

.el-header {
  padding: 0;
  margin: 0 !important;
  height: 40px !important;
  width: 100%
}

.header-container {
  background-color: rgba(255, 255, 255, 1);
  height: 50px;
  width: 100%;
  position: relative;

  .box1 {
    width: 50px;
    height: 30px;
    position: absolute;
    margin: 5px 10px;
    display: inline-block;
  }

  .box2 {
    width: 300px;
    height: 100%;
    margin-left: 30px;
    top: 7px;
    text-align: left;
    display: inline-block;
    position: absolute;
  }

}

.el-main {
  height: calc(100vh - 100px);
}

.inputchange {
  width: 100%;
  height: 30px;
  outline: none;
  border-radius: 25px;
  text-indent: 15px;
  font-size: 18px;
  margin: 10px 0;
}



//滚动条的样式
::-webkit-scrollbar {
  //滚动条宽高
  width: 10px;
  height: 10px;
}

::-webkit-scrollbar-thumb {
  //滚动条颜色和圆角
  background-color: #dbd9d9;
  border-radius: 3px;
}


/* 文字 */
::v-deep.el-submenu.is-active>.el-submenu__title {
  color: #409eff !important;
}

/* icon图标也跟着变 */
::v-deep .el-submenu.is-active>.el-submenu__title i {
  color: #409eff !important;
}
</style>
