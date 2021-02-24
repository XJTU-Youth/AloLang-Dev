# alolang关键字:type

* 类型别名标识符

用于声明一个类型别名。通常用在<!-- 类/结构定义以及 -->泛型支持上。

示例

```
type foo = float;
type bar = float;
//foo和bar都是float的别名，foo和float类型的变量可以相互隐式类型转换，bar和float也可以
//但是foo和bar不能。foo类型变量和bar类型变量只能通过强制类型转换或者经由float进行转换

type numeric = anytype<int,double,complex>;
//numeric是一个可用于匹配int,double以及complex的泛型
```