
<template>
  <el-card>
    <div slot="header" style="font-size: 20px; font-weight: 600">
      数据库查询
    </div>
    <div style="min-height: 68vh;">
      <div class="container8">
        <el-collapse>
          <el-collapse-item title="参考样例" name="1">
            <div style="float:left;width:90%;font-size:17px;">
              SELECT ?title
              <div style="float:left;width:99%;font-size:17px;">WHERE</div>
              <div style="float:left;width:95%;font-size:17px;">{</div>
              <div style="float:left;width:115%;font-size:17px;">
                &lt;http://example.org/book/book1&gt;
              </div>
              <div style="float:left;width:121%;font-size:17px;">
                &lt;http://purl.org/dc/elements/1.1/title&gt; ?title .
              </div>
              <div style="float:left;width:95%;font-size:17px;margin-bottom:15px;">}</div>
            </div>
          </el-collapse-item>
        </el-collapse>
        <table class="search" v-show="selectshow">
          <tr style="margin-bottom: 100%;">
            <td style="font-size: 17px;color: #000000;">SELECT</td>
            <td><textarea class="inputkuang" v-model="select" placeholder="请输入内容"></textarea>
            </td>
          </tr>
          <tr>
            <td style="margin-top: 10%;font-size: 17px;color: #000000;">WHERE</td>
            <td><textarea v-model="where" placeholder="请输入内容" class="inputkuang"
                style="width: 100%;margin-top: 5%;"></textarea>
            </td>
          </tr>
          <tr style="text-align: center;">
            <el-button style="margin-left: 230%;margin-top: 10%;" @click="put">提交</el-button>
          </tr>
        </table>
        <div style="width:100%;height:60px">
          <el-button v-show="returnshow" style="float: left;margin-left:1%;margin-top: 1%;"
            @click="returnback">返回查询页</el-button>
        </div>
        <div style="margin-top:15px;margin-left: 20%;">
          <table v-show="isshow" class="header">
            <tr>
              <td v-if="searchresult.length != 0">分解查询次数：{{ searchresult.分解查询次数 }}</td>
              <td v-if="searchresult.length != 0">分解次数: {{ searchresult.分解次数 }}</td>
              <td v-if="searchresult.length != 0">分解语句耗时:{{ searchresult.分解语句耗时 }}ms</td>
            </tr>
          </table>
        </div>
        <div style="margin-top:15px;">
          <table frame=box rules=all bordercolor="#a0e3e2;" v-show="isshow" class="bodyshow"
            v-for="(item, index) in displayedData" :key="item.分解次数">
            <tr style="height: 50px;background-color: #eff3f5;">
              <td style="width: 10%;height: 50px;">
                <p>分解次数</p>
              </td>
              <td>{{ item.分解次数 }}</td>
            </tr>
            <tr>
              <td style="height: 50px;">
                <p>连接前大小:</p>
              </td>
              <td>{{ item.连接前大小 }}</td>
            </tr>
            <tr>
              <td style="height: 50px;">
                <p>连接次数:</p>
              </td>
              <td>{{ item.连接次数 }}</td>
            </tr>
            <tr style="height: 50px;">
              <td>查询次数</td>
              <td>查询语句</td>
            </tr>
            <tr style="height: 90px;" v-for="(temp, index) in item.查询过程" :key="temp.查询次数">
              <td>
                <p>{{ temp.查询次数 }}</p>
              </td>
              <td>
                <p>{{ temp.查询语句 }}</p>
              </td>
            </tr>
            <tr style="height: 50px;" v-if="item.查询过程[0].查询节点">
              <td>节点ip+节点port</td>
              <td>
                <p>
                  {{ item.查询过程[0].查询节点[0] }}
                  {{ item.查询过程[0].查询节点[1] }}
                </p>
              </td>
            </tr>
            <tr v-for="(temp1, index) in item.连接过程" v-if="temp1" style="height: 50px;">
              <td>连接过程</td>
              <td>
                头部1：{{ temp1.头部1 }}
                头部2：{{ temp1.头部2 }}
                相等头部：{{ temp1.相等头部 }}
              </td>
            </tr>
            <tr v-if="!temp1" style="height: 50px;">
              <td>连接过程</td>
              <td>
                null
              </td>
            </tr>
          </table>
        </div>
        <div class="pagination" v-show="isshow">
          <el-button type="primary" icon="el-icon-arrow-left" @click="previousPage"
            :disabled="currentPage === 1">上一步</el-button>
          <span style="margin-left: 1%;margin-right: 1%;">{{ currentPage }} / {{ totalPages }}</span>
          <el-button type="primary" @click="nextPage">
            下一步<i class="el-icon-arrow-right el-icon--right"></i></el-button>
        </div>
        <el-input type="textarea" :rows="30" style="width: 80%;float: left;margin-left:10%;margin-top: 1%;"
          v-if="searchresult.结果" v-show="resultshow" v-model="searchresult.结果"></el-input>
        <!-- <table v-for="(item, index) in searchresult.总" v-show="resultshow" :key="item.分解次数" style="width: 20%;">
					<tr v-for="(temp1, n) in item.连接过程" v-if="temp1" :rows="30"
						style="width: 30%;float: left;margin-left:10%;margin-top: 1%;">
						<td>
							连接过程
						</td>
						<td>
							<p>{{ temp1.头部1 }}</p>
							<p>{{ temp1.头部2 }}</p>
							<p>{{ temp1.相等头部 }}</p>
						</td>
					</tr>
				</table> -->
        <!-- <div ref="ioc" style="height: 620px;width: 1000%;margin-left: 40%;" v-show="othershow"></div> -->
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
      select: '',
      where: '',
      isshow: false,
      othershow: false,
      selectshow: true,
      returnshow: false,
      resultshow: false,
      perPage: 1, // 每页显示的数据条数
      currentPage: 1, // 当前页数
      searchresult: []
    }
  },
  computed: {
    totalPages() {
      if (this.searchresult.length != 0)
        return Math.ceil(this.searchresult.总.length / this.perPage);
    },
    displayedData() {
      if (this.searchresult.length != 0) {
        const start = (this.currentPage - 1) * this.perPage;
        const end = start + this.perPage;
        return this.searchresult.总.slice(start, end);
      }
    }
  },
  methods: {
    previousPage() {
      if (this.currentPage > 1) {
        this.currentPage--;
      }
    },
    nextPage() {
      if (this.currentPage <= this.totalPages) {
        this.currentPage++;
      }
      if (this.currentPage == this.totalPages + 1) {
        this.isshow = false;
        this.othershow = true;
        this.currentPage = 1;
        this.resultshow = true;
      }
    },
    returnback() {
      this.isshow = false;
      this.othershow = false;
      this.currentPage = 1;
      this.selectshow = true;
      this.returnshow = false;
      this.resultshow = false;
    },
    put() {
      if (this.where == "") {
        this.$message({
          type: 'warning',
          message: '输入不能为空'
        });
        return;
      }
      this.$http.post('/DbQuery', JSON.stringify({
        db_name: this.a,
        database_creater_id: this.b,
        entity: this.select,
        inner_check: this.where,
        dbuser_id: this.c
      }),).then(resp => {
        const loading = this.$loading({
          lock: true,
          text: '正在查询中，请稍等.....',
          spinner: 'el-icon-loading',
          background: 'rgba(0, 0, 0, 0.7)'
        });

        console.log(this.$route.query.database_name);
        //console.log(resp.data);
        this.searchresult = resp.data;
        this.isshow = true;
        this.selectshow = false;
        this.returnshow = true;
        loading.close();
        this.$message({
          type: 'success',
          message: '查询成功!'
        });
      }).catch(err => {
        this.$message({
          type: 'info',
          message: '查询失败，请检查您输入的语句是否符合规范'
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
  border-radius: 10px;
  text-indent: 15px;
  font-size: 18px;
  margin: 10px 0;
}

.container8 {
  width: 100%;
  height: 100%;
}

.pagination {
  // width: 100%;
  margin-top: 3%;
  margin-bottom: 3%;
  text-align: center;
}

.search {
  width: 85%;
  margin-top: 4%;
  margin-left: 7%;
  border-radius: 10px;
  border-color: #d6d6d6;
}

.header {
  width: 100%;
  height: 30%;
}

.header tr td {
  font-size: 18px;
  color: #666666;
  line-height: 14px;
  font-weight: 600;
}

.bodyshow {
  height: 80vh;
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
  height: 18vh;
}

::v-deep .el-collapse-item__header {
  position: relative;
  font-size: large;
  padding-left: 30px;
}
</style>