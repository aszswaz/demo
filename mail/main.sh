#!/bin/zsh

# 加载 zsh 的 TCP 模块
zmodload zsh/net/tcp

# 通过 dig 获得网易云的 SMTP 邮箱地址
# 首先是查询 DNS 的 MX 记录
# dig @114.114.114.114 MX 163.com
# 会得到好几个网易云的 MX 解析记录，这里使用 163mx03.mxmail.netease.com，获得该域名的 IPv4 地址
# dig @114.114.114.114 163mx03.mxmail.netease.com
# 域名 163mx03.mxmail.netease.com 的地址是：220.181.12.119，与这个IP建立TCP连接，开始发送邮件
ztcp 220.181.12.119 25
# ztcp 会将建立的 socket 文件描述符给到变量 REPLY
socket=$REPLY

read response <&$socket
echo "$response" <&$socket
# 发送问候，表明自己的身份，一般是域名，需要与下面的 MAIL FROM 对应
echo "HELO mail.aszswaz.cn" >&$socket
# 读取响应
read -r response <&$socket
echo "$response"

# 邮件表明邮件发送人
echo "MAIL FROM:<aszswaz@aszswaz.cn>" >&$socket
read -r response <&$socket
echo "$response"

# 表明邮件目标账户
echo "RCPT TO:<aszswaz@163.com>" >&$socket
read -r response <&$socket
echo "$response"

# 发送邮件正文
echo "DATA\r\n" >&$socket
read -r response <&$socket
echo "$response"

# 发送邮件标题
echo "From: \"Bob Example\" <aszswaz@aszswaz.cn>" >&$socket
echo "To: Alice Example <aszswaz@163.com>" >&$socket
echo "Date: Tue, 15 Jan 2008 16:02:43 -0500" >&$socket
echo "Subject: Test message" >&$socket
echo "" >&$socket
# 发送邮件正文
echo "Hello World." >&$socket
# 结束发送邮件
echo "." >&$socket
read -r response <&$socket
echo "$response"
echo "QUIT" >&$socket
read -r response <&$socket
echo "$response"
# 关闭 socket
ztcp -c $socket
