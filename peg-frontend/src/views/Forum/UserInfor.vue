<template>
  <div style="height: 100%">
    <el-container style="height: 100%;position: relative;">
      <el-header>
        <forumHeader />
      </el-header>
      <el-container class="background">
        <el-main>

          <el-row style="margin-top:80px ; background-color: white;">
            <div style="margin:20px ;">
              <el-col :span="2">
                <div class="demo-basic--circle outside">
                  <div class="block"><el-avatar :size="50" :src="circleUrl"></el-avatar></div>
                </div>
              </el-col>
              <el-col :span="22">
                <el-row class="bold"><el-col :span="18">{{ userInformation.name }}</el-col>
                  <el-col :span="6" v-if="other"><el-button round @click="isFollow">{{ follow
                  }}</el-button>
                    <el-button round @click="isMessage">私信</el-button>
                  </el-col> </el-row>
                <el-row style="margin: 0px;margin-top: 4px;font-size: 12px;color: gray;">关注：{{ userInformation.follow
                }}|粉丝：{{ userInformation.fans }}|发帖：{{ userInformation.post }}|问答：{{ userInformation.question
}}</el-row>
                <el-row style="margin: 0px;margin-top: 4px;font-size: 12px;color: gray;margin-bottom: 5px;">简介：{{
                  userInformation.intro }}</el-row>
              </el-col>
            </div>
          </el-row>
          <el-row style="height: 10px;background-color: gainsboro;">
          </el-row>
          <el-row style="background-color: gainsboro;">
            <el-card style="min-height: calc(100vh - 350px);">
              <el-menu :default-active="activeIndex" class="el-menu-demo" mode="horizontal" @select="handleSelect"
                style="margin-top: -20px;">
                <el-menu-item index="1">文章</el-menu-item>
                <el-menu-item index="2">问答</el-menu-item>
                <el-menu-item index="3">收藏</el-menu-item>
              </el-menu>
              <div v-if="isShow == '1'" v-for="(item, index) in myPost" :key="index" class="dlog_content"
                style="margin-left: 5px; border-bottom: 1px solid rgb(199, 197, 197);" @mouseover="Darken(index)"
                @mouseout="Lighten(index)" @click="articleDetail(item)">
                <div class="content_other ">
                  <span :id="index" style="font-size: 18px;font-weight:bold;margin-bottom: 5px;">{{ item.title }} </span>
                  <p style="margin: 0px;margin-top: 4px;font-size: 12px;color: gray;" class="text-ellipsis"
                    v-html="item.intro"></p>
                  <span>
                    <i class="iconfont icon-dianzan" style="font-size: 15px; "></i>{{ item.like }}
                    <el-divider direction="vertical"></el-divider>
                    <i class="iconfont icon-pinglun" style="font-size: 15px;font-weight:600; "></i>{{ item.comments }}
                  </span>
                  <span style="margin: 0px;margin-top: 4px;font-size: 12px;color: gray; float: right;">{{ item.time
                  }}</span>
                </div>
              </div>
              <div v-if="isShow == '2'" :id="index" v-for="(item, index) in myQuestion" :key="index" class="dlog_content"
                style="margin-left: 5px;  border-bottom: 1px solid rgb(199, 197, 197);" @mouseover="Darken(index)"
                @mouseout="Lighten(index)" @click="questionDetail(item)">
                <el-row class="content_other ">
                  <el-col :span="4">
                    <el-col :span="12">
                      <div class="bold">{{ item.support_num }}</div>
                      <div class="text-normal">点赞</div>
                    </el-col>
                    <el-col :span="12">
                      <div class="bold">{{ item.comments_num }}</div>
                      <div class="text-normal">评论</div>
                    </el-col>
                  </el-col>
                  <el-col :span="20">
                    <div class="context-title">{{ item.question_title }}
                      <span
                        style="margin: 0px;margin-top: 4px;margin-right:10px;font-size: 12px;color: gray; float: right;">
                        {{ item.solved == true ? '已解决' : '未解决' }}
                      </span>
                    </div>

                    <span style="margin: 0px;margin-top: 4px;font-size: 12px;color: gray; float: right;">{{ item.ques_time
                    }}</span>
                  </el-col>
                </el-row>
              </div>
              <div v-if="isShow == '3'" v-for="(item, index) in myFavorites" :key="index" class="dlog_content"
                style="margin-left: 5px; border-bottom: 1px solid rgb(199, 197, 197);" @mouseover="Darken(index)"
                @mouseout="Lighten(index)" @click="articleDetail(item)">
                <div class="content_other ">
                  <span :id="index" style="font-size: 18px;font-weight:bold;margin-bottom: 5px;">{{ item.title }} </span>
                  <p style="margin: 0px;margin-top: 4px;font-size: 12px;color: gray;" class="text-ellipsis">{{ item.intro
                  }}</p>
                  <span>
                    <i class="iconfont icon-dianzan" style="font-size: 15px; "></i>{{ item.like }}
                    <el-divider direction="vertical"></el-divider>
                    <i class="iconfont icon-pinglun" style="font-size: 15px;font-weight:600; "></i>{{ item.comments }}
                  </span>
                  <span style="margin: 0px;margin-top: 4px;font-size: 12px;color: gray; float: right;">{{ item.time
                  }}</span>
                </div>
              </div>
            </el-card>
          </el-row>
        </el-main>
      </el-container>
    </el-container>
  </div>
</template>
<script>
import "../../assets/font_forum/iconfont.css"
import forumHeader from '@/components/ForumHeader.vue'
export default {
  data() {
    return {
      isShow: '1',
      activeIndex: "1",
      circleUrl: "https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png",
      myPost: [],
      myFavorites: [],
      myQuestion: [],
      userInformation: {
        name: '',
        intro: '',
        post: '',
        question: '',
        fans: '',
        follow: ''
      },
      follow: '关注',
      userId: '',
      other: false,
    }
  },
  components: {
    forumHeader
  },
  watch: {
    // 监听路由的参数的变化
    // to是目标路由对象
    // from:源路由对象
    '$route'(to, from) {
      console.log(from.query.user_id);
      var id = to.query.user_id
      if (id != from.query.user_id) {
        this.create();
      }
    }
  },
  mounted() {
    this.create();

  },
  methods: {
    handleSelect(index) {
      console.log(index);
      this.isShow = index;
      if (index == "1") {
        this.$http.get('/Forum/UserInformation/Post?user_id=' + this.userId).then(result => {
          console.log(result)
          this.myPost = JSON.parse(result.data.post_data);
        })
      }
      if (index == "2") {
        this.$http.get('/Forum/UserInformation/Question?user_id=' + this.userId).then(result => {
          console.log(result)
          this.myQuestion = JSON.parse(result.data.question_data)
        })
      }
      if (index == "3") {
        this.$http.get('/Forum/UserInformation/Favorites?user_id=' + this.userId).then(result => {
          console.log(result)
          this.myFavorites = JSON.parse(result.data.favorites_data)
        })
      }



    },
    Darken(index) {
      document.getElementById(index).style.color = "gold";
    },
    //鼠标离开后变亮
    Lighten(index) {
      document.getElementById(index).style.color = "black";
    },
    articleDetail(row) {
      console.log(row);
      this.$router.push({ path: '/forum/post', query: { post_id: row.postId } })

    },
    questionDetail(row) {
      console.log(row.question_id)
      this.$router.push({ path: '/forum/question/detail', query: { question_id: row.question_id } })

    },
    isFollow() {
      // this.follow == '关注' ? this.follow = '已关注' : this.follow = '关注';
      if (this.follow == '关注') {
        this.$http.get('/Forum/Post/Details?follow=true&user_id=' + this.$store.getters['user/userName'] + '&follow_id=' + this.userId).then(resp => {
          // follow=true&
          console.log(resp)
          if (resp.data.message == 'success') {
            this.follow = '已关注'
            this.userInformation.fans = (parseInt(this.userInformation.fans) + 1).toString()
          }
        })
      }
      if (this.follow == '已关注') {
        this.$http.get('/Forum/Post/Details?follow=false&user_id=' + this.$store.getters['user/userName'] + '&follow_id=' + this.userId).then(resp => {
          if (resp.data.message == 'success') {
            this.follow = '关注';
            this.userInformation.fans = (parseInt(this.userInformation.fans) - 1).toString()

          }
        })
      }
    },
    isMessage() {
      this.$router.push({ path: '/forum/message', query: { dest_user_id: this.userId, dest_user_name: this.userInformation.name } })
    },
    create() {
      console.log(this.$route.query.user_id)
      this.userId = this.$route.query.user_id;
      if (this.$route.query.follow != undefined) {
        this.follow = this.$route.query.follow
      }
      (this.userId == this.$store.getters['user/userName']) ? this.other = false : this.other = true
      this.$http.get('/Forum/Personal?user_id=' + this.userId).then(result => {
        // this.userInformation = JSON.parse(result.data)
        console.log(result)
        if (result.data.data != "null") {
          this.userInformation.name = result.data.name;
          this.userInformation.fans = result.data.follower_num;
          this.userInformation.follow = result.data.concern_num;
          this.userInformation.intro = result.data.intro;
          this.userInformation.post = result.data.post_num;
          this.userInformation.question = result.data.question_num;
          console.log(this.userInformation);
        }
        else {
          this.userInformation.name = "用户已注销";
          this.other = false
        }
      })
      this.$http.get('/Forum/UserInformation/Post?user_id=' + this.userId).then(result => {
        console.log(result)
        this.myPost = JSON.parse(result.data.post_data);
      })
      this.$http.get('/Forum/UserInformation/Question?user_id=' + this.userId).then(result => {
        console.log(result)
        this.myQuestion = JSON.parse(result.data.question_data)
      })
      this.$http.get('/Forum/UserInformation/Favorites?user_id=' + this.userId).then(result => {
        console.log(result)
        this.myFavorites = JSON.parse(result.data.favorites_data)
      })

    }
  }
}
</script>
<style lang="less" scoped>
.background {
  // width: 100%;
  // height: 100%;
  // padding: 0;
  // height: calc(100vh - 50px);
  background-image: url('../../assets/background.jpg');
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

.context-title {
  font-size: 18px;
  font-weight: bold;
  margin-top: 10px;
}

.dlog_content::-webkit-scrollbar {
  border-bottom: 1px solid rgb(199, 197, 197);
  // border-bottom: 1px solid rgb(203, 176, 22);
  overflow-y: scroll;
  margin-top: 10px;
  margin-left: 5px;
  margin-right: 5px;
}

.bold {
  font-size: 18px;
  font-weight: bold;
}

.text-normal {
  margin-top: 5px;
  font-size: 12px;

}

.outside {
  position: relative;
  top: -25px;
  left: 10px;
}

.el-main {
  position: absolute;
  right: 0;
  left: 0;
  top: 60px;
  bottom: 0;
  overflow-y: scroll;
  padding: 0;
  // border: 1px solid gainsboro;
}

.text-ellipsis {
  width: 100%;
  max-height: 40px;
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}
</style>