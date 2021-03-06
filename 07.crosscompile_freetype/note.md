#### 头文件/库文件 编译时的搜索路径  
可使用以下命令查看编译时，编译器会去哪里找头文件  
echo 'main(){}' | \<gcc> -E -v -  （这里\<gcc>为实际的交叉编译工具）   
例如 echo 'main(){}'| arm-buildroot-linux-gnueabihf-gcc -E -v -  
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220108204234.png)


#### 程序执行时 动态库搜索路径
系统会默认去 /lib /usr/lib下搜索
也可以自己指定，通过执行：  
export LD_LIBRARY_PATH=\<path>:$LD_LIBRARY_PATH


#### 交叉编译
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220108205354.png)
  
--host= 表示使用的工具连前缀  
//前提是已加入环境变量，像这样：  
//export PATH=$PATH:/home/book/100ask_stm32mp157_pro-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin  

--prefix= 表示make install时编译产物输出的位置

##### 编译后
把编译产物中的头文件和库放到交叉编译工具连内指定目录
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220108211219.png)
这里cp -rfd中的d参数表示复制时保留链接状态

#### freetype矢量字体
矢量字体解决了直接使用点阵显示放大缩小不方便以及锯齿模糊等问题
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220108223645.png)

字体文件内有charmaps，可支持多种字符集，通过字符的编码找到该字符的轮廓信息  
把轮廓信息转换为点阵信息，就可以显示到lcd上了  
这些操作freetype都提供了接口
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220108223928.png)

#### 使用wchar_t
使用wchar_t，宽字符，使代码内声明的字符串以utf-8编码
每个wchar_t占据4字节，可执行程序里wchar_t中保存的就是字符的UNICODE值。
