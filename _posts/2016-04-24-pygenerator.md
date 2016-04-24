---
layout: post
title: Generator expressions
---
## python 推导式

参考：[List Comprehensions][ref1]{:target="_blank"}, [List 推导式][ref2]{:target="_blank"}, [Dict Comprehensions][ref3]{:target="_blank"}

[ref1]:https://www.python.org/dev/peps/pep-0202/
[ref2]:http://blog.chinaunix.net/uid-28631822-id-3488324.html
[ref3]:https://www.python.org/dev/peps/pep-0274/

<h2 id="top"></h2>

***

*   [列表推导式](#list)
*   [字典和集合推导式](#dict)

***

## 列表推导式 {#list}

列表推导式常用于创建新列表，其基本格式为：

    [ expr for var in collection if condition ]

如创建一个列表：

    >>> [ (x, y, x + y) for x in range(2) for y in range(3) ]
    [(0, 0, 0), (0, 1, 1), (0, 2, 2), (1, 0, 1), (1, 1, 2), (1, 2, 3)]

这个列表中每个元素为一个元组，元组中的每一个元素都由推导式给出。

    >>> [(x,y) for x in range(10) if x%2 if x>3 for y in range(10) if y>7 if y!=8]
    [(5, 9), (7, 9), (9, 9)]

这个推导式中包含两个for语句，每个for语句包含两个if语句，每个if语句属于离它最近的左边的for语句。

推导式还可以嵌套，如：

    >>> lis = [[3,4,5,6],[4,5,6,7],[6,7,8,9]]
    >>> [x for li in lis for x in li if x%2]
    [3, 5, 5, 7, 7, 9]

**[[TOP](#top)]**

***

## 字典和集合推导式 {#dict}

字典和集合推导式与列表推导式的格式相似，如：

    { key: value for (key, value) in collection if condition }
    { key: foo(key) for key in collection if condition }
    { expr for var in collection if condition }

注：字典和集合推导式需要python 2.7和python 3.1以上版本支持。

**[[TOP](#top)]**

***