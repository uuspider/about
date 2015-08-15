---
layout: post
title: UNIX / Linux guide
---
## UNIX / Linux 指引 

参考：[UNIX Tutorial for Beginners][ref1]{:target="_blank"}, [Introduction to Linux][ref2]{:target="_blank"}

[ref1]:http://www.ee.surrey.ac.uk/Teaching/Unix/
[ref2]:http://www.tldp.org/LDP/intro-linux/html/

* * *
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
*   [5. 重定向和管道](#inout)
    *   [5.1 重定向](#redirection)
    *   [5.2 输出重定向](#outredirection)
    *   [5.3 输入重定向](#inredirection)
    *   [5.4 管道](#pipes)
*   [6. 通配符](#wildcards)
*   [7. 联机手册](#manuals)
*   [8. 权限管理](#right)
    *   [8.1 查看文件权限](#longls)
    *   [8.2 更改文件权限](#chmod)
    *   [8.3 用户管理](#useradd)
*   [9. 进程管理](#process)
    *   [9.1 查看系统进程](#ps)
    *   [9.2 后台运行](#backrun)
    *   [9.3 查看后台进程](#checkjobs)
    *   [9.4 终止进程](#kill)
*   [10. 其他常用命令](#others)
    *   [10.1 磁盘操作](#disk)
    *   [10.2 打包和压缩](#tar)
    *   [10.3 文件搜索](#find)
    *   [10.4 网络](#web)
*   [11. 下一步该做什么？](#next)

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

**[[TOP](#top)]**

* * *

<h2 id="files">2. 文件和目录</h2>

<h3 id="ls">2.1 查看当前目录中的内容</h3>

输入

    $ ls
    
可以查看当前目录或文件夹中的内容，但是目录中的隐藏文件不会显示，要查看所有内容，需要给命令附加一个参数(“选项”)。

    $ ls -a

注意观察输出结果，可以发现隐藏文件或目录都以.开头。

**[[TOP](#top)]**

<h3 id="mkdir">2.2 建立目录</h3>

学习UNIX / linux这些字符命令，靠死记硬背“Linux 手册”是行不通的，我们要把它们当成工具，真正用起来。

因此，我们首先建立一个专门的目录start来练习这些命令：

    $ mkdir start
    
输入`ls`命令，看看是不是已经多出了一个start。

**[[TOP](#top)]**

<h3 id="cd">2.3 进入目录</h3>

输入

    $ cd start
    
就进入了start目录。

输入

    $ cd ..
    
回到了上级目录。

输入

    $ cd .
    
表示进入当前目录，这个操作看上去没啥用，其实是为了告诉大家：`.`表示当前目录。

ps：`cd`和`.`之间有一个空格。

输入

    $ cd ~

或

    $ cd

都会返回用户的home目录。

小结：linux中，`~`表示用户的home目录，`..`表示上级目录，`.`表示当前目录。

**[[TOP](#top)]**

<h3 id="pwd">2.4 查看当前所在目录及其路径</h3>

输入

    $ pwd

计算机会显示当前目录的完整路径。

**[[TOP](#top)]**

* * *

<h2 id="workonfiles">3. 文件操作</h2>

<h3 id="touch">3.1 创建文件</h3>

输入

    $ touch lilei.txt
    
用ls命令可以看到我们在当前目录下创建了一个名为lilei.txt的文件。

ps：`mkdir`创建空目录，`touch`创建空文件。

**[[TOP](#top)]**

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

**[[TOP](#top)]**

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

**[[TOP](#top)]**

<h3 id="rm">3.4 删除文件</h3>

输入

    $ rm lileicp.txt
    $ ls
    
lileicp.txt被删除。

**[[TOP](#top)]**

* * *

<h2 id="checkfiles">4. 查看文件内容</h2>

<h3 id="mkfile">4.1 准备一个非空文件</h3>

创建一个有内容的文件：

    $ ps aux | cat > hanmeimei.txt

先不要纠结这条命令干了什么，只要知道：我们创建了一个名为hanmeimei.txt的文件。

**[[TOP](#top)]**

<h3 id="cat">4.2 查看文件内容</h3>

    $ cat hanmeimei.txt
    
终端输出了一堆字符，这就是文件hanmeimei.txt中的内容。

ps：在当前目录中，输入`cat h`，然后敲Tab键，可以发现文件名自动补齐了。Tab补齐在输入长文件名时非常有用。

使用cat查看文件内容时，屏幕上只能显示最后一屏信息。

    $ less hanmeimei.txt

`less`可以分屏显示较长的信息，PgUP和PgDn上下翻页，q退出。

    $ head hanmeimei.txt
    $ head -2 hanmeimei.txt
    
`head`命令默认返回文件的前10行，该命令可附加选项"-数字"。

    $ tail hanmeimei.txt

`tail`和`head`命令类似。

**[[TOP](#top)]**

<h3 id="search">4.3 搜索文件内容</h3>

    $ less hanmeimei.txt

在`less`的显示界面中输入

    /root
    
可以看到所有的"root"字段都被高亮显示。

    $ grep root hanmeimei.txt
    
屏幕上只输出了含有"root"字段的行。`grep`有以下几个常用选项：

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

**[[TOP](#top)]**

* * *

<h2 id="inout">5. 重定向和管道</h2>

<h3 id="redirection">5.1 重定向</h3>

    $ cat
    
此时，输入任意字段后敲Enter键，可以看到，终端将显示刚输入的内容，直到按下`Ctrl + d` (下文简写为^D)退出。

**[[TOP](#top)]**

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
    
`cat`将两个文件合并成了一个文件。

**[[TOP](#top)]**

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

**[[TOP](#top)]**

<h3 id="pipes">5.4 管道</h3>

    $ ps aux
    
输入这条命令，屏幕将显示系统当前的进程信息。注意：该命令的选项aux前没有短横线“-”。

[上文](#mkfile)中我们曾经这样创建过一个文件：

    $ ps aux | cat > hanmeimei.txt
    
竖线前后是两个我们已经练习过的命令，中间的竖线称为管道符。管道符左侧命令的输出结果将直接传递给右侧的命令。

**[[TOP](#top)]**

* * *

<h2 id="wildcards">6. 通配符</h2>

    $ ls *.txt
    $ ls *list*
    $ ls *list?
    
`*`表示0～n个字符，`?`表示1个字符。

**[[TOP](#top)]**

* * *

<h2 id="manuals">7. 联机手册</h2>

    $ man ls
    $ whatis ls

这两条命令都显示命令的说明文件，`man`给出详细的说明，`whatis`给出的结果则非常简单。

如果记不住命令的确切拼写方法，可以进行模糊查询：

    $ apropos copy

**[[TOP](#top)]**

* * *

<h2 id="right">8. 权限管理</h2>

<h3 id="longls">8.1 查看文件权限</h3>

    $ ls -l
    
该命令给出的结果类似于：

|---|---|---|---|---|---|---|
|-rw-rw-r-- |1 |admin |usergp |41454  |July  7 12:30 |lilei.txt|
|权限属性|文件个数|所有者|所属组|文件大小|创建时间|文件名|

<br>
权限属性分为几段：

|---|---|---|---|
|-|rw-|rw-|r--|
|文件格式|所有者的权限|同组用户的权限|其它用户的权限|

<br>
对于文件格式，`-`表示普通文件，`d`表示目录，`l`表示链接。

对于文件权限，`r`表示可读，`w`表示可编辑，`x`表示可执行；对于目录权限，`r`表示可读取目录内容列表，`w`表示可更改目录下内容，`x`表示可进入该目录。

计算机使用9位二进制数存储文件权限信息，如：111 101 101 表示 rwx r-x r-x，换算成十进制就是755，110 100 100 表示 rw- r-- r--，换算成十进制就是644。

**[[TOP](#top)]**

<h3 id="chmod">8.2 更改文件权限</h3>

`chmod`用于更改文件的权限，有以下常用选项：

|:---:|:---|
|u|user|
|g|group|
|o|other|
|a|all|
|r|read|
|w|write (and delete)|
|x|execute (and access directory)|
|+|add permission|
|-|take away permission|

<br>

    $ chmod go-rwx alllist
    $ chmod a+rw alllist
    $ chmod 755 allist
    
大多数情况下，`chmod`命令要求有root用户权限。

**[[TOP](#top)]**

* * *

<h3 id="useradd">8.3 用户管理</h3>

创建一个新用户：

    $ useradd user1

linux为每位用户分配唯一的uid，可以使用`id`查看用户的uid：

    $ id user1

创建用户组users，指定其gid为900：

    $ groupadd -g 900 users

将用户user1加入到用户组users中。

    # gpasswd -a user1 users

将用户user1从用户组users中删除。

    # gpasswd -d user1 users

删除用户组users：

    # groupdel users

**[[TOP](#top)]**

* * *

<h2 id="process">9. 进程管理</h2>

<h3 id="ps">9.1 查看系统进程</h3>

    $ ps aux
    
我们已经知道这个命令可用来查看系统的进程信息。

**[[TOP](#top)]**

<h3 id="backrun">9.2 后台运行</h3>

    $ sleep 10
    $ sleep 10 &
    
末尾加&表示后台运行该命令。

    $ sleep 100
    ^Z
    $ bg
    
^Z可将正在运行的进程挂起，然后输入`bg`将其转入后台运行。

ps：图形界面的进程，不能转入后台。

**[[TOP](#top)]**

<h3 id="checkjobs">9.3 查看后台进程</h3>

    $ jobs
    
列出挂起或后台运行的进程。

    $ fg %1
    
将`jobs`列出的第1个进程转到前台。

**[[TOP](#top)]**

<h3 id="kill">9.4 终止进程</h3>

前台运行的进程，^C即可终止。

    $ sleep 100
    ^C
    
对于挂起或后台运行的进程，使用`kill`终止。

    $ sleep 100 &
    $ jobs
    $ kill %1
    
最常用的还是通过`kill PID_number`来终止进程。

    $ sleep 100 &
    $ ps aux | grep sleep
    
找到进程的PID为xxx。

    $ kill xxx
    
这样就终止了该进程，如果该进程仍未终止，可以使用`-9`选项强制终止，即

    $ kill -9 xxx
    
**[[TOP](#top)]**

* * *

<h2 id="others">10. 其他常用命令</h2>

<h3 id="disk">10.1 磁盘操作</h3>

    $ df -h .
    
查看文件系统的容量使用情况，包括正在运行的进程所占用的容量。

    $ du -sh
    
查看目录占用容量情况，是静态**文件**占用的容量。

    $ mount
    
查看系统中挂载的设备。

    $ mount -a
    
依据配置文件`/etc/fstab`自动挂载设备。

    $ mkdir /mnt/cdrom
    $ mount -t iso9660 /dev/cdrom /mnt/cdrom/
    
建立挂载点并挂载光驱。

    $ umount /mnt/cdrom
    
卸载光驱。

    $ fdisk -l
    
查看设备文件名，可用于挂载移动硬盘或u盘。对于`-t`选项，fat、fat16均为fat，fat32为vfat。

**[[TOP](#top)]**

<h3 id="tar">10.2 打包和压缩</h3>

    $ gzip files
    
得到压缩文件files.gz。注：`gzip`压缩后不保留原文件。

    $ gunzip files.gz
    
解压缩files.gz。注：`gzip`只能针对文件操作，对目录无效。如果要打包和压缩目录，可以使用用`tar`。

    $ tar -zcf dir.tar.gz dir
    $ tar -zxf dir.tar.gz
    
|:---|:---|
|-c|打包|
|-x|解包|
|-f|指定文件名|
|-z|压缩/解压缩|

<br>
**[[TOP](#top)]**

<h3 id="find">10.3 文件搜索</h3>

    $ find /etc -name init
    
在目录`/etc`中查找文件init，默认区分大小写；如不需要区分大小写，用`-iname`选项。

    $ find / -size +2048000
    
在根目录下查找大于100MB的文件，小于用`-n`，大于用`+n`，等于用`n`。

    $ find / -user admin
    
在根目录下查找所有者为admin的文件。根据所属组查找用`-group`选项。

    $ find /etc -cmin -5
    
在`/etc`下查找5分钟内被修改过属性的文件和目录。`-amin`代指访问时间，`-mmin`代指文件内容。

    $ find /etc -size +163840 -a -size -204800
    
在`/etc`下查找大于80MB小于100MB的文件。`-a`表示两个条件同时满足，`-o`表示满足其中任意一个条件即可。

    $ find /etc -name inittab -exec ls -l {} \;
    
在`/etc`下查找inittab文件并显示其详细信息，`-exec`表示对`find`命令的结果进行操作，类似的也可以用`-ok`；`{} \;`代指`find`命令的结果。

**[[TOP](#top)]**

<h3 id="web">10.4 网络</h3>

    $ ping 127.0.0.1
    
和windows的用法一样，用于测试本机和目标IP的网络连通情况。

    $ ifconfig
    
查看网卡状态信息，也可以临时配置网卡。

    $ traceroute www.google.com
    
显示数据包到目标地址间的路径。

    $ netstat
    
显示网络相关信息，常用有如下选项。

|:---|:---|
|-tlun|查看本机监听的端口|
|-an|查看本机所有的网络连接|
|-rn|查看本机路由表|

<br>
**[[TOP](#top)]**

* * *

<h2 id="next">11. 下一步该做什么？</h2>

到目前为止，你已经可以通过linux终端向计算机下达各种常用指令了，linux已经可以作为你的生产工具来产生效益了，因此，请牢记：**从现在开始，Linux只是你的一个工具，你应该“使用”它，而不再是“学习”它**。你一定还会遇见自己没有见过的、不明白的或不理解的命令，请使用搜索引擎吧。如果有一条命令你始终记不住，很有可能是因为它对你根本不重要，你没有必要牢记每一条命令，因为，你还有更重要的事情要在linux中完成。

[[grep, sed, awk & regular expressions][add01]{:target="_blank"}] , [[shell scripts][add02]{:target="_blank"}] , [[curl guide][add03]{:target="_blank"}] , [[wget, amule & transmission][add04]{:target="_blank"}] , [[openssl: encoding, digest & cipher][add05]{:target="_blank"}] , [[ASCII, GB2312, GBK, unicode & UTF-8][add06]{:target="_blank"}] , [[mySQL basic][add07]{:target="_blank"}]

[add01]:http://about.uuspider.com/2015/07/15/grep.html
[add02]:http://about.uuspider.com/2015/07/28/shell.html
[add03]:http://about.uuspider.com/2015/07/25/curl.html
[add04]:http://about.uuspider.com/2015/06/21/downloadtool.html
[add05]:http://about.uuspider.com/2015/08/07/sslinshell.html
[add06]:http://about.uuspider.com/2015/07/20/decode.html
[add07]:http://about.uuspider.com/2015/08/02/mysql.html

**[[TOP](#top)]**

***
