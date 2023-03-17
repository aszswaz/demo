#!/bin/bash

set -o errexit
set -o nounset

# 使用 SMTP 协议发送邮件，不需要认证，一般用于邮件服务器之间的邮件传输

if [[ $TO_USER == "" ]]; then
    echo "请设置环境变量 TO_USER"
    exit 1
fi
if [[ $FORM_USER == "" ]]; then
    echo "请设置环境变量 FROM_USER"
    exit 1
fi
MAIL_SERVER="$(echo $TO_USER | awk '-F@' '{ print $2 }')"

IFS_BACKUP="IFS"
IFS=$'\n'
# 查询 163 邮箱的 IP 地址
# 获取 DNS 的 MX 记录，查询结果为 163 邮箱的可用节点的域名
mail_servers="$(dig +short @114.114.114.114 MX $MAIL_SERVER | awk '{ print $2 }')"
mail_servers=($mail_servers)
server="${mail_servers[0]}"
server="${server%.}"
# 查询节点的 IP
ip_address="$(dig +short $server)"
ip_address=($ip_address)
ip_address="${ip_address[0]}"
IFS="$IFS_BACKUP"

# 目标端口为 25，创建 TCP socket，将 socket 设置为指定的文件描述符
socket=3
eval "exec $socket<>/dev/tcp/$ip_address/25"

function mailSend() {
    echo "< $1"
    echo -n -e "$1\r\n" >&$socket
}
function mailRead() {
    local response
    set +o errexit
    while true; do
        read -r response <&$socket
        echo "> $response"
        # 判断目标服务器的响应是否发送完毕
        echo "$response" | grep -P '^\d{3}\s' 1>>/dev/null 2>&1
        if [ $? -eq 0 ]; then
            break
        fi
    done
    set -o errexit
}

mailRead
# 发送问候，表明自己的身份，一般是域名，需要与下面的 MAIL FROM 对应
mailSend "HELO mail.$(echo $FORM_USER | awk '-F@' '{ print $2 }')"
# 读取响应
mailRead

# 邮件表明邮件发送人
mailSend "MAIL FROM:<$FORM_USER>"
mailRead

# 表明邮件目标账户
mailSend "RCPT TO:<$TO_USER>"
mailRead

# 发送邮件正文
mailSend "DATA"
mailRead

# 发送邮件标题
mailSend "From: \"Bob Example\" <$FORM_USER>"
mailSend "To: Alice Example <$TO_USER>"
mailSend "Date: $(date --rfc-email)"
mailSend "Subject: Test message"
mailSend ""
# 发送邮件正文
mailSend "Hello World."
# 结束发送邮件
mailSend "."
mailRead

# 关闭连接
mailSend "QUIT"
mailRead
# 关闭 socket
