#include <fcntl.h>
#include <linux/input.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int fd;

const char*(EVENT_TYPE[]) = {
    "EV_SYN", "EV_KEY", "EV_REL", "EV_ABS", "EV_MSC", "EV_SW", "NULL",  "NULL",
    "NULL",   "NULL",   "NULL",   "NULL",   "NULL",   "NULL",  "NULL",  "NULL",
    "NULL",   "EV_LED", "EV_SND", "NULL",   "EV_REP", "EV_FF", "EV_PWR"};

void my_signal_handler(int sig) {
    printf("my_signal_handler sig:%d\n", sig);
    struct input_event event;
    while (read(fd, &event, sizeof(event)) == sizeof(event)) {
        printf("read event type=0x%x, code=0x%x, value=0x%x\n", event.type,
               event.code, event.value);
    }
}

/**
 * @brief
 *  #compile
 *   gcc 02_input_read.c -o 02_input_read
 *
 *   #run
 *   sudo ./04_input_read_fasync /dev/input/event0
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv) {
    int err;
    struct input_id id;
    unsigned int evbit[2];

    if (argc != 2) {
        printf("Usage:%s <dev>\n", argv[0]);
        return -1;
    }

    //注册信号处理函数
    signal(SIGIO, my_signal_handler);

    //打开驱动程序
    fd = open(argv[1], O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        printf("open error:%s\n", argv[1]);
        return -1;
    }

    //把app进程告诉驱动程序
    fcntl(fd, F_SETOWN, getpid());

    //使能”异步通知“
    int flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | FASYNC);

    int loop_count = 0;
    while (1) {
        printf("main loop %d\n", loop_count++);
        sleep(2);
    }

    return 0;
}
