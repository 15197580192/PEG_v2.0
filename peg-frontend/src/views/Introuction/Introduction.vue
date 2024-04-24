<template>
  <div style="width:100%,height:100%">
    <div class="header" style="margin-bottom:20px;text-align:center">
      <h1 class="title">PEG快速上手指南</h1>
      <p>Welcome to the PEG Quick Start Guide! Follow the steps below to get started</p>
    </div>

    <!-- Step 1: 知识图谱与gStore介绍 -->
    <div class="step">
      <h2>Step 1: 知识图谱与gStore介绍</h2>
      <p style="text-indent:2em">
        近年来随着“人工智能”概念再度活跃，除了“深度学习”这个炙手可热的名词以外，“知识图谱”无疑也是研
        究者、工业界和投资人心目中的又一颗“银弹”。简单地说，“知识图谱”是一种数据模型，是以图形
        （Graph）的方式来展现“实体”、实体“属性”，以及实体之间的“关系”。下图是截取的Google的知识图谱
        介绍网页中的一个例子。在例子中有4个实体，分别是“达芬奇”，“意大利”，“蒙拉丽莎”和“米可朗基
        罗”。这个图明确地展示了“达芬奇”的逐个属性和属性值（例如名字、生日和逝世时间等），以及之间的
        关系（例如蒙拉丽莎是达芬奇的画作，达芬奇出生在意大利等）。
      </p>
      <p style="text-align:center">
        <img src="@/assets/image1.jpg" alt="Description of the image" />
      </p>
      <p style="text-indent:2em">
        目前知识图谱普遍采用了语义网框架中RDF(Resource Description Framework,资源模式框架)模型来表
        示数据。语义网是万维网之父蒂姆·伯纳斯-李在1998年提出的概念，其核心是构建以数据为中心的网络，即Web of Data。其中RDF是W3C的语义网框架中的数据描述的标准，通常称之为
        RDF三元组（"主体 (subject)，谓词 (predicate)，宾语(object)"）。其中主体一定是一个被描述的资源，由
        URI来表示。谓词可以表示主体的属性，或者表示主体和宾语之间某种关系；当表示属性时，宾语就是
        属性值，通常是一个字面值（literal）；否则宾语是另外一个由URI表示的资源。

        下图展示了一个人物类百科的RDF三元组的知识图谱数据集。例如y:Abraham_Lincoln表示一个实体
        URI（其中y表示前缀http://en.wikipedia.org/wiki/），其有三个属性
        (hasName,BornOdate,DiedOnDate)和一个关系（DiedIn）。
      </p>
      <p style="text-align:center">
        <img src="@/assets/image2.jpg" alt="Description of the image" />
      </p>
      <p style="text-indent:2em">
        面向RDF数据集，W3C提出了一种结构化查询语言SPARQL；它类似于面向关系数据库的查询语言
        SQL。和SQL一样，SPARQL也是一种描述性的结构化查询语言，即用户只需要按照SPARQL定义的语法
        规则去描述其想查询的信息即可，不需要明确指定如何进行查询的计算机的实现步骤。2008年1月，
        SPARQL成为W3C的正式标准。SPARQL中的WHERE子句定义了查询条件，其也是由三元组来表示。我
        们不过多的介绍语法细节，有兴趣的读者可以参考[1]。下面的例子解释了SPARQL语言。假设我们需要
        在上面的RDF数据中查询“在1809年2月12日出生，并且在1865年4月15日逝世的人的姓名？” 这个查询
        可以表示成如下的SPARQL语句。
      </p>
      <p style="text-align:center">
        <img src="@/assets/image3.jpg" alt="Description of the image" />
      </p>
      <p style="text-indent:2em">
        知识图谱数据管理的一个核心问题是如何有效地存储RDF数据集和快速回答SPARQL查询。总的来
        说，有两套完全不同的思路。其一是我们可以利用已有的成熟的数据库管理系统（例如关系数据库系
        统）来存储知识图谱数据，将面向RDF知识图谱的SPARQL查询转换为面向此类成熟数据库管理系统的
        查询，例如面向关系数据库的SQL查询，利用已有的关系数据库产品或者相关技术来回答查询。这里面
        最核心的研究问题是如何构建关系表来存储RDF知识图谱数据，并且使得转换的SQL查询语句查询性能
        更高；其二是直接开发面向RDF知识图谱数据的Native的知识图谱数据存储和查询系统（Native RDF图
        数据库系统），考虑到RDF知识图谱管理的特性，从数据库系统的底层进行优化
      </p>
      <p style="text-align:center">
        <img src="@/assets/image4.jpg" alt="Description of the image" />
      </p>
    </div>

    <!-- Step 2: 安装指南 -->
    <div class="step">
      <h2>Step 2: 安装系统要求</h2>

      <table>
        <thead>
          <tr>
            <th>项目</th>
            <th>需求</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="(item, index) in tableData" :key="index">
            <td>{{ item.column1 }}</td>
            <td>{{ item.column2 }}</td>
          </tr>
        </tbody>
      </table>
    </div>

    <!-- Step 3: Mount the Vue Instance
    <div class="step">
      <h2>Step 3: 快速上手</h2>
      <div>
      <pdf :src="pdfSrc" :page="1" @loaded="onLoad"></pdf>
      </div>
    </div> -->


  </div>
</template>

<script>

//import { pdf } from 'vue-pdf';

export default {
  // components: {
  //   pdf,
  // },

  data() {
    return {
      pdfSrc: '@/assets/gStore帮助手册-1.0版本(2).pdf',

      tableData: [
        { column1: '操作系统', column2: 'Linux, 例如CentOS, Ubuntu等' },
        { column1: '架构', column2: 'x86_64, AMD64' },
        { column1: '磁盘容量', column2: '根据数据集的大小' },
        { column1: '内存大小', column2: '根据数据集的大小' },
        { column1: 'glibc', column2: '必须安装 version >= 2.14' },
        { column1: 'gcc', column2: '必须安装 version >= 5.0' },
        { column1: 'g++', column2: '必须安装 version >= 5.0' },
        { column1: 'make', column2: '必须安装' },
        { column1: 'cmake', column2: '必须安装 version >= 3.0' },
        { column1: 'pkg-config', column2: '必须安装' },
        { column1: 'uuid', column2: '必须安装' },
        { column1: 'boost', column2: '必须安装 version >= 1.56 && <= 1.59' },
        { column1: 'readline', column2: '必须安装' },
        { column1: 'curl', column2: '必须安装' },
        { column1: 'openssl', column2: '必须安装 version >= 1.1' },
        { column1: 'openjdk', column2: '如果使用Java api，则需要 version = 1.8.x' },
        { column1: 'requests', column2: '如果使用Python http api，则需要' },
        { column1: 'node', column2: '如果使用Nodejs http api则需要 version >=10.9.0' },
        { column1: 'pthreads', column2: '如果使用php http api，则需要' },
        { column1: 'realpath', column2: '如果使用gconsole，则需要' },
        { column1: 'ccache', column2: '可选，用于加速编译' },

        // 添加更多数据...
      ],

      config: {
        el: '#app',
        data: {
          message: 'Hello, Vue!'
        }
      }
    };
  },
  methods: {
    onLoad() {
      console.log('PDF loaded');
    },
  }
};
</script>

<style scoped>
.step {
  margin-left: 50px;
  width: 90%;
  border: 1px solid #ddd;
  padding: 20px;
  border-radius: 5px;
  /* text-align: left; */
  /* 居中文本 */
  display: inline-block;
  /* 将容器设置为内联块元素 */
  font-size: 20px;
  /* 设置描述文字字体大小 */
  line-height: 1.75;
  /* 设置行高，控制文字行与行之间的间距 */
}

.title {
  font-size: 30px;
}

table {
  width: 80%;
  border-collapse: collapse;
  margin-top: 20px;
  margin: 0 auto;
}

th,
td {
  border: 1px solid #ddd;
  padding: 8px;
  text-align: left;
}

th {
  background-color: #f2f2f2;
}
</style>
