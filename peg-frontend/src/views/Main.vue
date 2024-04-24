<template>
  <el-container>
    <!-- width自适应,不然header与aside有间隔 -->
    <el-aside class="el-aside" :width="isCollapse ? '60px' : '200px'">
      <el-menu class="el-menu-vertical-demo" :collapse="isCollapse" v-cloak :collapse-transition="false"
        :unique-opened="true" :background-color="backgroundColor" text-color="#fff" active-text-color="#409BFF"
        :default-active="onRoutes" router ref="menu">
        <!-- 要放到导航栏里面 -->
        <h3>{{ isCollapse ? "PEG" : "图数据库管理系统PEG" }}</h3>
        <common-aside :MenuData="MenuData"></common-aside>
      </el-menu>
    </el-aside>
    <el-container class="content">
      <el-header>
        <common-header />
      </el-header>
      <common-tags />
      <el-main>
        <!-- 路由出口，匹配到组件渲染到这里 -->
        <router-view></router-view>
      </el-main>
    </el-container>
  </el-container>
</template>

<script>
import CommonAside from '@/components/CommonAside.vue';
import CommonHeader from '@/components/CommonHeader.vue';
import CommonTags from '@/components/CommonTags.vue';
// import MenuData from '@/data/MenuData'
import { mapState } from 'vuex'


export default {
  components: {
    CommonAside,
    CommonHeader,
    CommonTags,
  },
  data() {
    return {
    }
  },
  // mounted() {
  //   window.addEventListener('beforeunload', e => this.beforeunloadHandler(e))
  //   window.addEventListener('unload', e => this.unloadHandler(e))
  // },
  // destroyed() {
  //   window.removeEventListener('beforeunload', e => this.beforeunloadHandler(e))
  //   window.removeEventListener('unload', e => this.unloadHandler(e))
  // },
  // methods: {
  //   beforeunloadHandler() {
  //     this._beforeUnload_time = new Date().getTime();
  //   },
  //   unloadHandler(e) {
  //     this._gap_time = new Date().getTime() - this._beforeUnload_time;
  //     debugger
  //     this.$http.get('/LoginOut?user_id=' + this.$store.getters['user/userName'])
  //     //判断是窗口关闭还是刷新
  //     if (this._gap_time <= 5) {
  //       console.log('页面关闭')

  //     }
  //     else {
  //       console.log('页面刷新')
  //     }
  //   },
  // },
  computed: {
    // 要放到计算属性, 自动计算  是否折叠
    isCollapse() {
      return this.$store.state.tab.isCollapse;
    },
    ...mapState({
      backgroundColor: state => state.theme.asideColor
    }),
    onRoutes() {
      return this.$route.path;
    },
    MenuData() {
      return this.$store.getters['user/MenuData']
    }

  },
}
</script>

<style lang="less" scoped>
.el-menu-vertical-demo:not(.el-menu--collapse) {
  width: 200px;
  min-height: 400px
}

.el-menu {
  height: 100vh;
  border-right: none;

  h3 {
    color: #fff;
    text-align: center;
    line-height: 48px;
    font-size: 16px;
    font-weight: 360;
    margin-top: 0 !important;
    margin-bottom: 0 !important;
  }

}

.el-header {
  padding: 0;
}

.content {
  height: 100vh;
  width: 100%;
}

//滚动条的样式
::-webkit-scrollbar {
  //滚动条宽高
  width: 10px;
  height: 10px;
}

::-webkit-scrollbar-thumb {
  //滚动条颜色和圆角
  background-color: #dbd9d9;
  border-radius: 3px;
}
</style>

