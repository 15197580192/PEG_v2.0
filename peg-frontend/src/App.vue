<template>
  <div id="app">
    <!-- 路由占位符 -->
    <router-view></router-view>
  </div>
</template>

<script>
export default {
  name: 'app',
  created() {
    document.body.style.background = '#E9EDF0'
  },
}
</script >

<style lang="less"></style>
