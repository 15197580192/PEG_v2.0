<template>
  <div class="manage">
    <div class="Mheader">
      <div class="dbnum">
        数据库数量: {{ databaseCount }}
      </div>
      <div class="buttom_group" style="float:right;width:400px;display: inline-block;">
        <el-button @click="createDatabase" type="primary"><i class="el-icon-plus"></i>新建数据库</el-button>
        <el-button @click="loginVisible = true;" type="primary"><i class="el-icon-s-promotion"></i>链接其他数据库</el-button>
        <el-button @click="refresh" type="primary"><i class="el-icon-refresh"></i>刷新</el-button>
      </div>
    </div>

    <div class="content">
      <div class="form" v-show="formVisible">
        <el-card class="formcard" style="width: 100%; height:100%">
          <div slot="header" class="clearfix">
            <span style="font-size:18px">新建数据库</span>
            <el-button style="font-size:16px;float: right; padding: 3px 0" type="text" @click="closeform">关闭</el-button>
          </div>
          <div class="dbform" style="width: 65%; height:100%">
            <el-form ref="form" :model="form" :rules="rules" label-width="100px" label-position="left">
              <!-- 每一项表单域:el-form-item -->
              <el-form-item label="数据库名称" prop="name">
                <el-input placeholder="请输入数据库名" v-model="form.name"></el-input>
              </el-form-item>
              <el-form-item label="密码" prop="password">
                <el-input placeholder="请输入密码" v-model="form.password" type="password"></el-input>
              </el-form-item>

              <el-form-item label="导入NT文件">
                <!-- accept=".nt,.NT" 接受文件的类型 -->
                <el-upload class="upload-demo" ref="uploadNT" action="#" :multiple="false" :limit="1" :auto-upload="false"
                  accept=".nt,.NT,.txt" :on-remove="handleRemoveNT" :on-change="handleChangeNT"
                  :http-request="httpRequestNT" :file-list="ntFileList" :show-file-list="true">
                  <el-button slot="trigger" size="small" type="primary">上传文件</el-button>
                  <div slot="tip" class="el-upload__tip">注:上传的文件须是NT文件</div>
                </el-upload>
              </el-form-item>

              <el-form-item label="导入划分文件">
                <el-upload class="upload-demo" action="#" ref="uploadTXT" :multiple="false" :limit="1"
                  :auto-upload="false" accept=".txt" :on-remove="handleRemoveTXT" :on-change="handleChangeTXT"
                  :http-request="httpRequestTXT" :file-list="txtFileList" :show-file-list="true">
                  <el-button slot="trigger" size="small" type="primary">上传文件</el-button>
                  <div slot="tip" class="el-upload__tip">注:上传的文件须是txt文件</div>
                </el-upload>
              </el-form-item>
              <el-form-item label="划分数量" prop="divisionNumber">
                <el-input type="number" v-model="form.divisionNumber" :min="1" :max="this.nodeCount"
                  placeholder="请输入划分数量"></el-input>
              </el-form-item>
              <el-form-item label="分配节点">
                <el-button type="primary" size="small" @click="assignVisible = true; getNode()">选择节点</el-button>
                <el-dialog title="请选择要分配的节点" :visible.sync="assignVisible" width="50%" :before-close="closeDivision"
                  class="my-dialog">
                  <span>
                    <el-table ref="multipleTable" :data="tableData" border style="width: 100%; margin-top: 20px; "
                      @selection-change="handleSelectionChange">
                      <!-- @row-click="textRowClick" -->
                      <el-table-column type="selection" width="40" align="center" :selectable="selectable">
                      </el-table-column>
                      <el-table-column align="center" label="状态" width="63">
                        <template slot-scope="scope">
                          <span>{{ noticeStatus(scope.row.status) }}</span>
                        </template>
                      </el-table-column>
                      <el-table-column fixed prop="id" label="节点ID" width="70" align="center">
                      </el-table-column>
                      <el-table-column prop="ip" label="节点IP" width="125" align="center">
                      </el-table-column>
                      <el-table-column prop="port" label="gStore端口" width="100" align="center">
                      </el-table-column>
                      <el-table-column align="center" prop="version" label="gStore版本" width="100">
                      </el-table-column>
                      <el-table-column prop="rootpath" label="配置路径" width="250" align="center">
                      </el-table-column>
                      toggleRowSelection
                    </el-table>

                  </span>
                  <span slot="footer" class="dialog-footer">
                    <el-button @click="cancleDivision()">取 消</el-button>
                    <el-button type="primary" @click="handleDivision()">确 定</el-button>
                    <!-- 新增函数!!! choosenode -->
                  </span>
                </el-dialog>
                <div v-show="assignInfo">
                  当前已选择：
                  <span v-for="(item, index) in form.selectNode" :key="index" style="margin-left:5px;">节点{{ item.id
                  }}{{ '\u3000' }} </span>
                </div>
              </el-form-item>

              <el-form-item label="备注" prop="remarks">
                <el-input type="textarea" v-model="form.remarks" placeholder="请在此输入"></el-input>
              </el-form-item>
            </el-form>
            <div slot="footer" class="dialog-footer">
              <el-button @click="closeform" style="margin-right:30px">取 消</el-button>
              <el-button type="primary" @click="onSubmit();">确
                定</el-button>
            </div>
          </div>
        </el-card>
      </div>

      <div class="database" v-show="dbListVisible">
        <div v-if="this.databaseCount == 0" style="width:100%;height:100%;margin:auto">
          <el-empty :image-size="250" description="请开始创建属于你的数据库吧！"></el-empty>
        </div>
        <el-card class="dbcard" :body-style="{ display: 'flex', padding: 0 }"
          v-for="( item, index ) in      databaseList     " :key="index">
          <div slot="header" class="clearfix">
            <span style="font-size: 16px;color: #9C9B9C;">数据库信息</span>
            <el-button type="danger" style="float:right; margin-right: 5px; " size="mini"
              @click="isDeleted = true; handelDel(item)">删除</el-button>
          </div>
          <el-tooltip content="点击进入此数据库" placement="top">
            <div class="dbname" @click="rootVisible = true; handelDel(item)">{{ item.database_name }}</div>
          </el-tooltip>
          <div class="button" style="text-align: center;" @click="openInfo(item); handelDel(item), getdbInfo()">
            <el-button type="text" style="font-size: 12px;" icon="el-icon-caret-right" size="mini">查看详情
            </el-button>
          </div>

          <el-dialog title="删除数据库" :visible.sync="isDeleted" width="35%" :before-close="close_delDialog">
            <el-form class="dialog" :model="delform" ref="delform" label-width="80px" label-position="left">
              <el-form-item label="密码">
                <el-input type="password" v-model="delform.delpassword" placeholder="请输入" autocomplete="off"
                  maxlength="20"></el-input>
              </el-form-item>
            </el-form>
            <div slot="footer" class="dialog-footer" style="text-align: center">
              <el-button @click="close_delDialog" style="margin-right: 20px;">取 消</el-button>
              <el-button type="primary" @click="handleDelete()">确认删除</el-button>
            </div>
          </el-dialog>
        </el-card>

        <el-dialog title="链接其他数据库" :visible.sync="loginVisible" width="40%" :before-close="close_LoginDialog"
          :append-to-body="true">
          <el-form class="dialog" :model="loginData" :rules="rules2" ref="loginData" label-width="100px"
            label-position="left">
            <el-form-item label="数据库名称" prop="dbname">
              <el-input v-model="loginData.dbname" placeholder="请输入" autocomplete="off" maxlength="10"></el-input>
            </el-form-item>
            <el-form-item label="创建者ID" prop="creater_id">
              <el-input v-model="loginData.creater_id" placeholder="请输入" autocomplete="off" maxlength="10"></el-input>
            </el-form-item>
            <el-form-item label="用户名" prop="dbusername">
              <el-input v-model="loginData.dbusername" placeholder="请输入" autocomplete="off" maxlength="10"></el-input>
            </el-form-item>
            <el-form-item label="密码" prop="dbpassword">
              <el-input type="password" v-model="loginData.dbpassword" placeholder="请输入" autocomplete="off"
                maxlength="20"></el-input>
            </el-form-item>
          </el-form>
          <div slot="footer" class="dialog-footer" style="text-align: center">
            <el-button @click="close_LoginDialog" style="margin-right: 30px;">取 消</el-button>
            <el-button type="primary" @click="Others_Database()">确 定</el-button>
          </div>
        </el-dialog>

        <el-dialog title="登录数据库" :visible.sync="rootVisible" width="40%" :append-to-body="true"
          :before-close="close_rootDialog">
          <el-form class="dialog" :model="rootData" :rules="rules3" ref="rootData" label-width="100px"
            label-position="left">
            <el-form-item label="用户名" prop="dbuserid">
              <el-input v-model="rootData.dbuserid" placeholder="请输入用户名" autocomplete="off" maxlength="10"></el-input>
            </el-form-item>
            <el-form-item label="密码" prop="dbpassword">
              <el-input type="password" v-model="rootData.dbpassword" placeholder="请输入密码" autocomplete="off"
                maxlength="20"></el-input>
            </el-form-item>
          </el-form>
          <div slot="footer" class="dialog-footer" style="text-align: center">
            <el-button @click="close_rootDialog" style="margin-right: 30px;">取 消</el-button>
            <el-button type="primary" @click="Tomain()">确 定</el-button>
          </div>
        </el-dialog>

        <el-dialog :visible.sync="showVisible" width="65%" class="my-dialog-name" :before-close="close_Info"
          :append-to-body="true">
          <div class="showInformation">
            <div class="show_header" style="display:inline-block; height:40px;width:100%">
              <span
                style="margin-left: 10px;line-height: 40px;font-size: 20px;color: #111011;padding: 5px 10px;width: 60px;height: 100%;"
                @click="changeInfo" v-bind:class="{ node_style: nodeInfo, none_node: !nodeInfo }">拓扑图</span>
              <span
                style="line-height: 40px;font-size: 20px;color: #111011;  margin-left:15px;padding: 5px 10px; width: 60px;height: 100%;"
                @click="changeInfo()" v-bind:class="{ database_style: dataInfo }">节点信息</span>

            </div>

            <div class="show_content" style="margin-top: 10px; background-color: #9C9B9C; width: 100%;height:490px;">
              <div v-loading="echartVisible" v-show="nodeInfo" ref="graphchart"
                style="margin-top:5px;height: 100%; width:100%;">
              </div>
              <div class="nodeInfo" v-show="dataInfo">
                <div v-if="isEmpty" style="width:100%;height:100%;margin:auto">
                  <el-empty :image-size="250" description="暂无数据！"></el-empty>
                </div>
                <div class="noti" v-for="(item, index) in current_info" :key="index">
                  <div class="data_header" style="width:100%;height:30px;line-height: 30px">
                    <span style=" height:20px; width:200px;font-size: 18px;color: #9C9B9C; padding:0 10px">节点IP:{{
                      item.nodeip }}</span>
                    <span style=" height:20px; width:250px;font-size: 18px;color: #9C9B9C; margin:0 10px;">数据库：{{
                      item.data.database }}</span>

                    <span style=" height:20px; width:200px;font-size: 18px;color: #9C9B9C; padding:0 20px">创建者：{{
                      item.data.creator }}</span>
                    <span style=" height:20px; width:200px;font-size: 18px;color: #9C9B9C; padding:0 20px">创建时间：{{
                      item.data.builtTime }}</span>
                  </div>
                  <div class="data_info">
                    <div class="Info_card" style="display: inline-block;">
                      <img src="@/assets/Info_card.png" alt="">
                      <p>三元组数量</p>
                      <div class="num" style="text-align: center height:50px;margin: 8px;">
                        <span style="color:#409EFF;font-size:40px;"> {{ item.data.tripleNum }}</span>个
                      </div>
                    </div>
                    <div class="Info_card" style="display: inline-block;">
                      <img src="@/assets/Info_card.png" alt="">
                      <p>实体数量</p>
                      <div class="num" style="text-align: center height:50px;margin: 8px;">
                        <span style="color:#409EFF;font-size:40px;"> {{ item.data.entityNum }}</span>个
                      </div>
                    </div>
                    <div class="Info_card" style="display: inline-block;">
                      <img src="@/assets/Info_card.png" alt="">
                      <p>主语数量</p>
                      <div class="num" style="text-align: center height:50px;margin: 8px;">
                        <span style="color:#409EFF;font-size:40px;"> {{ item.data.subjectNum }}</span>个
                      </div>
                    </div>

                    <div class="Info_card" style="display: inline-block;">
                      <img src="@/assets/Info_card.png" alt="">
                      <p>谓语数量</p>
                      <div class="num" style="text-align: center height:50px;margin: 8px;">
                        <span style="color:#409EFF;font-size:40px;"> {{ item.data.predicateNum }}</span>个
                      </div>
                    </div>
                    <div class="Info_card" style="display: inline-block;">
                      <img src="@/assets/Info_card.png" alt="">
                      <p>字符数量</p>
                      <div class="num" style="text-align: center height:50px;margin: 8px;">
                        <span style="color:#409EFF;font-size:40px;">{{ item.data.literalNum }}</span>个
                      </div>
                    </div>
                    <div class="Info_card" style="display: inline-block;">
                      <img src="@/assets/Info_card.png" alt="">
                      <p>连接数量</p>
                      <div class="num" style="text-align: center height:50px;margin: 8px;">
                        <span style="color:#409EFF;font-size:40px;"> {{ item.data.connectionNum }}</span>个
                      </div>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </el-dialog>


      </div>

    </div>

  </div>
</template>


<script>
import * as echarts from 'echarts'

export default {
  name: 'Database',
  data() {
    return {
      fullscreenLoading: false,//整页加载
      dbListVisible: true, //显示数据库列表
      formVisible: false, // 表单是否打开
      assignVisible: false, //是否分配节点
      assignInfo: false,//选择的节点
      isDeleted: false, //是否删除

      // 表单绑定的数据
      form: {
        name: '',
        divisionNumber: '',
        password: '',
        remarks: '',
        ntFilename: '',
        txtFilename: '',
        selectNode: []//新增！！！
      },
      ntFile: null,
      ntFileList: [], //nt文件列表
      txtFile: null,
      txtFileList: [], //txt文件列表
      //删除绑定的表单
      delform: {
        delpassword: '',
      },
      rules: {
        name: [
          { required: true, message: '请输入数据库名称', trigger: 'blur' },
          { min: 2, max: 8, message: '长度在 2 到 8 个字符', trigger: 'blur' },
        ],
        password: [
          { required: true, message: '请输入密码', trigger: 'blur' },
          { min: 2, max: 8, message: '长度在 3 到 8 个字符', trigger: 'blur' },
        ],
        divisionnumber: [
          { required: true, message: '请输入划分数量（小于节点总数）', trigger: 'blur', },
          { min: 1, max: this.nodeCount, message: '数量小于节点数量', trigger: 'blur' },
        ],
      },

      databaseCount: 0, //数据库数量
      databaseList: [], // 存储数据库的数组
      tableData: [],//节点列表
      multipleSelection: [],//选择节点
      multiple: false,
      current_db: '', //选择的数据库名称
      current_info: [], //选择的数据库的详细信息
      loginVisible: false, //登录弹窗是否可见
      loginData: {
        dbname: '',   //数据库名称
        creater_id: '', //创建者id
        dbusername: '',  //用户名
        dbpassword: '', //用户密码
      },
      rules2: {
        dbname: [{ required: 'true', message: '数据库名称不能为空', trigger: 'blur' }],
        creater_id: [{ required: 'true', message: '请输入创建者ID', trigger: 'blur' }],
        dbusername: [{ required: 'true', message: '请输入用户名', trigger: 'blur' }],
        dbpassword: [{ required: 'true', message: '请输入密码', trigger: 'blur' }]
      },
      rootVisible: false,
      rootData: {
        dbuserid: '',
        dbpassword: '',
      },
      rules3: {
        dbuserid: [{ required: 'true', message: '请输入用户名', trigger: 'blur' }],
        dbpassword: [{ required: 'true', message: '请输入密码', trigger: 'blur' }]
      },
      showVisible: false, //显示详细信息
      isEmpty: false,
      nodeInfo: true,
      dataInfo: false,
      echartVisible: true,
      nodeList: [],  //节点
      nodeCount: '', //节点数量
      masterlist: [], //根节点
      system_user: '', //登录系统的用户
      option: '',

    }
  },
  created() {
    this.system_user = this.$store.getters['user/userName']
    this.getDatabaseList(); //页面一打开就显示数据库列表

  },
  methods: {
    // 获取数据库
    getDatabaseList() {
      this.$http.get('/GetDatabaseList').then(
        (resp) => {

          console.log("数组获取", resp.data);
          if (resp.data.data != "null") {
            const list = JSON.parse(resp.data.data);
            if (list !== null && list.length > 0) {
              this.databaseList = list.map(item => {
                return {
                  cuid: item.database_id.slice(0, 6),
                  ...item
                }
              })
              this.databaseCount = list.length
              console.log("databaseList", this.databaseList)
            }
          }
        }
      )
    },
    //新建按钮 初始化表单
    createDatabase() {
      this.formVisible = !this.formVisible
      this.dbListVisible = !this.dbListVisible
    },
    //刷新按钮
    refresh() {
      // 处理刷新按钮点击事件
      const loading = this.$loading({
        lock: true,
        text: '刷新成功！',
        spinner: 'el-icon-loading',
        background: 'rgba(0, 0, 0, 0.7)'
      });
      setTimeout(() => {
        this.system_user = this.$store.getters['user/userName']
        this.getDatabaseList(); //页面一打开就显示数据库列表
        loading.close()
      }, 500);
    },

    closeform() {
      // 先重置
      this.$refs.form.resetFields()
      this.ntFileList = []
      this.txtFileList = [] //清空数据
      this.formVisible = !this.formVisible
      this.dbListVisible = !this.dbListVisible
    },
    // 移除文件钩子
    handleRemoveNT(file, fileList) {
      console.log('移除', file, fileList)
      this.ntFileList = []
    },
    handleRemoveTXT(file, fileList) {
      console.log('移除', file, fileList)
      this.txtFileList = []
    },
    //上传文件
    handleChangeNT(file, fileList) {
      console.log(file, fileList)
      //判断上传文件格式
      var testmsg = file.name.substring(file.name.lastIndexOf('.') + 1)
      const extension1 = testmsg === 'nt'
      const extension2 = testmsg === 'txt'
      if (!extension1 && !extension2) {
        this.$message({
          message: '只能上传nt/NT文件',
          type: 'warning',
        })
      }

      //选择文件后，给fileList对象赋值
      this.ntFileList = [...this.ntFileList, file]

      //限制文件只能上传一个
      if (this.ntFileList.length > 0) {
        this.ntFileList = [this.ntFileList[this.ntFileList.length - 1]] // 获取最后一次选择的文件
      }
      this.ntFile = this.ntFileList[0];
      this.form.ntFilename = this.ntFile.name; //文件名
      console.log(this.form.ntFilename)

    },
    handleChangeTXT(file, fileList) {
      console.log(file, fileList)
      //判断上传文件格式
      var testmsg = file.name.substring(file.name.lastIndexOf('.') + 1)
      const extension1 = testmsg === 'txt'
      if (!extension1) {
        this.$message({
          message: '只能上传txt文件',
          type: 'warning',
        })
      }

      //选择文件后，给fileList对象赋值
      this.txtFileList = [...this.txtFileList, file]

      //限制文件只能上传一个
      if (this.txtFileList.length > 0) {
        this.txtFileList = [this.txtFileList[this.txtFileList.length - 1]] // 获取最后一次选择的文件
      }
      this.txtFile = this.txtFileList[0];
      this.form.txtFilename = this.txtFile.name; //文件名
      console.log(this.form.txtFilename)
    },
    //自定义上传方式 param是自带参数。 this.$refs.upload.submit() 会自动调用 httpRequest方法.在里面取得file
    httpRequestNT(param) {
      this.ntfile = param.file // 将form中的files字段赋值File对象
      this.form.ntFilename = param.file.name; //文件名
    },
    httpRequestTXT(param) {
      this.txtfile = param.file // 将form中的files字段赋值File对象
      this.form.txtFilename = param.file.name; //文件名
    },

    // 回调表格选择的数据 当选择项发生变化时会触发该事件
    handleSelectionChange(list) {
      if (list.length > this.form.divisionNumber) {
        this.limitFn(list);
        return;
      }
      console.log(list)
      this.form.selectNode = list;
      console.log(this.form.selectNode)
    },
    // 限制数量方法
    limitFn(list) {
      this.$message({
        message: '不能超过划分数量',
        type: 'danger',
      })
      this.$refs.multipleTable.clearSelection(); //用于多选表格，清空用户的选择
      for (let i = 0; i < this.form.divisionNumber; i++) {
        this.$refs.multipleTable.toggleRowSelection(list[i]); //用于多选表格，切换某一行的选中状态，如果使用了第二个参数，则是设置这一行选中与否（selected 为 true 则选中）
      }
    },
    cancleDivision() {
      this.assignVisible = false
      this.form.selectNode = []
      this.$message({
        type: 'info',
        message: '已取消分配！'
      })
    },
    handleDivision() {
      if (this.form.selectNode.length != this.form.divisionNumber) {
        this.$message({
          type: 'danger',
          message: '节点数量不足，请继续选择！'
        })
      } else {
        this.assignVisible = false
        this.$message({
          type: 'success',
          message: '成功分配节点！'
        })
        this.assignInfo = true
      }
    },
    closeDivision(done) {
      this.$confirm('确认关闭？')
        .then(() => {
          this.assignVisible = false
          this.form.selectNode = []
          done()
        })
        .catch(() => { })

    },
    //分配节点
    getNode() {
      this.$http.get('/IndexGetNode').then(
        (resp) => {
          console.log("所有节点-选择", resp.data);
          let arr = resp.data.data.data;
          this.tableData = arr
        }
      )
    },
    noticeStatus(val) {
      if (val == "t") {
        return "开启";
      } else {
        return "关闭";
      }
    },
    selectable(row, index) {
      if (row.status == "f") {
        return false         //禁用
      } else {
        return true          //可选
      }

    },

    // 表单提交
    onSubmit() {
      if (this.form.ntFilename == '' || this.form.ntFilename == null || this.form.txtFilename == '' || this.form.txtFilename == null) {
        this.$notify.error({
          title: '错误',
          message: '请上传正确的文件！',
        });
        return
      }
      if (this.form.divisionNumber == '') {
        this.$notify({
          title: '警告',
          message: '请填写完整信息！',
          type: 'warning',
          offset: 80
        });
        return
      }
      if (this.form.selectNode.length == 0) {
        this.$notify({
          title: '警告',
          message: '请选择分配节点！',
          type: 'warning',
          offset: 160
        });
        return
      }
      // 校验合法性
      this.$refs.form.validate((valid) => {
        if (valid) {
          // 处理表单提交逻辑
          console.log(JSON.stringify(this.form)) // 在控制台打印表单数据
          // 手动调用上传，这里会调用我们自己定义的上传函数
          this.$refs.uploadNT.submit()
          this.$refs.uploadTXT.submit()
          const formDate = new FormData()
          formDate.append('name', this.form.name)
          formDate.append('divisionNumber', this.form.divisionNumber)
          formDate.append('user_id', this.system_user)
          formDate.append('dbpass', this.form.password)
          formDate.append('remarks', this.form.remarks)
          formDate.append('nodeList', JSON.stringify(this.form.selectNode))
          formDate.append('ntFilename', this.form.ntFilename)
          formDate.append('txtFilename', this.form.txtFilename)
          formDate.append('ntcontent', this.ntFile.raw)
          formDate.append('txtcontent', this.txtFile.raw)
          const loading = this.$loading({
            lock: true,
            text: '正在创建中,请稍等...',
            spinner: 'el-icon-loading',
            background: 'rgba(0, 0, 0, 0.7)'
          });
          this.$http({
            url: '/DbCreate',
            method: 'POST',
            data: formDate,
            headers: {
              'Content-Type': 'multipart/form-data',
            }
          }).then(res => {

            console.log("res", res)
            if (res.data.data == "fail") {
              this.$message({
                message: '数据库名称重复！创建失败！！',
                type: 'info',
              })
              loading.close();
            } else {
              if (res.data.message == "create success") {
                //提交成功
                this.$message({
                  message: '创建成功！',
                  type: 'success',
                })
                this.closeform()
                loading.close();
                this.getDatabaseList();
              } else {
                this.$message({
                  message: '创建失败，请重新尝试！',
                  type: 'info',
                })
                loading.close();
              }
            }
          }).catch(function (error) {
            console.log('创建失败' + error)
          })

        }
      })

    },
    // 分配节点的------关闭新增表单
    closeDialog(done) {
      this.$confirm('确认关闭？')
        .then(() => {
          this.closeform()
          done()
        })
        .catch(() => { })
    },
    //获取数据库
    handelDel(item) {
      this.current_db = item;
    },
    //删除数据库
    handleDelete() {
      if (this.delform.delpassword == '' || this.delform.delpassword == null) {
        this.$message({
          message: '请填写完整信息！',
          type: 'warning'
        })
        return
      }
      this.$confirm('此操作将永久删除该数据库, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        // 删除操作:根据后端接口,参数是对象,id是唯一标识符
        var data = JSON.stringify({
          database_creater_id: this.system_user, //PEG用户名
          db_name: this.current_db.database_name, //数据库名
          database_password: this.delform.delpassword,  //数据库用户名
          dbuser_id: this.system_user, //PEG用户名
        })
        console.log("删除数据", data)
        this.$http.post('/Delete', data).then((resp) => {
          console.log("删除数据库", resp.data)
          if (resp.data.message == "success") {
            this.$message({
              message: '删除成功！',
              type: 'success'
            })
            this.delform.delpassword = ''
            this.isDeleted = false
            // 刷新重新获取
            this.getDatabaseList()
          } else {
            this.$message({
              type: 'info',
              message: '删除失败！'
            })
            this.isDeleted = false
          }
        }).catch(function (error) {
          console.log("提交失败", error)
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除！'
        })
      })
    },
    //关闭删除弹窗
    close_delDialog() {
      this.delform.delpassword = ''
      this.isDeleted = false
      // 点击取消:不删除了
      this.$message({
        type: 'info',
        message: '已取消删除'
      });
    },

    //关闭登录弹窗
    close_LoginDialog() {
      this.loginData.dbname = ''
      this.loginData.user_id = ''
      this.loginData.dbuserName = ''
      this.loginData.dbpassword = ''
      this.loginVisible = false
    },

    //链接他人的数据库并跳转
    Others_Database() {
      if (this.loginData.dbname == '' || this.loginData.creater_id == '' || this.loginData.dbusername == '' || this.loginData.dbpassword == '') {
        this.$message({
          message: '请填写完整信息！',
          type: 'warning'
        })
        return
      }
      let data = JSON.stringify({
        db_name: this.loginData.dbname,  //数据库名
        database_creater_id: this.loginData.creater_id, //创建者ID 
        dbuser_id: this.loginData.dbusername, //用户名
        dbuser_password: this.loginData.dbpassword //用户密码
      })
      console.log("链接信息", data)
      this.$http.post("/SqlLogin", data).then((resp) => {
        console.log("SqlLogin", resp)
        if (resp.data.state == "success") {
          const loading = this.$loading({
            lock: true,
            text: '正在进入数据库主页...',
            spinner: 'el-icon-loading',
            background: 'rgba(0, 0, 0, 0.7)'
          });
          setTimeout(() => {
            // 跳转到数据库主页
            this.$router.push({
              name: 'databaseinterface',
              query: {
                database_name: this.loginData.dbname,
                cuid: this.loginData.creater_id,
                dbuser_id: this.loginData.dbusername, //用户名
              }
            }) //跳转到数据库主页,传递数据库名称
            this.$message({
              message: '连接成功，已登录该数据库！',
              type: 'success'
            })
            loading.close();
          }, 1000);
        } else {
          this.$message({
            message: '该用户不存在或已被禁用',
            type: 'info'
          })
        }
      }).catch(function (error) {
        console.log("提交失败", error)
      });

    },

    close_rootDialog() {
      this.rootData.dbuserid = ''
      this.rootData.dbpassword = ''
      this.rootVisible = false
    },
    //进入数据库的主界面
    Tomain() {
      if (this.rootData.dbuserid == '' || this.rootData.dbpassword == '') {
        this.$message({
          message: '请填写完整信息！',
          type: 'warning'
        })
        return
      }
      let data = JSON.stringify({
        db_name: this.current_db.database_name,  //数据库名
        database_creater_id: this.current_db.cuid, //创建者ID 
        dbuser_id: this.rootData.dbuserid, //用户名
        dbuser_password: this.rootData.dbpassword //用户密码
      })

      console.log("登录信息", data)
      this.$http.post("/SqlLogin", data).then((resp) => {
        console.log("SqlLogin", resp)
        if (resp.data.state == "success") {
          this.rootVisible = false
          const loading = this.$loading({
            lock: true,
            text: '正在进入数据库主页...',
            spinner: 'el-icon-loading',
            background: 'rgba(0, 0, 0, 0.7)'
          });
          setTimeout(() => {
            // 跳转到数据库主页
            this.$router.push({
              name: 'databaseinterface',
              query: {
                database_name: this.current_db.database_name,
                cuid: this.current_db.cuid,
                dbuser_id: this.rootData.dbuserid, //用户名
              }
            }) //跳转到数据库主页,传递数据库名称
            this.$message({
              message: '登录成功！',
              type: 'success'
            })
            loading.close();
          }, 1000);
        } else if (resp.data.state == "node put off") {
          this.$message({
            message: '当前数据库节点服务器未开启，无法进入！',
            type: 'info'
          })
          setTimeout(() => {
            this.rootVisible = false
          }, 500);

        } else {
          this.$message({
            message: '用户信息错误或被禁用！！',
            type: 'info'
          })
        }
      }).catch(function (error) {
        console.log("提交失败", error)
      });
    },


    //切换信息界面
    changeInfo() {
      this.dataInfo = !this.dataInfo;
      this.nodeInfo = !this.nodeInfo
    },

    //打开详情信息
    openInfo(item) {
      this.showVisible = !this.showVisible
      console.log("当前数据库是", item.database_name)
      this.masterlist = [
        {
          nodeName: "数据库 " + item.database_name,
          database_id: item.database_id,
        }
      ]

      // setTimeout(() => {
      //   this.drawChart()
      // }, 1000)
      this.$nextTick(() => {
        this.drawChart()
      })

    },
    //关闭抽屉
    handleClose() {
      this.masterlist = [];
      this.showVisible = false;
    },
    drawChart() {
      var db_id = this.current_db.database_id
      this.$http.post('/GetDatabaseNodeId', { db_id: db_id }).then(
        (resp) => {
          console.log("数据库的节点信息", resp)
          this.nodeList = JSON.parse(resp.data.data),
            this.nodeCount = this.nodeList.length
          console.log("节点", this.nodeList)

          this.echartVisible = false;
          let nodes = []; //节点
          let links = []; //连线
          //服务器节点
          for (let i = 0; i < this.masterlist.length; i++) {
            let tempsize = (this.nodeCount - 1) / 2;
            let tempnode = {
              x: (1 + i) * tempsize,
              y: 5,
              name: this.masterlist[i].nodeName,

            }
            nodes.push(tempnode);
          }
          //其余节点
          for (let i = 0; i < this.nodeCount; i++) {
            var tempnode = {
              x: i,
              y: 1,
              name: this.nodeList[i].id,
              nodeIP: this.nodeList[i].ip,
              port: this.nodeList[i].port,
            };
            let templink;  //连线
            if (i > this.nodeCount) {
              templink = {
                source: this.masterlist[0].nodeName,
                target: this.nodeList[i].id,
                name: '关闭'
              };
            } else {
              templink = {
                source: this.masterlist[0].nodeName,
                target: this.nodeList[i].id,
                name: '开启'
              };
            }
            nodes.push(tempnode);
            links.push(templink);
          }

          let charts = {
            nodes: [],
            links: [],
            linesData: []
          }

          let dataMap = new Map();  //去重
          for (let j = 0; j < nodes.length; j++) {
            let x = parseInt(nodes[j].x)
            let y = parseInt(nodes[j].y)
            let node;
            if (j == 0) {
              node = {
                name: nodes[j].name,
                value: [x, y],
                symbolSize: 70, // 设置图片大小为
                symbol: 'image://' + require('./iamges/data.png'),
                itemStyle: {
                  normal: {
                    color: '#12b5d0',
                  }
                },
                label: { //标签
                  formatter: nodes[j].name
                }
              }
            } else {
              //节点信息
              node = {
                name: nodes[j].name, //节点名称
                nodeId: nodes[j].nodeIP, //节点ID
                port: nodes[j].port, //节点端口号
                value: [x, y],
                symbolSize: [50, 50], // 设置图片大小为 100x100
                symbol: 'image://' + require('./iamges/node.png'),
                itemStyle: {
                  normal: {
                    color: '#12b5d0',
                  }
                },
                label: { //标签
                  formatter: "节点" + nodes[j].name
                }
              }
            }
            dataMap.set(nodes[j].name, [x, y])
            charts.nodes.push(node)
          }

          for (let i = 0; i < links.length; i++) {
            let link;
            if (i > this.nodeCount) {
              link = {
                source: links[i].source,
                target: links[i].target,
                label: {
                  normal: {
                    show: false,
                    // formatter: links[i].name
                  }
                },

                lineStyle: {
                  normal: {
                    color: '#FF0000',
                    width: 2, // 线条宽度
                  }
                }
              }
            } else {
              link = {
                source: links[i].source,
                target: links[i].target,
                label: {
                  normal: {
                    show: false,
                    // formatter: links[i].name
                  }
                },

                lineStyle: {
                  normal: {
                    color: '#1DE9B6',
                    width: 3, // 线条宽度
                    opacity: 0.6, // 尾迹线条透明度
                  }
                }
              }
            }

            charts.links.push(link)
            // 组装动态移动的效果数据
            var lines = [{
              coord: dataMap.get(links[i].source)
            }, {
              coord: dataMap.get(links[i].target)
            }]
            charts.linesData.push(lines)
          }

          this.option = {
            grid: {
              left: '10%',   // 与容器左侧的距离
            },
            backgroundColor: "#1b2735",
            xAxis: {
              show: false,
              type: 'value'
            },
            yAxis: {
              show: false,
              type: 'value'
            },
            tooltip: { //弹窗
              //show: true,
              enterable: true,//鼠标是否可进入提示框浮层中
              formatter: formatterHover,//修改鼠标悬停显示的内容
            },
            series: [
              {
                type: 'graph',
                layout: 'none',
                coordinateSystem: 'cartesian2d',
                hoverAnimation: true,//是否开启鼠标悬停节点的显示动画
                symbolSize: 50,
                label: {
                  normal: {
                    show: true,
                    position: 'bottom',
                    color: '#00FFFF'
                  }
                },
                lineStyle: {
                  normal: {
                    width: 2,
                    shadowColor: 'none'
                  }
                },
                edgeSymbolSize: 8,
                data: charts.nodes,
                links: charts.links,
                itemStyle: {
                  normal: {
                    label: {
                      show: true,
                      formatter: function (item) {
                        return item.data.name
                      }
                    }
                  }
                }
              },
              {
                name: 'line-echart',
                type: 'lines',
                coordinateSystem: 'cartesian2d',
                effect: {
                  show: true,
                  trailLength: 0,
                  smooth: true,
                  symbol: 'arrow',
                  color: 'rgba(55,155,255,0.5)',
                  symbolSize: 10,
                },
                data: charts.linesData
              }
            ]
          };


          /**
         * 鼠标悬停时显示节点具体信息：节点名称、gStore 版本号
         */
          function formatterHover(params) {
            if (params.dataType == "node") {
              if (!params.data.name.includes("数据库")) {
                return '<span style="padding: 0 5px;font-size: 14px;">节点名称：' + params.data.name + '</span>' + '<br>'
                  + '<span style="padding-left:5px;height:30px;line-height:30px;display: inline-block;font-size: 14px;">节点ID：' + params.data.nodeId + '</span>' + '<br>'
                  + '<span style="padding-left:5px;height:30px;line-height:30px;display: inline-block;font-size: 14px;">端口：</span>' + params.data.port + '</span>';

              }
            }

          }
          let Myechart;
          setTimeout(() => {
            Myechart = echarts.init(this.$refs.graphchart)
            Myechart.clear();
            Myechart.setOption(this.option)
            //清空画布，防止缓存
          }, 500)

          // 为窗口加上宽度变化事件，当宽高发生改变时，调用echarts的resize()方法，调整图表尺寸
          window.addEventListener('resize', function () {
            Myechart.resize();
          })
        }
      )
    },
    close_Info() {
      this.nodeInfo = true;
      this.dataInfo = false;
      this.showVisible = false;
      this.nodeList = []
      this.current_info = []
      var Myechart = echarts.init(this.$refs.graphchart)
      Myechart.clear(this.option); //清空当前画布所有数据
      this.echartVisible = true

    },
    //数据库的详细信息
    getdbInfo() {
      var db_name = this.current_db.database_name
      var data = JSON.stringify({
        db_name: db_name,
        database_creater_id: this.current_db.cuid,
        dbuser_id: "root",
      })
      this.$http.post('/Monitor', data).then(
        (resp) => {
          console.log("monitor", resp.data)
          if (resp.data.data != null) {
            if (resp.data.message == "success") {
              var temp = resp.data.data
              temp.forEach((item) => {
                var tmp = {
                  nodeip: item.节点ip,
                  data: JSON.parse(item.信息.replace(/\n/g, ""))
                  // data: JSON.parse(item.信息.replace(/\n/g, ""))
                }
                this.current_info.push(tmp)
              })
              console.log("数据库的详细信息", this.current_info)
            } else {
              this.$message({
                message: '获取失败！暂无节点信息',
                type: 'info',
              })
              this.isEmpty = true;
            }
          } else {
            this.$message({
              message: '当前节点服务器未开启，无法获取信息',
              type: 'info',
            })
            this.isEmpty = true;
          }

        }
      ).catch(error => {
        console.log(error);
      })
    }
  }
}
</script>

<style lang="less">
.my-dialog-name {
  .el-dialog__header {
    padding: 0;
  }

  .el-dialog__body {
    padding: 0 10px;
    height: 540px
  }
}

.my-dialog {
  .el-dialog__header {
    padding-bottom: 0;
  }

  .el-dialog__body {
    padding: 0 10px;
  }
}
</style>

<style lang="less" scoped>
.Mheader {
  width: 100%;
  height: 50px;
  display: flex;
  align-items: center;
  justify-content: space-between;
  position: relative;

  .dbnum {
    // 垂直居中
    display: flex;
    align-items: center;
    width: 700px;
    height: 100%;
    line-height: 50px;
    font-size: 36px;
    color: #3476FF;
    font-weight: bold;
    padding: 0 10px;
  }

  .button_group {
    display: inline-block;
    width: 400px;
    height: 100%;
    right: 0;
    bottom: 0;
    position: absolute;
  }
}

.content {
  width: 100%;
  margin-top: 15px;
  position: relative;

  .form {
    display: flex;
    height: 100%;
    color: #303133;
    overflow: hidden;

    .dialog-footer {
      /* 父元素设置为浮动布局 */
      display: flex;
      /* 父元素下的子元素位于主轴上的位置为：center */
      justify-content: center;
      /* 父元素下的子元素位于交叉轴上的位置为：center */
      align-items: center;
    }
  }

  .database {
    width: 100%;
    box-sizing: border-box;
    display: flex;
    /* 自动换行属性 */
    flex-wrap: wrap;
    // 从头到尾均匀排列
    // justify-content: space-between;
    justify-content: flex-start; // 替代原先的space-between布局方式
    align-items: center;
    height: 100%;
    overflow: hidden;
  }

  .database::after {
    content: '';
    width: 23%;
  }

  .database .dbcard {
    width: 23%;
    height: 170px;
    margin-bottom: 20px;
    margin-right: 22px;
    position: relative;

    &:nth-child(4n + 4) {
      margin-right: 0;
    }

    ::v-deep .el-card__header {
      padding: 10px 6px !important;

      .el-button {
        margin-right: 5px !important;
        margin-top: -3px !important;
      }
    }

    ::v-deep .el-card__body {
      height: 120px;
    }

    .dbname {
      text-align: center;
      height: 80px;
      width: 100%;
      font-size: 32px;
      line-height: 80px;
      color: #020405;
    }

    .button {
      position: absolute;
      border: 1px solid #409EFF;
      width: 70%;
      height: 25px;
      bottom: 20px;
      right: 15%;
    }


  }

  .dialog {
    height: 100%;
    width: 90%;
  }

  .dbNodeInfo {
    position: absolute;
    bottom: 0px;
    z-index: 399 !important;
  }

}

.el-form {
  .el-form-item {

    /deep/ .el-form-item__content {
      .el-upload__tip {
        line-height: 10px;
        font-size: 10px;
      }
    }
  }
}

.showInformation {
  width: 100%;
  height: 540px;

  .node_style {
    border-bottom: 3px solid #4682FE;
  }

  .none_node {
    border: none
  }

  .database_style {
    border-bottom: 3px solid #4682FE;
  }

}


.nodeInfo {
  width: 100%;
  height: 490px;
  color: #fff;
  background-color: #1b2735;
  border-radius: 5px;
  overflow: auto;
}

.noti {
  height: 300px;
  width: 100%;
  margin-bottom: 20px;
}

.data_info {
  width: 100%;
  margin-left: 20px;
  margin-top: 8px;
  box-sizing: border-box;
}

.Info_card {
  width: 220px;
  height: 120px;
  border: 1px solid #ebeef5;
  border-radius: 10px;
  color: #303133;
  transition: .3s;
  background-color: #fff;
  box-shadow: 0 2px 12px 0 rgba(0, 0, 0, .1);
  text-align: center;
  margin-right: 50px;
  margin-bottom: 20px;

  img {
    width: 30px;
    height: 30px;
    border-radius: 50%;
  }

  p {
    font-size: 16px;
    color: #BFC3C5;
    margin-top: 0;
    margin-bottom: 5px;
  }

}

//滚动条的样式
::-webkit-scrollbar {
  //滚动条宽高
  width: 5px;
  height: 10px;
}

::-webkit-scrollbar-thumb {
  //滚动条颜色和圆角
  background-color: #dbd9d9;
  border-radius: 3px;
}
</style>




