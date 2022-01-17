#### GCC编译过程
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20211231115449.png)


#### 常用选项  
-E	预处理，开发过程中想快速确定某个宏可以使用“-E  -dM”  
-S  汇编  
-c	把预处理、编译、汇编都做了，但是不链接  
-o	指定输出文件  
-I	指定头文件目录  
-L	指定链接时库文件目录  
-l	指定链接哪一个库文件  
-v  输出编译过程  



#### 制作、使用动态库
gcc -c -o main.o main.c  
gcc -c -o sub.o sub.c  
gcc -shared  -o libsub.so  sub.o  sub2.o  sub3.o (生成.so动态库) (可以使用多个.o生成动态库)  
gcc -o test main.o  -lsub  -L <libsub.so所在目录>  

#运行时，需要把so库放到系统库目录下，或像下面添加一个环境变量
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<libsub.so所在目录>  
  

  
#### 制作、使用静态库
gcc -c -o main.o  main.c
gcc -c -o sub.o   sub.c
ar  crs  libsub.a  sub.o  sub2.o  sub3.o (生成.a静态库) (可以使用多个.o生成静态库)
gcc  -o  test  main.o  libsub.a  (如果.a不在当前目录下，需要指定它的绝对或相对路径)  


#### 常用命令
gcc -E main.c   // 查看预处理结果，比如头文件是哪个  
gcc -E -dM main.c  > 1.txt  // 把所有的宏展开，存在1.txt里  
gcc -Wp,-MD,abc.dep -c -o main.o main.c  // 生成依赖文件abc.dep，后面Makefile会用  
echo 'main(){}'| gcc -E -v -  // 它会列出头文件目录、库目录(LIBRARY_PATH)  


