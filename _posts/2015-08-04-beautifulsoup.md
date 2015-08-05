---
layout: post
title: Beautiful Soup
---
## Beautiful Soup

参考：[Beautiful Soup Doc][ref1]{:target="_blank"},  [Beautiful Soup][ref2]{:target="_blank"}

[ref1]:http://beautifulsoup.readthedocs.org/zh_CN/latest/
[ref2]:http://www.crummy.com/software/BeautifulSoup/

<h2 id="top"></h2>

***

*   [引言](#preface)
*   [虚拟python环境](#virtualenv)
*   [抓取网页](#scraping)
*   [解析网页](#parser)
*   [HTML标签](#html)
*   [层级标签](#multitag)
*   [find方法](#find)
*   [更多find方法](#findmore) [tagname](#tagname), [attrs](#attrs), [text](#text), [recursive和limit](#recursive)
*   [异常处理](#error)

***

## 引言 {#preface}

> Beautiful Soup 是一个可以从HTML或XML文件中提取数据的Python库.它能够通过你喜欢的转换器实现惯用的文档导航,查找,修改文档的方式.Beautiful Soup会帮你节省数小时甚至数天的工作时间.

本文假设读者已经具备了python的基础知识，因此我们从创建虚拟的python开发环境开始，简单回顾python抓取网页，重点介绍Beautiful Soup对网页的解析方法，这些说明不会面面俱到，也不会深入探讨优化方法。

**[[TOP](#top)]**

***

## python 虚拟环境 {#virtualenv}

virtualenv用于创建虚拟的python环境，在虚拟环境中可以：

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
    
**[[TOP](#top)]**

***

## 抓取网页 {#scraping}

python是这样抓取网页的：

    >>> import urllib2
    >>> html = urllib2.urlopen("http://www.douban.com/group/haixiuzu/")
    >>> print(html.read())

从网页源码中提取我们的目标信息，可以使用beautifulsoup4套件。

**[[TOP](#top)]**

***

## 解析网页 {#parser}

    >>> from bs4 import BeautifulSoup
    >>> soup = BeautifulSoup(html)
    >>> print(soup)
    
输入的`html`会被自动转换为unicode编码。

**[[TOP](#top)]**

***

## HTML标签 {#html}

HTML元素包括标签、标签内容、标签属性。

    #!/usr/bin/env python 
    # coding=utf-8
    # Python 2.7.3
    from bs4 import BeautifulSoup
    soup = BeautifulSoup('<td class="title"><a href="http://www.douban.com/group/topic/77911318/" title="别看世界了 看看我" class="">别看世界了 看看我</a></td>')
    tag = soup.td
    print(tag) # 整个标签
    print(tag.name) # 标签名称
    print(tag.text) # 标签内容
    print(tag['class']) # 属性

**[[TOP](#top)]**

***

## HTML标签的层级 {#multitag}

    #!/usr/bin/env python 
    # coding=utf-8
    # Python 2.7.3
    from bs4 import BeautifulSoup
    soup = BeautifulSoup('<tr class=""><td class="title"><a href="http://www.douban.com/group/topic/77911318/" title="别看世界了 看看我" class="">别看世界了 看看我</a></td><td nowrap="nowrap"><a href="http://www.douban.com/group/people/72348962/" class="">芝栀</a></td><td nowrap="nowrap" class="">1714</td><td nowrap="nowrap" class="time">08-05 19:47</td></tr>')
    maintag = soup.tr
    
    print(maintag.contents[0])
    print(maintag.contents[1])
    
    print(maintag.td)
    
    tagtd1 = maintag.td
    print(tagtd1.parent)
    print(tagtd1.a)
    print(tagtd1.a.parents)
    print(tagtd1.nextSibling)
    print(tagtd1.nextSibling.previousSibling)
    
这里给出了三种解析tag的方式，第一种的`contents`提供了一个子tag的列表，第二种`maintag.td`是最常用的，第三种使用了`parent`返回当前tag的上级tag，`previousSibling`返回与当前tag同级的前一个tag，`nextSibling`返回与当前tag同级的后一个tag。

**[[TOP](#top)]**

***

## find 方法 {#find}

`find`和`find_all`是常用的两种查找方法，前者返回第一个符合条件的tag，后者返回一个包含所有符合条件tag的列表。

    #!/usr/bin/env python 
    # coding=utf-8
    # Python 2.7.3
    import urllib2
    from bs4 import BeautifulSoup
    
    html = urllib2.urlopen("http://www.douban.com/group/haixiuzu/")
    soup = BeautifulSoup(html)
    
    print(soup.find('title'))
    print(soup.find_all('link'))
    
    taghtml = soup.html
    taghead = taghtml.head
    #下边是在同一级查找相关tag
    print(taghead.find_parents())
    print(taghead.find_next_sibling())
    print(taghead.find_previous_siblings())
    #下边是在整个HTML查找相关tag
    print(taghead.find_all_next())
    print(taghead.find_next())
    print(taghead.find_previous())

**[[TOP](#top)]**

***

## 更多 find 方法 {#findmore}

    find(name=None, attrs={}, recursive=True, text=None, **kwargs)

`find`除了可以直接根据层级关系查找tag，还可以通过name、 attrs、 text等查找tag。

### 搜索tagname {#tagname}

    find(tagname)  
    find(list)  # 如: find(['head', 'body'])
    find(dict)  # 如:find({'head':True, 'body':True})
    find(re.compile('')) # 使用正则, 如:find(re.compile('^a')) 搜索以a开头的tag
    find(lambda)  # 搜索函数返回结果为true的tag, 如:find(lambda name: if len(name) == 1) 搜索长度为1的tag
    find(True)  # 搜索所有tag

### 搜索attrs {#attrs}

    find(id='xxx')  # 寻找id属性为xxx的tag
    find(attrs={id=re.compile('xxx'), algin='xxx'})  # 寻找id属性符合正则且algin属性为xxx的tag
    find(attrs={id=True, algin=None})  # 寻找有id属性但是没有algin属性的tag
    
### 搜索text {#text}

方法与搜索tag一致。注意：搜索text时，其他搜索值如tagname、attrs等都失效。

### recursive 和 limit {#recursive}

    find(recursive=False)  #只搜索子tag，默认为True，即搜索整个子树
    findAll("a", limit=3)   # 限制返回的符合项数量

关于BeautifulSoup详细用法，请看[这里](http://beautifulsoup.readthedocs.org/zh_CN/latest/){:target="_blank"}。

**[[TOP](#top)]**

***

## 抓取和解析的异常处理 {#error}

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

**[[TOP](#top)]**

***