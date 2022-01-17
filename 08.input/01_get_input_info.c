#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

const char*(EVENT_TYPE[]) = {
    "EV_SYN", "EV_KEY", "EV_REL", "EV_ABS", "EV_MSC", "EV_SW", "NULL",  "NULL",
    "NULL",   "NULL",   "NULL",   "NULL",   "NULL",   "NULL",  "NULL",  "NULL",
    "NULL",   "EV_LED", "EV_SND", "NULL",   "EV_REP", "EV_FF", "EV_PWR"};

/**
 * @brief 不使用系统API获得设备信息
 *  /dev/input/event0
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

    if (argc != 2) {
        printf("Usage:%s <dev>\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDONLY);
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
                //看byte中是1的位有哪些
                if (byte & (1 << bit)) {
                    printf("%s\n", EVENT_TYPE[i * 8 + bit]);
                }
            }
        }
    }

    return 0;
}

// compile
// gcc 01_get_input_info.c -o 01_get_input_info
// run
//./01_get_input_info /dev/input/event0