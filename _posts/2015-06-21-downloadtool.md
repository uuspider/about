---
layout: post
title: wget, transmission-remote & amulecmd
---
## wget, transmission-remote & amulecmd

*   [wget](#wget) 
*   [transmission-remote](#transmission)
*   [amulecmd](#amule)

***

# wget {#wget}

#### 下载文件

    wget [url]    

#### 下载时重命名

    wget -O aoi_sola.avi http://url/download.php?id=1024    

#### 限速

    wget –limit-rate=300k [url]    

#### 断点续传

    wget -c [url]    

#### 后台下载

    wget -b [url]

查看下载进度

    tail -f wget-log

#### 下载多个文件

保存一份下载链接文件

    cat > filelist.txt 
    url1
    url2
    url3
    url4

下载该文件中的链接

    wget -i filelist.txt

#### FTP下载

    wget [ftp-url]

如需用户名和密码认证

    wget –ftp-user=USERNAME –ftp-password=PASSWORD [ftp-url]
    
#### 代理服务器

    wget -Y on -e "http_proxy=http://10.0.0.172:80" [url]

注：`curl`有和`wget`类似的功能，查看[这里](http://about.uuspider.com/2015/07/25/curl.html){:target="_blank"}。

***

# transmission-remote {#transmission}

#### 下载文件

    transmission-remote -a [torrent | magnet]

#### 查看下载进程信息

    transmission-remote -l

#### 对下载进程的操作

    transmission-remote -t [all | hash] -[ ]

进程详情 | | **`i`**
停止 | | **`S`**
重启 | | **`s`**
取消 | | **`r`**
下载限速 | | **`d [rate]`**
取消下载限速 | | **`D`**
上传限速 | | **`u [rate]`**
取消上传限速 | | **`U`**

***

# amulecmd {#amule}

#### 下载文件

    add [ed2k]

#### 查看下载进程信息

    show dl

#### 对下载进程的操作

    暂停   pause [hash | id]  
    重启  resume [hash | id]  
    取消  cancel [hash | id]

***
