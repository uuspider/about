---
layout: post
title: Shell with Style
---

# Shell with Style

参考：[Google shell styleguide][ref1]{:target="_blank"}

[ref1]:http://zh-google-styleguide.readthedocs.io/en/latest/google-shell-styleguide/contents/

<h2 id="top"></h2>

***

*   [背景](#background)
    *   [选择shell](#which_shell)
    *   [shell适用场景](#when_to_use)
*   [脚本与解释器](#invocation)
    *   [扩展名](#extensions)
    *   [SUID/SGID](#suid)
*   [环境](#environment)
    *   [重定向输出信息](#so_se)
*   [注释](#comments)
    *   [文件头](#header)
    *   [功能注释](#funcomments)
    *   [细节注释](#codecomments)
    *   [TODO注释](#todocomments)
*   [格式](#formatting)
    *   [缩进](#indentation)
    *   [语句块](#part)
    *   [行的长度](#line_length)
    *   [管道组合](#pipelines)
    *   [if/for/while](#loops)
    *   [case](#case)
    *   [变量展开](#var_expansion)
    *   [引号](#quotes)
*   [shell陷阱](#features)
    *   [命令替换](#command_substitution)
    *   [test, \[与\[\[](#test)
    *   [字符串比对](#filter)
    *   [通配符](#wildcard)
    *   [eval](#eval)
    *   [重定义 IFS](#ifs)
    *   [最小化 PATH](#path)
    *   [管道导向while](#pipetowhile)
*   [命名约定](#naming_conventions)
    *   [函数名](#fun_names)
    *   [变量名](#var_names)
    *   [常量和环境变量名](#con_names)
    *   [源文件名](#script_names)
    *   [临时文件名](#tmp_names)
    *   [只读变量](#readonly)
    *   [局部变量](#local_var)
    *   [函数位置](#fun_location)
    *   [主函数](#main)
*   [命令调用](#calling)
    *   [检查返回值](#returnvalue)
    *   [内建命令](#invsext)
*   [结论](#conclusion)

***

## 背景 {#background}

### 使用哪种 shell {#which_shell}

<div class="tip"> 优先选择 bash。 </div>

可执行文件必须以类似 `#!/bin/bash` 的标志开始。使用 `set` 设置 shell 的选项，以确保使用 `bash <script_name>` 运行脚本时不会出现异常。

优先选择 bash ，如果系统不支持 bash ，可使用其他 shell 语言。例如 Solaris SVR4，需要用纯 Bourne shell。

> uuspider 的 shell 脚本使用 `#!/usr/bin/env bash` 开始。

## 何时使用shell {#when_to_use}

<div class="tip"> shell 适用于编写小工具或者简单的包装脚本。</div>

shell 不是一种开发语言，而是一种工具语言，因此，有必要明确 shell 在生产环境下的一些使用准则：

- 如果你主要是在调用其他的工具并且做一些相对很小数据量的操作，可以使用 shell。

- 如果你关注性能，请选择其他语言， shell 不是一种高效的语言。

- 如果发现你的项目涉及数组，不要使用 shell，可选择 python 。

- 如果你的 shell 脚本已经超过100行，请使用 python 。

**[[TOP](#top)]**

***

## 脚本与解释器 {#invocation}

### 文件扩展名 {#extensions}

<div class="tip"> 可执行文件不需要扩展名(强烈建议)或者使用 .sh 扩展名。库文件必须使用 .sh 作为扩展名，而且应该是不可执行的。</div>

执行一个程序时，不需要知道它是用什么语言编写的，同时 shell 脚本也不要求有扩展名，所以我们推荐可执行文件不使用扩展名。

对于库文件，明确其编写语言很重要，使用 .sh 这样特定语言后缀作为扩展名，就可以使不同语言编写的具有相同功能的库文件采用同一个文件名。

### SUID/SGID {#suid}

<div class="tip"> 禁止使用SUID和SGID。 </div>

禁止在 shell 中使用 SUID/SGID ，如果需要更高权限，可使用 `sudo` 。

**[[TOP](#top)]**

***

## 环境 {#environment}

### 重定向输出信息 {#so_se}

<div class="tip"> 正常内容输出到标准输出 (STDOUT) ，警告、错误、诊断等状态信息，应重定向到标准错误输出 (STDERR) 。</div>

警告、错误、诊断等状态信息可能默认输出到 STDOUT ，应将其重定向到 STDERR ，以便于查看脚本运行状态。

推荐使用以下函数，可将错误信息和其他状态信息同时定向到 STDERR 。


    err() {
      echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: $@" >&2
    }

    if ! do_something; then
      err "Unable to do_something"
      exit "${E_DID_NOTHING}"
    fi


**[[TOP](#top)]**

***

## 注释 {#comments}

### 文件头 {#header}

<div class="tip"> 文件开头处应有脚本说明。</div>

每个脚本必须有一个顶层注释，简述其功能，也可以加入版权声明、作者信息、版本说明等。

> uuspider 的 shell 脚本文件头格式为：

    #!/usr/bin/env bash
    ########################################
    #  脚本：cnbeta爬虫
    #  版本：0.9
    #  作者：uuspider
    #  日期：2015-07-24
    #  修订：2015-09-09 v0.4
    #  修订：2015-12-09 v0.5 20条新内容时发送
    #  修订：2016-09-09 v0.6 邮件题目重复问题
    #  更新：2016-12-20 v0.7 cnbeta rss升级
    #  更新：2017-03-04 v0.8 cnbeta rss升级
    #  更新：2018-03-31 v0.9 cnbeta rss升级 http -> https
    #  语言：shell
    #  功能：获取cnbeta更新并发送到邮箱
    ########################################

### 函数注释 {#funcomments}

<div class="tip"> 函数，尤其是库函数，无论其长度大小和复杂性都必须有注释。</div>

函数注释应该包含如下内容:

- 函数的功能描述

- 使用的和修改的全局变量

- 参数信息

- 返回值，应该明确定义函数返回值，避免使用默认值

例如:

    #!/usr/bin/env bash
    ...

    export PATH='/usr/xpg4/bin:/usr/bin:/opt/csw/bin:/opt/goog/bin'

    #######################################
    # Cleanup files from the backup dir
    # Globals (全局变量) :
    #   BACKUP_DIR
    #   ORACLE_SID
    # Arguments (参数) :
    #   None
    # Returns (返回值) :
    #   None
    #######################################
    cleanup() {
      ...
    }


### 代码细节的注释 {#codecomments}

<div class="tip"> 对代码中含有技巧的、不容易读懂的、有趣的或重要的部分添加注释。</div>

注释应与被注释的代码同级缩进，对变量的注释应紧跟在变量后面。

注意不应为所有代码都添加注释。

### TODO {#todocomments}

<div class="tip"> 对临时、短期解决方案，或仍需完善的代码添加 TODO 注释。</div>

TODO 注释以大写 TODO 开头，在后边紧跟的一个括号中注明用户名，冒号(可省略)之后是注释正文，最后以 bug 号或 ticket 号结束。如:

    # TODO(mrmonkey): Handle the unlikely edge cases (bug ####)


**[[TOP](#top)]**

***

## 格式 {#formatting}

优先沿用文件原本的风格，如果是新文件，应遵循以下风格。

### 缩进 {#indentation}

<div class="tip"> 每一级缩进为 2 个空格，不要使用 tab 。</div>

### 语句块 {#part}

<div class="tip"> 两个语句块之间以一个空白行分隔。</div>

### 行长度和长字符串 {#line_length}

<div class="tip"> 每一行最多 80 个字符。</div>

当一行很长时，使用 `\` 换行，这时应使用与命令宽度相同的缩进。使用 `\` 换行的原则是整齐美观，体现代码的逻辑性。

如果字符串超过 80 字符，应尽量使用 here document 或者嵌入一个新行，如果有一个文字字符串长度超过 80 字符，并且不能合理的分割，也应尽量使它短一点。

    # 使用 'here document's
    cat <<END;
    I am an exceptionally long
    string.
    END

    # 直接使用换行分割字符串
    long_string="I am an exceptionally
      long string."

### 管道组合 {#pipelines}

<div class="tip"> 如果一行不能完成整套管道操作，应将多个管道拆分成一行一个。</div>

如果一行可以完成整套管道操作，应将其写在同一行。否则，应该分割为每行一个管道(缩进 2 个空格)。这条规则适用于那些通过使用 `|` 或逻辑运算符 `||` 、 `&&` 等组合起来的链式命令。

    # 管道组合命令
    command1 \
      | command2 \
      | command3 \
      | command4


### if/for/while {#loops}

<div class="tip"> '; then' 、 '; do' 应和对应的 'if/for/while' 放在同一行，下一行增加一个缩进级别。</div>

`else` 单独一行，与相应的 `if` 对齐； `fi/done` 单独一行，与相应的 `if/for/while` 对齐。

如：

    for dir in ${dirs_to_cleanup}; do
      if [[ -d "${dir}/${ORACLE_SID}" ]]; then
        log_date "Cleaning up old files in ${dir}/${ORACLE_SID}"
        rm "${dir}/${ORACLE_SID}/"*
        if [[ "$?" -ne 0 ]]; then
          error_message
        fi
      else
        mkdir -p "${dir}/${ORACLE_SID}"
        if [[ "$?" -ne 0 ]]; then
          error_message
        fi
      fi
    done


### case {#case}

<div class="tip"> 匹配项表达式比 case 和 esac 多一个缩进级别。</div>

<div class="tip"> 匹配项和执行命令在同一行时，应在右括号后面和 ;; 号前面添加一个空格。</div>

    verbose='false'
    aflag=''
    bflag=''
    files=''
    while getopts 'abf:v' flag; do
      case "${flag}" in
        a) aflag='true' ;;
        b) bflag='true' ;;
        f) files="${OPTARG}" ;;
        v) verbose='true' ;;
        *) error "Unexpected option ${flag}" ;;
      esac
    done

<div class="tip"> 如果某一匹配项下有多个命令，应分成多行，其中匹配项、单条命令和 ;; 号各占一行，命令和 ;; 号比匹配项多一个缩进级别。</div>

    case "${expression}" in
      a)
        variable="..."
        some_command "${variable}" "${other_expr}" ...
        ;;
      absolute)
        actions="relative"
        another_command "${actions}" "${other_expr}" ...
        ;;
      *)
        error "Unexpected expression '${expression}'"
        ;;
    esac

<div class="tip"> 匹配项的表达式一般不需要添加引号，同时应避免使用 ;& 和 ;;s& 等符号。</div>

### 变量展开 {#var_expansion}

<div class="tip"> 除了单个字符的 shell 特殊变量或位置参数，其他所有变量都应使用花括号，如 "${var}" 。</div>

单个字符的特殊变量和位置参数:

    echo "Specials: !=$!, -=$-, _=$_. ?=$?, #=$# *=$* @=$@ \$=$$ ..."
    echo "Positional: $1" "$5" "$3"
    echo "many parameters: ${10}"

明确变量的边界:

    # Output is "a0b0c0"
    set -- a b c
    echo "${1}0${2}0${3}0"

单个字符的普通变量也应使用花括号:

    echo "PATH=${PATH}, PWD=${PWD}, mine=${some_var}"
    while read f; do
      echo "file=${f}"
    done < <(ls -l /tmp)

错误用法:

    # <错误用法> 无引号，无花括号，单个字符的特殊变量和位置参数不需要花括号
    echo a=$avar "b=$bvar" "PID=${$}" "${1}"

    # <错误用法> 不易区分: "${1}0${2}0${3}0" or "${10}${20}${30}"？
    set -- a b c
    echo "$10$20$30"

### 引号 {#quotes}

<div class="tip"> 尽量将包含变量、命令替换符、空格或 shell 元字符的字符串用引号括起来。</div>

<div class="tip"> 优先对类单词的字符串使用引号(而不是命令选项或者路径名)。</div>

<div class="tip"> 不要对整数使用引号。</div>

<div class="tip"> 注意 [[ ... ]] 中正则表达式的引号用法。</div>

<div class="tip"> 尽量使用 $@ ，除非有特殊原因需要使用 $* 。</div>

注意单引号不会识别和展开变量，双引号将展开或替换变量。

变量定义或引用时使用双引号:

    flag="$(some_command and its args "$@" 'quoted separately')"
    echo "${flag}"
    number="$(generate_number)"
    echo "${number}"

不要对整数使用引号:

    value=32

优先对类单词的字符串使用引号:

    readonly USE_INTEGER='true'

单引号中的特殊字符不需要转义:

    echo 'Hello stranger, and well met. Earn lots of $$$'
    echo "Process $$: Done making \$\$\$."

命令选项和路径不加引号:

    # ($1 is assumed to contain a value here)
    grep -li Hugo /dev/null "$1"

一些较复杂的引号用法:

    # Less simple examples
    # "quote variables, unless proven false": ccs might be empty
    git send-email --to "${reviewers}" ${ccs:+"--cc" "${ccs}"}

    # Positional parameter precautions: $1 might be unset
    # Single quotes leave regex as-is.
    grep -cP '([Ss]pecial|\|?characters*)$' ${1:+"$1"}

    # For passing on arguments,
    # "$@" is right almost everytime, and
    # $* is wrong almost everytime:
    #
    # * $* and $@ will split on spaces, clobbering up arguments
    #   that contain spaces and dropping empty strings;
    # * "$@" will retain arguments as-is, so no args
    #   provided will result in no args being passed on;
    #   This is in most cases what you want to use for passing
    #   on arguments.
    # * "$*" expands to one argument, with all args joined
    #   by (usually) spaces,
    #   so no args provided will result in one empty string
    #   being passed on.
    # (Consult 'man bash' for the nit-grits ;-)

    set -- 1 "2 two" "3 three tres"; echo $# ; set -- "$*"; echo "$#, $@")
    set -- 1 "2 two" "3 three tres"; echo $# ; set -- "$@"; echo "$#, $@")


**[[TOP](#top)]**

***

## shell 陷阱 {#features}

### 命令替换 {#command_substitution}

<div class="tip"> 命令替换使用 $(command) ，不要使用反引号。</div>

反引号嵌套的反引号需要使用反斜杠("\\")转义内部的反引号，而 `$(command)` 嵌套的反引号不需要转义。如：

    var="$(command "$(command1)")"

    # <错误用法> 不要使用反引号进行命令替换
    var="`command \`command1\``"

### test, \[\] 和 \[\[\]\] {#test}

<div class="tip"> 优先使用 [[ ... ]]，而不是 [ ... ] 和 test。 </div>

在 `[[` 和 `]]` 之间不会展开路径或切分单词，使用 `[[ ... ]]` 可以避免错误，同时， `[[ ... ]]` 支持正则表达式， `[ ... ]` 不支持。

    # This ensures the string on the left is made up of characters in the
    # alnum character class followed by the string name.
    # Note that the RHS should not be quoted here.
    # For the gory details, see
    # E14 at http://tiswww.case.edu/php/chet/bash/FAQ
    if [[ "filename" =~ ^[[:alnum:]]+name ]]; then
      echo "Match"
    fi

    # This matches the exact pattern "f*" (Does not match in this case)
    if [[ "filename" == "f*" ]]; then
      echo "Match"
    fi

    # This gives a "too many arguments" error as f* is expanded to the
    # contents of the current directory
    if [ "filename" == f* ]; then
      echo "Match"
    fi

### 字符串比对 {#filter}

<div class="tip"> 比对字符串使用 = ，检测字符串是否为空(非空)时使用 -z 或 -n。</div>

字符串比对:

    if [[ "${my_var}" = "some_string" ]]; then
      do_something
    fi

    # <错误用法>:
    if [[ "${my_var}X" = "some_stringX" ]]; then
      do_something
    fi

检测字符串是否为空时使用`-z`，检测字符串是否非空时使用`-n`:

    if [[ -z "${my_var}" ]]; then
      do_something
    fi

    # <不推荐的用法>:
    if [[ "${my_var}" = "" ]]; then
      do_something
    fi

    # <错误用法>: 应使用 -n
    if [[ "${my_var}" ]]; then
      do_something
    fi

### 通配符扩展 {#wildcard}

<div class="tip"> 当文件含有通配符时，应使用完整路径，比如，使用 ./* ，而不是 * 。</div>

这是因为文件名可以使用 `-` 开头，使用 `\*` 可能会被系统误认为是选项，如:

当前目录下有 -f ， -r ， somedir ， somefile 等文件和目录，使用

    rm -v *

会扩展成

    rm -v -r -f somedir simefile

这就导致当前目录所有的文件和目录被删除。使用 `./*` 可以避免这种情况：

    rm -v ./*
    removed './-f'
    removed './-r'
    rm: cannot remove './somedir': Is a directory
    removed './somefile'

### eval {#eval}

<div class="tip"> 禁止使用 eval 。</div>

`eval` 用于变量赋值，可以设置变量，但是不检查这些变量。如:

    variable="$(eval some_function)"

如果函数某个返回值中含有空格，`variable` 的值就会出错。

### 重定义 IFS {#ifs}

<div class="tip"> 重新定义 IFS 。</div>

对于安全性要求较高的 shell 脚本，应在全局变量定义区域重新定义 `IFS` :

    IFS='   
    '

`IFS` 重定义为'空格-tab-换行'，也可以使用:

    # 注意 Bourne Shell 不支持这种方式。
    IFS="\040\t\n"

### 最小化 PATH {#path}

<div class="tip"> 最小化 PATH 的范围，禁止将普通用户的目录加入 PATH 。</div>

对于安全性要求较高的 shell 脚本，应在全局变量定义区域重新定义 `PATH` 并 `export`:

    OLDPATH="$PATH"
    PATH=/bin:/usr/bin
    export PATH

注意保存系统原来的 `PATH` 。

当需要使用某个目录时，可为其设置一个全局变量，如当前脚本所在目录:

    SCRIPTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

    # <错误用法> 不要直接切换到某个目录
    cd "$(dirname "${BASH_SOURCE[0]}")"

### 管道导向 while {#pipetowhile}

<div class="tip"> 不要将管道直接导向 while ，应使用进程替换或 for 循环。</div>

这是因为 `while` 循环是在一个子 shell 中运行的，管道直接导向 `while` 使 bug 难以追踪。

    last_line='NULL'
    your_command | while read line; do
      last_line="${line}"
    done

    # This will output 'NULL'
    echo "${last_line}"

如果确定输入中不包含空格或者特殊符号(通常不是用户输入的)，可以使用 `for` 循环。

    total=0
    # Only do this if there are no spaces in return values.
    for value in $(command); do
      total+="${value}"
    done

也可以使用进程替换 `< <()` :

    total=0
    last_file=
    while read count filename; do
      total+="${count}"
      last_file="${filename}"
    done < <(your_command | uniq -c)

    # This will output the second field of the last line of output from
    # the command.
    echo "Total = ${total}"
    echo "Last one = ${last_file}"


<div class="tip"> while 中修改的变量不能传递到循环外，需要向循环外传递变量时尽量选用 awk 。</div>

如

    awk '$3 == "nfs" { print $2 " maps to " $1 }' /proc/mounts

用 `while` 的实现方法:

    while read src dest type opts rest; do
      if [[ ${type} == "nfs" ]]; then
        echo "NFS ${dest} maps to ${src}"
      fi
    done < /proc/mounts


**[[TOP](#top)]**

***

## 命名约定 {#naming_conventions}

### 函数名 {#fun_names}

<div class="tip"> 函数名使用小写字母，单词之间用下划线分隔。</div>

<div class="tip"> 函数名之后必须有圆括号，函数名和圆括号之间没有空格。</div>

<div class="tip"> 花括号必须和函数名位于同一行，花括号与圆括号之间加一个空格。</div>

<div class="tip"> 关键词 function 可省略，但必须在一个项目中保持一致。</div>

    my_func() {
      ...
    }

<div class="tip"> 使用双冒号 :: 分隔函数库。</div>

    # Part of a package
    mypackage::my_func() {
      ...
    }

### 变量名 {#var_names}

<div class="tip"> 使用小写字母，单词用下划线分隔，所有变量都应初始化。</div>

<div class="tip"> 在函数内部使用有意义的变量名接收参数，禁止直接操作 $1， $2 等。</div>

循环的变量名应该和要循环的变量保持一致，如:

    for zone in ${zones}; do
      something_with "${zone}"
    done

<div class="tip"> 变量一经定义，不允许删除。</div>

### 常量和环境变量名 {#con_names}

<div class="tip"> 使用大写字母，下划线分隔，在文件的开头处声明。</div>

常量和任何导出到环境的变量都应该大写，常量的值一旦确定就应立即声明为 `readonly` 。

    # Constant
    readonly PATH_TO_FILES='/some/path'

    # Both constant and environment
    # declare -r设置只读变量，-x设置为环境变量
    declare -xr ORACLE_SID='PROD'

有些变量被脚本使用后(例如使用 `getopts` 情况下)就变成了常量，此时应立即设置其为只读。注意 `declare` 不能在函数内部操作全局变量，这时可使用 `readonly` 和 `export` 来代替。

    VERBOSE='false'
    while getopts 'v' flag; do
      case "${flag}" in
        v) VERBOSE='true' ;;
      esac
    done
    readonly VERBOSE

### 源文件名 {#script_names}

<div class="tip"> 使用小写字母，下划线分隔单词。</div>

### 临时文件名 {#tmp_names}

<div class="tip"> 临时文件的命名应体现其与脚本的关联，并使用 $$ 后缀，临时文件应存放在系统 /tmp 目录中。</div>

可使用如下方式为当前脚本创建临时文件目录:

    mktemp -d /tmp/SCRIPT_NAME$$

### 只读变量 {#readonly}

<div class="tip"> 使用 readonly 或者 declare -r 来确保变量只读。</div>

使用只读变量可以帮助查找 bug ，只读变量应明确声明。

    zip_version="$(dpkg --status zip | grep Version: | cut -d ' ' -f 2)"
    if [[ -z "${zip_version}" ]]; then
      error_message
    else
      readonly zip_version
    fi


### 局部变量 {#local_var}

<div class="tip"> 使用 local 声明函数内部变量，变量赋值应另起一行。</div>

使用 `local` 来声明局部变量以确保其只在函数内部和子函数中可用，避免了影响全局命名空间和无意间设置的函数外变量。

当赋值由命令替换提供时，局部声明和赋值必须分开，因为内建的 `local` 不会从命令替换中传递状态码。

    my_func2() {
      local name="$1"

      # 局部变量声明和赋值应分行:
      local my_var
      my_var="$(my_func)" || return

      # DO NOT do this: $? contains the exit code of 'local', not my_func
      local my_var="$(my_func)"
      [[ $? -eq 0 ]] || return

      ...
    }


### 函数位置 {#fun_location}

<div class="tip"> 将文件中所有的函数一起放在常量定义之后。</div>

函数应集中在文件头部定义，只有 `includes`，`set` 语句和常量设置可在函数定义前完成。

<div class="tip"> 不要在函数之间隐藏可执行代码。</div>

### 主函数 {#main}

<div class="tip"> 对于较长的脚本，应定义一个名为 `main` 的函数来调用其它的函数。</div>

为了便于找到程序的起始位置，应把主程序放在 `main` 函数中，列在其它函数下面，文件中最后一句非注释行应调用 `main` 函数，注意将变量传递进去。

    #!/usr/bin/env bash

    CONFIGURATION_VARIABLES

    MY_FUNCTION_DEFINITIONS

    main() {
        ...
    }

    main "$@"


**[[TOP](#top)]**

***

## 命令调用 {#calling}

### 检查返回值 {#returnvalue}

<div class="tip"> 必须检查返回值， return 和 exit 都要设置状态码。</div>

对于一条不包含管道的命令，可以使用 `$?` 或者直接指向 `if` 语句来检查其返回值，如:

    if ! mv "${file_list}" "${dest_dir}/" ; then
      echo "Unable to move ${file_list} to ${dest_dir}" >&2
      exit "${E_BAD_MOVE}"
    fi

    # Or
    mv "${file_list}" "${dest_dir}/"
    if [[ "$?" -ne 0 ]]; then
      echo "Unable to move ${file_list} to ${dest_dir}" >&2
      exit "${E_BAD_MOVE}"
    fi


对于管道命令，可使用 `PIPESTATUE` 变量检查其所有部分的返回码，如：

    tar -cf - ./* | ( cd "${dir}" && tar -xf - )
    if [[ "${PIPESTATUS[0]}" -ne 0 || "${PIPESTATUS[1]}" -ne 0 ]]; then
      echo "Unable to tar files to ${dir}" >&2
    fi

注意，一旦运行其他命令，`PIPESTATUS` 就会被覆盖，如果需要根据管道发生错误的地方来进行不同的操作，应该在运行完管道命令后立即将 `PIPESTATUS` 的值赋给另外一个变量(尤其注意 `[` 这个符号也是一个命令)，如：

    tar -cf - ./* | ( cd "${DIR}" && tar -xf - )
    return_codes=(${PIPESTATUS[*]})
    if [[ "${return_codes[0]}" -ne 0 ]]; then
      do_something
    fi
    if [[ "${return_codes[1]}" -ne 0 ]]; then
      do_something_else
    fi


## 内建命令 vs 外部命令 {#invsext}

<div class="tip"> 优先选用内建命令。</div>

如使用:

    addition=$((${X} + ${Y}))
    substitution="${string/#foo/bar}"

而不是:

    # <不推荐的用法>:
    addition="$(expr ${X} + ${Y})"
    substitution="$(echo "${string}" | sed -e 's/^foo/bar/')"


**[[TOP](#top)]**

***

## 结论 {#conclusion}

<div class="tip"> 运用常识和判断力，并且保持一致。</div>

编辑代码时，花点时间看看项目中的其它代码，并熟悉其风格。如果其它代码中`if`语句使用空格，那么你也要使用；如果其中的注释用星号`*` 围成一个盒子状，那么你同样要这么做。

风格指南的重点在于提供一个通用的编程规范，这样大家可以把精力集中在实现内容而不是表现形式上。我们展示的是一个总体的的风格规范，但局部风格也很重要，如果你在一个文件中新加的代码和原有代码风格相去甚远，这就破坏了文件本身的整体美观，也会打乱读者在阅读代码时的节奏，所以要尽量避免。


**[[TOP](#top)]**

***
