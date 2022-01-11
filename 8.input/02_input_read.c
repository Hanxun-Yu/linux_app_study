#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

const char*(EVENT_TYPE[]) = {
    "EV_SYN", "EV_KEY", "EV_REL", "EV_ABS", "EV_MSC", "EV_SW", "NULL",  "NULL",
    "NULL",   "NULL",   "NULL",   "NULL",   "NULL",   "NULL",  "NULL",  "NULL",
    "NULL",   "EV_LED", "EV_SND", "NULL",   "EV_REP", "EV_FF", "EV_PWR"};

/**
 * @brief
 *  #compile
 *   gcc 02_input_read.c -o 02_input_read
 *
 *   #run  加上noblock参数，将会异步获取设备输入
 *   sudo ./02_input_read /dev/input/event1 noblock
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv) {
    int fd;
    int err;
    int len;
    struct input_id id;
    unsigned int evbit[2];

    if (argc < 2) {
        printf("Usage:%s <dev> [noblock]\n", argv[0]);
        return -1;
    }

    // strcmp(strA,strB),若strA==strB则返回0
    if (argc == 3 && !strcmp(argv[2], "noblock")) {
        fd = open(argv[1], O_RDONLY | O_NONBLOCK);

    } else {
        fd = open(argv[1], O_RDONLY);
    }
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

    len = ioctl(fd, EVIOCGBIT(0, sizeof(evbit)), &evbit);
    if (len > 0 && len <= sizeof(evbit)) {
        unsigned char byte;
        for (int i = 0; i < len; i++) {
            //这里先把evbit强转成byte，这样在使用evbit[i]就会按byte偏移
            byte = ((unsigned char*)evbit)[i];

            for (int bit = 0; bit < 8; bit++) {
                if (byte & (1 << bit)) {
                    printf("%s\n", EVENT_TYPE[i * 8 + bit]);
                }
            }
        }
    }

    struct input_event event;
    while(1) {
        //不加noblock，下面read将阻塞进程将休眠，直到有输入 （休眠唤醒机制）
        //加上noblock参数，下面将立即返回 （轮询方式）
        len = read(fd,&event,sizeof(event));
        if(len == sizeof(event)) {
            printf("read event type=0x%x, code=0x%x, value=0x%x\n",event.type,event.code,event.value);
        } else {
            printf("read error\n");
        }
    }

    close(fd);

    return 0;
}
