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