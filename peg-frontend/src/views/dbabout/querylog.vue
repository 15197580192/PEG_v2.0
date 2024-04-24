<template>
  <el-card class="box-card">
    <div slot="header" style="font-size: 20px; font-weight: 600">
      数据库日志
    </div>
    <el-container>
      <el-main>
        <el-table v-loading="listLoading" :data="tableData.slice((currentPage - 1) * pageSize, currentPage * pageSize)"
          style="width: 812px; margin-top: 30px;margin:0px auto;" header-align="center" border>
          <el-table-column fixed align="center" type="index" width="60">
          </el-table-column>
          <el-table-column align="center" label="数据库" prop="databaseid" width="150">
          </el-table-column>
          <el-table-column align="center" label="用户" prop="dbuserid" width="150">
          </el-table-column>
          <el-table-column align="center" label="操作时间" prop="operatetime" width="250"></el-table-column>
          <el-table-column align="center" :show-overflow-tooltip="true" label="操作类型" prop="operatetype" width="200">
          </el-table-column>
          toggleRowSelection
        </el-table>
      </el-main>
      <el-footer style="margin-left: 20vh;">
        <div class="block" style="margin-top:10px;margin-left: 20%;">
          <el-pagination @current-change="handleCurrentChange" :current-page="currentPage" :page-size="pageSize"
            layout="total,  prev, pager, next, jumper" :total="tableData.length">
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
      pageSize: 6, // 每页的数据条数
      searchresult: [],
      listLoading: false,
    }
  },
  created() {
    this.getData()
  },
  methods: {
    getData() {
      this.listLoading = true
      this.$http.get("/GetDbLogByDbId", {
        params: {
          db_name: this.$route.query.database_name,
          database_creater_id: this.$route.query.cuid
        }
      })
        .then((result) => {
          this.tableData = JSON.parse(result.data.data);
          this.listLoading = false
        })
        .catch((err) => {
          console.log(err);
        });
    },
    //当前页改变时触发 跳转其他页
    handleCurrentChange(val) {
      console.log(`当前页: ${val}`);
      this.currentPage = val;
    },
  }
}
</script>

<style lang="less" scoped>
select {
  background-color: white;
  color: gray;
  border: 0px;
  font-family: Arial, Helvetica, sans-serif;
  font-size: 20px;
  margin-left: 5px;
  outline: none;
}

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

