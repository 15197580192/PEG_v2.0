<template>
  <div class="Home" style="height: 100%;">
    <div style="display: inline-block; width:100%;height:100px">
      <div class="Box">
        <div class="Box-title">总数据库数</div>
        <div class="Box-number">{{ databaseCount }}</div>
        <img class="photo" src="@/assets/data.png" alt="">
      </div>

      <div class="Box" style="margin-left:40px">
        <div class="Box-title">总节点数</div>
        <div class="Box-number">{{ nodeCount }}</div>
        <img class="photo" src="@/assets/node.png" alt="">
      </div>
      <div class="Box" style="margin-left:40px">
        <div class="Box-title">用户人数 </div>
        <div class="Box-number">{{ usersCount }}</div>
        <img class="people" src="@/assets/people.png" alt="">
      </div>
    </div>
    <div class="echart" style="margin-top:40px;height:400px">
      <div class="echart-header"> gStore分布式集群网络拓扑结构图</div>
      <div class="echart-body" ref="graphchart" style="margin-top:5px;height: 100%; width:100%-30px; ">
      </div>
    </div>
  </div>
</template>

<script>
import * as echarts from 'echarts'

export default {
  data() {
    return {
      databaseCount: '',
      nodeCount: '',
      usersCount: '',
      nodeList: [],  //节点
      masterlist: [], //服务器
      system_user: '',
    }
  },
  created() {
    this.getDatabaseCount()
    this.getUserNumber()
  },
  mounted() {
    this.drawChart()

    if (this.$route.query.state == 'new') {
      this.$alert('新用户您好,您的id是' + this.$store.getters['user/userName'], '欢迎来到PEG系统', {
        confirmButtonText: '确定',
      });
    }
  },

  methods: {
    getDatabaseCount() {
      this.$http.get('/GetDatabaseNum').then((resp) => {
        console.log("数据库个数获取成功！", resp.data);
        this.databaseCount = resp.data.message
      }).catch(function (err) {
        console.log("数据库个数获取失败！", err);
      })
    },

    // // 画出拓扑图
    drawChart() {
      this.$http.get('/IndexGetNode').then(
        (resp) => {
          console.log("节点获取成功！", resp.data);
          let arr = resp.data.data.data
          this.nodeList = arr,
            this.nodeCount = arr.length;
          this.masterlist = [
            {
              nodeName: "PEG",
              systemusername: "root",
              user_id: "root",
            }
          ]
          console.log("this.List", this.nodeList)
          console.log("this.nodeCount", this.nodeCount)

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
          //其余节点
          for (let i = 0; i < this.nodeList.length; i++) {
            var tempnode = {
              x: i,
              y: 1,
              name: this.nodeList[i].id,
              nodeIP: this.nodeList[i].ip,
              port: this.nodeList[i].port,
              version: this.nodeList[i].version,
              rootPath: this.nodeList[i].rootpath,
              status: this.nodeList[i].status
            };
            var templink;  //连线
            if (tempnode.status == "f" || tempnode.status == '') {
              templink = {
                source: this.masterlist[0].nodeName,
                target: this.nodeList[i].id,
                name: '关闭'
              };
            }
            if (tempnode.status == "t") {
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
                symbolSize: 60, // 设置图片大小为
                symbol: 'image://' + require('./images/Server.png'),
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
                version: nodes[j].version,
                rootPath: nodes[j].rootPath,
                value: [x, y],
                symbolSize: [50, 50], // 设置图片大小为 100x100
                symbol: 'image://' + require('./images/computer.png'),
                itemStyle: {
                  normal: {
                    color: '#12b5d0',
                  }
                },
                label: { //标签
                  formatter: nodes[j].name
                }
              }
            }
            dataMap.set(nodes[j].name, [x, y])
            charts.nodes.push(node)
          }

          for (let i = 0; i < links.length; i++) {
            let link;
            if (links[i].name == "关闭") {
              link = {
                source: links[i].source,
                target: links[i].target,
                label: {
                  normal: {
                    show: true,
                    formatter: links[i].name
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
                    show: true,
                    formatter: links[i].name
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
          let option = {
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
              if (params.data.name != "PEG") {
                return '<span style="padding: 0 5px;font-size: 14px;">节点名称：' + params.data.name + '</span>' + '<br>'
                  + '<span style="padding-left:5px;height:30px;line-height:30px;display: inline-block;font-size: 14px;">节点ID：' + params.data.nodeId + '</span>' + '<br>'
                  + '<span style="padding-left:5px;height:30px;line-height:30px;display: inline-block;font-size: 14px;">端口：</span>' + params.data.port + '</span>' + '<br>' + '<span style="padding-left:5px;height:30px;line-height:30px;display: inline-block;font-size: 14px;">版本：</span>' + params.data.version + '</span>' + '<br>' + '<span style="padding-left:5px;height:30px;line-height:30px;display: inline-block;font-size: 14px;">路径：</span>' + params.data.rootPath + '</span>';

              }
            }

          }
          let Myechart = echarts.init(this.$refs.graphchart)
          Myechart.setOption(option)

          // 为窗口加上宽度变化事件，当宽高发生改变时，调用echarts的resize()方法，调整图表尺寸
          window.addEventListener('resize', function () {
            Myechart.resize();
          })

        }
      )
    },

    getUserNumber() {
      this.$http.get('/GetUserNum').then((resp) => {
        console.log("用户个数获取成功！", resp.data);
        this.usersCount = resp.data.message
      }).catch(function (err) {
        console.log("用户个数获取失败！", err);
      })
    }


  }

}

</script>

<style lang="less" scoped>
.echart-header {
  height: 35px;
  width: 100%-30px;
  line-height: 35px;
  border-left: 4px solid #4E71EB;
  padding: 0 10px;
  font-size: 18px;
  color: #333;
}

.Box {
  display: inline-block;
  border-radius: 4px;
  transition: .3s;
  box-shadow: 0 2px 12px 0 rgba(0, 0, 0, .1);
  width: 30%;
  height: 100px;
  border: 1px solid #fff;
  margin-bottom: 15px;
  flex: 1;
  position: relative;
  vertical-align: top;

  .Box-title {
    width: 100% -20px;
    height: 15px;
    line-height: 15px;
    color: #8f8f91;
    font-size: 16px;
    padding: 10px 0 5px 20px;
  }

  .Box-number {
    width: 100%-35px;
    line-height: 70px;
    color: #060606;
    font-size: 48px;
    font-weight: bold;
    height: 70px;
    padding: 0 0 0 35px;

  }

  .photo {
    width: 100px;
    height: 100px;
    position: absolute;
    right: 12px;
    bottom: -15px;
  }

  .people {
    width: 80px;
    height: 80px;
    border-radius: 10px;
    position: absolute;
    right: 12px;
    top: 10px;
  }
}
</style>