#include <fcntl.h>
#include <linux/input.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const char*(EVENT_TYPE[]) = {
    "EV_SYN", "EV_KEY", "EV_REL", "EV_ABS", "EV_MSC", "EV_SW", "NULL",  "NULL",
    "NULL",   "NULL",   "NULL",   "NULL",   "NULL",   "NULL",  "NULL",  "NULL",
    "NULL",   "EV_LED", "EV_SND", "NULL",   "EV_REP", "EV_FF", "EV_PWR"};

/**
 * @brief
 *  #compile
 *   gcc 03_input_read_poll.c -o 03_input_read_poll
 *
 *   #run 
 *   sudo ./03_input_read_poll /dev/input/event1
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv) {
    int fd;
    int err;
    struct input_id id;
    unsigned int evbit[2];

    if (argc != 2) {
        printf("Usage:%s <dev>\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        printf("open error:%s\n", argv[1]);
        return -1;
    }

    err = ioctl(fd, EVIOCGID, &id);

    if (err == 0) {
        /**
         * struct input_id {
                __u16 bustype;
                __u16 vendor;
                __u16 product;
                __u16 version;
            };
         */
        printf("bustype=0x%x,vendor=0x%x,product=0x%x,version=0x%x\n",
               id.bustype, id.vendor, id.product, id.version);
    }

    // len = ioctl(fd, EVIOCGBIT(0, sizeof(evbit)), &evbit);
    // if (len > 0 && len <= sizeof(evbit)) {
    //     unsigned char byte;
    //     for (int i = 0; i < len; i++) {
    //         //这里先把evbit强转成byte，这样在使用evbit[i]就会按byte偏移
    //         byte = ((unsigned char*)evbit)[i];

    //         for (int bit = 0; bit < 8; bit++) {
    //             if (byte & (1 << bit)) {
    //                 printf("%s\n", EVENT_TYPE[i * 8 + bit]);
    //             }
    //         }
    //     }
    // }

    // poll
    struct pollfd fds[1];
    nfds_t nfds = 1;

    struct input_event event;
    while (1) {
        fds[0].fd = fd;
        fds[0].events = POLLIN;//注册poll事件类型
        fds[0].revents = 0;  //事件出发时被系统赋值

        printf("polling...\n");

        // int poll(struct pollfd *fds, nfds_t nfds, int timeout);
        // poll调用后会开始阻塞，直到有poll事件或timeout
        int pollLen = poll(fds, nfds, 5000);
        printf("poll return\n");

        if (pollLen > 0) {
            if (fds[0].revents == POLLIN) {
                while (read(fd, &event, sizeof(event)) == sizeof(event)) {
                    printf("read event type=0x%x, code=0x%x, value=0x%x\n",
                           event.type, event.code, event.value);
                }
            }
        } else if (pollLen == 0) {
            //超时
            printf("poll timeout\n");
        } else {
            printf("poll error\n");
        }
    }

    close(fd);

    return 0;
}
