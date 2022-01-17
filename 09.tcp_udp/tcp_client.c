#include <arpa/inet.h>
#include <linux/in.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */
#include <unistd.h>

#define SERVER_PORT 8888

/**
 * @brief
 *
 * socket
 * connect
 * send/recv
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv) {
    int mSocket = socket(AF_INET, SOCK_STREAM, 0);
    int ret;

    if (argc != 2) {
        printf("Usage:\n");
        printf("%s <server_ip>\n", argv[0]);
        return -1;
    }

    // connect
    // int connect(int sockfd, const struct sockaddr *addr,
    //                   socklen_t addrlen);
    struct sockaddr_in tSocketServerAddr;
    tSocketServerAddr.sin_family = AF_INET;
    tSocketServerAddr.sin_port = htons(SERVER_PORT);
    if (0 == inet_aton(argv[1], &tSocketServerAddr.sin_addr)) {
        printf("invlid server_ip\n");
        return -1;
    }
    memset(tSocketServerAddr.sin_zero, 0, 8);

    ret = connect(mSocket, (struct sockaddr*)&tSocketServerAddr,
                  sizeof(struct sockaddr));

    if( -1 == ret) {
        printf("connect error\n");
        return -1;
    }

    unsigned char sendBuf[1000];
    while(1) {
        //接收控制台输入
        printf("please input data to send:");
        if(fgets(sendBuf,999,stdin)) {
            //ssize_t send(int sockfd, const void *buf, size_t len, int flags);
            int sendLen = send(mSocket,sendBuf,strlen(sendBuf),0);
            if(sendLen <=0) {
                close(mSocket);
                printf("send error\n");
                return -1;
            }
        }
    }
    close(mSocket);
    return 0;
}