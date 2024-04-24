<template>
  <div>
    <template v-for="(item) in MenuData">
      <!-- 没有子级级菜单的 -->
      <el-menu-item @click="clickItem(item)" v-if="!item.children" :key="item.name" :index="item.path">
        <i :class="item.icon"></i>
        <span slot="title">{{ item.lable }}</span>
      </el-menu-item>

      <!-- 有次级菜单的,则展开子选项-->
      <el-submenu v-if="item.children && item.children.length > 0" :key="item.name" :index="item.path">
        <template slot="title">
          <i :class="item.icon"></i>
          <span slot="title">{{ item.lable }}</span>
        </template>
        <!-- 递归,实现无限级展开 -->
        <Common-aside :MenuData="item.children"></Common-aside>
      </el-submenu>

    </template>

  </div>
</template>

<script>

export default {
  name: "CommonAside",
  props: {
    MenuData: {
      type: Array,
      default() {
        return []
      }
    }
  },
  methods: {
    clickItem(item) {
      const user = this.$store.getters['user/identity']
      if (user == "normal") {
        if (this.$route.path !== item.path && !(this.$route.path === '/home' && item.path === '/')) {
          this.$router.push(item.path)
        }
        // 面包屑
        this.$store.dispatch('tab/SelectMenu', item)
      } else if (user == "administrator") {
        // 防止自己跳自己的报错
        if (
          this.$route.path !== item.path && !(this.$route.path === '/AdminHome' && item.path === '/')) {
          this.$router.push(item.path)
        }
        // 面包屑
        this.$store.dispatch('tab/SelectMenu', item)
      }

    },
  },
  computed: {
    // 要放到计算属性, 自动计算
    isCollapse() {
      return this.$store.state.tab.isCollapse;
    },
  },
}
</script>

<style lang="less" scoped>
.el-menu {
  el-menu-item {
    padding-left: 20px;
  }

  span {
    margin-left: 15px;
  }

}

/* 文字 */
::v-deep.el-submenu.is-active>.el-submenu__title {
  color: #409eff !important;
}

/* icon图标也跟着变 */
::v-deep .el-submenu.is-active>.el-submenu__title i {
  color: #409eff !important;
}
</style>



