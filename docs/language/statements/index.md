# 控制语句

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

# TODO:待完善