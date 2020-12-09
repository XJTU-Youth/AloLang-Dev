# 预处理器
预处理的结果是单个文件，接下来它会被传递给实际编译器。

## 指令
预处理指令控制预处理器的行为。每个指令占据一行并拥有下列格式：
```
%预处理指令（import、def、rmdef、ifdef、ifndef、endif之一） 实参（取决于指令）
```
不允许空指令（即在 # 后直接换行）。

## 能力
预处理器有能力翻译源文件：

1.有条件地编译源文件的某些部分（由 `%ifdef`、`%ifndef`和 `%endif` 指令控制），参见[“条件编译”](language/preprocessor/conditional/index)。

2.替换文本宏，同时可能对标识符进行拼接或加引号（由 `%def` 和 `%rmdef` 指令与 % 运算符控制），参见[“宏定义”](language/preprocessor/replace/index)。

3.包含其他文件（由 `%import` 指令控制），参见[“包含”](language/preprocessor/import/index)。