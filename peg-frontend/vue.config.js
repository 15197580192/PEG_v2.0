const { defineConfig } = require("@vue/cli-service");
module.exports = defineConfig({
  transpileDependencies: true,
  lintOnSave: false, //关闭哦语法检查
  devServer: {
    host: "0.0.0.0",
    // https:true,
    port: 8080,
    client: {
      webSocketURL: "ws://0.0.0.0:8080/ws",
    },
    headers: {
      "Access-Control-Allow-Origin": "*",
    },
  },
  publicPath: "./", //修改目录
  outputDir: "dist", // build时构建文件的目录 构建时传入 --no-clean 可关闭该行为
  assetsDir: "assets", // build时放置生成的静态资源 (js、css、img、fonts) 的 (相对于 outputDir 的) 目录
  filenameHashing: true, // 默认在生成的静态资源文件名中包含hash以控制缓存
  runtimeCompiler: false, // 是否使用包含运行时编译器的 Vue 构建版本
  productionSourceMap: true, // 如果你不需要生产环境的 source map，可以将其设置为 false 以加速生产环境构建
});

// proxy: {
//       // 对象中键是本地请求地址,值是代理服务器配置对象
//       // 注意: vue/cli已经安装并配置了代理模块,可以直接用
//       "/dev-api": {
//         target: "http://ip:1888", // 要跨域的域名
//         //是否开启跨域
//         changeOrigin: true,
//         // 解决页面弹出红色报错遮罩层
//       },
//     },
