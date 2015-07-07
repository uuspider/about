---
layout: default
title: UNIX / Linux beginner
---

## UNIX / Linux 指引 

参考：[UNIX Tutorial for Beginners][ref1], [Introduction to Linux][ref2], [UNIX Commands Guide][ref3]

[ref1]:http://www.ee.surrey.ac.uk/Teaching/Unix/
[ref2]:http://www.tldp.org/LDP/intro-linux/html/
[ref3]:http://cs.brown.edu/courses/bridge/1998/res/UnixGuide.html

<h2 id="top"></h2>

*   [1. 进入终端](#terminal)
*   [2. 文件和目录](#files)
    *   [2.1 查看当前目录中的内容](#ls)
    *   [2.2 建立目录](#mkdir)
    *   [2.3 进入目录](#cd)
    *   [2.4 查看当前所在目录及其路径](#pwd)
*   [3. 文件操作](#workonfiles)
    *   [3.1 创建文件](#touch)
    *   [3.2 复制文件](#cp)
    *   [3.3 移动文件](#mv)
    *   [3.4 删除文件](#rm)
*   [4. 查看文件内容](#workonfiles)
    *   [4.1 准备一个非空文件](#mkfile)
    *   [4.2 查看文件内容](#cat)
    *   [4.3 搜索文件内容](#search)


* * *
<h2 id="terminal">1. 进入终端</h2>

学习UNIX或Linux，是为了使用字符命令操控计算机，我们通过在终端输入字符下达指令，同时计算机也通过终端显示程序运行结果。终端是人机交互的窗口。

- 怎么进入终端？

如果开机进入了字符模式，就可以立即敲键盘输入命令了。

如果进入的是图形界面，通过“程序/终端”，“Applications/Terminal”或“Ctrl+Alt+t”可打开终端窗口，也可以通过“Ctrl+Alt+F1~6”进入字符终端。

当看到

    uuspider@localhost:~$
    
或

    root@localhost:~#
    
时，表示计算机已经在等待我们下达指令了。

ps：提示符可能是上面的$，#，也可能是%，&等等。

* * *

<h2 id="files">2. 文件和目录</h2>

<h3 id="ls">2.1 查看当前目录中的内容</h3>

输入

    $ ls
    
可以查看当前目录或文件夹中的内容，但是目录中的隐藏文件不会显示，要查看所有内容，需要给命令附加一个参数(“选项”)。

    $ ls -a

注意观察输出结果，可以发现隐藏文件或目录都以.开头。

<h3 id="mkdir">2.2 建立目录</h3>

学习UNIX / linux这些字符命令，靠死记硬背“Linux 手册”是行不通的，我们要把它们当成工具，真正用起来。

因此，我们首先建立一个专门的目录start来练习这些命令：

    $ mkdir start
    
输入ls命令，看看是不是已经多出了一个start。

<h3 id="cd">2.3 进入目录</h3>

输入

    $ cd start
    
就进入了start目录。

输入

    $ cd ..
    
回到了上级目录。

输入

    $ cd .
    
表示进入当前目录，这个操作看上去没啥用，其实是为了告诉大家：.表示当前目录。

ps：cd和.之间有一个空格。

输入

    $ cd ~

或

    $ cd

都会返回用户的home目录。

小结：linux中，~表示用户的home目录，..表示上级目录，.表示当前目录。

<h3 id="pwd">2.4 查看当前所在目录及其路径</h3>

输入

    $ pwd

计算机会显示当前目录的完整路径。

* * *

<h2 id="workonfiles">3. 文件操作</h2>

<h3 id="touch">3.1 创建文件</h3>

输入

    $ touch lilei.txt
    
用ls命令可以看到我们在当前目录下创建了一个名为lilei.txt的文件。

ps：mkdir创建空目录，touch创建空文件。

<h3 id="cp">3.2 复制文件</h3>

创建一个新目录dr1并进入该目录：

    $ mkdir dr1
    $ cd dr1
    
输入

    $ cp ../lilei.txt lileicp.txt
    
这样就将lilei.txt复制到dr1中并命名为lileicp.txt。

输入

    $ ls ..
    
可以看到上级目录中的文件lilei.txt仍然存在。

<h3 id="mv">3.3 移动文件</h3>

输入

    $ mv ../lilei.txt lileimv.txt
    $ ls ..
    $ ls
    
可以看到上级目录中的文件lilei.txt已经没有了，当前目录中则出现了名为lileimv.txt的文件。

输入

    $ mv lileimv.txt lilei.txt
    $ ls
    
可以看到，lileimv.txt被重命名为lilei.txt。

<h3 id="rm">3.4 删除文件</h3>

输入

    $ rm lileicp.txt
    $ ls
    
lileicp.txt被删除。

<h2 id="checkfiles">4. 查看文件内容</h2>

<h3 id="mkfile">4.1 准备一个非空文件</h3>

创建一个有内容的文件：

    $ ps aux | cat > hanmeimei.txt

先不要纠结这条命令干了什么，只要知道：我们创建了一个名为hanmeimei.txt的文件。

<h3 id="cat">4.2 查看文件内容</h3>

    $ cat hanmeimei.txt
    
终端输出了一堆字符，这就是文件hanmeimei.txt中的内容。

ps：在当前目录中，输入“cat h”，然后敲Tab键，可以发现文件名自动补齐了。Tab补齐在输入长文件名时非常有用。

使用cat查看文件内容时，屏幕上只能显示最后一屏信息。

    $ less hanmeimei.txt

less可以分屏显示较长的信息，PgUP和PgDn上下翻页，q退出。

    $ head hanmeimei.txt
    $ head -2 hanmeimei.txt
    
head命令默认返回文件的前10行，该命令可附加选项"-数字"。

    $ tail hanmeimei.txt

tail和head命令类似。

<h3 id="search">4.3 搜索文件内容</h3>

    $ less hanmeimei.txt

在less的显示界面中输入

    /root
    
可以看到所有的"root"字段都被高亮显示。

    $ grep root hanmeimei.txt
    
屏幕上只输出了含有"root"字段的行。grep有以下几个常用选项：

|:---|---|
|-v|显示不匹配的行|
|-n|显示行号|
|-c|显示匹配的总行数|
|-i|忽略大小写|


    $ grep -v 'a few words' hanmeimei.txt
    
显示不含"a few words"字段的行。

    $ wc -w hanmeimei.txt
    
显示文件的总单词数。

    $ wc -l hanmeimei.txt

显示文件的总行数。

<h2 id="inout">5. 重定向和管道</h2>

<h3 id="redirection">5.1 重定向</h3>

    $ cat
    
此时，输入任意字段后敲Enter键，可以看到，终端将显示刚输入的内容，直到按下Ctrl + d (下文简写为^D)退出。

<h3 id="outredirection">5.2 输出重定向</h3>

    $ cat > list1
    lilei
    hanmeimei
    lintao
    ^D
    $ cat list1
    
刚刚输入的字段就保存在list1中了。

    $ cat > list2
    Green
    Lily
    Mary
    ^D
    $ cat >>list1
    UncleWang
    ^D
    
我们现在有了两个文件list1和list2。

    $ cat list1 list2 > alllist
    $ cat alllist
    
cat将两个文件合并成了一个文件。
    
<h3 id="inredirection">5.3 输入重定向</h3>

    $ sort
    pig
    cat
    dog
    ^D
    
屏幕将按照字母顺序输出刚刚输入的字段。

    $ sort < alllist
    $ sort < alllist > newlist
    
文件中的内容经过重新排序，输出到新的文件中。
    
<h3 id="pipes">5.4 管道</h3>

    $ ps aux
    
输入这条命令，屏幕将显示系统当前的进程信息。注意：该命令的选项aux前没有短横线“-”。

[上文](#mkfile)中我们曾经这样创建过一个文件：

    $ ps aux | cat > hanmeimei.txt
    
竖线前后是两个我们已经练习过的命令，中间的竖线称为管道符。管道符左侧命令的输出结果将直接传递给右侧的命令。

<h2 id="wildcards">6. 通配符</h2>

    $ ls *.txt
    $ ls *list*
    $ ls *list?
    
*表示0～n个字符，?表示1个字符。

<h2 id="manuals">7. 联机手册</h2>

    $ man ls
    $ whatis ls

这两条命令都显示命令的说明文件，man给出详细的说明，whatis给出的结果则非常简单。

如果记不住命令的确切拼写方法，可以进行模糊查询：

    $ apropos copy

<h2 id="right">8. 权限管理</h2>



