<template>
  <div style="height: 100%">
    <el-container style="height: 100%;position: relative;">
      <el-header>
        <forumHeader ref="childData" />
      </el-header>
      <el-container class="background">
        <el-aside style="border: 1px solid gainsboro;background-color: white;">
          <div class="aside-message">
            <div
              style="height: 50px;border-bottom: 1px solid gainsboro; font-size:larger; text-align: center;margin-top: 10px;">
              私信
            </div>
            <div style=" height: 90%; width:100%;" class="list-aside">
              <div v-if="messageBox.length == 0 || messageBox == null"
                style="height: 50px;text-align: center;margin-top: 50px;">
                暂无消息
              </div>
              <div v-if="messageBox.length != 0 && messageBox != null">
                <div :id="index" v-for="(item, index) in messageBox" :key="index" class="dlog_content message-list"
                  @click="getDetail(item)" @mouseover="Darken(index)" @mouseout="Lighten(index)">
                  <el-badge :value="(((item.flag == '1') || (item.oldFriend != true)) ? '' : '...')" class="item"
                    style="width: 95%;height: =100%;">
                    <el-row class="content_other ">
                      <el-col :span="16" class="context-title">
                        {{ item.dest_user_name }}
                      </el-col>
                      <el-col :span="8" style="float: right;" class="text-normal">
                        {{ item.send_time.slice(0, 10) }}
                      </el-col>
                    </el-row>
                    <el-row class="text-normal text-ellipsis" style="margin-bottom: 10px;  margin-left: 15px; ">
                      {{ item.content }}
                    </el-row>
                  </el-badge>
                </div>
              </div>
            </div>
          </div>
        </el-aside>
        <el-main class="chat-window">

          <div
            style="background-color: rgb(255, 255, 255);height: 8%;text-align: center;border: 1px solid gainsboro; font-size:larger;padding-top: 15px;">
            {{ destUserName }}
          </div>
          <el-scrollbar ref="myScrollbar" style="height: 65%;width:100%; background-color: rgb(244, 244, 244);">
            <div class="chat-content">

              <!-- recordContent 聊天记录数组-->
              <div v-for="(itemc, indexc) in recordContent" :key="indexc">
                <!-- 对方 -->
                <div class="word" v-if="!(itemc.source_id == userId)">
                  <img src="../../assets/user.png">
                  <div class="info">
                    <p class="time">{{ itemc.source_name }} {{ (itemc.send_time) }}</p>
                    <div class="info-content">{{ itemc.content }}</div>
                  </div>
                </div>
                <!-- 我的 -->
                <div class="word-my" v-else>
                  <div class="info">
                    <p class="time">{{ itemc.source_name }} {{ (itemc.send_time) }}</p>
                    <div class="info-content">{{ itemc.content }}</div>
                  </div>
                  <img src="../../assets/user.png">
                </div>
              </div>
            </div>
          </el-scrollbar>
          <div v-if="startChat" class="mine-chat">
            <el-row class="inputarea">
              <el-input type="textarea" placeholder="请输入内容" v-model="textarea" :rows="4">
              </el-input>
            </el-row>
            <el-row>
              <el-button type="primary" style="float: right;" round @click="SubmitContent">发送</el-button>
            </el-row>
          </div>
        </el-main>
      </el-container>
    </el-container>
  </div>
</template>
<script>
import forumHeader from '@/components/ForumHeader.vue'
export default {
  name: 'ForumMessage',
  data() {
    return {
      //发信息内容
      textarea: '',
      //对方名称
      destUserName: '',
      //对方ID
      destUserId: '',
      //左侧消息栏
      messageBox: [],
      //右侧具体消息
      recordContent: [],
      startChat: false,
      userId: this.$store.getters['user/userName'],
      // routeChange: this.$route.fullPath
    }
  },
  components: {
    forumHeader
  },
  //默认向后台得到左侧边栏信息
  mounted() {
    this.getData();

  },
  //调用函数右侧信息滑条默认下方
  updated: function () {
    this.scrollDown()
  },
  watch: {
    $route: {
      immediate: true, // 一旦监听到路由的变化立即执行
      handler(to, from) {
        console.log("监听路由：" + JSON.stringify(to.name));
      },
    }
  },
  methods: {
    getPath() {
      console.log(this.$route.path);
    },
    getData() {
      this.$http.get('/Forum/Chat?user_id=' + this.userId).then(
        resp => {
          console.log(resp)
          if (resp.data.data != "null") {
            var data = JSON.parse(resp.data.data);
            this.messageBox = data;
            this.messageBox.forEach(it => {
              it.oldFriend = true;
            })
            if (this.$route.query.dest_user_id != undefined) {
              //需要对方id 对方昵称 与对方最后一条信息内容、时间戳
              let flag = 1;
              this.messageBox.forEach(it => {
                if (this.$route.query.dest_user_id != undefined) {
                  if (this.$route.query.dest_user_id == it.dest_user_id) {
                    flag = 0;
                  }
                }
              })
              if (flag == 1) {
                console.log(this.$route.query.dest_user_id);
                //message数组加入新的对话
                this.messageBox.unshift({
                  dest_user_id: this.$route.query.dest_user_id,
                  dest_user_name: this.$route.query.dest_user_name,
                  send_time: ' ',
                  content: '暂无聊天',
                  oldFriend: false
                })
              }
            }
          } else {
            if (this.$route.query.dest_user_id != undefined) {
              this.messageBox.unshift({
                dest_user_id: this.$route.query.dest_user_id,
                dest_user_name: this.$route.query.dest_user_name,
                send_time: ' ',
                content: '暂无聊天',
                oldFriend: false
              })
            }
          }
        }
      )

      console.log(this.messageBox)
    },
    //鼠标悬停变暗
    Darken(index) {
      document.getElementById(index).style.background = "gainsboro";
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
      row.flag = '1';
      this.startChat = true;
      this.destUserName = row.dest_user_name;
      this.destUserId = row.dest_user_id;
      if (row.oldFriend) {
        this.chatDetail();
        let timer = setInterval(() => {
          if (this.destUserId === '' || this.$route.fullPath != '/forum/message') {
            clearInterval(timer);
          }
          this.chatDetail();
        }, 20000)
      }
    },
    chatDetail() {
      let url = '/Forum/Chat/Detail?user_id=' + this.userId + '&dest_id=' + this.destUserId
      console.log(url)
      this.$http.get(url).then(
        resp => {
          console.log(resp)
          let contentData = JSON.parse(resp.data.chat_data)
          contentData.forEach(item => {
            item.send_time = this.timeToTimestamp(item.send_time)
            return item
          })
          this.recordContent = contentData
          this.recordContent.sort(this.sortBy('send_time', 1))
        }
      )
    },
    timeToTimestamp(time) {
      let j = 0;
      let str = [...time]
      for (let i = 0; i < str.length; i++) {
        if (str[i] == '-') {
          j++;
          if (j == 3) { str[i] = ' '; }
          if (j == 4) { str[i] = ':'; }
          if (j == 5) { str[i] = ':'; }
        }

      }
      console.log(str.toString().split(",").join(""))
      return str.toString().split(",").join("");
    },
    sortBy(attr, rev) {
      if (rev == undefined) { rev = 1 } else { (rev) ? 1 : -1; }
      return function (a, b) {
        a = Date.parse(new Date(a[attr]).toString());
        b = Date.parse(new Date(b[attr]).toString());
        if (a < b) { return rev * -1 }
        if (a > b) { return rev * 1 }
        return 0;
      }
    },
    //发送消息，给后台双方id和内容,如果是新朋友，要放入messagebox里
    SubmitContent() {
      if (this.textarea == "") {
        this.$message({
          type: 'danger',
          message: '发送不能为空'
        });
        return;
      }
      this.$http.post('/Forum/Chat', JSON.stringify({
        user_id: this.userId,
        dest_user_id: this.destUserId,
        content: this.textarea
      })).then(resp => {
        console.log(resp);
        if (resp.data.status == 'success') {
          this.textarea = '';
          this.chatDetail();
          this.getData();
          this.messageBox.forEach((item) => {
            if (item.dest_user_id == this.destUserId && item.oldFriend == false) {
              item.oldFriend = true;
            }
            console.log(item);
            return item;
          })
        }
      })

    }
  }
}
//对方向我发信息时如何自动更新
</script>
<style lang="less" scoped>
.background::-webkit-scrollbar {
  width: 100%;
  // height: 100%;
  padding: 0;
  height: calc(100vh - 70px);
  background-color: white;
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
  margin-left: 15px;
  // font-weight: bold;
}

.dlog_content::-webkit-scrollbar {

  cursor: pointer;
  overflow-y: scroll;
  // margin: 5px;

}

.message-list {
  height: 70px;
  border-bottom: 1px solid rgb(221, 219, 219);
  padding-top: 10px;
}

.text-ellipsis {
  width: 200px;
  max-height: 40px;
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}

.text-normal {
  margin: 0px;
  margin-top: 4px;
  font-size: 12px;
  color: gray;

}

.aside-message::-webkit-scrollbar {
  width: 100%;
  height: 100%;
  border: 1px solid black;
}

.el-aside {
  width: 250px;
  display: block;
  position: absolute;
  left: 0;
  top: 60px;
  bottom: 0;
}

.el-main {
  background-color: #ffffff;
  position: absolute;
  left: 300px;
  right: 0;
  top: 60px;
  bottom: 0;
  overflow-y: scroll;
  padding: 0;
  // border: 1px solid gainsboro;
}

.chat-window ::-webkit-scrollbar {
  background-color: #ffffff;
}

/deep/ .el-tabs__item {
  margin-left: 20px;
  font-size: medium;
  width: 250px;
}

.mine-chat::-webkit-scrollbar {
  height: 25%;
  border: 1px solid gainsboro;
}

.chat-content {
  width: 90%;
  height: 80%;
  margin: 0 auto;
  // position: absolute;
  // bottom: 50px;
  // left: 20px;
  // top: 0;
  // background-color: #A3C3F6;

  .word {
    display: flex;
    margin-bottom: 20px;

    // margin-left: 20px;
    img {
      width: 40px;
      height: 40px;
      border-radius: 50%;
    }

    .info {
      margin-left: 10px;

      .time {
        font-size: 12px;
        color: rgba(51, 51, 51, 0.8);
        margin: 0;
        height: 20px;
        line-height: 20px;
        margin-top: -5px;
      }

      .info-content {
        padding: 10px;
        font-size: 14px;
        background: #fff;
        position: relative;
        margin-top: 8px;
      }

      //小三角形
      .info-content::before {
        position: absolute;
        left: -8px;
        top: 8px;
        content: '';
        border-right: 10px solid #FFF;
        border-top: 8px solid transparent;
        border-bottom: 8px solid transparent;
      }
    }
  }

  .word-my {
    display: flex;
    justify-content: flex-end;
    margin-bottom: 20px;
    // margin-right: -20px;

    img {
      width: 40px;
      height: 40px;
      border-radius: 50%;
    }

    .info {
      width: 90%;
      margin-left: 10px;
      text-align: right;

      .time {
        font-size: 12px;
        color: rgba(51, 51, 51, 0.8);
        margin: 0;
        height: 20px;
        line-height: 20px;
        margin-top: -5px;
        margin-right: 10px;
      }

      .info-content {
        max-width: 70%;
        padding: 10px;
        font-size: 14px;
        float: right;
        margin-right: 10px;
        position: relative;
        margin-top: 8px;
        background: #A3C3F6;
        text-align: left;
      }

      //小三角形
      .info-content::after {
        position: absolute;
        right: -8px;
        top: 8px;
        content: '';
        border-left: 10px solid #A3C3F6;
        border-top: 8px solid transparent;
        border-bottom: 8px solid transparent;
      }
    }
  }
}

.inputarea {
  background-color: #ffffff;
  border-radius: 10px;
  font-style: normal;

  &/deep/ .el-textarea__inner {
    border: none;
    border-radius: 10px;
    resize: none;
  }
}
</style>