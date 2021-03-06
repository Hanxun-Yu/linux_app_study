#### uart 接线方式
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220115141339.png)
##### 通讯前双方需确认：
1. 波特率（确定了1bit占用的时间）
2. 数据位（去定了开始位与停止位之间的数据位长度，即一次传输多少有效数据）
3. 停止位（确定了停止位长度）
4. 校验位（校验方式）
   
#### uart 传输过程
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220115140913.png)
上图是发送端通过Tx引脚控制电平，从而发送字符'A'的过程  
发送的是'A'的ASCII码 01000001，从最低位1开始发送（从右向左）  


1. tx默认一直保持1（高电平）
2. 此时要发送数据了
   1. 发送端拉低tx到0（低电平），保持1bit时间t（由波特率确定）
   2. 同时接收端感知到tx变成了0，开始计时，时长达到t后，开始读取有效数据
3. 传输有效数据
   1. 通过上面的开始位确认后，两端时序都同步了
   2. 发送端一位一位发送数据，每位保持时间t
   3. 同时接收端一位一位接受数据，接收每一位数据（每一位读取时长为t）
4. 校验位（不设置/奇/偶校验）
   1. 不设置，将跳过，那这一位就是停止位
   2. 奇校验，若有效数据中1的个数为奇数，则校验位填0，反之填1
   3. 偶校验，若有效数据中1的个数为偶数，则校验位填0，反之填1
5. 停止位
   1. 把tx拉高持续一定bit时间（到底几个bit由约定好的停止位长度确定）
<br>  

#### 不同设备的逻辑电平
LSB 表示数据中最低位  
MSB 表示数据中最高位
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220115144640.png)
TTL/CMOS 电压低，不适合长距离传输  

![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220115144914.png)
RS232 适合长距离传输，但他的电压大，而且是反过来的，所以需要电平转换芯片，看下图
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220115145258.png)
TTL：集成电路的全名是晶体管-晶体管逻辑集成电路（Transistor-Transistor Logic)
