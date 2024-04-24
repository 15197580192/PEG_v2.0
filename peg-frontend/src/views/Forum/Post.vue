<template>
  <div style="height: 100%">
    <el-container style="height: 100%;position: relative;">
      <el-header>
        <forumHeader />
      </el-header>
      <el-main>
        <div>
          标题：
          <el-input v-model="input" placeholder="请输入内容"></el-input>
        </div>
        <div style="margin-top: 10px;height: 100%;">
          <Toolbar style="border-bottom: 1px solid #ccc" :editor="editor" :defaultConfig="toolbarConfig" :mode="mode" />
          <Editor style="height: 500px; overflow-y: hidden;" v-model="html" :defaultConfig="editorConfig" :mode="mode"
            @onCreated="onCreated" />
        </div>

      </el-main>
      <el-footer>
        <div>
          <el-button type="text" round @click="GetPost">查看草稿</el-button>
          <el-select v-model="value" placeholder="请选择">
            <el-option v-for="item in draftList" :key="item.title" :label="item.title" :value="item.title">
              <div style="float: left" class="ellips">{{ item.title }}</div>
              <div style="float: right; color: #8492a6; font-size: 10px">{{ item.time.slice(0, 10) }}</div>
            </el-option>
          </el-select>
          <el-button type="primary" round style="float: right;" @click="Submit">发布</el-button>
          <el-button type="primary" round style="float: right;margin-right: 20px;" @click="SavePost">保存</el-button>
          <el-radio v-model="radio" label="帖子" style="float: right;margin: 15px;">帖子</el-radio>
          <el-radio v-model="radio" label="问答" style="float: right;margin: 15px;">问答</el-radio>
        </div>
      </el-footer>
    </el-container>
  </div>
</template>
<script>
import { Editor, Toolbar } from '@wangeditor/editor-for-vue'
import forumHeader from '@/components/ForumHeader.vue'
// import { json } from 'stream/consumers'
export default {
  components: { Editor, Toolbar, forumHeader },
  data() {
    return {
      showSave: false,
      radio: "问答",
      input: '',
      editor: null,
      html: '<p></p>',
      userId: this.$store.getters['user/userName'],
      toolbarConfig: {
        excludeKeys: [
          'emotion',
          "insertLink",
          'group-image',
          'group-video'

        ]
      },
      editorConfig: { placeholder: '请输入内容...' },
      mode: 'default', // or 'simple'
      draftList: [],
      value: ''
    }
  },

  watch: {
    $route(to, from) {
      // console.log("到哪个页面去", to.path);
      // console.log("从哪个页面来", from.path);
      if (to.path != "") {
        console.log('紧急保存');
      }
    }
  },
  methods: {
    onCreated(editor) {
      this.editor = Object.seal(editor) // 一定要用 Object.seal() ，否则会报错

    },
    getText(str) {
      return str
        .replace(/<[^<>]+>/g, '')   // 是将所有<>的内容 replace成 ''    
        .replace(/&nbsp;/gi, '')   // gi是全局搜索，将所有的 &nbsp 都replace成 ''         
    },
    isNull(str) {
      if (str == '') return true
      var regu = '^[ ]+$'
      var re = new RegExp(regu)
      return re.test(str)
    },
    Submit() {
      if (this.input == '') {
        this.$message({
          message: '标题不能为空',
          type: 'warning'
        });
        return;
      }
      let text = this.getText(this.html);
      if (this.isNull(text)) {
        this.$message({
          message: '内容不能为空',
          type: 'warning'
        });
        return;
      }
      console.log(this.html)
      this.$http.post('/Forum/Creation/Editor', JSON.stringify({
        type: this.radio,
        title: this.input,
        content: this.html,
        user_id: this.$store.getters['user/userName'],
        choice: "发布"
      })).then(resp => {
        console.log(resp)
        if (resp.data.message = 'success') {
          this.$message({
            message: '发布成功',
            type: 'success'
          })
          this.$confirm('是否继续编辑?', '提示', {
            confirmButtonTextt: '确定',
            cancelButtonText: '取消',
            type: 'warning'
          }).then(() => {
            this.html = '<p></p>';
            this.input = "";
          }).catch(() => {
            this.$router.push('/forum');
          })

        }
        else {
          this.$message({
            message: '发布失败',
            type: 'warning'
          });
        }
      })
    },
    SavePost() {
      if (this.input == '') {
        this.$message({
          message: '标题不能为空',
          type: 'warning'
        });
        return;
      }
      let text = this.getText(this.html);
      if (this.isNull(text)) {
        this.$message({
          message: '内容不能为空',
          type: 'warning'
        });
        return;
      }
      this.$http.post('/Forum/Creation/Editor', JSON.stringify({
        type: this.radio,
        title: this.input,
        content: this.html,
        user_id: this.$store.getters['user/userName'],
        choice: "保存"
      })).then(resp => {
        console.log(resp)
        if (resp.data.message = 'success') {
          this.$message({
            message: '保存成功',
            type: 'success'
          })
          this.$http.get('/Forum/Creation/Editor?user_id=' + this.userId).then(resp => {
            console.log(resp);
            if (resp.data.data != undefined)
              this.draftList = JSON.parse(resp.data.data)

          })
          this.$confirm('是否继续编辑?', '提示', {
            confirmButtonTextt: '确定',
            cancelButtonText: '取消',
            type: 'warning'
          }).then(() => {
            this.html = '<p></p>';
            this.input = "";
          }).catch(() => {
            this.$router.push('/forum');
          })
        }
        else {
          this.$message({
            message: '保存失败',
            type: 'warning'
          });
        }
      })
    },
    GetPost() {
      console.log(this.value)
      let draft = {};
      if (this.value != '') {
        this.draftList.forEach(item => {
          if (item.title === this.value) {
            draft = item
          }
          return item
        })
      }
      else {
        this.$message({
          message: '请先选择草稿',
          type: 'danger',
        })
        return;
      }
      console.log(draft)
      if (draft != null) {
        this.$http.post('/Forum/Creation/Editor', JSON.stringify({
          author_id: draft.author_id,
          type: draft.type,
          title: draft.title
        })).then(resp => {
          console.log(resp);
          this.value = ""
          this.input = JSON.parse(resp.data.data).title
          this.html = JSON.parse(resp.data.data).content
          this.radio = JSON.parse(resp.data.data).type

          this.$http.get('/Forum/Creation/Editor?user_id=' + this.userId).then(resp => {
            console.log(resp);
            if (resp.data.data != undefined)
              this.draftList = JSON.parse(resp.data.data)
            else {
              this.draftList = []
            }

          })
        })

      }

      // if (this.value != '') {

      //   this.$http.post('/forum/creation/editor?user_id=' + this.userId, { title: this.value.title, type: this.value.type }).then(resp => {
      //     console.log(resp);

      //   })
      // }
    },

  },
  mounted() {
    this.showSave = true
    this.$http.get('/Forum/Creation/Editor?user_id=' + this.userId).then(resp => {
      console.log(resp);
      if (resp.data.data != undefined)
        this.draftList = JSON.parse(resp.data.data)

    })
  },
  beforeDestroy() {
    const editor = this.editor
    if (editor == null) return
    editor.destroy() // 组件销毁时，及时销毁编辑器
  }
}
</script>
<style scoped lang="less">
@import url("@wangeditor/editor/dist/css/style.css");

.el-main::-webkit-scrollbar {
  // position: absolute;
  right: 0;
  top: 60px;
  bottom: 0;
  overflow-y: scroll;
  padding: 0;
  // border: 1px solid gainsboro;
}

.el-footer {
  border: 1px solid gainsboro;
  position: absolute;
  top: calc(100vh - 180px);
  width: 100%;
  box-shadow: 0 0 20px 2px rgba(7, 7, 7, 0.1);
  padding: 10px 30px 10px 10px;
  background-color: white;
}

.ellips {
  width: 100px;
  max-height: 40px;
  overflow: hidden;
  /*超出部分隐藏*/
  white-space: nowrap;
  /*禁止换行*/
  text-overflow: ellipsis;
  /*省略号*/

}
</style>