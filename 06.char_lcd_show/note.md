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

  
#### 代码字符编码
test_charset_ansi.c 代码文件编码为gb2312  
test_charset_utf8.c 代码文件编码为utf8  
执行后发现代码内相同的中文，输出的字节不同  
使用gcc -finput-charset=GB2312 -fexec-charset=UTF-8 把代码内字符串转码为utf-8  
  
show_chinese.c 代码文件编码为utf8  
使用HZK16点阵库需要使用gb2312编码  
故使用-fexec-charset=GB2312来编译  
arm-buildroot-linux-gnueabihf-gcc -fexec-charset=GB2312 show_chinese.c -o show_chinese
