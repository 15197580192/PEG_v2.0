<template>
  <el-card class="box-card">
    <!-- 设置标题公告管理 -->
    <div slot="header" class="clearfix">
      <span style="font-size:25px">日志列表</span>
    </div>
    <el-container>
      <el-main>
        <el-input v-model="searchData" placeholder="请输入用户名/事件" prefix-icon="el-icon-search" style="width: 30%;" clearable
          @clear="getData" @keyup.enter.native="searchTable">
        </el-input>
        <el-button type="primary" icon="el-icon-search" style="margin-left:8px" @click="searchTable">搜索</el-button>
        <el-button type="primary" icon="el-icon-refresh" style="float:right" @click="getmessage">刷新</el-button>
        <el-table :data="tableData.slice((currentPage - 1) * pageSize, currentPage * pageSize)"
          style="width: 70%; margin-top: 20px; margin-left:15%" v-loading="listLoading">
          <el-table-column fixed align="center" type="index" width="50">
          </el-table-column>
          <el-table-column fixed align="center" prop="peguserid" label="用户ID" width="150"></el-table-column>
          <el-table-column :show-overflow-tooltip="true" align="center" prop="pegtime" label="时间" width="160">
          </el-table-column>
          <el-table-column :show-overflow-tooltip="true" prop="pegthings" label="事件" width="320" align="center">
          </el-table-column>
          <el-table-column align="center" label="操作" width="150">
            <template v-slot="scope">
              <el-button size="mini" type="danger" icon="el-icon-delete" style="text-align: center;"
                @click="delete_box(scope.row)">删除</el-button>
            </template>
          </el-table-column>
          toggleRowSelection
        </el-table>
      </el-main>
      <el-footer>
        <div class="block" style="margin-top:15px;">
          <el-pagination align='center' @current-change="handleCurrentChange" :current-page="currentPage"
            :page-size="pageSize" layout="total,  prev, pager, next, jumper" :total="tableData.length">
          </el-pagination>
        </div>
      </el-footer>
    </el-container>
  </el-card>
</template>

<script>
export default {
  data() {
    return {
      tableData: [],//表格数据
      currentPage: 1, // 当前页码
      total: 20, // 总条数
      pageSize: 5, // 每页的数据条数
      searchData: "",
      listLoading: true,
    }
  },
  mounted() {
    this.getData()
  },
  watch: {
    searchData: {
      handler: function (n, o) {
        console.log("new", o);
        if (n == "") {
          this.getData()
        }
      }
    }

  },
  methods: {
    getData() {
      this.listLoading = true
      this.$http.get('/GetPegLog').then(resp => {
        console.log("系统日志", resp.data.data);
        this.tableData = JSON.parse(resp.data.data);
        this.listLoading = false
      })
    },
    //当前页改变时触发 跳转其他页
    handleCurrentChange(val) {
      console.log(`当前页: ${val}`);
      this.currentPage = val;
    },
    //刷新时得到节点信息，请求
    getmessage() {
      const loading = this.$loading({
        lock: true,
        text: '刷新成功！',
        spinner: 'el-icon-loading',
        background: 'rgba(0, 0, 0, 0.7)'
      });
      setTimeout(() => {
        this.getData()
        loading.close()
      }, 500);
    },

    //删除用户、在多选之后
    delete_box(row) {
      //text得到节点名显示在弹窗
      this.$confirm("是否确认删除用户" + row.peguserid + "的此条日志", '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        var data = JSON.stringify({
          peguser_id: row.peguserid,
          peg_things: row.pegthings,
          peg_time: row.pegtime
        })
        this.$http.post('/PegLogDelete', data).then(resp => {
          console.log("delete", resp)
          if (resp.data.data == "success") {
            this.$message({
              message: '删除成功!',
              type: 'success'
            })
            this.getData()
          }
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除!'
        });
      });
    },
    //根据信息查询节点
    searchTable() {
      if (this.searchData == null || this.searchData === '') {
        this.$message({
          type: 'info',
          message: '查找内容为空'
        });
        return;
      }
      var newtableData = this.tableData;
      this.tableData = newtableData.filter((item) => {
        if (item.peguserid == this.searchData) {
          return item;
        } else if (item.pegthings.includes(this.searchData)) {
          return item;
        }
      })
    },
  },
}
</script>

<style lang="less" scoped>
.el-container {
  min-height: 500px;
}

.box-card {
  width: 99%;
  height: 600px;
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

.el-card {
  ::v-deep .el-card__header {
    padding: 10px 20px !important;
  }

  ::v-deep .el-card__body {
    padding: 10px 20px 0 20px !important;
  }
}
</style>