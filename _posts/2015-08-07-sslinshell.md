---
layout: post
title: base64, md5/SHA1, AES/DES3
---
## base64, md5/SHA1, AES/DES3

参考：[openssl][ref1]{:target="_blank"}

[ref1]:https://www.openssl.org/docs/apps/openssl.html

<h2 id="top"></h2>

***

*   [编码与解码](#base64)
*   [摘要](#md5)
*   [加密与解密](#aes)

***

## base64 编码与解码 {#base64}

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

## md5/SHA1 摘要 {#md5}

    $ echo hello world | openssl md5
    (stdin)= 6f5902ac237024bdd0c176cb93063dc4
    $ openssl md5 file.txt
    MD5(file.txt)= xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    $ echo hello world | openssl sha1
    (stdin)= 22596363b3de40b06f981fb85d82312e8c0ed511
    $ openssl sha1 file.txt
    SHA1(file.txt)= xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
**[[TOP](#top)]**

***

## AES 加密与解密 {#aes}

    $ echo hello world | openssl aes-128-cbc -k 123 -base64
    U2FsdGVkX18OHihiZ6nWX1QOA43V64h3Shu5QIHkQVM=

这是对字符串“hello world”进行aes加密，密钥为123，输出结果以base64编码输出。`-k`现多写为`-key`。

    $ echo U2FsdGVkX18OHihiZ6nWX1QOA43V64h3Shu5QIHkQVM= | openssl aes-128-cbc -d -k 123 -base64
    hello world

这是对上述结果解密。

对于文件的加密或密文的解密，使用`-in`即可，加密或解密后输出文件名可用`-out`指定。
    
更多编码、摘要、加密方法可使用`openssl help`或到[这里](https://www.openssl.org/docs/apps/openssl.html#STANDARD-COMMANDS){:target="_blank"}查看。
    
**[[TOP](#top)]**

***
