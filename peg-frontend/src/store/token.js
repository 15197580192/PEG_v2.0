const token = {
  namespaced: true,
  state: {
    // 存储token
    token: "",
  },

  getters: {
    getToken(state) {
      return state.token || localStorage.getItem("token") || "";
    }
  },

  mutations: {
    // 修改token，并将token存入localStorage
    setToken(state, token) {
      state.token = token;
      localStorage.setItem('token', token);
      console.log('store、localstorage保存token成功！');
    },
    delToken(state) {
      state.token = "";
      localStorage.removeItem("token");
    },
  },

  actions: {
    removeToken: (context) => {
      context.commit('delToken')
    },
    saveTokenInfo({ commit }, data) {
      commit("setToken", data)
    }
  },
};

export default token;
