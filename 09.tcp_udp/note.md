#### tcp
```
gcc tcp_client.c -o tcp_client
gcc tcp_server.c -o tcp_server

./tcp_server
#另起终端
./tcp_client 127.0.0.1
```
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220114162043.png)
图中可以看到，启动tcp_server后，进程号为16715  
tcp_client启动后，连上了server  
server fork出了子进程16751，他的父进程号为16715

这时如果终止client，会产生以下情况
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220114162255.png)
server子进程16751被\<defunct>标记，变成了僵尸进程  
在server中加入signal(SIGCHLD,SIG_IGN); 解决


#### udp
```
gcc udp_client.c -o udp_client
gcc udp_server.c -o udp_server

./udp_server
#另起终端
./udp_client 127.0.0.1
```
在udp_client中，可以使用connect，发送使用send  
也可以不connect，但发送时需要使用sendto 指定目标地址