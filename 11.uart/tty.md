#### tty 历史
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220115150511.png)
1. tty即teletype，是用来通讯的，2台tty直连
2. 最早的计算机通过打孔卡片输入太麻烦了
3. 发展成以teletype来输入
4. 把输入调制成串口信号，再接串口设备，cpu则可以读取了
5. tty则表示与计算机通讯的远端

#### tty 现代计算机中的tty
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220115152259.png)
这里去看视频吧  
https://www.bilibili.com/video/BV1kk4y117Tu?p=36&spm_id_from=pageDriver  
1. 前台只能有1个tty终端
2. /dev/tty0 表示当前前台的那个tty终端
3. /dev/tty 表示当前终端
    （在ubuntu图形界面下，可以通过ctrl+alt+f3/4/5进入终端，f2再切回gui）

一个tty可以理解成一个terminal

#### console 控制台
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220115153536.png)
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220115154310.png)
但我们不知道内核指定的输出设备是哪个tty，所以我们直接读取/dev/console


#### tty 驱动框架
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220115162754.png)
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220115162856.png)
串口、键盘鼠标、显示，都会最终被驱动注册成tty设备


#### pc与arm串口命令行通讯过程