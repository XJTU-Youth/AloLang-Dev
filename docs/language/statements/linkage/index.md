# 语言链接
用于资源的引用和导出。

使用方法：

```alolang
extern(optional"language")type identifier;
export identifier;
```

## 1.extern:用于c,cpp内容的链接

#### 链接规则：

1.在同一文件中具有相同名字和相同形参列表的两个函数，不能拥有两个不同的语言链接(形参的链接允许重载)。

2.一个外部语言变量不能与一个外部语言函数具有相同的名称。

3.当链接内容相互调用的时候，遵从cpp的链接规则

#### 注解：

一般仅用于系统底层的调用，不建议在正常的代码中使用

#### 例子:

```
extern("C") func puts(const char*)->int;
```

用于表示puts原型为C函数，编译器会将其封装为alolang函数，使其可以在alolang程序中被调用。

## 2.extern:用于alolang内容的链接

* 表明某个变量或者函数在其他地方定义并export

#### 例子：

```
extern("alolang") func add(int a,int b)->int;
```

## 3.export:用于alolang内容的导出

* 用于导出某个声明

#### 例子:

```
export func add(int a,int b)->int
{
	return a+b;
}
```

