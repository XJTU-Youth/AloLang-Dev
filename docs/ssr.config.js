module.exports = {
    template: 'docs/ssr.html',
    maxAge: 60 * 60 * 1000,
    config: {
      basePath: 'http://127.0.0.1:4000/',
      auto2top: true,
      coverpage: true,
      executeScript: true,
      loadSidebar: true,
      loadNavbar: true,
      mergeNavbar: true,
      maxLevel: 4,
      subMaxLevel: 2,
      name: 'AloLang 语言参考文档',
      search: {
        noData: '没有结果!',
        paths: 'auto',
        placeholder: '搜索',
      }
    }
  }