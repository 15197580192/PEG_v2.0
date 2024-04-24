import NoticeListVue from './NoticeList.vue';
<template>
  <el-card class="box-card">
    <!-- 设置标题公告管理 -->
    <div slot="header" class="clearfix">
      <span style="font-size:25px">发布公告</span>
    </div>
    <!-- 发布文章 -->
    <div class="article-title-container">
      <el-input clearable size="medium" maxlength="40" show-word-limit v-model="notice.noticeTitle"
        placeholder="输入公告标题" />
      <el-button type="danger" size="medium" @click="openDialog" style="margin-left:10px">发布公告</el-button>
    </div>
    <!-- 公告内容 -->
    <mavon-editor ref="md" v-model="notice.noticeContent" style="height:calc(100vh - 260px)" />

    <el-dialog title="发布公告" :visible.sync="showDialog" width="30%" :before-close="handleCancel">
      <el-form label-position="left" label-width="80px">
        <el-form-item label="公告标题">
          {{ notice.noticeTitle }}
        </el-form-item>
        <el-form-item label="创建者">
          {{ notice.creater }}
        </el-form-item>
        <el-form-item label="内容">
          {{ notice.noticeContent }}
        </el-form-item>
      </el-form>
      <span slot="footer">
        <el-button @click="handleCancel">取 消</el-button>
        <el-button type="primary" @click="handleSubmit">发布</el-button>
      </span>
    </el-dialog>
  </el-card>
</template>

<script>

export default {
  data() {
    return {
      showDialog: false,
      notice: {
        noticeContent: "", //内容
        noticeTitle: "",  //标题
        creater: this.$store.getters['user/userName'], //创建者
      }
    }
  },
  methods: {
    // 打开文章信息填写框
    openDialog() {
      if (
        this.assertNotEmpty(this.notice.noticeTitle, "请填写公告标题") &&
        this.assertNotEmpty(this.notice.noticeContent, "请填写公告内容")
      ) {
        this.showDialog = true;
      }
    },

    assertNotEmpty(target, msg) {
      if (!target) {
        this.$message({
          message: msg,
          type: "warning",
        });
        return false;
      }
      return true;
    },
    handleCancel() {
      this.notice = {}
      this.showDialog = false;
    },
    handleSubmit() {
      var data = JSON.stringify({
        creater_id: this.notice.creater,
        topic: this.notice.noticeTitle,
        content: this.notice.noticeContent
      })
      console.log(data)
      this.$http.post('/UpdateNotice', data).then((resp) => {
        console.log("发布", resp)
        if (resp.data.data == "success") {
          //退出时要清空
          this.$notify({
            title: "提示",
            message: `公告发布成功!`,
            type: "success",
          });

          this.notice = {};//清空
          this.showDialog = false;
        } else {
          this.$notify({
            title: "提示",
            message: `公告发布失败!`,
            type: "success",
          });
        }
      }).catch(function (error) {
        console.log("提交失败", error)
      })
    }
  }


}
</script>

<style  lang="less" scoped>
.box-card {
  width: 100%;
}

.clearfix:before,
.clearfix:after {
  display: table;
  content: "";
}

.clearfix:after {
  clear: both
}

.clearfix span {
  font-weight: 600;
}

.article-title-container {
  display: flex;
  align-items: center;
  margin-bottom: 1.25rem;
  margin-top: 10px;
}

.el-card {

  ::v-deep .el-card__header {
    padding: 10px 20px !important;
  }

  ::v-deep .el-card__body {
    padding: 0 20px !important;
  }
}
</style>

