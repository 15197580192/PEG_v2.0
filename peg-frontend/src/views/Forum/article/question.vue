<template>
  <div style="height: 100%">
    <el-container style="height: 100%;width:100%;position: relative; ">
      <el-header>
        <forumHeader />
      </el-header>

      <el-container class="article-background">

        <el-main class="article-main main-scrollbar">
          <div style="height: 100%;width:100%;">
            <div @click="goBack"><i class="el-icon-back"
                style="font-size:large; margin-left: 50px;margin-top: 10px;">返回</i></div>
            <div class="article-title">
              {{ article.title }}
            </div>
            <el-row class="article-detail">
              <el-col :span="1"><el-avatar :size="30" :src="circleUrl" style=""></el-avatar></el-col>
              <el-col :span="3">{{ article.questioner_name }}</el-col>
              <el-col :span="7">发布时间：{{ article.time }}</el-col>
              <el-col :span="10" style="text-align: right;">{{ article.isResolve == true ? '已解决' : '未解决' }}</el-col>

            </el-row>
            <div class="article-content">
              <p v-html="article.content">
              </p>
            </div>
            <!-- <el-card style="height: 80%;width: 400px;position:relative;top:50px;right:10px;" v-if="isComment"> -->
            <el-row :gutter="10" style="margin-left: 70px;margin-right: 70px;margin-top: -30px;" id="pinglun">
              <el-col :span="20"><el-input v-model="myComments"></el-input></el-col>
              <el-col :span="4"><el-button type="primary" @click="sendComment">发送</el-button></el-col>
            </el-row>
            <div :id="index" v-for="(item, index) in comments" :key="index" class="article-comments"
              @click="setBestAnswer(item)" @mouseover="Darken(index)" @mouseout="Lighten(index)">
              <el-row class="content_other ">
                <el-col :span="2"><el-avatar :size="40" :src="circleUrl"></el-avatar></el-col>
                <el-col :span="6" class="context-title">
                  {{ item.comments_user_name }}
                </el-col>
                <el-col :span="14" style="text-align: right;" class="text-normal">
                  {{ item.comments_time }}
                </el-col>
              </el-row>
              <el-row class=" text-ellipsis" style="margin-bottom: 10px;  margin-left: 15px; ">
                <el-col :span="20">{{ item.content }}</el-col>
                <el-col :span="4" v-if="item.bestAnswer == '1'" style="font-size: 20px;color: rgb(236, 126, 92);"><i
                    class="el-icon-circle-check" style="font-size: 40px;color: rgb(236, 126, 92);"></i>已采纳</el-col>
              </el-row>
            </div>

          </div>



          <!-- </el-card> -->
        </el-main>

        <el-footer>

          <el-card>
            <el-col :span="2"><el-avatar :size="40" :src="circleUrl" style="margin-left:30px ;"></el-avatar></el-col>
            <el-col style="padding: 10px;" :span="4">{{ article.questioner_name }}</el-col>
            <el-col style="padding: 10px;" :span="10"></el-col>
            <el-col :span="3"><i class="iconfont icon-pinglun" style="font-size: 30px;font-weight:600; "
                @click="CommentOpen"> </i><span style=" font-size: larger; margin-left: 20px;">{{ article.comments
                }}</span></el-col>
            <el-col :span="3"><i id="dianzan" class="iconfont icon-dianzan" style="font-size: 30px; "
                @click="getLike"></i><span style="font-size: larger; margin-left: 20px;">{{ article.like
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
      isLike: false,
      myComments: "",
      question: [],
      comments: [],
      articleclick: true,
      circleUrl: "https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png",
      article: {},
      userId: this.$store.getters['user/userName']

    }
  },
  components: {
    forumHeader
  },
  watch: {

    article: function () {
      this.$nextTick(() => {
        console.log(this.isLike);
        if (this.isLike === 'true') {
          document.getElementById("dianzan").style.color = "gold";
        }
      })
    }
  },
  methods: {
    getData() {
      this.$http.get('/Forum/Question/Detail?questionId=' + this.$route.query.question_id + '&user=' + this.userId).then(resp => {
        console.log(resp);
        this.article = JSON.parse(resp.data.data);
        this.comments = JSON.parse(resp.data.comments);
        this.isLike = resp.data.if_liked;
      })
    },
    Darken(index) {
      document.getElementById(index).style.background = "rgb(244, 244, 244)";
    },
    Lighten(index) {
      document.getElementById(index).style.background = "white";
    },

    setBestAnswer(row) {
      if (this.userId != this.article.questioner_id) {
        return;
      }
      if (this.article.isResolve == "0") {
        this.$confirm('确认将' + row.comments_user_name + '的回答为最佳答案?', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
          type: 'warning'
        }).then(() => {
          this.$http.post('/Forum/Question/Detail', JSON.stringify({
            question_id: this.article.questionId,
            user_id: row.comments_user_id,
            time: row.comments_time
          })).then(resp => {
            console.log(resp)
            if (resp.data.message === 'success') {
              this.article.isResolve = "1"
              this.comments.forEach(item => {
                if (item === row) {
                  item.bestAnswer = "1";
                }
                return item;
              })
            }
          })
          this.$message({
            type: 'success',
            message: '设置成功!'
          });
        }).catch(() => {
          this.$message({
            type: 'info',
            message: '已取消'
          });
        });
      }
    },
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
      } //+ '&like=' + this.isLike
      this.$http.get('/Forum/Question/Detail?questionId=' + this.article.questionId + '&user=' + this.userId + '&like=' + this.isLike).then(
        resp => {
          console.log(resp)
        }
      )
    },
    CommentOpen() {
      window.location.hash = '#pinglun';
      history.replaceState(null, '', location.pathname + location.search);
    },
    goBack() {
      this.$router.back()

    },
    sendComment() {
      if (this.myComments == "") {
        this.$message({
          message: '评论不能为空',
          type: 'warning'
        })
        return;
      }
      this.$http.post('/Forum/Post?post_id=' + this.article.questionId, JSON.stringify({
        user_id: this.userId,
        content: this.myComments,
      })).then(resp => {
        console.log(resp);
        if (resp.data.status == 'success') {
          this.myComments = "";
          this.getData();
        }
        else {
          this.$message({
            message: '评论失败',
            type: 'warning'
          })
        }
      })
    }
  },
  mounted() {
    console.log(this.$route.query)
    this.getData();
  }

}
</script>
<style lang="less" scoped>
.dlog_content {
  border-bottom: 1px solid rgb(199, 197, 197);
  overflow-y: scroll;
  // margin-top: 10px;
}

.bold {
  font-size: 18px;
  font-weight: bold;
}

.text-normal {
  margin-top: 5px;
  font-size: 12px;

}

.background {

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

.heigh-card {
  margin-top: 10px;
}

.border {
  border-top: 1px solid;
}


// .dlog_content {
// // width: 680px;
// // height: 370px;
// // border-bottom: 1px solid rgb(199, 197, 197);
// overflow-y: scroll;
// // margin-top: 10px;
// // margin-bottom: 10px;
// }


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
  font-size: 26px;
  font-weight: bold;
  text-align: left;
  margin-left: 100px;
  margin-right: 100px;
  margin-top: 30px;
}

.article-detail {
  font-size: 18px;
  color: gray;
  text-align: left;
  margin-left: 100px;
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

.article-comments {
  margin-left: 80px;
  margin-right: 80px;
  // padding: 20px;
  border-bottom: 1px solid gainsboro;

}

.el-footer {
  // border: 1px solid gainsboro;
  position: absolute;
  top: calc(100vh - 180px);
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
  bottom: 50px;
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
</style>