<template>
  <div style="height: 100%">
    <el-container style="height: 100%;position: relative;">
      <el-header>
        <forumHeader />
      </el-header>
      <el-container v-if="articleclick" style="background-color: rgb(242, 241, 241);">

        <el-aside style="width: 250px;">
          <el-card>
            <div style="height: 10%; font-size:larger; text-align: center;" slot="header">
              我的关注
            </div>
            <el-scrollbar style="width:100%;">
              <div v-if="messageBox == null" style="height: 50px;text-align: center;">
                暂无关注
              </div>
              <div>

                <div :id="index" v-for="(item, index) in messageBox" :key="index" class="dlog_content"
                  @mouseover="Darken(index)" @mouseout="Lighten(index)" @click="getFollowDetail(item)">
                  <el-row class="content_other ">
                    <el-col :span="4"><el-avatar :size="25" :src="circleUrl"></el-avatar></el-col>

                    <el-col :span="8" class="context-title">
                      {{ item.follow_user_name }}
                    </el-col>
                  </el-row>
                  <el-row class="text-normal text-ellipsis" style="margin-bottom: 10px;  margin-left: 15px; ">
                    {{ item.intro }}
                  </el-row>
                </div>
              </div>
            </el-scrollbar>
          </el-card>
        </el-aside>
        <el-main style="background-color: white;">
          <el-scrollbar class="post-content">
            <div v-if="recordContent == null" style="height: 50px;text-align: center;margin-top: 50px;">
              暂无关注
            </div>
            <el-card :id="index" v-for="(item, index) in recordContent" :key="index" class="dlog_content"
              @click="getDetail(item.postId)" @mouseover="Darken(index)" @mouseout="Lighten(index)">
              <el-row class="content_other ">
                <el-col :span="2"><el-avatar :size="40" :src="circleUrl"></el-avatar></el-col>
                <el-col :span="6" class="context-title">
                  {{ item.autherName }}
                </el-col>
                <el-col :span="14" style="text-align: right;" class="text-normal">
                  {{ item.time }}
                </el-col>
              </el-row>
              <el-row class="text-ellipsis" style="margin-bottom: 10px;  margin-left: 15px; ">
                {{ item.title }}
              </el-row>
              <el-row :class="item.textEllipsis ? 'text-ellipsis-content' : ''"
                style="margin-bottom: 10px;  margin-left: 15px; " v-html="item.intro">
              </el-row>
              <el-row class="footer">
                <el-col :span="14">
                  <el-col :span="2" style="margin-left: 10px;"><el-button type="text" @click="textExpanded(item)">{{
                    item.textEllipsis ? '详情' : '收起'
                  }}</el-button></el-col>
                </el-col>
                <el-col :span="3" style="margin-top: 10px;"><i class="iconfont icon-pinglun"
                    style="font-size: 20px;font-weight:600; "></i><span style="font-size: medium; margin-left: 20px;">{{
                      item.comments }}</span></el-col>
                <el-col :span="3" style="margin-top: 10px;"><i :id="index + 'dianzan'" class="iconfont icon-dianzan"
                    style="font-size: 20px; " @click="getLike(item, index)"></i><span
                    style="font-size: medium; margin-left: 20px;">{{ item.like }}</span></el-col>
                <el-col :span="3" style="margin-top: 10px;"><i :id="index + 'shoucang'" class="iconfont icon-shoucang"
                    style="font-size: 20px;" @click="getFavorites(item, index)"></i><span
                    style="font-size: medium; margin-left: 20px;">{{ item.favorites }}</span></el-col>
              </el-row>
            </el-card>
          </el-scrollbar>
        </el-main>

      </el-container>

    </el-container>
  </div>
</template>
<script>
import forumHeader from '@/components/ForumHeader.vue'
import "../../assets/font_forum/iconfont.css"

export default {
  name: 'ForumMessage',

  data() {
    return {
      articleclick: true,
      textEllipsis: '详情',
      textClass: 'text-ellipsis-content',
      circleUrl: "https://cube.elemecdn.com/3/7c/3ea6beec64369c2642b92c6726f1epng.png",
      //发信息内容
      textarea: '',
      //对方名称
      destUserName: '',
      //对方ID
      destUserId: '',
      //左侧消息栏
      messageBox: [],
      //右侧具体消息
      recordContent: [
      ],
      myComments: '',
      userId: this.$store.getters['user/userName']
    }
  },
  components: {
    forumHeader
  },
  //默认向后台得到左侧边栏信息
  mounted() {
    this.$http.get('/Forum/Follow?user_id=' + this.userId).then(
      resp => {
        console.log(resp.data);
        //需要对方id 对方昵称 与对方最后一条信息内容、时间戳
        this.messageBox = JSON.parse(resp.data.user_infor);
        console.log(this.messageBox);
        this.recordContent = JSON.parse(resp.data.post_data);
        // console.log(this.recordContnt)
        if (this.recordContent != null) {
          this.recordContent.forEach(item => {
            item.textEllipsis = true;
            return item;
          })
        }

      }
    )

  },
  //调用函数右侧信息滑条默认下方
  watch: {

    recordContent: function () {
      this.$nextTick(() => {
        this.recordContent.forEach((it, index) => {
          if (it.if_collection == "true") {
            document.getElementById(index + "shoucang").style.color = "gold";
          }
          if (it.if_liked == "true") {
            document.getElementById(index + "dianzan").style.color = "gold";
          }
        })
      })
    }

  },

  methods: {
    getFollowDetail(row) {
      console.log(row);
      this.$router.push({ path: "/forum/userInformation", query: { user_id: row.follow_user_id, follow: '已关注' } });
    },
    //鼠标悬停变暗
    Darken(index) {
      document.getElementById(index).style.background = "rgb(244, 244, 244)";
    },
    //鼠标离开恢复
    Lighten(index) {
      document.getElementById(index).style.background = "white";

    },
    //滑条默认下方
    scrollDown() {
      this.$refs['myScrollbar'].wrap.scrollTop = this.$refs['myScrollbar'].wrap.scrollHeight
    },
    //按左侧一栏得到对方信息，向后台请求双方聊天记录
    getDetail(row) {
      console.log(row);
      this.articleclick = false

    },
    //发送消息，给后台双方id和内容
    SubmitContent() {
      this.$http.post('/Content', JSON.stringify({
        user_id: '111',
        dest_user_id: this.destUserId,
        content: this.textarea
      })).then(resp => {
        console.log(resp)
      })
    },
    //点赞时向后台返回信息，改变样式
    getLike(row, index) {
      console.log(index)
      let isLike = false
      if (document.getElementById(index + "dianzan").style.color != "gold") {
        document.getElementById(index + "dianzan").style.color = "gold";
        var dianzan = parseInt(row.like)
        dianzan += 1;
        row.like = dianzan.toString()
        isLike = true
      }
      else {
        document.getElementById("dianzan").style.color = "black";
        var dianzan = parseInt(row.like)
        dianzan -= 1;
        row.like = dianzan.toString();
        isLike = false
      } //
      let url = '/Forum/Post/Details?post_id=' + row.postId + '&user_id=' + this.userId + '&like=' + isLike;
      this.$http.get(url).then(
        resp => {
          console.log(resp)
          this.recordContent.forEach(item => {
            if (item.postId === row.postId) {
              return row;
            }
            else { return item }
          })
          console.log(this.recordContent)
        }
      )
    },
    //收藏时向后台返回信息，修改样式
    getFavorites(row, index) {
      let isFavorites = false
      if (document.getElementById(index + "shoucang").style.color != "gold") {

        document.getElementById(index + "shoucang").style.color = "gold";
        var shoucang = parseInt(row.favorites)
        shoucang += 1;
        row.favorites = shoucang.toString()
        isFavorites = true
      }
      else {
        document.getElementById(index + "shoucang").style.color = "black";
        var shoucang = parseInt(row.favorites)
        shoucang -= 1;
        row.favorites = shoucang.toString()
        isFavorites = false

      }
      let url = '/Forum/Post/Details?post_id=' + row.postId + '&user_id=' + this.userId + '&favorites=' + isFavorites;
      console.log(url)
      this.$http.get(url).then(
        resp => {
          console.log(resp)
        }
      )
    },
    textExpanded(row) {
      console.log(row)
      this.$router.push({ path: '/forum/post', query: { post_id: row.postId } })
      // this.recordContent[index].textEllipsis = !this.recordContent[index].textEllipsis
      // console.log(this.recordContent);
      // this.$forceUpdate();

    }

  }
}//对方向我发信息时如何自动更新
</script>
<style lang="less" scoped>
.background::-webkit-scrollbar {
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

.post-content::-webkit-scrollbar {
  height: 100%;
  width: 100%;
}

.context-title {
  font-size: 18px;
  // font-weight: bold;
}

.dlog_content::-webkit-scrollbar {
  cursor: pointer;
  overflow-y: scroll;
  // margin: 5px;
  // border-bottom: 1px solid rgb(221, 219, 219);
}

.text-ellipsis-content {
  display: -webkit-box;
  overflow: hidden;
  -webkit-line-clamp: 3;
  -webkit-box-orient: vertical;
}

.text-ellipsis {
  font-size: larger;
  font-weight: bold;
}


.text-normal {
  margin: 0px;
  margin-top: 4px;
  font-size: 12px;
  color: gray;

}

.el-aside {
  display: block;
  position: absolute;
  left: 2px;
  top: 65px;
  bottom: 0;
}

.el-main {
  position: absolute;
  left: 255px;
  right: 5px;
  top: 65px;
  bottom: 0;
  overflow-y: scroll;
  padding: 5px;
  // border: 1px solid gainsboro;
}

.footer {
  border-top: 1px solid gainsboro;
  margin-bottom: -10px;
}
</style>