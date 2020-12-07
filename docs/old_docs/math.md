﻿# math库文档

## 一.math库概述

### 1 如何引用math库

```alolang
%import math
```

### 2 介绍

math库中定义了以下常量(括号内为引用的名称)

$\pi(\text{PI}),e(\text{\_E}),\lg2,\lg3,\lg5(\text{LG2,LG3,LG5}),\sqrt 2,\sqrt 3,\sqrt 5(\text{SQRT2,SQRT3,SQRT5}),\ln 2,\ln3,\ln10(\text{LN2,LN3,LN10})$

包含了C++中的数学计算，同时支持高精度类型(高精度开高精度次根暂时不支持，以后可能也不会支持)

包含了虚数，四元数的有关计算，和一部分数论有关的算法

### 3.备注

某些用法源自C++库，有些虽然和C++的函数名称相同，但是作用，时间复杂度却不同

## 2新数据类型

虚数: complex



## 三.内部函数

1.判断质数 

调用:isprime(long a)

若a为质数，返回true，否则返回false

2.快速幂

调用:q_pow(long a,long n,long mod)

作用:返回$a^n \%mod$

3.最大公约数

调用 gcd(long a,long b)

作用：返回a,b的最大公约数

4.最小公倍数

调用:lcm(long a,long b)

作用:返回a,b的最小公倍数

5.绝对值

调用

abs(long a)

dabs(double a)

作用:返回a的绝对值

6.四舍五入

调用:round(double a)

作用:四舍五入

7.是否整数

调用beint(double a)

作用,若double a是一个整数，返回true，否则返回false

p.s为啥函数名称不用 isint？是为了避免和sin联系到一起

8.向下取整

调用:floor(double a)

作用:返回不大于a的最大整数

9.向上取整

调用:ceil(double a)

作用:返回不小于a的最小整数

10.整数乘方

调用:lpow(long a,long b)

作用:返回$a^b$ 类型为long

备注:a请不要传入浮点数，精度损失会很严重

11.浮点数乘方

调用:dpow(double a,double b)

作用，返回$a^b$ 类型为double

备注:请不要超过double的精度范围！！！

12.开根号

调用:lsqrt( long a)

作用:返回$\sqrt a$ 保留整数，类型为long

调用:sqrt(double a)

作用:返回$\sqrt a$为double类型

备注:请不要传入一个小于0的数，会返回NaN,若对负数开根，请不要用这个函数

13.角度制和弧度制相互转换

调用:deg(double a) 弧度->角度

​        rad(double a)角度->弧度
14.一系列对数
调用:ln(double x)
作用:返回x的自然对数
lg(double x)
作用:返回x以10为底的对数
log(double a,double x)
作用:返回x以a为底的对数
备注：当x<0时，请不要用这个函数
15.e的乘方
exp(double x)
作用:返回$e^x$为double类型

###三角函数部分
1.弧度系列
sin(double radians)
cos(double radians)
tan(double radians)
cot(double radians)
sec(double radians)
csc(double radians)
sinh(double radians)
cosh(double radians)
tanh(double radians)
coth(double radians)
sech(double radians)
csch(double radians)
作用:传入一个角的弧度，返回它的某三角函数或者双曲函数值
2.角度系列
dsin(double degrees)
dcos(double degrees)
dtan(double degrees)
dcot(double degrees)
dsec(double degrees)
dcsc(double degrees)
dsinh(double degrees)
dcosh(double degrees)
dtanh(double degrees)
dcoth(double degrees)
dsech(double degrees)
dcsch(double degrees)
作用:传入一个角的角度，返回它的某三角函数或者双曲函数值
