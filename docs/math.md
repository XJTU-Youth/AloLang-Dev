# math库文档

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

## 二.内部函数

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

