# alolang关键字:goto
* goto语句:用于goto语句的声明

例子：

```AloLang
func main() -> int
{
    int a = 0;
    while (statements){
        if (statement)
            goto LAB1;
    }
LAB1:
    //After loop
}

```

建议仅用于跳出多层循环使用

!> 注意：使用goto语句跳过变量声明/初始化语句是未定义行为，可能会有危险后果
