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

#### 电阻屏上报数据
按下时：
```java
EV_KEY   BTN_TOUCH     1        /* 按下 */
EV_ABS   ABS_PRESSURE  1        /* 压力值，可以上报，也可以不报，可以是其他压力值 */
EV_ABS   ABS_X         x_value  /* X坐标 */
EV_ABS   ABS_Y         y_value  /* Y坐标 */
EV_SYNC  0             0        /* 同步事件 */
```
松开时：
```java
EV_KEY   BTN_TOUCH     0        /* 松开 */
EV_ABS   ABS_PRESSURE  0        /* 压力值，可以上报，也可以不报 */
EV_SYNC  0             0        /* 同步事件 */
```

#### 电容屏上报数据（多点触控）
当有2个触点时(type, code, value)：
```java
EV_ABS   ABS_MT_SLOT 0                  // 这表示“我要上报一个触点信息了”，用来分隔触点信息
EV_ABS   ABS_MT_TRACKING_ID 45          // 这个触点的ID是45
EV_ABS   ABS_MT_POSITION_X x[0]         // 触点X坐标
EV_ABS   ABS_MT_POSITION_Y y[0]         // 触点Y坐标
EV_ABS   ABS_MT_SLOT 1                  // 这表示“我要上报一个触点信息了”，用来分隔触点信息
EV_ABS   ABS_MT_TRACKING_ID 46          // 这个触点的ID是46
EV_ABS   ABS_MT_POSITION_X x[1]         // 触点X坐标
EV_ABS   ABS_MT_POSITION_Y y[1]         // 触点Y坐标
EV_SYNC  SYN_REPORT        0            // 全部数据上报完
```
当ID为45的触点正在移动时：
```java
EV_ABS   ABS_MT_SLOT 0   // 这表示“我要上报一个触点信息了”，之前上报过ID，就不用再上报ID了
EV_ABS   ABS_MT_POSITION_X x[0]   // 触点X坐标
EV_SYNC  SYN_REPORT         0     // 全部数据上报完毕
```
松开ID为45的触点时(在前面slot已经被设置为0，这里这需要再重新设置slot，slot就像一个全局变量一样：如果它没变化的话，就无需再次设置)：
```java
// 刚刚设置了ABS_MT_SLOT为0，它对应ID为45，这里设置ID为-1就表示ID为45的触点被松开了
EV_ABS   ABS_MT_TRACKING_ID -1   
EV_SYNC  SYN_REPORT         0    // 全部数据上报完毕
```
最后，松开ID为46的触点：
```java
EV_ABS   ABS_MT_SLOT 1       // 这表示“我要上报一个触点信息了”，在前面设置过slot 1的ID为46
EV_ABS   ABS_MT_TRACKING_ID -1  // ID为-1，表示slot 1被松开，即ID为46的触点被松开
EV_SYNC  SYN_REPORT             // 全部数据上报完毕
```

#### 电容屏实验数据
在157开发板上执行 hexdump /dev/input/event0
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220111233144.png)  
其中 ABS_MT_TOUCH_MAJOR 表示触点椭圆长轴  
其中 ABS_MT_WIDTH_MAJOR 表示接触面椭圆长轴
