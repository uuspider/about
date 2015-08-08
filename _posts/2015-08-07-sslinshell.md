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

## AES/RSA: cipher {#aes}

    $ echo hello world | openssl aes-128-cbc -k 123 -base64
    U2FsdGVkX18OHihiZ6nWX1QOA43V64h3Shu5QIHkQVM=

这是对字符串“hello world”进行aes加密，密钥为123，输出结果以base64编码输出。`-k`现多写为`-key`。

    $ echo U2FsdGVkX18OHihiZ6nWX1QOA43V64h3Shu5QIHkQVM= | openssl aes-128-cbc -d -k 123 -base64
    hello world

这是对上述结果解密。

对于文件的加密或解密，使用`-in`即可，加密或解密后输出文件名可用`-out`指定。

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
