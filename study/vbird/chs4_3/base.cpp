#if 0

FTP 
======

明码传输

用户身份：user,      guest,   anonymous
          实体帐号， 访客，   匿名登录者

命令记录与登录文件记录：syslogd --- 一般在 /var/log/

限制用户活动的目录：charge root 简称 chroot

FTP 的传输使用 TCP 协议
==========================

FTP 服务器使用两个连接，分别是命令信道与数据流通道

以下是 ftp 服务器的主动式联机示意图

client                               ftp server

port AA <------- 三次握手 --------->   port 21 // 建立连接

port AA - 告知数据通道端口号是 BB ->   port 21 // 客户端请求传输数据

port BB <---------------------------   port 20 // 服务器用 port 20 向客户端的 port BB 连接进行数据传输


以下是 ftp 服务器的被动式联机示意图

client                               ftp server

port AA <------- 三次握手 --------->   port 21 // 建立连接

port AA ---- 被动连接请求(PASV) --->   port 21

port AA <- 主机主动告知 port PASV --   port 21

port BB --------------------------->   port PASV


vsftpd (very secure ftp daemon)
==========

重要配置文件
/etc/vsftpd/vsftpd.conf // 详细的 vsftpd.conf 可用 man 5 vsftpd.conf 来查

/etc/pam.d/vsftpd // 主要用来作身份认证用

/var/ftp/  // 这个时 vsftpd 的默认匿名者登入的根目录

vsftpd 启动
=============

stand alone 模式

/etc/init.d/vsftpd start




#endif
