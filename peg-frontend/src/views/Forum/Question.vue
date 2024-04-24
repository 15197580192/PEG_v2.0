<template >
  <div style="height: 100%" v-loading="loading">
    <el-container style="height: 100%;position: relative; ">
      <el-header>
        <forumHeader />
      </el-header>
      <el-container class="background">
        <el-main>
          <el-card>
            <el-menu default-active="1" class="el-menu-demo" mode="horizontal" style="margin-top: -20px;">
              <el-menu-item index="1">推荐</el-menu-item>
              <!-- <el-menu-item index="2">最新</el-menu-item> -->
            </el-menu>
            <div v-if="question == null" style="height: 50vh;">
              <el-empty description="暂无问答"></el-empty>
            </div>
            <div :id="index" v-for="(item, index) in question" :key="index" class="dlog_content main-scrollbar"
              style="margin-left: 5px;" @mouseover="Darken(index)" @mouseout="Lighten(index)"
              @click="articleDetail(item)">
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
                      {{ item.solved == '1' ? '已解决' : '未解决' }}
                    </span>
                  </div>

                  <span style="margin: 0px;margin-top: 4px;font-size: 12px;color: gray; float: right;">{{ item.ques_time
                  }}</span>
                </el-col>
              </el-row>
            </div>
          </el-card>
        </el-main>
      </el-container>

    </el-container>

  </div>
</template>

<script>
import forumHeader from '@/components/ForumHeader.vue'
import "../../assets/font_forum/iconfont.css"
export default {
  data() {
    return {
      loading: false,
      myComments: "",
      question: [],
      comments: [],
      articleclick: true,
      circleUrl: "https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png",
      article: {},
    }
  },
  components: {
    forumHeader
  },
  methods: {
    Darken(index) {
      document.getElementById(index).style.background = "rgb(244, 244, 244)";
    },
    Lighten(index) {
      document.getElementById(index).style.background = "white";
    },
    articleDetail(row) {

      this.$router.push({ path: '/forum/question/detail', query: { question_id: row.question_id } })
    },

  },
  mounted() {
    this.loading = true
    this.$http.get('/Forum/Question').then(resp => {
      console.log(resp);
      this.question = JSON.parse(resp.data.question_data);
    })
    this.loading = false
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

.el-carousel__item:nth-child(2n) {
  background-image: url('../../assets/image2.jpg');
}

.el-carousel__item:nth-child(2n+1) {
  background-image: url('../../assets/image1.jpg');
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

.article-main {
  position: absolute;
  right: 0;
  top: 60px;
  bottom: 50px;
  overflow-y: scroll;
  padding: 0;
  background-color: white;


}

.main-scrollbar::-webkit-scrollbar {
  width: 100%;
}

.context-title {
  font-size: 18px;
  margin-top: 5px;
  // font-weight: bold;
}
</style>