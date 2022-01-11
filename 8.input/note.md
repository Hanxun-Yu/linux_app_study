#### linux输入框架
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220110174636.png)
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220110175009.png)
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220110181147.png)
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220110181259.png)
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220110181330.png)


#### 查看有哪些输入设备
cat /proc/bus/input/devices
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220110212113.png)

#### hexdump
使用hexdump命令，读取设备节点发出的事件  
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220110181606.png)


#### ioctl获取设备信息
代码:01_get_input_info.c


#### 读取设备输入的几种方式
1. 查询方式  
open函数时，传入“O_NONBLOCK”表示“非阻塞“
2. 休眠-唤醒方式  
open函数时，不传入“O_NONBLOCK”，read时无事件将阻塞，进程随之休眠，有事件后将返回，进程被唤醒
3. POLL/SELECT方式  
poll提供了超时机制，并可以给一组设备（fds）注册一个poll事件（比如”POLLIN“表示有数据可读）
4. 异步通知
通过注册信号处理函数，等待驱动程序发出的信号
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220111220106.png)