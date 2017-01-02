#if 0

IP 的分级

class A: 0xxxxxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
class B: 10xxxxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
class C: 110xxxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
class D: 1110xxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx
class E: 1111xxxx.xxxxxxxx.xxxxxxxx.xxxxxxxx

class A: 0.xx.xx.xx ~ 127.xx.xx.xx
class B: 128.xx.xx.xx ~ 191.xx.xx.xx
class C: 192.xx.xx.xx ~ 223.xx.xx.xx
class D: 224.xx.xx.xx ~ 239.xx.xx.xx
class E: 240.xx.xx.xx ~ 255.xx.xx.xx

private IP:

class A: 10.0.0.0 ~ 10.255.255.255
class B: 172.16.0.0 ~ 172.31.255.255
class A: 192.168.0.0 ~ 192.168.255.255

----------------------------------------------------------

Netmask 或 Subnet mask 子网掩码

Netmask:   255.255.255.0
Network:   192.168.0.0 // 网段
Broadcast: 192.168.0.255 // 最后一个 IP

------------------------------------------------------------------

子网切分

11000000.10101000.00000000.00000000       Network:    192.168.0.0
11000000.10101000.00000000.11111111       Broadcast:  192.168.0.255

11000000.10101000.00000000.00000000
11000000.10101000.00000000.10000000

first
Network:   11000000.10101000.00000000.00000000     192.168.0.0
Broadcast: 11000000.10101000.00000000.01111111     192.168.0.127
Netmask:   11111111.11111111.11111111.10000000     255.255.255.128

second
Network:   11000000.10101000.00000000.10000000     192.168.0.128
Broadcast: 11000000.10101000.00000000.11111111     192.168.0.255
Netmask:   11111111.11111111.11111111.10000000     255.255.255.128

-----------------------------------------------------------------------

路由

每一部主机都有自己的路由表
每一部主机都有自己的路由表
每一部主机都有自己的路由表

route
Kernel IP routing table
+------------------------------------------------------------------------------+
|Destination     Gateway         Genmask         Flags Metric Ref    Use Iface |
|10.0.2.0        *               255.255.255.0   U     0      0        0 eth0  |
|link-local      *               255.255.0.0     U     1002   0        0 eth0  |
|default         10.0.2.2        0.0.0.0         UG    0      0        0 eth0  |
+------------------------------------------------------------------------------+

route -n
Kernel IP routing table
+------------------------------------------------------------------------------+
|Destination     Gateway         Genmask         Flags Metric Ref    Use Iface |
|10.0.2.0        0.0.0.0         255.255.255.0   U     0      0        0 eth0  |
|169.254.0.0     0.0.0.0         255.255.0.0     U     1002   0        0 eth0  |
|0.0.0.0         10.0.2.2        0.0.0.0         UG    0      0        0 eth0  |
+------------------------------------------------------------------------------+

Destination:    其实就是 Network 的意思
Gateway:        网关 IP，若为 0.0.0.0(即*) 表示不需要额外的 IP
Genmask:        Netmask 与 Network 组合成为一部主机或网域
Flags:
	  U: 代表该路由可用
	  G: 代表该网域需要经由 Gateway 来帮忙转递
	  H: 代表该路由为一部主机，而非一整个网域
Iface:          就是接口（interface）的意思

如果要传送出去的分组第二栏 Gateway 为 *，就直接以后面的网络接口传送出去，而不透过 Gateway
万一要传送出去的分组的目的地 IP 不在路由规则里，就会将分组传送到 default 所在的那个路由去

----------------------------------------------------------------------------------

ARP 网络地址解析
RARP 反向网络地址解析

arp 命令
-n   将主机名以 IP 的形态显示
-d   将 hostname 的 hardware_address 由 ARP table 中删除掉
-s   设定某个 IP 或 hostname 的 MAC 到 ARP table 中

------------------------------------------------------------------------------------

ICMP - 网络层

错误侦测与回报机制

ping 或 traceroute



#endif
