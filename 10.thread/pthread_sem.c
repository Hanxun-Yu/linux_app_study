#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

static pthread_mutex_t g_tMutex = PTHREAD_MUTEX_INITIALIZER;  //互斥锁
static pthread_cond_t g_tConVar = PTHREAD_COND_INITIALIZER;   //条件变量

static sem_t g_sem;

static unsigned char g_input_buf[1000];

static void* thread_B(void* data) {
    while (1) {
        printf("thread_B waiting...\n");
        //等待信号量，休眠
        sem_wait(&g_sem);
        // sleep(1);
        printf("thread_B recv:%s\n", g_input_buf);

    }
}

/**
 * @brief 
 * 为了避免线程B等待中，死循环耗cpu
 * 使用信号量机制，使线程休眠
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char** argv) {
    //初始化信号量
    sem_init(&g_sem, 0, 0);

    //创建接受线程B
    pthread_t tid_B;
    int ret = pthread_create(&tid_B, NULL, thread_B, NULL);
    //成功返回0
    if (ret) {
        printf("create thread error\n");
        return -1;
    }
    //主线程A，接收用户输入，发给线程B
    while (1) {
        printf("thread_mainA input:\n");

        fgets(g_input_buf, 1000, stdin);
        //通知
        sem_post(&g_sem);
    }
    return 0;
}