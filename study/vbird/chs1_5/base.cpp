#if 0

ifconfig : 查询、设定网络卡与 IP 网域等相关参数
ifup, ifdown : 属于 script，透过更简单的方式来启动网络接口
route : 查询、设定路由表
ip : 复合式指令，可以直接修改上述提到的功能

ifconfig
==========

RX : 网络由启动到目前为止的数据包接收情况，packets 代表数据包数、errors 代表
     数据包发生错误的数量、dropped 代表数据包由于有问题而丢弃的数量等等
TX : 与 RX 相反，为网络由启动到目前为止的传送情况
collisions : 数据包碰撞情况

ifconfig eth0 mtu 9000 // 修改该接口的 MTU 值，其他保持不变

route
==========

路由的增加与删除
route del -net 169.254.0.0 netmask 255.255.0.0 dev eth0
route add -net 192.168.100.0 netmask 255.255.255.0 dev eth0
route add default gw 192.168.1.250

/etc/init.d/network restart // 重启网络服务，会恢复原来的 route 设定

手动使用 DHCP 自动取得 IP 参数 : dhclient
=============================================

dhclient eth0

ping
==========

用 ping 追踪路径中的最大 MTU 数值
ping -c 2 -s 1000 -M do 192.168.1.254

-c : ping 次数
-s : 数据包大小，IP 数据包表头占用 20 byyes，再加上 ICMP 表头有 8 bytes，所以
     当你在使用 -s size 时，那个数据包大小就要扣除 28 的大小
-M do : 不许重新拆包

如果有响应，那就是可以接受这个数据包，否则表示这个 MTU 太大了

两主机间各节点分析 : traceroute
==================================

traceroute -n www.baidu.com
traceroute -w 1 -n -T www.baidu.com // 等待 1 秒，使用 TCP 侦测

netstat
===========

netstat -tulnp // 观察目前已经启动的网络服务
netstat -atunp // 查看本机上所有的网络联机状态

侦测主机名与 IP 对应 : host, nslookup
=========================================


#endif
