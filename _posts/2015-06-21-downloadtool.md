---
layout: post
title: wget, amulecmd & transmission-remote
---

## wget 

- 下载文件

```wget [url]```

- 下载时重命名

```wget -O aoi_sola.avi http://url/download.php?id=1024```

- 限速

```wget –limit-rate=300k [url]```

- 断点续传

```wget -c [url]```

- 后台下载

```wget -b [url]```

>查看下载进度

    tail -f wget-log

- 下载多个文件

>保存一份下载链接文件

    cat > filelist.txt 
    url1
    url2
    url3
    url4

>下载该文件中的链接

    wget -i filelist.txt

- FTP下载

    wget [ftp-url]

>如需用户名和密码认证

    wget –ftp-user=USERNAME –ftp-password=PASSWORD [ftp-url]

## transmission-remote

- 下载文件

    transmission-remote -a [torrent \| magnet]

- 查看下载进程信息

    transmission-remote -l

- 对下载进程的操作

>进程详情 | | transmission-remote -t [all \| hash] -i
>停止 | | transmission-remote -t [all \| hash] -s
>重启 | | transmission-remote -t [all \| hash] -S
>取消 | | transmission-remote -t [all \| hash] -r
>下载限速 | | transmission-remote -t [all \| hash] -d [rate]
>取消下载限速 | | transmission-remote -t [all \| hash] -D
>上传限速 | | transmission-remote -t [all \| hash] -u [rate]
>取消上传限速 | | transmission-remote -t [all \| hash] -U

## amulecmd

- 下载文件

    add [ed2k]

- 查看下载进程信息

    show dl

- 对下载进程的操作

    暂停   pause [hash \| id]  
    重启  resume [hash \| id]  
    取消  cancel [hash \| id]





