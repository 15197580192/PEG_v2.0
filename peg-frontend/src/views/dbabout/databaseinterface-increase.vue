<template>
  <el-card>
    <div slot="header" style="font-size: 20px; font-weight: 600">
      数据库增加
    </div>
    <div style="min-height: 68vh;">
      <div class="container8">
        <el-collapse>
          <el-collapse-item title="参考样例" name="1">
            <p style="float:left;width:99%;font-size:17px;">可以参考以下样例：INSERT DATA
            <p style="float:left;width:103%;font-size:17px;">{</p>
            <p style="float:left;width:140%;font-size:17px;"> swp:LuxuryApartment rdfs:subClassOf swp:Apartment.</p>
            <p style="float:left;width:103%;font-size:17px;"> }</p>
            </p>
          </el-collapse-item>
        </el-collapse>

        <table class="search" v-show="selectshow">
          <tr>
            <td style="margin-top: 10%;font-size: 17px;color: #000000;">INSERT WHERE</td>
            <td><textarea v-model="where" placeholder="请输入内容" class="inputkuang"
                style="width: 100%;margin-top: 5%;"></textarea>
            </td>
          </tr>
          <tr>
            <el-button style="margin-left: 230%;margin-top: 10%;" @click="put">提交</el-button>
          </tr>
        </table>
        <el-button v-show="returnshow" style=" width: 120px;height: 10%;" @click="returnback">返回查询页</el-button>
        <!-- <textarea v-show="isshow" style="width: 60%;margin-top: 5%;height: 70px;">
				主语:{{tempdata.主语}}
				宾语:{{tempdata.宾语}}
				插入情况:{{tempdata.插入情况}}
				插入语句:{{tempdata.插入语句}}
				节点个数:{{tempdata.节点个数}}
			</textarea> -->
        <textarea v-show="isshow" class="inputkuang" style="margin-top: 40px;height: 50vh;">
				{{ formattedResult }}
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
  computed: {
    formattedResult() {
      return `主语: ${this.tempdata.主语}\n\n 宾语: ${this.tempdata.宾语}\n\n 插入情况: ${this.tempdata.插入情况}\n\n 插入语句: ${this.tempdata.插入语句}\n\n 节点个数: ${this.tempdata.节点个数}`;
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
      this.$http.post('/DbInsert', JSON.stringify({
        db_name: this.a,
        database_creater_id: this.b,
        inner_check: this.where,
        dbuser_id: this.c
      }),).then(resp => {
        this.tempdata = resp.data;
        this.isshow = true;
        this.selectshow = false;
        this.returnshow = true;
        this.$message({
          type: 'success',
          message: '增加成功!'
        })
      }).catch(err => {
        this.$message({
          type: 'info',
          message: '增加失败，请检查您输入的语句是否符合规范'
        })
      });
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

.pagination {
  width: 100%;
  margin-top: 3%;
  margin-bottom: 3%;
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
  border-radius: 60px;
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