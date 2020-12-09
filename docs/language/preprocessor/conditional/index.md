# 条件包含
预处理器支持有条件地编译源文件的某些部分。这一行为由 #if、#else、#elif、#ifdef、#ifndef 与 #endif 指令所控制。

## 语法
```
%ifdef 标识符
%ifndef 标识符
%endif
```
## 解释
条件预处理块由`%ifdef`或`%ifndef`指令开始，并以`%endif`指令结束。嵌套的条件预处理块会被单独处理。

`%ifdef` 和 `%ifndef` 指令所控制的代码块在第一个不属于内部嵌套的条件预处理块的 `%endif` 指令处结束。

`%ifdef` 和 `%ifndef` 指令测试其所指定的条件（见下文），如果条件求值为真，则编译其控制的代码块。否则，如果所指定的条件求值为假，则跳过其所控制的代码块。
## 条件的求值
`%ifdef`, `%ifndef`检查标识符是否被定义为宏名。

## 示例(TODO:待更改)

```
#define ABCD 2
#include <iostream>
 
int main()
{
 
#ifdef ABCD
    std::cout << "1: yes\n";
#else
    std::cout << "1: no\n";
#endif
 
#ifndef ABCD
    std::cout << "2: no1\n";
#elif ABCD == 2
    std::cout << "2: yes\n";
#else
    std::cout << "2: no2\n";
#endif
 
#if !defined(DCBA) && (ABCD < 2*4-3)
    std::cout << "3: yes\n";
#endif
}
输出：

1: yes
2: yes
3: yes
```