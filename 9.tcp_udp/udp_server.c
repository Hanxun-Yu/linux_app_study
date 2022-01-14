#include <arpa/inet.h>
#include <linux/in.h>
#include <netinet/in.h>
#include <signal.h>
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
 * bind
 * recvfrom
 * sendto
 *
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv) {
    //解决僵尸子进程
    signal(SIGCHLD, SIG_IGN);  //忽略,将自动解决僵尸子进程
    // signal(SIGCHLD,handleChildProcessDied); //还是会有僵尸进程

    // socket
    // int socket(int domain, int type, int protocol);
    // SOCK_STREAM 表示tcp方式
    int mSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == mSocket) {
        printf("socket error\n");
        return -1;
    }

    // bind
    struct sockaddr_in tSocketServerAddr;
    tSocketServerAddr.sin_family = AF_INET;
    tSocketServerAddr.sin_port = htons(SERVER_PORT);
    tSocketServerAddr.sin_addr.s_addr = INADDR_ANY;
    // htonl(INADDR_ANY);  // INADDR_ANY 表示本机所有ip
    memset(tSocketServerAddr.sin_zero, 0, 8);

    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    int bindRet = bind(mSocket, (struct sockaddr*)&tSocketServerAddr,
                       sizeof(struct sockaddr_in));
    if (-1 == bindRet) {
        printf("bind error\n");
        return -1;
    }

    // accept
    // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    while (1) {
        /**
         * @ ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                        struct sockaddr *src_addr, socklen_t *addrlen);
         */
        struct sockaddr_in tSocketClientAddr;
        socklen_t addrlen = sizeof(struct sockaddr_in);
        unsigned char recvBuff[1000];
        int recvLen = recvfrom(mSocket, recvBuff, 999, 0,
                               (struct sockaddr*)&tSocketClientAddr,&addrlen);

        if (recvLen <= 0) {
            printf("recv error. client %s\n",
                   inet_ntoa(tSocketClientAddr.sin_addr));
            close(mSocket);
            return -1;
        } else {
            recvBuff[recvLen] = '\0';
            printf("recv msg from %s msg:%s\n",
                   inet_ntoa(tSocketClientAddr.sin_addr), recvBuff);
        }
    }

    close(mSocket);
    return 0;
}