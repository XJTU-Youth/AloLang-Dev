# 特性表

## 代码块

支持`begin: ... end`并可以在begin后面紧跟代码块命名。例如：

``` alolang
begin xxx
    //do
    //something
end xxx
```

以及大括号方式。上方xxx作为说明符等同于注释，但要求配套的必须一致

## 控制语句

支持`while(): ... end while`、`for(): ... end for`等

``` alolang
while (i-->0):
    //do
    //something
end while
```

以及代码块

同时，应有for each的支持，如：

``` alolang
vector<int> items;
items.assign({1,2,3,4,5});
for each item in items:
    printf(item);
end for
```

支持goto控制语句，支持行标
