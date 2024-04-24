import router from './router'
import store from './store'//删除token的方法在vuex中

//白名单：就是指不需要登录就可以直接进入的路由地址名单
const whiteList = ['/login', "/adminster/login", "/recover/password", "/Register", "/register/password"]

//to：进入到哪个路由去
//from：从哪个路由离开
//next：进入下一步
router.beforeEach(async (to, from, next) => {
  // console.log('to.meta:', to.meta);
  console.log(to.fullPath)
  if (to.meta) {
    document.title = to.meta.title;
    //以下判断和操作，大家根据实际的项目需求去做，这里做参考即可。
    try {
      // 获取token，判断用户是否登录
      const hasToken = store.getters['token/getToken'];
      console.log('hasToken:', hasToken)
      let userRole = localStorage.getItem('identity'); // 从本地存储获取用户角色
      // console.log(userRole)
      /* 如果有token*/
      if (hasToken && userRole != undefined) {
        if (userRole === 'administrator') {
          // 管理员角色，允许访问所有页面
          next();
        }
        else if (userRole === 'normal') {
          // 普通用户角色，只允许访问特定页面
          console.log(to.meta.requiresAuth)
          if (!to.meta.requiresAuth) {
            console.log(userRole)
            next(); // 允许访问需要权限的页面
          } else {
            next('/login'); // 重定向到未授权页面
          }
        }
      }

      /* 没有token*/
      else {
        // 如果没有登录且路由地址在白名单当中，则直接进入该路由地址
        if (whiteList.indexOf(to.path) !== -1) {
          next()
        }
        // 如果没有登录且路由地址不在白名单当中，则重定向到登录页去
        else {

          next(`/login`);

        }
      }
    }
    catch (error) {
      // // 删除token，然后跳转到登录页面重新登录。
      // await store.dispatch('user/resetToken');
      // Toast(error || 'Has Error');
      next(`/login`)
    }
  }
});
