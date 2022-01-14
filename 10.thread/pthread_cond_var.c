#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static pthread_mutex_t g_tMutex = PTHREAD_MUTEX_INITIALIZER;  //互斥锁
static pthread_cond_t g_tConVar = PTHREAD_COND_INITIALIZER;   //条件变量

static unsigned char g_input_buf[1000];

static void* thread_B(void* data) {
    while (1) {
        pthread_mutex_lock(&g_tMutex);
        printf("thread_B waiting...\n");
        pthread_cond_wait(&g_tConVar, &g_tMutex);
        // sleep(1);
        printf("thread_B recv:%s\n", g_input_buf);

        pthread_mutex_unlock(&g_tMutex);
    }
}

int main(int argc, char** argv) {
    //创建接受线程B
    pthread_t tid_B;
    int ret = pthread_create(&tid_B, NULL, thread_B, NULL);
    //成功返回0
    if (ret) {
        printf("create thread error\n");
        return -1;
    }

    //这里休眠以下，让线程B启动
    sleep(0.1);
    //主线程A，接收用户输入，发给线程B
    while (1) {
        printf("thread_mainA input:");

        //先写入临时buf
        unsigned char tempBuf[1000];
        fgets(tempBuf, 1000, stdin);

        pthread_mutex_lock(&g_tMutex);
        //访问互斥量时，需加锁
        memcpy(g_input_buf,tempBuf,sizeof(tempBuf));
        pthread_cond_signal(&g_tConVar);
        pthread_mutex_unlock(&g_tMutex);

    }
    return 0;
}