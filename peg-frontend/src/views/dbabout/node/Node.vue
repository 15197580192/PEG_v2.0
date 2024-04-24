<template>
  <div>
    <el-container>
      <el-main>
        <!-- v-model="input2" -->
        <el-input placeholder="请输入内容" prefix-icon="el-icon-search" style="width: 30%;" v-model="searchData" clearable
          @clear="getData" @keyup.enter.native="searchTable">
        </el-input>
        <el-button type="primary" icon="el-icon-search" style="margin-left: 10px;" @click="searchTable">搜索</el-button>
        <el-button type="danger" icon="el-icon-delete" style="float: right;" @click="delete_box"
          v-if="showButton">删除</el-button>
        <el-button type="primary" icon="el-icon-refresh" style="float: right;" @click="getmessage">刷新</el-button>
        <el-button type="primary" icon="el-icon-circle-plus-outline" style="float: right;" @click="skipNewNode"
          v-if="showButton">新增</el-button>
        <el-table v-loading="listLoading" :data="tableData.slice((currentPage - 1) * pageSize, currentPage * pageSize)"
          border style="width: 100%; margin-top: 20px; table-layout: auto;" @selection-change="handleSelectionChange"
          @row-click="textRowClick">
          <!-- @row-click="textRowClick" -->
          <el-table-column type="selection" width="40" align="center">
          </el-table-column>
          <el-table-column fixed prop="node_id" label="节点名称" width="150">
          </el-table-column>
          <el-table-column prop="node_ip" label="节点IP" width="150">
          </el-table-column>
          <el-table-column prop="user_id" label="Linux用户" width="120">
          </el-table-column>
          <el-table-column prop="gstore_user_id" label="gStore用户" width="120">
          </el-table-column>
          <el-table-column prop="gstore_user_password" label="gStore密码" width="120">
          </el-table-column>
          <el-table-column prop="version" label="gStore版本" width="120">
          </el-table-column>
          <el-table-column prop="apitype" label="gStore接口类型" width="120">
          </el-table-column>
          <el-table-column prop="port" label="gStore端口" width="120">
          </el-table-column>
          <el-table-column prop="rootpath" label="配置路径" width="220">
          </el-table-column>

          <el-table-column fixed="right" label="状态" width="120">

            <template v-slot="scope">
              <el-popover trigger="hover" placement="top">
                <p>点击得到节点实时状态</p>
                <div slot="reference" class="name-wrapper">
                  <el-tag :type="scope.row.state == '0' ? 'danger' : 'success'" v-if="scope.row.state != 'unknow'">{{
                    scope.row.state == '0' ? '已关闭' : '已开启'
                  }}</el-tag>
                  <el-tag type="warning" v-if="scope.row.state == 'unknow'">未知</el-tag>
                </div>
              </el-popover>
            </template>
          </el-table-column>

          <el-table-column fixed="right" label="操作" width="100">
            <template v-slot="scope">
              <el-button @click="handleClick(scope.row)" type="text" size="small">{{ showChange }}</el-button>
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
  </div>
</template>
<!-- rootpath -->
<script>
export default {

  // created() {
  //   this.getmessage();
  // },
  data() {

    return {
      tableData: [],//表格数据
      currentPage: 1, // 当前页码
      total: 20, // 总条数
      pageSize: 4, // 每页的数据条数
      multipleSelection: [],
      multiple: false,
      searchData: "",
      showButton: false,
      showChange: '查看',
      listLoading: false
    }
  },
  //初始请求节点
  mounted() {
    this.getData()
  },
  methods: {
    getData() {
      //根据身份显示不同按钮文字
      this.listLoading = true
      if (this.$store.getters['user/identity'] == 'administrator') {
        this.showButton = true;
        this.showChange = '修改';
      }
      else if (this.$store.getters['user/identity'] == 'normal') {
        this.showButton = false;
        this.showChange = '查看';
      }
      this.$http.get('/ManageNode').then(
        (resp) => {
          console.log(resp);
          var arr = JSON.parse(resp.data.data);
          arr.forEach(item => {
            item.state = 'unknow';
            return item;
          })
          this.tableData = arr;
          console.log(this.tableData)
          this.listLoading = false
        }
      )
    },
    //点击操作按钮事件
    handleClick(row) {
      console.log(row);
      var modifyNode = {
        nodeId: row.node_id,
        nodeIp: row.node_ip,
        userId: row.user_id,
        gstoreUserId: row.gstore_user_id,
        gstoreUserPassword: row.gstore_user_password,
        port: row.port,
        version: row.version,
        apiType: row.apitype,
        rootPath: row.rootpath,
        identity: this.showChange,
        state: row.state
      }
      this.$router.push({ path: '/databaseManage/node/fixnode', query: modifyNode });
    },

    //当前页改变时触发 跳转其他页
    handleCurrentChange(val) {
      console.log(`当前页: ${val}`);
      this.currentPage = val;
    },
    //刷新时得到节点信息，请求
    getmessage() {
      this.getData();
    },
    //多选触发事件
    handleSelectionChange(val) {
      this.multipleSelection = val;
    },
    textRowClick(row) {
      console.log(row);
      let list = this.tableData
      this.$http.post('/CheckNodeOnline', JSON.stringify({ node_port: row.port, node_ip: row.node_ip })).then(
        (resp) => {
          console.log(resp);

          if (resp.data.data == 'success') {
            list.forEach(element => {
              if (element == row) {
                element.state = '1';
              }
              console.log(element)
              return element;

            });
          }
          else if (resp.data.data == 'failed') {
            list.forEach(element => {
              if (element == row) {
                element.state = '0';
              }
              console.log(element)
              return element;
            });
          }

        }
      ).catch(err => {
        list.forEach(element => {
          if (element == row) {
            element.state = '0';
          }
          console.log(element)
          return element;
        });
      })
      this.tableData = list.map(item => {
        return item
      })
    },
    //删除节点、在多选之后
    delete_box() {
      if (!this.multipleSelection.length) {
        this.$message({
          message: '请选择要删除的节点',
          type: 'warning'
        });
        return
      };
      var text = "";
      var params = [];
      this.multipleSelection.forEach((item) => {
        text = text + '节点' + item.node_id + ' ';
        params.push(item.node_id,);
      })
      //text得到节点名显示在弹窗
      this.$confirm("是否确认删除" + text, '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        var data = JSON.stringify({
          user_id: this.$store.getters['user/userName'],
          node_id: params
        });
        console.log(data);
        this.$http.post('/ManageNode',
          data).then((resp) => {
            var dataNode = resp.data;
            if (dataNode.message == 'success') {
              console.log(dataNode);
              this.multipleSelection.forEach((item) => {
                var newtableData = this.tableData;
                this.tableData = newtableData.filter((it) => { return it != item });
              })//返回新的数据库内容
            }
          })
        this.$message({
          type: 'success',
          message: '删除成功!'
        });
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除'
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
        console.log(this.searchData);
        console.log(item.node_id);
        console.log(item.node_ip);
        if (item.node_id == this.searchData || item.node_ip == this.searchData) {
          return item;
        }
      })
    },
    //跳转到新建节点
    skipNewNode() {
      this.$router.push('/databaseManage/node/newnode');
    }
  },
}
</script>

<style lang="less" >
.el-container {
  min-height: 70vh;
}

.text-id {
  font-size: large;
}

.message {

  width: 10px;
}

.item {
  margin: 4px;
}
</style>