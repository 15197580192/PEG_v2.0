<template>
  <el-card class="box-card">
    <!-- 设置标题公告管理 -->
    <div slot="header" class="clearfix">
      <span style="font-size:25px">公告列表</span>
    </div>
    <el-container>
      <el-main>
        <div style="margin-top:10px">
          <span style="font-size:20px;margin-right:10px;height:30px;line-height: 30px;"> 公告主题</span>
          <el-input v-model="searchData" placeholder="请输入关键词" prefix-icon="el-icon-search" style="width: 30%;" clearable
            @clear="getData" @keyup.enter.native="searchTable">
          </el-input>
          <el-button type="primary" icon="el-icon-search" style="margin-left:8px" @click="searchTable">搜索</el-button>
          <el-button type="primary" icon="el-icon-refresh" style="float:right" @click="getmessage">刷新</el-button>
        </div>

        <el-table v-loading="listLoading" :data="tableData.slice((currentPage - 1) * pageSize, currentPage * pageSize)"
          style="width: 100%; margin-top: 30px;">
          <el-table-column fixed align="center" type="index" width="60">
          </el-table-column>
          <el-table-column align="center" label="公告ID" prop="noticeid" width="120"></el-table-column>
          <el-table-column align="center" :show-overflow-tooltip="true" label="公告标题" prop="noticetopic" width="300">
          </el-table-column>
          <el-table-column align="center" label="创建者" prop="createrid" width="120">
          </el-table-column>
          <el-table-column align="center" label="创建时间" prop="createtime" width="200">
          </el-table-column>
          <el-table-column align="center" label="操作" width="300" fixed="right">
            <template v-slot="scope">
              <el-button size="small" plain icon="el-icon-view" style="text-align: center;" class="table-buttom"
                @click="handleOpen(scope.row)">查看</el-button>
              <el-button size="mini" type="danger" class="table-buttom" icon="el-icon-delete" style="text-align: center;"
                @click="delete_box(scope.row)">删除</el-button>
            </template>
          </el-table-column>
          toggleRowSelection
        </el-table>

        <el-dialog title="公告信息" :visible.sync="open" width="700px" append-to-body class="my-dialog-name">
          <el-form class="form" :model="currentItem" label-width="80px" label-position="left">
            <el-form-item label="公告主题" prop="noticetopic">
              <el-input disabled v-model="currentItem.noticetopic" size="small" />
            </el-form-item>
            <el-form-item label="公告内容">
              <mavon-editor class="md" v-model="currentItem.content" style="height:210px" :toolbarsFlag="false"
                :subfield="false" :editable="false" placeholder="公告内容..." />
            </el-form-item>
          </el-form>
        </el-dialog>

      </el-main>
      <el-footer>
        <div class="block" style="margin-top:30px;">
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
      visible: false,
      currentItem: {},
      open: false,
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
      this.$http.get('/GetNotice').then(resp => {
        console.log("noticeList", resp)
        this.tableData = JSON.parse(resp.data.data);
        this.listLoading = false
      })
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
        loading.close()
        this.getData()
      }, 500);
    },
    //当前页改变时触发 跳转其他页
    handleCurrentChange(val) {
      console.log(`当前页: ${val}`);
      this.currentPage = val;
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
      this.$http.get('/GetNoticeFuzzyFind?fuzzy_str=' + this.searchData).then(resp => {
        var result = JSON.parse(resp.data.data)
        console.log("查找resp", resp, result)
        if (result != null) {
          this.tableData = JSON.parse(resp.data.data)
          this.$message({
            type: 'success',
            message: '查找成功!'
          })
        } else {
          this.$message({
            type: 'info',
            message: '查找失败!'
          })
        }
      })

    },
    handleOpen(item) {
      this.currentItem = item;
      this.open = true;
    },
    delete_box(row) {
      this.$confirm('此操作将永久删除该公告, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        var noticeid = JSON.stringify(row.noticeid)
        this.$http.post('/DeleteNotice', { notice_id: noticeid }).then(resp => {
          console.log("删除resp", resp)
          if (resp.data.data == "success") {
            this.$message({
              type: 'success',
              message: '删除成功!'
            })
            this.getData()
          }
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除该公告！'
        })
      })
    },

  }
}

</script>

<style lang="less"> // 注意别用scoped,重新写一个style
 .set-popper {
   width: 500px;
   display: -webkit-box;
   overflow: hidden;
   text-overflow: ellipsis;
   -webkit-line-clamp: 12;
   -webkit-box-orient: vertical;
 }

 .set-content {
   cursor: default;
   width: 100%;
   overflow: hidden;
   white-space: nowrap;
   text-overflow: ellipsis;
 }

 .el-popover.monitor-popover {
   background-color: #303133;
   border-color: #303133;
   color: #FFFFF2;
 }

 //修改下面的小三角，属性名根据组件的placement位置做相应修改
 .monitor-popover .popper__arrow::after {
   border-top-color: #303133 !important;
 }
</style>

<style lang="less" scoped>
.table-buttom {
  width: 80px;
  margin-right: 15px;
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

.my-dialog-name {
  .el-dialog__header {
    padding: 5px 5px;
    background-color: #E5F6FE;

    .el-dialog__headerbtn {
      top: 10px;
      right: 8px;
    }
  }

  .el-dialog__body {
    padding: 10px 8px 0 8px;
  }
}
</style>
