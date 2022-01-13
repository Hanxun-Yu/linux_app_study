#### tslib
一个库，用于方便读取屏幕设备的输入，过滤掉一些杂讯或噪音  
框架流程：
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220113004740.png)
可以配置模块列表，模块可以理解成处理输入数据的处理层  
模块以动态库的形式载入

#### tslib 交叉编译
```shell
#工具链
export ARCH=arm
export CROSS_COMPILE=arm-buildroot-linux-gnueabihf-
export PATH=$PATH:/home/book/100ask_stm32mp157_pro-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin


#注意这里prefix必须为/
./configure --host=arm-buildroot-linux-gnueabihf  --prefix=/
make
make install DESTDIR=$PWD/tmp

#拷贝到工具链中
cd tmp/
cp include/* /home/book/100ask_stm32mp157_pro-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/arm-buildroot-linux-gnueabihf/sysroot/usr/include
cp -d lib/*so*  /home/book/100ask_stm32mp157_pro-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/
```


#### tslib 测试程序
拷贝测试程序到开发板
```
cp  /mnt/tslib-1.21/tmp/lib/*so*  -d     /lib
cp  /mnt/tslib-1.21/tmp/bin/*            /bin
cp  /mnt/tslib-1.21/tmp/etc/ts.conf  -d  /etc
```
