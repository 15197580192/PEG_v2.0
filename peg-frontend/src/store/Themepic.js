export default {
  namespaced: true,
  state: {
    asideColor: window.localStorage.getItem("setAsideColor")
      ? window.localStorage.getItem("setAsideColor")
      : "#304156",
    // headerColor: "#1d3b52",
    headerColor: window.localStorage.getItem("setHeaderColor")
      ? window.localStorage.getItem("setHeaderColor")
      : "#1d3b52",
  },
  //  mutations可以当作methods
  mutations: {
    //修改导航栏展开和收起的方法
    setAsideColor(state, item) {
      state.asideColor = item;
    },
    setHeaderColor(state, item) {
      state.headerColor = item;
    },
    delColor(state) {
      state.asideColor = "#304156";
      state.headerColor = "#1d3b52";
      localStorage.removeItem("setAsideColor");
      localStorage.removeItem("setHeaderColor");
    },
  },
  actions: {
    removeColor: (context) => {
      context.commit("delColor");
    },
  },
};
