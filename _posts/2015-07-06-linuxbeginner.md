---
layout: default
title: UNIX / Linux beginner
---

## UNIX / Linux 指引 

参考：[UNIX Tutorial for Beginners][ref1], [Introduction to Linux][ref2]

[][ref3]

[ref1]:http://www.ee.surrey.ac.uk/Teaching/Unix/
[ref2]:http://www.tldp.org/LDP/intro-linux/html/
[ref3]:

<h2 id="top"></h2>

*   [1. 进入终端](#terminal)
*   [2. 文件和目录](#files)
    *   [2.1 查看当前目录中的内容](#ls)
    *   [2.2 建立目录](#mkdir)
    *   [2.3 进入目录](#cd)
    *   [2.4 查看当前所在目录及其路径](#pwd)
*   [3. 文件操作](#workonfiles)


* * *
<h2 id="terminal">1. 进入终端</h2>

学习UNIX或Linux，是为了使用字符命令操控计算机，我们通过在终端输入字符下达指令，同时计算机也通过终端显示程序运行结果。终端是人机交互的窗口。

- 怎么进入终端？

如果开机就进入了字符模式，就可以直接通过键盘输入命令了。

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

<h2 id="workonfiles">3.1 文件操作</h2>

输入

    $ cp











