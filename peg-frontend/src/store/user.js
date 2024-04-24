const user = {
  namespaced: true,
  state: {
    user: "",
    password: "",
    identity: "",
    MenuData: [],
    //区别用户管理员 字符串normal和administrator
  },
  getters: {
    userName: (state) => {
      return state.user || localStorage.getItem("user") || "";
    },
    password: (state) => {
      return state.password || localStorage.getItem("password") || "";
    },
    identity: (state) => {
      return state.identity || localStorage.getItem("identity") || "";
    },
    MenuData: (state) => {
      state.MenuData = JSON.parse(localStorage.getItem("menu")) || [];
      return state.MenuData;
    },
  },
  mutations: {
    USER_INFO(state, info) {
      state.user = info;
      localStorage.setItem("user", info);
      console.log("成功");
    },
    PASSWD_INFO(state, info) {
      state.password = info;
      localStorage.setItem("password", info);
      console.log("成功");
    },
    IDENTITY_INFO(state, info) {
      state.identity = info;
      localStorage.setItem("identity", info);
      console.log("成功");
    },
    delUserInfo(state) {
      state.token = "";
      localStorage.removeItem("user");
      localStorage.removeItem("password");
      localStorage.removeItem("identity");
    },
    setMenu(state, menu) {
      console.log("设置菜单");
      state.MenuData = menu;
      localStorage.setItem("menu", JSON.stringify(menu));
    },
  },
  actions: {
    saveUserInfo({ commit }, data) {
      commit("USER_INFO", data.username),
        commit("PASSWD_INFO", data.password),
        commit("IDENTITY_INFO", data.identity);
    },
    removeUserInfo: (context) => {
      context.commit("delUserInfo");
    },
    setMenu({ commit }, menu) {
      commit("setMenu", menu);
    },
  },
};
export default user;
