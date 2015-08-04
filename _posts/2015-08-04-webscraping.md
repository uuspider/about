---
layout: post
title: Web scraping with shell / python
---
## 爬虫基础

参考：[Shell Scripts][ref1]{:target="_blank"},  [Advanced Bash-Scripting Guide][ref2]{:target="_blank"}, 

[ref1]:http://www.cnblogs.com/mr-wid/archive/2013/05/09/3068229.html
[ref2]:http://blog.csdn.net/ithomer/article/details/5134201

<h2 id="top"></h2>

***

*   [引言](#preface)
*   [变量](#var)
    *   [本地变量](#local)
    *   [环境变量](#env)
*   [条件判断](#test)
    *   [数值比较](#NumericComparison)
    *   [字符串比较](#StringComparison)
    *   [文件判断](#FileComparison)
    *   [布尔运算](#Boolean)
*   [流程控制](#statement)
    *   [if](#if)
    *   [case](#case)
    *   [for](#for)
    *   [until](#until)
    *   [while](#while)
    *   [break和continue](#break)
*   [特殊变量和位置参数](#othervar)
*   [数组](#array)
*   [函数](#function)
*   [脚本调试](#go)

***

## 引言 {#preface}

能够自动抓取网页，提取目标数据的程序就是爬虫。

**[[TOP](#top)]**

***

## virtualenv

virtualenv用于创建虚拟的Python环境，在虚拟环境中可以：

1. 在没有权限的情况下安装新套件

2. 根据不同的应用，使用不同的套件版本

3. 套件升级不影响其他应用

安装：

    $ sudo apt-get install python-virtualenv

创建虚拟环境：

    $ virtualenv SPI

创建一个名为SPI的虚拟环境。

启动虚拟环境：

    $ cd SPI
    $ source ./bin/activate

退出虚拟环境：

    (SPI)$ deactivate

安装套件：

    (SPI)$ pip install beautifulsoup4

## 抓取网页

首先，爬虫需要把网页抓取下来，python可以这样实现：

    >>> import urllib2
    >>> html = urllib2.urlopen("http://www.douban.com/group/haixiuzu/")
    >>> print(html.read())

从网页源码中提取我们的目标信息，可以使用beautifulsoup4套件。

## 解析网页

    >>> soup0 = BeautifulSoup(html)
    >>> print(soup0)
    >>> print(soup0.title)

关于BeautifulSoup详细用法，请看这里。

## 抓取和解析的异常处理

抓取网页可能发生的异常包括：

- 找不到目标网页

- 找不到服务器

对于“找不到网页”的情况，可以这样处理：

    try:
        html = urlopen("http://www.douban.com/group/haixiuzu/")
    except HTTPError as e:
        print(e)
    else:
        #program continues.
    
对于“找不到服务器”的情况，`urlopen`会返回`None`，可以这样处理：

    if html is None:
        print("URL is not found")
    else:
        #program continues.



