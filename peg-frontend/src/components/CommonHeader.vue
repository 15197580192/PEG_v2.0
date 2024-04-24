<!-- 位置：components/ComHeader.vue -->
<template>
  <div class="header-container" :style="{ backgroundColor }">
    <div class="l-content">
      <el-button @click="handleMenu" icon="el-icon-menu" size="mini"></el-button>
      <!-- 面包屑 -->
      <el-breadcrumb separator="/">
        <!-- 首页是不管怎样都会有的，因此首页的路由数据是写死在vuex的store的state中的，而其他的是动态添加的(Array.push) -->
        <el-breadcrumb-item v-for="item in tags" :key="item.path" :to="{ path: item.path }"> {{ item.lable
        }}</el-breadcrumb-item>
      </el-breadcrumb>
    </div>
    <div class="r-content">
      <div v-show="show" style="margin:-2px 10px 0 0;display: inline-block;">
        <el-popover placement="left-start" width="330" trigger="manual" v-model="visible">
          <i class="el-icon-bell" style="font-size: 22px; font-weight: 500; color: #9ea0a3;" slot="reference"
            @click="hanldeData()"></i>
          <div>
            <div style="width:100%;height:40px;position: relative;">
              <span style="font-size:18px;font-weight:bold">消息中心</span>
              <span class="bottom_button_left" @click="clearAll()">一键清空</span>
              <span style="width: 20px;line-height: 30px; height: 30px;text-align: right; float:right;margin-top:2px"
                @click="visible = !visible">
                <i class="el-icon-close" style="font-size: 20px"></i>
              </span>
            </div>
            <div class="box">
              <div class="notification_text" v-for="(item, index) in InfoList" :key="index">
                <img src="../assets/notice.png" alt="" class="left_image" />
                <div class="text" @click="handleOpen(item)">
                  <p class="topic">{{ item.noticetopic }}</p>
                  <p style="font-size: 12px; color: #ccc">{{ item.createrid }} {{ '\u3000' }}{{ '\u3000' }}
                    {{ item.createtime }}</p>
                </div>
              </div>
            </div>
          </div>

          <el-dialog title="我的消息" :visible.sync="open" width="700px" append-to-body class="my-dialog-name">
            <el-form class="form" :model="currentItem" label-width="80px" label-position="left">
              <el-form-item label="公告主题" prop="noticetopic">
                <el-input disabled v-model="currentItem.noticetopic" size="small" />
              </el-form-item>
              <el-form-item label="公告内容">
                <mavon-editor class="md" v-model="currentItem.content" style="height:210px" :toolbarsFlag="false"
                  :subfield="false" :editable="false" placeholder="公告内容..." />
              </el-form-item>
            </el-form>

            <div slot="footer" class="dialog-footer">
              <el-button @click="handleClose()">关闭</el-button>
              <!-- <el-button type="primary" @click="handleDelete()" icon="el-icon-delete">删 除</el-button> -->
            </div>
          </el-dialog>
        </el-popover>
      </div>
      <div class="settings">
        <i class="el-icon-setting" style="font-size: 20px; font-weight: 500; color: #9ea0a3;" @click="toSettings()"></i>
      </div>
      <el-dropdown @command="handleClick">
        <span class="el-dropdown-link">
          <img class="user" src="../assets/user.png" alt="">
          <i class="el-icon-caret-bottom" />
        </span>
        <el-dropdown-menu slot="dropdown">
          <el-dropdown-item command="information" v-show="showInfo">个人信息</el-dropdown-item>
          <el-dropdown-item command="logout">退出</el-dropdown-item>
        </el-dropdown-menu>
      </el-dropdown>
    </div>

  </div>
</template>
 
<script>
import { mapState } from 'vuex'

export default {
  data() {
    return {
      setting: {
        id: 15,
        parentid: "0",
        path: "/Personalization",
        name: "Personalization",
        lable: "个性化设置",
        icon: "el-icon-s-tools",
      },
      information: {
        id: 16,
        parentid: "0",
        path: "/user",
        name: "user",
        lable: "个人信息",
      },
      show: this.isVisible(),
      InfoList: [],
      open: false,
      currentItem: {},
      visible: false,
      showInfo: this.isVisible()
    }
  },

  methods: {
    handleMenu() {
      // 相当于调用这个方法
      this.$store.commit('tab/CollapseMenu')
    },
    handleClick(command) {
      if (command === 'logout') {
        this.$confirm('确认退出?', '提示', {
          confirmButtonTextt: '确定',
          cancelButtonText: '取消',
          type: 'warning'
        }).then(() => {
          this.$http.get('/LoginOut?user_id=' + this.$store.getters['user/userName'])
          this.$store.dispatch('user/removeUserInfo')
          this.$store.dispatch('token/removeToken')
          this.$store.dispatch('theme/removeColor')
          this.$router.push('/login');
        }).catch(err => { console.log(err) })
      }
      else if (command === 'information') {
        this.$store.dispatch('tab/SelectMenu', this.information)
        this.$router.push('/user')
      }
    },
    toSettings() {
      this.$store.dispatch('tab/SelectMenu', this.setting)
      this.$router.push({ name: "Personalization" })
    },
    isVisible() {
      const identity = this.$store.getters['user/identity']
      console.log("this.identity", identity)
      if (identity == "administrator") {
        return false
      }
      if (identity == "normal") {
        return true
      }
    },
    hanldeData() {
      this.visible = !this.visible
      this.getData()
    },
    getData() {
      this.$http.get('/GetNotice').then(resp => {
        console.log("noticeList", resp)
        this.InfoList = JSON.parse(resp.data.data);

      })
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
        this.getData()
        loading.close()
      }, 500);
    },
    //清空
    clearAll() {
      this.InfoList = []
      window.localStorage.removeItem("List")
    },
    handleOpen(item) {
      this.currentItem = item;
      this.open = true;
    },
    handleClose() {
      this.open = false;
    },
    handleDelete() {
      this.$confirm('此操作将永久删除该公告, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        var notice_id = JSON.stringify(this.currentItem.noticeid)
        this.$http.post('/DeleteNotice', { notice_id: notice_id }).then(resp => {
          console.log("删除resp", resp)
          if (resp.data.data == "success") {
            this.$message({
              type: 'success',
              message: '删除成功!'
            })
            this.open = false
            this.getData()
          }
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除该公告！'
        })
      })
    }
  },
  computed: {
    tags() {
      return this.$store.getters['tab/TabList']
    },
    ...mapState({
      backgroundColor: state => state.theme.headerColor
    })
  }
};
</script>
 
<style lang="less" scoped>
.my-dialog-name {
  .el-dialog__header {
    padding: 5px 5px;
    background-color: #E5F6FE;

    .el-dialog__headerbtn {
      top: 10px;
      right: 8px;
    }
  }

  .el-dialog__body {
    padding: 10px 8px 0 8px;
  }

  .el-dialog__footer {
    padding: 0 0 15px 0;
    margin: -10px 10px 0 0;
  }
}

.header-container {
  height: 50px;

  // 让按钮和头像居中
  display: flex;
  justify-content: space-between;
  align-items: center;
  // 不要紧贴边框
  padding: 0 20px;
  color: #fff;
}


.r-content {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.settings {
  margin-right: 15px;
}

.el-dropdown-link {
  position: relative;

  .user {
    cursor: pointer;
    width: 30px;
    height: 30px;
    // 50%变圆形
    border-radius: 50%;
  }

  .el-icon-caret-bottom {
    cursor: pointer;
    position: absolute;
    right: -10px;
    top: 5px;
    font-size: 10px;
  }
}

.l-content {
  display: flex;
  // 上下居中
  align-items: center;

  .el-breadcrumb {
    margin-left: 20px;

    // deep 强制生效
    /deep/.el-breadcrumb__item {
      .el-breadcrumb__inner {
        &.is-link {
          color: #9A9A9A;
        }
      }

      &:last-child {
        .el-breadcrumb__inner {
          color: #fff;
        }
      }
    }
  }
}

//图片
.left_image {
  width: 40px;
  height: 40px;
  position: absolute;
  top: 50%;
  left: 10px;
  margin-top: -20px;
  border-radius: 50%;
}

//每一条
.notification_text {
  width: 100%;
  height: 80px;
  border-bottom: 1px #ccc solid;
  position: relative;
}

//左右按钮
.bottom_button_left {
  display: inline-block;
  width: 120px;
  height: 30px;
  text-align: right;
  line-height: 30px;
  cursor: pointer;
  position: absolute;
  right: 25px;
}

//右按钮
.bottom_button_left:hover {
  color: #40aaf7;
}

//文字部分位置
.text {
  display: inline-block;
  position: absolute;
  top: 5px;
  left: 65px;
  width: 80%;

  .topic {
    white-space: nowrap;
    width: 150px;
    text-overflow: ellipsis;
    overflow: hidden;
  }
}

//内容部分超出隐藏，给滚动条
.box {
  overflow: auto;
  height: 400px;
  margin-bottom: 37px;
}

.form {
  width: 95%;

  .md {
    width: 100%;
  }
}


//滚动条的样式
::-webkit-scrollbar {
  //滚动条宽高
  width: 5px;
  height: 10px;
}

::-webkit-scrollbar-thumb {
  //滚动条颜色和圆角
  background-color: #dbd9d9;
  border-radius: 3px;
}
</style>