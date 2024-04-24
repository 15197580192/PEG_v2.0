module.exports = {
  presets: [
    '@vue/cli-plugin-babel/preset',
    ["@babel/preset-env", { "modules": false }]
  ],
  "plugins": [
    "transform-remove-console",
    [
      "component",
      {
        "libraryName": "element-ui",
        "styleLibraryName": "theme-chalk",

      }
    ]
  ]
}