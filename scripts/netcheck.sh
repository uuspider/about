#!/bin/bash
#------------------------------------
#  脚本：network_check
#  版本：0.4
#  作者：uuspider
#  日期：2015-09-13 v0.1
#  日期：2015-10-28 v0.3
#  日期：2016-01-17 v0.4
#  语言：shell
#  功能：1.网络中断后重启网络或重启树莓派;
#  功能：2.当公网ip变化时，发送邮件通知。
#  使用：(crontab) */2 * * * * $PATH/netcheck.sh
#------------------------------------

# http://www.silisoftware.com/tools/ip.php
# http://ipecho.net/plain
# http://whatismyip.akamai.com
# http://tnx.nl/ip #curl无法连接，浏览器连接正常
# http://myip.dnsomatic.com/
# http://members.3322.org/dyndns/getip
## http://ipinfo.io
## http://ipinfo.io/developers
# http://ifconfig.me/ #太慢
# http://ip.appspot.com/ #太慢
# curl --silent http://1212.ip138.com/ic.asp | tail -1 | tr '\n' ' ' | awk -F '[\\[\\]]' '{print $2}'

export PATH="/usr/sbin:/usr/bin:/sbin:/bin"

cd $(dirname $BASH_SOURCE)
touch "./ip.log"
IP_Log=$(cat "./ip.log")

To_Addr="uuspider@gmail.com uuspider@yahoo.com"
IP_URL=("http://www.silisoftware.com/tools/ip.php" "http://ipecho.net/plain" "http://whatismyip.akamai.com" "http://myip.dnsomatic.com/" "http://members.3322.org/dyndns/getip")
PING_URL=("www.baidu.com" "www.sina.com.cn" "www.163.com" "www.qq.com")

pull() {
#访问IP_URL
  for ((j=0; j < ${#IP_URL[@]}; j++))
  do
    IP_New=$(curl -s ${IP_URL[$j]})
    echo $IP_New | grep "^[0-9]*\.[0-9]*\.[0-9]*\.[0-9]*$" && break
  done
  ip_check
}

net_check() {
  sleep 30
  connected=0
#检查网络连接是否正常
  for ((i=0; i < ${#urls[@]}; i++))
  do
    ping ${PING_URL[$i]} -c2 &> /dev/null
    if [ $? -eq 0 ]; then
      connected=$((++connected))
    fi
  done
#网络无法连接时，重启网络或重启树莓派
  if [ $connected -eq 0 ]; then
    sudo service networking restart
    sudo ifup wlan0
#   sudo /etc/init.d/networking restart
#   sudo /sbin/ifup wlan0
#   sudo reboot
  else
    pull
  fi
}

ip_check() {
  if [ "$IP_New" = "$IP_Log" ]; then
    :
  elif [ "$IP_New" = "" ]; then
    net_check
  else
    echo -n $IP_New > ./ip.log
    mutt -s "[IP Checked] $IP_New" $To_Addr < ./ip.log || rm ./ip.log
  fi
}

pull

exit 0

##END##
