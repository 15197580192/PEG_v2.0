<template>
  <div style="height: 100%">
    <el-menu class="el-menu-demo" mode="horizontal" @select="handleSelect" style="margin-top: -10px;"
      :default-active="defaultIndex">
      <el-menu-item index="/forum">首页</el-menu-item>
      <el-menu-item index="/forum/question">问答</el-menu-item>
      <el-menu-item index="/forum/follow">关注</el-menu-item>
      <el-menu-item index="/forum/editor">发帖</el-menu-item>
      <el-input placeholder="请输入内容" style="width: 30%; margin-left: 30vw;margin-top: 10px;" v-model="searchData" clearable
        @clear="getData" @keyup.enter.native="searchTable">
        <el-button slot="append" icon="el-icon-search" @click="searchPost"></el-button>
      </el-input>
      <div class="r-content">
        <el-dropdown @command="handleClick">
          <span class="el-dropdown-link">
            <img class="user" src="../assets/user.png" alt="">
            <i class="el-icon-caret-bottom" />
          </span>
          <el-dropdown-menu slot="dropdown">
            <el-dropdown-item command="information">个人中心</el-dropdown-item>
            <el-dropdown-item command="message">我的私信</el-dropdown-item>
            <el-dropdown-item command="unread">点赞评论</el-dropdown-item>
          </el-dropdown-menu>
        </el-dropdown>

      </div>
    </el-menu>
  </div>
</template>
<script>
export default {
  data() {
    return {
      defaultIndex: '/forum',
      userId: this.$store.getters['user/userName'],
      searchData: '',
      forumRoute: ''
    }
  },

  created() {
    this.defaultIndex = this.$route.path
    this.forumRoute = this.$route.path
    if (this.$route.query.searchData != null) {
      this.searchData = this.$route.query.searchData
    }
  },
  methods: {
    handleSelect(index) {
      this.forumRoute = index
      console.log(index);
      this.$router.push({
        path: index,
      })
    },
    searchPost() {
      if (this.searchData != '')
        this.$router.push({ path: '/forum/search', query: { searchData: this.searchData } });
    },
    getData() {
      this.$router.go(-1);
    },

    handleClick(command) {
      if (command === 'message') {

        this.$router.push('/forum/message');

      }
      else if (command === 'information') {
        this.$router.push({ path: '/forum/userInformation', query: { user_id: this.userId } })
      }
      else if (command === 'unread') {
        this.$router.push({ path: '/forum/unread', query: { user_id: this.userId } })

      }
    },
  }
}
</script>
<style lang="less" scoped>
.background {
  width: 100%;
  height: 100%;
  padding: 0;
  height: calc(100vh - 70px);
}

.r-content {
  display: flex;
  justify-content: space-between;
  align-items: center;
  float: right;
  margin-right: 5%;
  margin-top: 2%;
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
</style>