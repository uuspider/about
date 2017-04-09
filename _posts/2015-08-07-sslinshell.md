---
layout: post
title: base64, md5/SHA1, AES
---
## base64, md5/SHA1, AES

参考：[openssl][ref1]{:target="_blank"} , [openssl 命令参数][ref2]{:target="_blank"}

[ref1]:https://www.openssl.org/docs/apps/openssl.html
[ref2]:http://netkiller.github.io/cryptography/openssl/index.html

<h2 id="top"></h2>

***

*   [编码与解码](#base64)
*   [摘要](#md5)
*   [加密与解密](#aes)
*   [ssh-keygen](#ssh)

***

## base64: encoding {#base64}

    $ echo hello world | openssl base64
    aGVsbG8gd29ybGQK
    $ echo aGVsbG8gd29ybGQK | openssl base64 -d
    hello world
    $ openssl base64 -in file.txt
    [...]
    $ openssl base64 -d -in file.base64
    [...]

**[[TOP](#top)]**

***

## md5/SHA1: digest {#md5}

    $ echo -n "hello world" | md5sum
    5eb63bbbe01eeed093cb22bb8f5acdc3  -
    $ echo -n "hello world" | openssl md5
    (stdin)= 5eb63bbbe01eeed093cb22bb8f5acdc3
    $ openssl md5 file.txt
    MD5(file.txt)= xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    $ echo -n "hello world" | openssl sha1
    (stdin)= 2aae6c35c94fcfb415dbe95f408b9ce91ee846ed
    $ openssl sha1 file.txt
    SHA1(file.txt)= xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

注意：`echo`与`echo -n`是不同的。

**[[TOP](#top)]**

***

## AES/RSA: cipher {#aes}

### AES

    $ echo hello world | openssl aes-128-cbc -k 123 -base64
    U2FsdGVkX18OHihiZ6nWX1QOA43V64h3Shu5QIHkQVM=

这是对字符串“hello world”进行aes加密，密钥为123，输出结果以base64编码输出。`-k`现多写为`-key`。

    $ echo U2FsdGVkX18OHihiZ6nWX1QOA43V64h3Shu5QIHkQVM= | openssl aes-128-cbc -d -k 123 -base64
    hello world

这是对上述结果解密。

对于文件的加密或解密，使用`-in`即可，加密或解密后输出文件名可用`-out`指定。

### RSA

    $ openssl genrsa -out key.pem 1024

生成RSA密钥，指定长度为1024。

    $ openssl rsa -in key.pem -pubout -out pubkey.pem

提取PEM格式公钥。

    $ openssl rsa -in key.pem -RSAPublicKey_out -out pubkey.pem

提取PEM RSAPublicKey格式公钥。

    $ openssl rsautl -encrypt -in input.file -inkey pubkey.pem -pubin -out output.file

使用公钥加密文件，`-inkey`指定加密公钥文件。

    $ openssl rsautl -decrypt -in input.file -inkey key.pem -out output.file

使用私钥解密文件，`-inkey`指定解密私钥文件。

更多编码、摘要、加密方法可使用`openssl help`或到[这里](http://netkiller.github.io/cryptography/openssl/index.html){:target="_blank"}查看。
    
**[[TOP](#top)]**

***

## ssh-keygen {#ssh}

使用rsa密钥可以使ssh登陆时免于输入密码。

    $ ssh-keygen  #等价于ssh-keygen -t rsa，-t用于指定密钥类型，默认为rsa
    Generating public/private rsa key pair.
    Enter file in which to save the key (/home/USER/.ssh/id_rsa): /home/USER/.ssh/USER_rsa  #这里是为密钥命名
    Enter passphrase (empty for no passphrase):   #输入口令，可设为空
    Enter same passphrase again: 
    Your identification has been saved in /home/USER/.ssh/USER_rsa.  #私钥文件
    Your public key has been saved in /home/USER/.ssh/USER_rsa.pub.  #公钥文件
    The key fingerprint is:
    26:09:2e:cd:5a:fd:fc:61:65:83:8a:c7:04:8f:b1:25 USER@LOCALHOST
    The key's randomart image is:
    +--[ RSA 2048]----+
    |                 |
    |                 |
    |    . E .        |
    |   + o X   .     |
    |  . = * S . +    |
    |   +   O . o .   |
    |  .   . * o      |
    |       . o .     |
    |          .      |
    +-----------------+
    $ ssh-copy-id USER@REMOTEHOST  #将公钥传到远程主机上，添加到~/.ssh/authorized_keys文件中

**[[TOP](#top)]**

***


