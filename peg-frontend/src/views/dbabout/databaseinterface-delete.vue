<template>
  <el-card>
    <div slot="header" style="font-size: 20px; font-weight: 600">
      数据库删除
    </div>
    <div style="min-height: 68vh;">
      <div class="container8">
        <el-collapse>
          <el-collapse-item title="参考样例" name="1">
            <div style="float:left;width:99%;font-size:17px;">可以参考以下样例：DELETE DATA</div>
            <div style="float:left;width:91%;font-size:17px;">{</div>
            <div style="float:left;width:95%;font-size:17px;">{</div>
            <div style="float:left;width:115%;font-size:17px;">GRAPH &lt;http: / /my.graph.com&gt;
            </div>
            <div style="float:left;width:145%;font-size:17px;">
              &lt;http: / /my. domain.com/foo&gt;
              &lt;http: / /standard.com/ catalog#title&gt;"ABC" .
            </div>
            <div style="float:left;width:95%;font-size:17px;"> }</div>
            <div style="float:left;width:91%;font-size:17px;">};</div>
          </el-collapse-item>
        </el-collapse>

        <table class="search" v-show="selectshow">
          <tr>
            <td style="margin-top: 10%;font-size: 17px;color: #000000;">DELETE WHERE</td>
            <td><textarea v-model="where" placeholder="请输入内容" class="inputkuang"
                style="width: 100%;margin-top: 5%;"></textarea>
            </td>
          </tr>
          <tr>
            <el-button style="margin-left: 230%;margin-top: 10%;" @click="put">提交</el-button>
          </tr>
        </table>
        <el-button v-show="returnshow" style="width: 120px;height: 10%;" @click="returnback">返回查询页</el-button>
        <textarea v-show="isshow" style="margin-top: 40px;height: 50vh;" class="inputkuang">
				删除语句:{{ tempdata.删除语句 }}
				结果:{{ tempdata.结果 }}
				节点个数:{{ tempdata.节点个数 }}
			</textarea>
      </div>
    </div>
  </el-card>
</template>

<script>
export default {
  data() {
    return {
      a: this.$route.query.database_name,
      b: this.$route.query.cuid,
      c: this.$route.query.dbuser_id,
      where: '',
      isshow: false,
      selectshow: true,
      returnshow: false,
      tempdata: []
    }
  },

  methods: {
    returnback() {
      this.isshow = false;
      this.selectshow = true;
      this.returnshow = false;
    },
    put() {
      if (this.where == "") {
        this.$message({
          type: 'warning',
          message: '输入不能为空'
        });
        return;
      }
      this.$http.post('/DbDelete', JSON.stringify({
        db_name: this.a,
        database_creater_id: this.b,
        inner_check: this.where,
        dbuser_id: this.c
      }),).then(resp => {
        this.tempdata = resp.data;
        console.log(this.tempdata.结果)
        var tmp = [];
        console.log(this.tempdata.结果[0].结果)
        console.log(this.tempdata.结果[0].结果.replace("\n", " "))
        for (let i = 0; i < this.tempdata.结果.length; i++) {
          tmp.push(this.tempdata.结果[i].节点 + " " + "状态码：" + JSON.parse(this.tempdata.结果[i].结果.replace("\n", " ")).StatusCode + " " + "信息：" + JSON.parse(this.tempdata.结果[i].结果.replace("\n", " ")).StatusMsg)
        }
        this.tempdata.结果 = tmp
        this.isshow = true;
        this.selectshow = false;
        this.returnshow = true;
        this.$message({
          type: 'success',
          message: '删除成功!'
        });
      }).catch(err => {
        this.$message({
          type: 'info',
          message: '删除失败，请检查您输入的语句是否符合规范'
        })
      })
    },
  },
}
</script>

<style lang="less" scoped>
.inputchange {
  width: 100%;
  height: 30px;
  outline: none;
  border-radius: 25px;
  text-indent: 15px;
  font-size: 18px;
  margin: 10px 0;
}

.container8 {
  width: 100%;
  height: 100%;
}

.search {
  width: 85%;
  margin-top: 4%;
  margin-left: 7%;
  border-radius: 20px;
  border-color: #d6d6d6;
}

.header {
  width: 40%;
  height: 30%;
  margin-left: 5%;
  margin-top: 0.5%;
}

.header tr td {
  font-size: 18px;
  color: #666666;
  line-height: 14px;
  font-weight: 600;
}

.bodyshow {
  width: 85%;
  margin-top: 1%;
  margin-left: 10%;
  border-radius: 50px;
}

.bodyshow tr td {
  height: 4opx;
  font-size: 16px;
  color: #000000;
  line-height: 14px;
  font-weight: 400;
}

.bodyshow tr:nth-child(2n+1) {
  background-color: #a0e3e2;
}

.el-input__inner {
  border-radius: 10px;
  box-shadow: 0 2px 10px 3px #9c9c9c;
  background-color: rgba(255, 255, 255, 0.247);
  -moz-box-shadow: none;
  -webkit-box-shadow: none;
}

.inputkuang {
  border-radius: 10px;
  padding-top: 10px;
  padding-left: 7px;
  border-color: #9c9c9c;
  border-width: 1px 1px 1px 1px;
  box-shadow: 0 2px 10px 3px #d5d5d5;
  background-color: rgba(255, 255, 255, 0.247);
  color: #000000;
  opacity: 0.6;
  font-size: 20px;
  -moz-box-shadow: none;
  -webkit-box-shadow: none;
  width: 100%;
  resize: vertical;
  height: 30vh;
}

::v-deep .el-collapse-item__header {
  position: relative;
  font-size: large;
  padding-left: 30px;
}
</style>