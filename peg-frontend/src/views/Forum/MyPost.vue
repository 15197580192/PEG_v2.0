<template >
  <div style="height: 100%" v-loading="loading">
    <el-container style="height: 100%;position: relative; ">
      <el-header>
        <forumHeader />
      </el-header>
      <el-container class="background">
        <el-main>
          <el-row>
            <div @click="goBack();"><i class="el-icon-back"
                style="font-size:large; margin-left: 50px;margin-top: 10px;">返回</i></div>
            <el-divider></el-divider>
          </el-row>
          <el-row>
            <el-card>
              <el-menu :default-active="activeIndex" class="el-menu-demo" mode="horizontal" style="margin-top: -20px;">
                <el-menu-item index="1">推荐</el-menu-item>
                <!-- <el-menu-item index="2">最新</el-menu-item> -->
              </el-menu>
              <div v-if="isShow" style="height: 50vh;">
                <el-empty description="未找到搜索内容"></el-empty>
              </div>
              <div :id="index" v-for="(item, index) in forumIntro" :key="index" class="dlog_content"
                style="margin-left: 5px;" @mouseover="Darken(index)" @mouseout="Lighten(index)"
                @click="articleDetail(item)">
                <div class="content_other ">
                  <span style="font-size: 18px;font-weight:bold;margin-bottom: 5px;">{{ item.title }} </span>
                  <p style="margin: 0px;margin-top: 4px;font-size: 12px;color: gray;" class="text-ellipsis"
                    v-html="item.intro"></p>
                  <span style="margin: 0px;margin-top: 4px;font-size: 12px;color: gray;">
                    {{ item.autherName }}
                    <el-divider direction="vertical"></el-divider>
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
import forumHeader from '@/components/ForumHeader.vue'
import "../../assets/font_forum/iconfont.css"
export default {
  data() {
    return {
      isShow: false,
      loading: false,
      unreadComments: 0,
      unreadLike: 0,
      unreadMessage: 0,
      activeIndex: "1",
      //头像
      circleUrl: "https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png",
      //首页介绍
      forumInformation: [],
      //本人的关注和收藏数量
      follow: "",
      favorites: "",
      //首页文章简介
      forumIntro: [],
      userId: this.$store.getters['user/userName']

    }
  },
  mounted() {
    console.log(this.$route.query.searchData);
    this.$http.post('/Forum', JSON.stringify({ fuzzy_str: this.$route.query.searchData })).then(resp => {
      console.log(resp)
      if (resp.data.status == 'success') {
        let forumData = resp.data;
        this.forumIntro = JSON.parse(forumData.data);
        console.log(this.forumIntro)
      }
      else {
        this.isShow = true;
      }

    })
    // window.addEventListener('beforeunload', e => this.beforeunloadHandler(e))
  },

  components: {
    forumHeader
  },
  methods: {
    // beforeunloadHandler(e) {
    //   console.log('关闭窗口之后')
    // },
    //鼠标停留时变暗
    Darken(index) {
      document.getElementById(index).style.background = "rgb(244, 244, 244)";
    },
    //鼠标离开后变亮
    Lighten(index) {
      document.getElementById(index).style.background = "white";
    },
    //用户点击后，向后台请求文章详细信息
    articleDetail(row) {
      console.log(row);
      this.$router.push({ path: '/forum/post', query: { post_id: row.postId } })
    },
    gotoUnread() {
      this.$router.push('/forum/unread')
    },
    goBack() {
      this.$router.go(-1);
    },
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


.dlog_content::-webkit-scrollbar {
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

.el-carousel__item:nth-child(2n) {
  background-image: url('../../assets/image2.jpg');
}

.el-carousel__item:nth-child(2n+1) {
  background-image: url('../../assets/image1.jpg');
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
  top: calc(100vh - 180px);
  width: 100%;
  background-color: white;


}

.article-main {
  position: absolute;
  right: 0;
  top: 60px;
  bottom: 0px;
  overflow-y: scroll;
  padding: 0;
  background-color: white;


}

.context-title {
  font-size: 18px;
  margin-top: 5px;
  // font-weight: bold;
}

.text-ellipsis {
  width: 100%;
  max-height: 40px;
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}

.el-container ::-webkit-scrollbar {
  display: none
}
</style>