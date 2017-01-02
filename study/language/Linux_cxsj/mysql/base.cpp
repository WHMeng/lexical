#if 0

service mysqld start // 启动数据库

chkconfig --list | grep mysqld // 查看 mysql 服务是否开机自动启动

chkconfig mysqld on // 设置 mysql 服务开机自动启动

mysqladmin -u root password 'root' // 给 root 帐号设置密码为 root

mysql -u root -p // 登录数据库

--------------------------------------------------------------------------

/etc/my.cnf // mysql 主配置文件

/var/lib/mysql // mysql 数据库文件存放位置

/var/log // mysql 数据库的日志输出存放位置

mysql 数据库绑定的端口号是 3306

netstat -anp | more // 查看网络

-------------------------------------------------------

检查权限表确认密码被设置，使用 use 命令切换到 mysql 数据库，
然后查询内部表

use mysql
SELECT user, host, password FROM user;

DELETE FROM user WHERE user != 'root'; // 从权限表中删除所有非 root 用户
DELETE FROM user WHERE host != 'localhost'; // 从权限表中删除 localhost 以外任何主机的登录

现在，这个正在运行的 mysql 版本，已经被限制为只有使用我们设定密码的 root 用户才能连接数据
库服务器，并且这个 root 用户只能从本地机器链接

---------------------------------------------------------------------------------------------

创建一个拥有相当广泛权限的新用户 rick，它将可以使用 3 种不同的方法进行连接

1）从本地机器连接
2）从 IP 地址在 192.168.0.0~192.168.0.255 范围内的任何机器连接
3）从 wiley.com 域中的任何机器连接

以 root 用户身份连接到 mysql 后执行如下操作

GRANT ALL ON *.* TO rick@localhost IDENTIFIED BY 'rick';
GRANT ALL ON *.* TO rick@'192.168.0.0/255.255.255.0' IDENTIFIED BY 'rick';
GRANT ALL ON *.* TO rick@'%.wiley.com' IDENTIFIED BY 'rick';

查看 user 表核对条目

SELECT user, host, password FROM mysql.user;

--------------------------------------------------------------------------------------

在 mysql 控制台中使用 grant 和 revoke 命令来管理用户权限

grant <privilege> on <object> to <user> [identified by user-password] [with grant option]; // 常规格式

它可以授予的权限

alter                  改变表和索引
create                 创建数据库和表
delete                 从数据库中删除数据
drop                   删除数据库和表
index                  管理索引
insert                 在数据库中添加数据
lock tables            允许锁定表
select                 提取数据
update                 修改数据
all                    以上所有

-------------------------------------------------------------

sql 语法中 % 代表通配符

GRANT ALL ON foo.* TO rick@'%' IDENTIFIED BY 'bar';

这将创建用户 rick, 他拥有对数据库 foo 的所有权限，并能以初始密码 bar 从任何机器进行连接
如果数据库 foo 尚未存在，那么用户 rick 现在将拥有使用 sql 命令 create database 来创建
该数据库的权限

注意！！！
命名少用下划线，因为 sql 中的下划线是一种匹配任意单个字符的模式

----------------------------------------------------------------------------------

revoke <a_privilege> on <an_object> from <a_user>

REVOKE INSERT ON foo.* FROM rick@'%';

revoke 不能删除用户，如果要完全删除一个用户，应该用 revoke 删除他们的权限，
然后切换到内部的 mysql 数据库通过从 user 表中删除对应的行来删除一个用户

use mysql
DELETE FROM user WHERE user = "rick";
FLUSH PRIVILEGES; // 重载权限表

完成了这个之后，请一定要返回自己的数据库，否则你仍然在 mysql 自己的内部数据库中

-------------------------------------------------------------------------------------

密码

以 root 用户身份连接 mysql 数据库，然后更新信息

给 foo 用户制定密码 bar

UPDATE user SET password = password('bar') WHERE user = 'foo';

------------------------------------------------------------------

创建数据库

以 rick 用户连接 mysql

mysql -u rick -p

CREATE DATABASE rick; // 创建名为 rick 的数据库
use rick // 告诉 mysql 我们想使用新的数据库

---------------------------------------------------------------------------

创建表

CREATE TABLE <table_name> (
		column type [NULL | NOT NULL] [AUTO_INCREMENT] [PRIMARY KEY]
		[, ...]
		[, PRIMARY KEY (column [, ...])]
)

DROP TABLE <table_name> // 删除表

AUTO_INCREMENT
无论何时，当你在该列中写入 NULL 值时，它都会自动把一个自动分配的递增数字填入列数据中

PRIMARY KEY
指出此列的数据必须是唯一的，每个表只能有一个主键

CREATE TABLE children (
		childno INTEGRE AUTO_INCREMENT NOT NULL PRIMARY KEY,
		fname VARCHAR(30),
		age INTEGER
);

或者

CREATE TABLE children (
		childno INTEGRE AUTO_INCREMENT NOT NULL,
		fname VARCHAR(30),
		age INTEGER
		PRIMARY KEY(childno)
);

插入数据

INSERT INTO children(fname, age) VALUES("Jenny", 21);
INSERT INTO children(fname, age) VALUES("Andrew", 17);
SELECT childno, fname, age FROM children;

#endif
