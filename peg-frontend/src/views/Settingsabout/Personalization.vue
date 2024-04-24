<template>
  <el-card>
    <div slot="header" style="font-size: 20px; font-weight: 600">
      个性化设置
    </div>
    <div>
      <div style="width: 1300px; height: 450px" ref="chart" id="np666">
        <div class="drawer-container">
          <div class="setting-drawer-content">
            <div class="setting-drawer-title">
              <h3>导航栏主题设置</h3>
            </div>
            <el-color-picker v-model="color1" show-alpha :predefine="predefineColors1" @change="changeHeader">
            </el-color-picker>
          </div>

          <div class="setting-drawer-content">
            <div class="setting-drawer-title">
              <h3>菜单栏主题设置</h3>
            </div>
            <el-color-picker v-model="color2" show-alpha :predefine="predefineColors2" @change="changeAside">
            </el-color-picker>
          </div>

          <el-button size="meduim" type="primary" icon="el-icon-refresh" @click="resetSetting">重置</el-button>
        </div>
      </div>

    </div>
  </el-card>
</template>

<script>
export default {
  data() {
    return {
      color1: 'rgba(29, 59, 82, 1)',
      color2: 'rgba(48, 65, 86, 1)',
      predefineColors1: [
        '#1d3b52',
        '#22670C',
        '#123B05',
        '#16CD71',
        '#00ced1',
        '#1e90ff',
        '#c71585',
        'hsl(181, 100%, 37%)',
        'hsla(209, 100%, 56%, 0.73)',
      ],
      predefineColors2: [
        '#304156',
        '#1d3b52',
        '#22670C',
        '#123B05',
        '#16CD71',
        '#00ced1',
        '#1e90ff',
        '#c71585',
        'hsl(181, 100%, 37%)',
        'hsla(209, 100%, 56%, 0.73)',
      ]

    }
  },
  methods: {
    changeHeader(value) {
      window.localStorage.setItem("setHeaderColor", value)
      this.$store.commit('theme/setHeaderColor', value)
    },
    changeAside(value) {
      window.localStorage.setItem("setAsideColor", value)
      this.$store.commit('theme/setAsideColor', value)
    },
    resetSetting() {
      this.color1 = "#1d3b52"
      window.localStorage.setItem("setHeaderColor", "#1d3b52")
      this.$store.commit('theme/setHeaderColor', "#1d3b52")

      this.color2 = "#304156"
      window.localStorage.setItem("setAsideColor", '#304156')
      this.$store.commit('theme/setAsideColor', '#304156')
    }
  }
};
</script>



<style lang="less" scoped>
.setting-drawer-content {
  height: 90px;
  width: 50%;
  border-bottom: 1px solid #dbd7d7;
  margin-bottom: 15px;

  .setting-drawer-title {
    margin-bottom: 13px;
    color: rgba(48, 47, 47, 0.75);
    font-size: 14px;
    line-height: 22px;
    font-weight: bold;
  }

}


.drawer-container {
  padding: 10px;
  font-size: 14px;
  line-height: 1.5;
  word-wrap: break-word;
  height: 100%;

  .drawer-title {
    margin-bottom: 12px;
    color: rgba(0, 0, 0, .85);
    font-size: 14px;
    line-height: 22px;
  }

  .drawer-item {
    color: rgba(0, 0, 0, .65);
    font-size: 14px;
    padding: 12px 0;
  }
}
</style> 
