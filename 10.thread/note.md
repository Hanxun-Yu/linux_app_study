#### thread
主要使用这几个函数
```c
#include <pthread.h>

//创建线程
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
     void *(*start_routine) (void *), void *arg;

//互斥
static pthread_mutex_t g_tMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&g_tMutex);
pthread_mutex_unlock(&g_tMutexL);

//同步
static pthread_cond_t g_tConVar = PTHREAD_COND_INITIALIZER; //条件变量

pthread_mutex_lock(&g_tMutex);//线程A加锁
pthread_cond_wait(&g_tConVar,&g_tMutex);//若不成立，将等待条件成立，并释放锁
若成立了，被唤醒，自动加锁
...处理...
pthread_mutex_unlock(&g_tMutex);//线程A解锁


pthread_cond_signal(&g_tConVar);//线程B 唤醒等待g_tConVar条件的线程
```

#### ps查看
可以使用命令查看进程/进程
ps -T #加上-T参数，可以显示线程
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220114172429.png)

#### 查看进程目录
```
cd /proc/21038/task
ls
```
![](https://picbed-xunxun.oss-cn-shanghai.aliyuncs.com/20220114172553.png)

