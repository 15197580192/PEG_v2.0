import Vue from "vue";
import Vuex from "vuex";
// 导出的这个对象要在index.js中引入，因为它是其中一个模块(modules)
import tab from "./tab";
import user from "./user";
import theme from "./Themepic";
import token from "./token";
Vue.use(Vuex);

// 创建Vuex实例并导出
export default new Vuex.Store({
  modules: {
    tab,
    user,
    theme,
    token,
  },
});
