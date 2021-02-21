# 发行注意事项

AloLang编译器dev beta 0.0.1发行版

## 功能

- AloLang部分子集的编译
  - `int`和`bool`型变量
  - `if else`和`while`控制语句
  - 单变量返回值函数声明定义使用导入
  - 无返回值函数声明定义使用导入
- AloLang语言开发核心库（`libalolangcore.a`以及`libalolangcore.so`）
  - 用于测试的函数
    - `testPuts()` 用于输出内置调试信息
    - `testPrintInt(int i)` 用于输出一个整数
    - `testGetInt() -> int` 用于从命令行输入获取一个整数

## 编译以及安装

使用`autotools`工具链，同时也提供`configure`脚本

### 依赖

程序编译时依赖`flex`以及`llvm 11`。

动态编译的程序依赖`llvm 11`的动态库，静态编译的程序无需动态库

### 编译安装过程

```bash
[user@machine alolang]$ autoreconf #可选操作
[user@machine alolang]$ mkdir -p build #建议在build子文件夹进行编译操作
[user@machine alolang]$ cd build
[user@machine build]$ mkdir installdir #创建安装文件夹，为方便使用发行版的包管理器打包
[user@machine build]$ ../configure --prefix=$PWD/installdir #指定安装到的文件夹
[user@machine build]$ make -j #并行编译
[user@machine build]$ make install #安装到先前指定的文件夹
```

执行完后，`build`目录的结构应该是这样的

```
build
├── config.h
├── config.log
├── config.status
├── installdir
│   ├── bin
│   │   └── aloc
│   ├── lib
│   │   ├── libalolangcore.a
│   │   └── libalolangcore.so
│   └── share
│       └── doc
│           └── alolang-compiler
│               └── README.md
├── Makefile
├── src
│   ├── aloc
│   ├── aloc-aloc.o
│   ├── aloc-CompileUnit.o
│   ├── aloc-preprocessor.o
│   ├── aloc-Token.o
│   ├── aloc-utils.o
│   ├── ast
│   │   ├── aloc-AssignmentAST.o
│   │   ├── aloc-BaseAST.o
│   │   ├── aloc-BinaryExprAST.o
│   │   ├── aloc-BoolExprAST.o
│   │   ├── aloc-CallExprAST.o
│   │   ├── aloc-CodeBlockAST.o
│   │   ├── aloc-ExprAST.o
│   │   ├── aloc-ExternAST.o
│   │   ├── aloc-FunctionAST.o
│   │   ├── aloc-IfExprAST.o
│   │   ├── aloc-IntExprAST.o
│   │   ├── aloc-PrototypeAST.o
│   │   ├── aloc-TypeAST.o
│   │   ├── aloc-VariableDefExprAST.o
│   │   ├── aloc-VariableExprAST.o
│   │   └── aloc-WhileExprAST.o
│   ├── lib
│   │   ├── libalolangcore.a
│   │   ├── libalolangcore.so
│   │   ├── Makefile
│   │   └── testPuts.o
│   ├── Makefile
│   └── yacc_stuff
│       ├── aloc-tokenizer.o
│       └── tokenizer.cpp
└── stamp-h
```

在`installdir`目录下的就是编译得到的编译器以及核心库。建议使用发行版包管理工具的相关工具链进行打包安装等操作，当然您也可以手动将这些文件放入系统对应的路径（通常为`/usr/local/`下的对应文件夹）内。