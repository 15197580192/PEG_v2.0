import Vue from "vue";
import App from "./App.vue";
import router from "./router";
import store from "./store/index";
import "./plugins/element.js";
import './permission'
// 导入全局样式表
import "./assets/css/global.css";
// 导入字体图标
import "./assets/fonts/iconfont.css";
import http from "@/utils/request";
import ElementUI from "element-ui";
import "element-ui/lib/theme-chalk/index.css";
import "./mock/index";
import axios from "axios";
// 隐藏 右侧浏览器 滚动条
import VueSmoothScroll from "vue2-smooth-scroll";
//富文本插件mavon-editor。
import mavonEditor from "mavon-editor";
import "mavon-editor/dist/css/index.css";
Vue.use(VueSmoothScroll);
Vue.use(ElementUI);
Vue.use(mavonEditor);

// 配置请求的跟路径
axios.defaults.baseURL = "/";
axios.interceptors.request.use((config) => {
  // console.log(config)
  config.headers.Authorization = window.localStorage.getItem("token");
  // 最后必须 return config，固定写法
  return config;
});
Vue.prototype.$http = http;
Vue.config.productionTip = false;

new Vue({
  render: (h) => h(App),
  router,
  store,
}).$mount("#app");
