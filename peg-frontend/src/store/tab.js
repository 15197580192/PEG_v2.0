export default {
  namespaced: true,
  state: {
    isCollapse: false, //导航栏是否折叠
    currentItem: null,
    tabList: [], //面包屑的数据:点了哪个路由,首页是一定有的
    otherList: [
      {
        path: "/databaseinterface/databaseinterface-query",
        name: "databaseinterface-query",
        lable: "查询",
        icon: "el-icon",
      },
    ],
  },
  getters: {
    TabList: (state) => {
      state.tabList = JSON.parse(localStorage.getItem("tabList")) || [];
      return state.tabList;
    },
  },
  //  mutations可以当作methods
  mutations: {
    //修改导航栏展开和收起的方法
    CollapseMenu(state) {
      state.isCollapse = !state.isCollapse;
    },
    // 更新面包屑的数据
    SelectMenu(state, item) {
      if (item.name !== "home" || item.name !== "AdminHome") {
        // 如果点击的不在面包屑数据中,则添加
        const index = state.tabList.findIndex((val) => val.name === item.name);
        if (index === -1) {
          state.tabList.push(item);
          localStorage.setItem("tabList", JSON.stringify(state.tabList));
        }
      }
    },
    // 更新数据库界面的面包屑数据
    SelectdatabaseMenu(state, item) {
      const index = state.otherList.findIndex((val) => val.name === item.name);
      if (index === -1) {
        state.otherList.push(item);
      }
    },
    // 删除tag:删除tabList中对应的item
    closeTag(state, item) {
      // 要删除的是state.tabList中的item
      const index = state.tabList.findIndex((val) => val.name === item.name);
      state.tabList.splice(index, 1);
      localStorage.setItem("tabList", JSON.stringify(state.tabList));
    },
    // 删除tag:删除otherList中对应的item
    closedatabaseTag(state, item) {
      // 要删除的是state.tabList中的item
      const index = state.otherList.findIndex((val) => val.name === item.name);
      state.otherList.splice(index, 1);
    },

    setTabList(state, item) {
      state.tabList = item;
      console.log("默认TabList", state.tabList);
      localStorage.setItem("tabList", JSON.stringify(state.tabList));
    },
  },
  actions: {
    setTabList({ commit, rootState }) {
      // commit("setTabList", data);

      if (rootState.user.identity === "administrator") {
        var tabList = [
          {
            path: "/Adminhome",
            name: "AdminHome",
            lable: "首页",
            icon: "el-icon-s-home",
            url: "home/AdminHome.vue",
          },
        ];

        commit("setTabList", tabList);
      }
      if (rootState.user.identity === "normal") {
        var tabLists = [
          {
            path: "/home",
            name: "home",
            lable: "首页",
            icon: "el-icon-s-home",
            url: "home/Home.vue",
          },
        ];
        commit("setTabList", tabLists);
      }
    },
    closeTag({ commit }, data) {
      commit("closeTag", data);
    },
    SelectMenu({ commit }, data) {
      commit("SelectMenu", data);
    },
  },
};
