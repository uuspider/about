---
layout: post
title: shell with style
---

# shell with style

参考：[Google shell styleguide][ref1]{:target="_blank"}

[ref1]:http://zh-google-styleguide.readthedocs.io/en/latest/google-shell-styleguide/contents/

<h2 id="top"></h2>

***

*   [PIL安装](#setup)
*   [图像模式](#mode)
*   [Image](#image)
    *   [Image实例属性](#image_attribute)
    *   [Image函数](#image_fun)
    *   [Image实例方法](#image_method)
*   [ImageFilter](#imagefilter)
    *   [ImageFilter过滤器](#filter)
    *   [ImageFilter函数](#filter_fun)
*   [ImageDraw](#imagedraw)
    *   [ImageDraw函数](#draw_fun)
    *   [ImageDraw实例方法](#draw_method)
*   [结论](#conclusion)

***

# 背景 {#background}

## 使用哪种shell {#which_shell}

<span style="background:#87CEFA"> 推荐使用bash。 </span>

可执行文件必须以`#!/bin/bash`和最小数量的标志开始。使用`set`设置shell的选项，使得用`bash <script_name>`调用脚本时不会破坏其功能。

限制所有的可执行shell脚本为bash，这样可以保证其具有良好的移植性。如果系统不支持bash，可使用其他shell语言。例如 Solaris SVR4，需要用纯Bourne shell。

* uuspider的shell脚本使用`#!/usr/bin/env bash`开始。

## 何时使用shell {#when_to_use}

### shell仅仅用于编写小工具或者简单的包装脚本。

shell脚本不是一种开发语言，但在Google被用于编写各种实用工具。本条风格指南重点在于认同shell的使用，而不具有强制性，也就是说，原则上你可以用shell做任何事。

以下是一些准则：

- 如果你主要是在调用其他的工具并且做一些相对很小数据量的操作，可以使用shell。

- 如果你关注性能，请选择其他语言，不推荐shell。

- 如果你发现需要使用数组，请使用python。

- 如果你的shell脚本超过100行，请使用python。

**[[TOP](#top)]**

***

# shell文件和解释器调用 {#invocation}

## 文件扩展名 {#extensions}

### 可执行文件应该没有扩展名(强烈建议)或者使用`.sh`扩展名。库文件必须使用`.sh`作为扩展名，而且应该是不可执行的。

当执行一个程序时，并不需要知道它是用什么语言编写的。而且shell脚本也不要求有扩展名。所以我们推荐可执行文件不使用扩展名。但对于库文件，知道其用什么语言编写的是很重要的，有时候会需要使用不同语言编写的相似的库文件。使用`.sh`这样特定语言后缀作为扩展名，就使得用不同语言编写的具有相同功能的库文件可以采用一样的名称。

## SUID/SGID {#suid}

### 脚本中禁止使用SUID和SGID。

出于安全性的考虑，禁止在shell中使用SUID/SGID。如果需要更高权限，可使用`sudo`。

**[[TOP](#top)]**

***

# 环境 {#environment}

## 错误信息 {#so_se}

### 所有错误信息应该输入到标准错误输出(STDERR)。

这样做便于查看脚本运行状态。

推荐使用以下函数，可将错误信息和其他状态信息同时输出。


    err() {
      echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: $@" >&2
    }
    
    if ! do_something; then
      err "Unable to do_something"
      exit "${E_DID_NOTHING}"
    fi


**[[TOP](#top)]**

***

# 注释 {#comments}

## 文件头 {#header}

### 脚本开头处应包含当前脚本的说明。

每个脚本必须有一个顶层注释，简述其功能，也可以加入版权声明、作者信息、版本说明等。

例如：

    #!/bin/bash
    #
    # Perform hot backups of Oracle databases.

> uuspider的shell脚本文件头格式为：

    #!/usr/bin/env bash
    #------------------------------------
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
    #------------------------------------

## 函数注释 {#funcomments}

### 除非很短或功能显而易见，函数都必须有注释。任何库函数，无论其长度大小和复杂性都必须要有注释。

函数注释应该包含如下内容:

- 函数的描述

- 使用的和修改的全局变量

- 参数信息

- 返回值，应该明确定义函数返回值，避免使用默认值

例如:

    #!/usr/bin/env bash
    #
    # Perform hot backups of Oracle databases.

    export PATH='/usr/xpg4/bin:/usr/bin:/opt/csw/bin:/opt/goog/bin'

    #######################################
    # Cleanup files from the backup dir
    # Globals:
    #   BACKUP_DIR
    #   ORACLE_SID
    # Arguments:
    #   None
    # Returns:
    #   None
    #######################################
    cleanup() {
      ...
    }


## 代码正文的注释 {#codecomments}

### 对代码中含有技巧的、不容易读懂的、有趣的或重要的部分添加注释。

不要所有代码都加注释。

## TODO {#todo}

### 对临时、短期解决方案，或仍需完善的代码添加TODO注释。

TODO注释，以大写TODO开头，在后边的括号中注明用户名，冒号(可省略)之后是注释正文，最后以bug号或ticket号结束。如：

    # TODO(mrmonkey): Handle the unlikely edge cases (bug ####)


**[[TOP](#top)]**

***

# 格式 {#formatting}

优先遵循原脚本文件的风格，但是新的代码必须遵循以下风格。

## 缩进 {#indentation}

### 使用2个空格来缩进，不要使用tab。两个语句块中间应使用空白行来提高可读性。

## 行长度和长字符串 {#line_length}

### 一行最长包含80个字符.

如果字符串超过80字符，应尽量使用here document或者嵌入一个新行，如果有一个文字字符串长度超过80字符，并且不能合理的分割，强烈推荐你想办法使它更短一点。

    # DO use 'here document's
    cat <<END;
    I am an exceptionally long
string.
    END

    # Embedded newlines are ok too
    long_string="I am an exceptionally
      long string."


## 多个管道 {#pipelines}

### 如果一行不能完成整套管道操作，应将多个管道拆分成一行一个。

如果一行容得下整个管道操作，应将整个管道操作写在同一行。否则，应该分割成每行一个管道，新的一行应该缩进2个空格。这条规则适用于那些通过使用”|”或者是一个逻辑运算符”||”和”&&”等组合起来的链式命令。

    # All fits on one line
    command1 | command2

    # Long commands
    command1 \
      | command2 \
      | command3 \
      | command4

## 循环 {#loops}

### 请将’; do’、’; then’和’while’、’for’或者’if’放在同一行。

shell中的循环遵循像声明函数时用大括号同样的原则，也就是说：’; do’、’; then’应该和 ‘if/for/while’放在同一行。’else’应该单独一行，结束语句应该单独一行并且跟开始语句垂直对齐。

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


## case语句 {#case}

### 缩进使用2个空格。

可用一行替代的，需要在右括号后面和 ;; 号前面添加一个空格。

对于长的，有多个命令的，应该分割成多行，其中匹配项，对于匹配项的处理以及 ;; 号各自在单独的行。

case 和 esac 中匹配项的表达式应该都在同一个缩进级别，匹配项的（多行）处理也应该在另一个缩进级别。通常来说，没有必要给匹配项的表达式添加引号。匹配项的表达式不应该在前面加一个左括号，避免使用 ;& 和 ;;s& 等符号。

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


对于一些简单的匹配项处理操作，可以和匹配项表达式以及 ;; 号在同一行,只要表达式仍然可读。这通常适合单字符的选项处理，当匹配项处理操作不能满足单行的情况下，可以将匹配项表达式单独放在一行，匹配项处理操作和 ;; 放在同一行，当匹配项操作和匹配项表达式以及 ;; 放在同一行的时候在匹配项表达式右括号后面以及 ;; 前面放置一个空格。

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


## 变量扩展(Variable expansion)

### 按优先级顺序：保持跟你所发现的一致；把你的变量用括号印起来；推荐用 "${var}" 而不是 "$var"，详细解释如下。

这些仅仅是指南，因为按标题作为强制的规定饱受争议。

以下按照优先顺序列出。

与现存代码中你所发现的保持一致。

把变量用（大）扩号引起来，参阅下面一节：引用。

除非绝对必要或者为了避免深深的困惑，否则不要用大括号将单个字符的 Shell 特殊变量或位置参数括起来。推荐将其他所有变量用大括号括起来。

    # Section of recommended cases.

    # Preferred style for 'special' variables:
    echo "Positional: $1" "$5" "$3"
    echo "Specials: !=$!, -=$-, _=$_. ?=$?, #=$# *=$* @=$@ \$=$$ ..."

    # Braces necessary:
    echo "many parameters: ${10}"

    # Braces avoiding confusion:
    # Output is "a0b0c0"
    set -- a b c
    echo "${1}0${2}0${3}0"

    # Preferred style for other variables:
    echo "PATH=${PATH}, PWD=${PWD}, mine=${some_var}"
    while read f; do
      echo "file=${f}"
    done < <(ls -l /tmp)

    # Section of discouraged cases

    # Unquoted vars, unbraced vars, brace-quoted single letter
    # shell specials.
    echo a=$avar "b=$bvar" "PID=${$}" "${1}"

    # Confusing use: this is expanded as "${1}0${2}0${3}0",
    # not "${10}${20}${30}
    set -- a b c
    echo "$10$20$30"

# 引号

### 尽量将包含变量、命令替换符、空格或 shell 元字符的字符串用引号括起来。

### 优先对是单词的字符串使用引号（而不是命令选项或者路径名）。

### 不要对整数使用引号。

### 注意 [[ 中模式匹配的引号用法。

### 尽量使用 $@ ，除非有特殊原因需要使用 $*。

    # 单引号不会识别和展开变量。
    # 双引号将展开或替换变量。

    # Simple examples
    # "quote command substitutions"
    flag="$(some_command and its args "$@" 'quoted separately')"

    # "quote variables"
    echo "${flag}"

    # 不要对整数使用引号。
    value=32
    # "quote command substitutions", even when you expect integers
    number="$(generate_number)"

    # "prefer quoting words", not compulsory
    readonly USE_INTEGER='true'

    # "quote shell meta characters"
    echo 'Hello stranger, and well met. Earn lots of $$$'
    echo "Process $$: Done making \$\$\$."

    # "command options or path names"
    # ($1 is assumed to contain a value here)
    grep -li Hugo /dev/null "$1"

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


# 特征和错误(Features and Bugs)

## 命令替换(Command Substitution)

### 使用 $(command) ，不推荐使用反引号。

嵌套的反引号要求用反斜杠("\")转义内部的反引号。而 $(command) 形式嵌套时不需要转义。如：

    # This is preferred:
    var="$(command "$(command1)")"

    # This is not:
    var="`command \`command1\``"
<span id='Test,[and[['>Test, [ 和 [[(Test, [ and [[)</span>

优先使用 [[ ... ]]，而不是 [, test 和 /usr/bin/[。

因为在 [[ 和 ]] 之间不会展开路径或切分单词，所以使用 [[ ... ]] 能够减少错误。而且 [[ ... ]] 允许正则表达式匹配，而 [ ... ] 不允许。

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

## 测试字符串

### 尽可能使用引号，而不是过滤字符串。

Bash 足以在测试中处理空字符串。所以，请使用空（非空）字符串测试，而不是过滤字符，使得代码更易于阅读。

    # Do this:
    if [[ "${my_var}" = "some_string" ]]; then
      do_something
    fi

    # -z (string length is zero) and -n (string length is not zero) are
    # preferred over testing for an empty string
    if [[ -z "${my_var}" ]]; then
      do_something
    fi

    # This is OK (ensure quotes on the empty side), but not preferred:
    if [[ "${my_var}" = "" ]]; then
      do_something
    fi

    # Not this:
    if [[ "${my_var}X" = "some_stringX" ]]; then
      do_something
    fi

为了避免对你测试的目的产生困惑，请明确使用 -z 或者 -n ：

    # Use this
    if [[ -n "${my_var}" ]]; then
      do_something
    fi

    # Instead of this as errors can occur if ${my_var} expands to a test
    # flag
    if [[ "${my_var}" ]]; then
      do_something
    fi

## 文件名的通配符扩展(Wildcard Expansion of Filenames)

### 当做文件名通配符扩展的时候，使用显式路径。

因为文件名可以使用 - 开头，所以使用扩展通配符 ./* 比 * 安全得多。

    # Here's the contents of the directory:
    # 当前目录下又-f -r somedir somefile等文件和目录
    # -f  -r  somedir  somefile

    # 使用rm -v *将会扩展成rm -v -r -f somedir simefile，这将导致删除当前目录所有的文件和目录
    # This deletes almost everything in the directory by force
    psa@bilby$ rm -v *
    removed directory: `somedir'
    removed `somefile'

    # 相反如果你使用./*则不会，因为-r -f就不会变成rm的参数了
    # As opposed to:
    psa@bilby$ rm -v ./*
    removed `./-f'
    removed `./-r'
    rm: cannot remove `./somedir': Is a directory
    removed `./somefile'

## Eval

### eval 命令应该被禁止执行。

eval 用于给变量赋值的时候，可以设置变量，但是不能检查这些变量是什么。

    # What does this set?
    # Did it succeed? In part or whole?
    eval $(set_my_variables)

    # What happens if one of the returned values has a space in it?
    variable="$(eval some_function)"

## 管道导向 while 循环(Pipes to While)

### 优先使用过程替换或者 for 循环，而不是管道导向 while 循环。在 while 循环中被修改的变量是不能传递给父 Shell 的，因为循环命令是在一个子 Shell 中运行的。

管道导向 while 循环中的隐式子 Shell 使得追踪 bug 变得很困难。

    last_line='NULL'
    your_command | while read line; do
      last_line="${line}"
    done

    # This will output 'NULL'
    echo "${last_line}"

如果你确定输入中不包含空格或者特殊符号（通常意味着不是用户输入的），那么可以使用一个 for 循环。

    total=0
    # Only do this if there are no spaces in return values.
    for value in $(command); do
      total+="${value}"
    done

使用过程替换允许重定向输出，但是请将命令放入一个显式的子 Shell 中，而不是 bash 为 while 循环创建的隐式子 Shell。

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

当不需要传递复杂的结果给父 Shell 时可以使用 while 循环。这通常需要一些更复杂的“解析”。请注意简单的例子使用如 awk 这类工具可能更容易完成。当你特别不希望改变父 Shell 的范围变量时这可能也是有用的。

    # Trivial implementation of awk expression:
    #   awk '$3 == "nfs" { print $2 " maps to " $1 }' /proc/mounts
    cat /proc/mounts | while read src dest type opts rest; do
      if [[ ${type} == "nfs" ]]; then
        echo "NFS ${dest} maps to ${src}"
      fi
    done

# 命名约定(Naming Conventions)

## 函数名(Function Names)

### 使用小写字母，并用下划线分隔单词。使用双冒号 :: 分隔库。函数名之后必须有圆括号。关键词 function 是可选的，但必须在一个项目中保持一致。

如果你正在写单个函数，请用小写字母来命名，并用下划线分隔单词。如果你正在写一个包，使用双冒号 :: 来分隔包名。大括号必须和函数名位于同一行（就像在 Google 的其他语言一样），并且函数名和圆括号之间没有空格。

    # Single function
    my_func() {
      ...
    }

    # Part of a package
    mypackage::my_func() {
      ...
    }

当函数名后存在 () 时，关键词 function 是多余的。但是其促进了函数的快速辨识。

# 变量名(Variable Names)

### 同函数名。

循环的变量名应该和要循环的任何变量同样命名。

    for zone in ${zones}; do
      something_with "${zone}"
    done

# 常量和环境变量名(Constants and Environment Variable Names)

### 要大写、用下划线分割、声明在文件的开头。

常量和任何导出到环境的变量都应该大写。

    # Constant
    readonly PATH_TO_FILES='/some/path'

    # Both constant and environment
    # declare -r设置只读变量，-x设置为环境变量
declare -xr ORACLE_SID='PROD' 
有些第一次设置时(例如使用 getopts 情况下)就变成了常量。也就是说，可以在 getopts 中或基于条件来设定常量，但之后应该立即设置其为只读。需要注意的是，declare 不能在函数内部操作全局变量，所以这时推荐使用 readonly 和 export 来代替。

    VERBOSE='false'
    while getopts 'v' flag; do
      case "${flag}" in
        v) VERBOSE='true' ;;
      esac
    done
    readonly VERBOSE

# 源文件名(Source Filenames)

### 使用小写，如果需要的话使用下划线分隔单词。

这是为了和在 Google 中的其他代码风格保持一致：maketemplate 或者 make_template，而不是 make-template。

## 只读变量(Read-ony Variables)

### 使用 readonly 或者 declare -r 来确保变量只读。

因为全局变量在 Shell 中广泛使用，所以在使用它们的过程中捕获错误是很重要的。当你声明了一个希望其只读的变量，那么请明确指出。

    zip_version="$(dpkg --status zip | grep Version: | cut -d ' ' -f 2)"
    if [[ -z "${zip_version}" ]]; then
      error_message
    else
      readonly zip_version
    fi


## 使用本地变量

### 使用local声明函数内部变量。声明和赋值应该在不同行。

使用 local 来声明局部变量以确保其只在函数内部和子函数中可用，避免了污染全局命名空间和无意间设置函数外的变量。

当赋值的值由命令替换提供时，声明和赋值必须分开。因为内建的 local 不会从命令替换中传递退出码。

    my_func2() {
      local name="$1"

      # 变量声明和赋值应分行:
      local my_var
      my_var="$(my_func)" || return

      # DO NOT do this: $? contains the exit code of 'local', not my_func
      local my_var="$(my_func)"
      [[ $? -eq 0 ]] || return

      ...
    }


## 函数位置(Function Location)

### 将文件中所有的函数一起放在常量下面。不要在函数之间隐藏可执行代码。

函数应集中在文件头部定义。只有 includes，set 语句和设置常数可在函数定义前完成。

不要在函数之间隐藏可执行代码，避免调试脚本时难以跟踪问题代码。

## 主函数(main)

### 对于较长的脚本，应定义一个名为 main 的函数来调用其它的函数。

为了便于找到程序的起始位置，把主程序放在一个叫 main 的函数中，放在其它函数的下面，应尽量使用本地变量(如果主程序不是一个程序，那么不能这么做)，文件中最后一句非注释行应调用 main 函数。

    main "$@"

# 命令调用

## 检查返回值

### 必须检查返回值，给出返回值相关的信息。

对于一条不包含管道的命令，可以使用$?或者直接指向if语句来检查其返回值，如:

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


对于管道命令，可使用PIPESTATUE变量检查其所有部分的返回码，如：

    tar -cf - ./* | ( cd "${dir}" && tar -xf - )
    if [[ "${PIPESTATUS[0]}" -ne 0 || "${PIPESTATUS[1]}" -ne 0 ]]; then
      echo "Unable to tar files to ${dir}" >&2
    fi

注意，一旦运行其他命令，PIPESTATUS就会被覆盖，如果需要根据管道发生错误的地方来进行不同的操作，应该在运行完管道命令后立即将PIPESTATUS的值赋给另外一个变量(尤其注意[这个符号也是一个命令)，如：

    tar -cf - ./* | ( cd "${DIR}" && tar -xf - )
    return_codes=(${PIPESTATUS[*]})
    if [[ "${return_codes[0]}" -ne 0 ]]; then
      do_something
    fi
    if [[ "${return_codes[1]}" -ne 0 ]]; then
      do_something_else
    fi


## 内建命令 vs 外部命令

### 优先选用内建命令。

如：

    # Prefer this:
    addition=$((${X} + ${Y}))
    substitution="${string/#foo/bar}"

    # Instead of this:
    addition="$(expr ${X} + ${Y})"
    substitution="$(echo "${string}" | sed -e 's/^foo/bar/')"


**[[TOP](#top)]**

***

# 结论 {#conclusion}

运用常识和判断力，并且**保持一致**。

编辑代码时，花点时间看看项目中的其它代码，并熟悉其风格。如果其它代码中`if`语句使用空格，那么你也要使用；如果其中的注释用星号`*` 围成一个盒子状，那么你同样要这么做。

风格指南的重点在于提供一个通用的编程规范，这样大家可以把精力集中在实现内容而不是表现形式上。我们展示的是一个总体的的风格规范，但局部风格也很重要，如果你在一个文件中新加的代码和原有代码风格相去甚远，这就破坏了文件本身的整体美观，也会打乱读者在阅读代码时的节奏，所以要尽量避免。


**[[TOP](#top)]**

***
