# alolang关键字:anytype

* 用于函数的任意类型传入，传出
* 用于接收函数传出值的临时变量，在接收后，编译器会自动将其变为一个确定的类型，此时的用法等同于auto

### 使用
```
anytype<type1,type2,type3......>
```
当在传入列表时，表示传入函数的某一个参数类型为type1,type2,type3的一种。

当在传出列表时，返回值需要自己指定一个类型。

若指定的类型与实际传出类型不一致，则将传出的数据截取并复制到使用者指定的变量中，并不保证截取后数据的准确性。

例如

```
test(int a) -> anytype<int,double>
{
	if(a>0)
		return 1;
	else
		return 2.0;
}
int k1=test(1);
array(int,3) k2=test(1);
anytype k3=test(1);
anytype k4=test(-1);
array(int,2) k5=test(-1);
```

此时

```
k1为int类型，k1=1
k2为array类型,k2=2.0
k3被限制为int类型，k3=1
k4被限制为double类型,k4=2.0
此时有k5[0]为返回值的前四个字节，k5[1]为返回值的后四个字节，我们不保证这样的操作结果的准确性
```

