#### 文字编码
1. ASCII  
1个字节表示1个字符，最高位位0,即只表示128个字符，缺点：太少了
2. ANSI  
ASCII的扩展，是windows为不同国家定义的字符集，但是同一个ANSI值在同一个国家不同地区又有不同的编码方式，比如同一个ANSI值在GB2312和BIG5中表示的字不同  
3. UNICODE
统一字符集，1个字符唯一对应1个值
    1. utf-16 LE ：2个字节表示1个字符，小端存放
    2. utf-16 BE ：2个字节表示1个字符，大端存放  
    以上2中unicode无法表示3个字节的字符，且容错性差  
    3. utf-8 ：可变长的编码方案
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220107170517.png)
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220107201811.png)

#### 文字显示
1. ASCII  
源码位置：lib\fonts\font_8x16.c
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220107170743.png)

2. 中文
显示原理同ASCII