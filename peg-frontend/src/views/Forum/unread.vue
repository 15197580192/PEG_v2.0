<template>
  <div style="height: 100%">
    <el-container style="height: 100%;position: relative; ">
      <el-header>
        <forumHeader />
      </el-header>
      <el-container class="background">
        <el-main>
          <el-card>
            <el-menu default-active="1" class="el-menu-demo" mode="horizontal" style="margin-top: -20px;"
              @select="handleSelect">
              <el-menu-item index="1">点赞</el-menu-item>
              <el-menu-item index="2">评论</el-menu-item>
            </el-menu>
            <div v-if="unread == null" style="height: 50vh;">
              <el-empty description="暂无未读"></el-empty>
            </div>
            <div :id="index" v-for="(item, index) in unread" :key="index" class="dlog_content post-content"
              style="margin-left: 5px;" @mouseover="Darken(index)" @mouseout="Lighten(index)"
              @click="articleDetail(item)">
              <el-col :span="2" style="margin-top: 10px;"><el-avatar :size="40" :src="circleUrl"
                  style="margin-left:30px ;" @click.native="AuthorHomePage"></el-avatar></el-col>
              <el-col :span="22">
                <el-row class="content_other ">
                  <div class="bold">{{ item.name }}</div>
                </el-row>
                <el-row>
                  <el-col>
                    <div class="article-detail">{{ item.time }}{{ type }}{{ item.postTitle }}这篇文章</div>
                  </el-col>
                </el-row>
              </el-col>
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
      myComments: "",
      question: [],
      comments: [],
      articleclick: true,
      circleUrl: "https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png",
      unread: [],
      unreadLike: [],
      unreadComments: [],
      type: '点赞了',
      userId: this.$store.getters['user/userName']
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
    handleSelect(index) {
      console.log(index)
      if (index == '1') {
        this.type = '点赞了';
        this.unread = this.unreadLike
      }
      if (index == '2') {
        this.type = '评论了';
        this.unread = this.unreadComments
      }
    }
  },
  mounted() {
    this.$http.get('/Forum/Unread?user_id=' + this.userId).then(resp => {
      console.log(resp);
      this.unreadLike = JSON.parse(resp.data.support);
      this.unreadComments = JSON.parse(resp.data.comments);
      this.unread = this.unreadLike
    })
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

.post-content::-webkit-scrollbar {
  height: 100%;
  width: 100%;
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
  margin-left: 30px;
  margin-bottom: 10px;
  margin-top: 10px;
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

.context-title {
  font-size: 18px;
  margin-top: 5px;
  // font-weight: bold;
}
</style>