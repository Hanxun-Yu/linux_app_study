#include <arpa/inet.h>
#include <linux/in.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */
#include <unistd.h>
#include <signal.h>

#define SERVER_PORT 8888
#define BACKLOG 10


// void handleChildProcessDied(int signal) {
//     printf("handleChildProcessDied signal:%d\n",signal);
// }

/**
 * @brief socket server
 *
 * socket
 * bind
 * listen
 * accept
 * send/recv
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv) {

    //解决僵尸子进程
    signal(SIGCHLD,SIG_IGN); //忽略,将自动解决僵尸子进程
    // signal(SIGCHLD,handleChildProcessDied); //还是会有僵尸进程

    // socket
    // int socket(int domain, int type, int protocol);
    // SOCK_STREAM 表示tcp方式
    int mSocket = socket(AF_INET, SOCK_STREAM, 0);
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

    // listen
    // int listen(int sockfd, int n); n表示允许连接数
    int listenRet = listen(mSocket, BACKLOG);
    if (-1 == listenRet) {
        printf("listen error\n");
        return -1;
    }

    // accept
    // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    int clientNum = -1;
    while (1) {
        // client ip
        struct sockaddr_in tSocketClientAddr;
        socklen_t addrlen = sizeof(struct sockaddr_in);
        int socketClient = accept(
            mSocket, (struct sockaddr*)&tSocketClientAddr, &addrlen);
        if (socketClient != -1) {
            clientNum++;

            printf("Accept client %d %s\n", clientNum,
                   inet_ntoa(tSocketClientAddr.sin_addr));
            // fork() 返回0 表示子进程   1表示父进程
            if (!fork()) {
                //子
                unsigned char recvBuff[1000];
                int recvLen = 0;
                while (1) {
                    // ssize_t recv(int sockfd, void *buf,size_t len, int
                    // flags);

                    //最多接受999个字节
                    recvLen = recv(socketClient, recvBuff, 999, 0);
                    if (recvLen <= 0) {
                        printf("recv error. client %d %s\n", socketClient,
                               inet_ntoa(tSocketClientAddr.sin_addr));
                        close(socketClient);
                        return -1;
                    } else {
                        recvBuff[recvLen] = '\0';
                        printf("recv msg from %d %s msg:%s\n", clientNum,
                               inet_ntoa(tSocketClientAddr.sin_addr),
                               recvBuff);
                    }
                }
            }
            {
                //父
            }
        }
    }

    close(mSocket);
    return 0;
}