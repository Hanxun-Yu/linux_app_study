![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220105143806.png)

##### 查看已挂载信息
```cat /proc/mounts```



##### 挂载SD卡
插入sd卡时查看串口日志，确定设备节点/dev/sd1  
```mount /dev/sd1 /mnt```

##### 挂载虚拟文件
```mount -t sysfs none /mnt```  
<br>

##### 设备文件类型
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220105144425.png)
<br>

##### open/read 内核交互过程
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220105150546.png)
