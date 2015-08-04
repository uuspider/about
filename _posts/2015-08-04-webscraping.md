---
layout: post
title: Web scraping with shell / python
---
## 爬虫基础

参考：[Shell Scripts][ref1]{:target="_blank"},  [BeautifulSoup详解][ref2]{:target="_blank"}, 

[ref1]:
[ref2]:http://cuiqingcai.com/1319.html

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

本文假设读者已经具备了python的基础知识，对于python的语法、调试等都不会详细说明。

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
    >>> print html.read()

从网页源码中提取我们的目标信息，可以使用beautifulsoup4套件。

## 解析网页

    >>> soup = BeautifulSoup(html)
    >>> print soup
    >>> print soup.title
    >>> title = soup.find('title')
    >>> head = soup.contents[0].contents[0]

这里列出了三种解析tag的方式，第一种`soup.title`是最常用的，第二种`find`会在当前tag寻找符合条件的子tag，第三种的`contents`提供了一个子tag的列表。

    >>> html = body.parent

`parent`返回当前tag的父tag。

    >>> head = body.previousSibling

`previousSibling`返回与当前tag同级的前一个tag。

    >>> body = head.nextSibling

`nextSibling`返回与当前tag同级的后一个tag。

`find`会从当前节点开始，遍历整个子树，返回第一个符合项，`findall`则以列表形式返回所有符合项。

    >>> print soup.findAll('td')

类似的，还有`findParent`、 `findParents`、 `findNextSibling`、 `findNextSiblings`、 `findPreviousSibling`、 `findPreviousSiblings`。

    >>> find(name=None, attrs={}, recursive=True, text=None, **kwargs)

`find`可用于搜索tag、 attrs、 text等。

    find(tagname) 
    find(list)           # 如: find(['head', 'body'])
    find(dict)           # 如:find({'head':True, 'body':True})
    find(re.compile('')) # 使用正则, 如:find(re.compile('^a')) 搜索以a开头的tag
    find(lambda)         # 搜索函数返回结果为true的tag, 如:find(lambda name: if len(name) == 1) 搜索长度为1的tag
    find(True)           # 搜索所有tag
    find(id='xxx')        # 寻找id属性为xxx的
    find(attrs={id=re.compile('xxx'), algin='xxx'}) # 寻找id属性符合正则且algin属性为xxx的
    find(attrs={id=True, algin=None})         # 寻找有id属性但是没有algin属性的
    find(recursive=False)  #只搜索子tag，否则搜索整个子树，默认为True
    findAll("a", limit=3)   # 限制返回的符合项数量

关于BeautifulSoup详细用法，请看[这里](http://cuiqingcai.com/1319.html){:target="_blank"}。

## 抓取和解析的异常处理

抓取网页可能发生的异常包括：

- 找不到目标网页

- 找不到服务器

对于“找不到网页”的情况，可以这样处理：

    try:
        html = urlopen("http://www.douban.com/group/haixiuzu/")
    except HTTPError as e:
        print e
    else:
        #program continues.
    
对于“找不到服务器”的情况，`urlopen`会返回`None`，可以这样处理：

    if html is None:
        print "URL is not found"
    else:
        #program continues.

使用BeautifulSoup解析网页可能发生的异常可以这样处理：

    try:
        badContent = soup.notTag.otherTag
    except AttributeError as e:
        print "Tag was not found"
    else:
        if badContent == None:
            print "Tas was not found"
        else:
            print  badContent






























