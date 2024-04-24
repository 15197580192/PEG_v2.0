<template>
  <div style="height: 100%">
    <el-container style="height: 100%;position: relative; ">
      <el-header>
        <forumHeader />
      </el-header>

      <el-container style="background-color: rgb(235, 235, 235);" class="article-background">

        <el-main class="article-main main-scrollbar">
          <div @click="goBack(); quirePostDetail();"><i class="el-icon-back"
              style="font-size:large; margin-left: 50px;margin-top: 10px;">返回</i></div>
          <div class="article-title">
            {{ article.title }}
          </div>
          <el-row class="article-detail">
            <el-col :span="4">时间：{{ article.time.slice(0, 10) }}</el-col>
            <el-col :span="3">作者：{{ article.autherName }}</el-col>
            <el-col :span="3">收藏：{{ article.favorites }}</el-col>
            <el-col :span="3">点赞：{{ article.like }}</el-col>
          </el-row>
          <div class="article-content">
            <p v-html="article.intro">
            </p>
          </div>
          <el-card style="height: 80%;width: 400px;position:fixed;top:50px;right:10px;" v-if="isComment">
            <el-scrollbar class="comments-text" :native="false">
              <div :id="index" v-for="(item, index) in comments" :key="index" class="dlog_content main-scrollbar">
                <el-row class="content_other ">
                  <el-col :span="4"><el-avatar :size="40" :src="circleUrl"></el-avatar></el-col>
                  <el-col :span="10" class="context-title">
                    {{ item.comments_user_name }}
                  </el-col>
                  <el-col :span="10" style="text-align: right;" class="text-normal">
                    {{ item.comments_time.slice(0, 10) }}
                  </el-col>
                </el-row>
                <el-row style="margin-bottom: 10px;  margin-left: 15px; ">
                  {{ item.content }}
                </el-row>
              </div>
            </el-scrollbar>
            <div class="comments-botttom">
              <el-row :gutter="10">
                <el-col :span="18"><el-input v-model="myComments"></el-input></el-col>
                <el-col :span="2"><el-button type="primary" @click="submitComment">发送</el-button></el-col>
              </el-row>
            </div>
          </el-card>
        </el-main>

        <el-footer>

          <el-card>
            <el-col :span="2"><el-avatar :size="40" :src="circleUrl" style="margin-left:30px ;"
                @click.native="AuthorHomePage"></el-avatar></el-col>
            <el-col style="padding: 10px;" :span="2">{{ article.autherName }}</el-col>
            <el-col style="float: left;" :span="6"><el-button round @click="isFollow">{{ follow }}</el-button></el-col>
            <el-col :span="3"><i @click="CommentOpen" class="iconfont icon-pinglun"
                style="font-size: 30px;font-weight:600; "></i><span style="font-size: larger; margin-left: 20px;">{{
                  article.comments }}</span></el-col>
            <el-col :span="3"><i id="dianzan" class="iconfont icon-dianzan" style="font-size: 30px; "
                @click="getLike"></i><span style="font-size: larger; margin-left: 20px;">{{ article.like
                }}</span></el-col>
            <el-col :span="3"><i id="shoucang" class="iconfont icon-shoucang" style="font-size: 30px;"
                @click="getFavorites"></i><span style="font-size: larger; margin-left: 20px;">{{ article.favorites
                }}</span></el-col>
          </el-card>
        </el-footer>

      </el-container>
    </el-container>

  </div>
</template>

<script>
import forumHeader from '@/components/ForumHeader.vue'
import "../../../assets/font_forum/iconfont.css"
export default {
  data() {
    return {
      unreadComments: 0,
      unreadLike: 0,
      unreadMessage: 0,
      myComments: '',
      activeIndex: "1",
      isLike: false,
      isFavorites: false,
      //是否显示评论
      isComment: false,
      //是否显示文章详情
      articleclick: true,
      //头像
      circleUrl: "https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png",
      //文章内容，需要点击文章详情
      article: {
      },
      //本人的关注和收藏数量
      follow: "关注",
      comments: '',
      userId: this.$store.getters['user/userName']

    }
  },
  mounted() {
    console.log(this.$route.query)
    this.getData();

    // window.addEventListener('beforeunload', e => this.beforeunloadHandler(e))
  },
  // destroyed() {
  //   window.removeEventListener('beforeunload', e => this.beforeunloadHandler(e))
  // },
  components: {
    forumHeader
  },
  watch: {

    article: function () {
      this.$nextTick(() => {
        console.log(this.isFavorites);
        console.log(this.isLike);
        if (this.isFavorites === 'true') {
          document.getElementById("shoucang").style.color = "gold";
        }
        if (this.isLike === 'true') {
          document.getElementById("dianzan").style.color = "gold";
        }
      })
    }


  },

  methods: {
    getData() {
      this.$http.get('/Forum/Post/Details?post_id=' + this.$route.query.post_id + '&user_id=' + this.userId).then(result => {
        console.log(result);
        this.article = JSON.parse(result.data.data)
        this.comments = JSON.parse(result.data.comments)
        this.isLike = result.data.if_liked
        this.isFavorites = result.data.if_collection
        if (result.data.if_follow == 'true') {
          this.follow = '已关注'
        }
      })
    },
    //鼠标停留时变暗

    Darken(index) {
      document.getElementById(index).style.background = "rgb(244, 244, 244)";
    },
    //鼠标离开后变亮
    Lighten(index) {
      document.getElementById(index).style.background = "white";
    },
    //点赞时向后台返回信息，改变样式
    getLike() {
      if (document.getElementById("dianzan").style.color != "gold") {
        document.getElementById("dianzan").style.color = "gold";
        var dianzan = parseInt(this.article.like)
        dianzan += 1;
        this.article.like = dianzan.toString()
        this.isLike = true;
      }
      else {
        document.getElementById("dianzan").style.color = "black";
        var dianzan = parseInt(this.article.like)
        dianzan -= 1;
        this.article.like = dianzan.toString();
        this.isLike = false;
      } //
      let url = '/Forum/Post/Details?post_id=' + this.article.postId + '&user_id=' + this.userId + '&like=' + this.isLike;
      this.$http.get(url).then(
        resp => {
          console.log(resp)
        }
      )
    },
    isFollow() {
      if (this.userId === this.article.authorId) {
        this.$message({
          message: '不能关注自己',
          type: 'warning'
        });
        return;
      }
      // this.follow == '关注' ? this.follow = '已关注' : this.follow = '关注';
      if (this.follow == '关注') {
        this.$http.get('/Forum/Post/Details?follow=true&user_id=' + this.userId + '&follow_id=' + this.article.authorId).then(resp => {
          // follow=true&
          console.log(resp)
          if (resp.data.message == 'success') {
            this.follow = '已关注'
          }
        })
      }

      if (this.follow == '已关注') {
        this.$http.get('/Forum/Post/Details?follow=false&user_id=' + this.userId + '&follow_id=' + this.article.authorId).then(resp => {
          if (resp.data.message == 'success') {
            this.follow = '关注'
          }
        })
      }

    },
    //收藏时向后台返回信息，修改样式
    getFavorites() {
      if (document.getElementById("shoucang").style.color != "gold") {
        document.getElementById("shoucang").style.color = "gold";
        var shoucang = parseInt(this.article.favorites)
        shoucang += 1;
        this.article.favorites = shoucang.toString()
        this.isFavorites = true
      }
      else {
        document.getElementById("shoucang").style.color = "black";
        var shoucang = parseInt(this.article.favorites)
        shoucang -= 1;
        this.article.favorites = shoucang.toString()
        this.isFavorites = false

      }
      let url = '/Forum/Post/Details?post_id=' + this.article.postId + '&user_id=' + this.userId + '&favorites=' + this.isFavorites;
      console.log(url)
      this.$http.get(url).then(
        resp => {
          console.log(resp)
        }
      )
    },
    //监听页面改变
    quirePostDetail() {
      console.log('页面变了')
    },
    //用户点击后，向后台请求文章详细信息
    articleDetail(row) {
      this.articleclick = false;
      console.log(row);
      this.$http.get('/Forum/Post?post_id=').then(
        resp => {
          console.log(resp)
          var data = JSON.parse(resp.data);
          this.article = data.data
        }
      )
    },
    //返回首页，从详情页退出
    goBack() {
      this.$router.back()
    },
    //是否打开评论区
    CommentOpen() {
      if (this.isComment === false) {
        this.isComment = true
      }
      else if (this.isComment === true) {
        this.isComment = false
      }

    },
    //用户发表评论并将信息返回后台
    submitComment() {
      if (this.myComments == "") {
        this.$message({
          message: '评论不能为空',
          type: 'warning'
        })
        return;
      }
      this.$http.post('/Forum/Post?post_id=' + this.article.postId, JSON.stringify({
        user_id: this.userId,
        content: this.myComments
      })).then(
        resp => {
          console.log(resp)
          this.myComments = "";
          this.article.commentsNumber = (parseInt(this.article.commentsNumber) + 1).toString()
          if (resp.data.status == 'success') {
            this.getData();
          }
          else {
            this.$message({
              message: '评论失败',
              type: 'warning'
            })
          }
        }
      )
    },
    //点击作者头像，跳转作者个人主页
    AuthorHomePage() {
      console.log("跳转作者页面")
      this.$router.push({ path: "/forum/userInformation", query: { user_id: this.article.authorId, follow: this.follow } });
    }
  }
}
</script >

<style lang="less" scoped>
.background::-webkit-scrollbar {

  right: 0;
  top: 60px;
  bottom: 0;
  overflow-y: scroll;
  padding: 0;
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

.graph-left {
  position: relative;
}

.text-right {
  border-radius: 4px;
}

.text-center {
  text-align: center;
  // min-height: 100px;
}

.container {
  height: 30%;
  margin-top: 10px;
  display: flex;
  align-items: center;
  justify-content: center;
}

.border {
  border-top: 1px solid;
}


.dlog_content {
  // width: 680px;
  // height: 370px;
  // border-bottom: 1px solid rgb(199, 197, 197);
  overflow-y: scroll;
  // margin-top: 10px;
  // margin-bottom: 10px;
}


.content_other {
  margin-left: 2%;
  margin-right: 5%;
  margin-top: 15px;
}

.el-carousel__item h3 {
  color: #475669;
  font-size: 18px;
  opacity: 0.75;
  line-height: 300px;
  margin: 0;
}



.article-title {
  font-size: 30px;
  font-weight: bold;
  text-align: center;

}

.article-detail {
  font-size: 12px;
  color: gray;
  text-align: right;
  margin-left: 30%;
  margin-top: 30px;
}

.article-content {
  margin-left: 80px;
  margin-right: 80px;
  margin-bottom: 80px;
  margin-top: 30px;
  padding: 20px;
  border: 1px solid gainsboro;
}

.el-footer {
  // border: 1px solid gainsboro;
  position: absolute;
  top: calc(100vh - 200px);
  width: 100%;
  background-color: white;
}

.main-scrollbar::-webkit-scrollbar {
  width: 100%;
}

.article-main {
  position: absolute;
  right: 0;
  top: 60px;
  bottom: 0px;
  overflow-y: scroll;
  padding: 0;
  background-color: white;
  width: 100%;

}

.context-title {
  font-size: 18px;
  margin-top: 5px;
  // font-weight: bold;
}

.text-ellipsis {
  width: 100%;
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}

.comments-botttom {
  position: absolute;
  bottom: 10px;
  left: 10px;
  right: 0;
  margin: 0;
}

.comments-text {
  width: 100%;
  max-height: calc(100vh - 240px);
  // border: 1px solid;
  overflow-y: auto;
  overflow-x: hidden;
}
</style>