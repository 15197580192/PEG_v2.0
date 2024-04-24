import axios from "axios";
// import store from "../store/user";

// 封装一个axios实例
const http = axios.create({
  // 通用请求的地址前缀
  baseURL: "http://localhost:18888/api",
  // 超时时间
  timeout: 200000,
});

// 请求拦截器
http.interceptors.request.use(
  function (config) {
    // 在发送请求之前做什么
    console.log(localStorage.getItem("token"));
    config.headers["Authorization"] = localStorage.getItem("token");
    return config;
  },

  function (error) {
    // 对请求错误做什么
    return Promise.reject(error);
  }
);

// 添加响应拦截器
http.interceptors.response.use(
  function (response) {
    // 对响应数据做什么
    return response;
  },
  function (error) {
    // 对响应错误做什么
    return Promise.reject(error);
  }
);

export default http;
