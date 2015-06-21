---
layout: default
title: wget, amulecmd & transmission-remote
---

#1. wget 

- 下载文件

>wget [url]

- 下载时重命名

>wget默认会以最后一个符合”/”的后面的字符来命令，对于动态链接的下载通常文件名会不正确。

>wget http://url/download?id=1024 | #下载文件以名称download.php?id=1024保存

>wget -O aoi_sola.avi http://url/download.php?id=1024 | #下载文件以名称aoi_sola.avi保存

- 限速

>wget –limit-rate=300k [url]

- 断点续传

>wget -c [url]

- 后台下载

>wget -b [url]
>Continuing in background, pid 1024.
>Output will be written to `wget-log’.

>查看下载进度
>tail -f wget-log

- 下载多个文件

>保存一份下载链接文件

>cat > filelist.txt
>url1
>url2
>url3
>url4

>下载该文件中的链接
>wget -i filelist.txt

- FTP下载

>wget [ftp-url]

>如需用户名和密码认证
>wget –ftp-user=USERNAME –ftp-password=PASSWORD [ftp-url]

#2. amulecmd

- 下载文件

>add [ed2k]

- 显示所有下载进程

>show dl

- 对下载进程的操作

>暂停 | pause [hash \| id]
>重启 | resume [hash \| id]
>取消 | cancel [hash \| id]


#3. transmission-remote

- 下载文件

>transmission-remote -a [torrent | magnet]

- 查看下载进程信息

>transmission-remote -l

- 对下载进程的操作

>进程详情 | transmission-remote -t [all \| hash] -i
>停止 | transmission-remote -t [all \| hash] -s
>重启 | transmission-remote -t [all \| hash] -S
>取消 | transmission-remote -t [all \| hash] -r
>下载限速 | transmission-remote -t [all \| hash] -d [rate]
>取消下载限速 | transmission-remote -t [all \| hash] -D
>上传限速 | transmission-remote -t [all \| hash] -u [rate]
>取消上传限速 | transmission-remote -t [all \| hash] -U







