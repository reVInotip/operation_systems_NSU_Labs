#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define BUFFER_SIZE 13

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("too low count args\n");
        exit(1);
    }

    int tcp_sock_fd;
    int client_fd;
    struct sockaddr_in server_sockaddr;
    struct sockaddr_in client_sockaddr;
    struct hostent *clientp;
    int port_to_listen;
    size_t client_len = 0;
    char *clientaddrp;

    tcp_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sock_fd < 0) {
        printf("socket() failed: %s\n", strerror(errno));
        exit(1);
    }

    port_to_listen = atoi(argv[1]);

    memset(&server_sockaddr, 0, sizeof(struct sockaddr_in));

    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(port_to_listen);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;

    if ((bind(tcp_sock_fd, (struct sockaddr*) &server_sockaddr, (socklen_t) sizeof(server_sockaddr))) < 0) {
        printf("bind() failed: %s\n", strerror(errno));
        close(tcp_sock_fd);
        exit(1);
    }

    if (listen(tcp_sock_fd, 5) < 0) {
        printf("listen() failed: %s\n", strerror(errno));
        close(tcp_sock_fd);
        exit(1);
    }

    int pid;
    while (1) {
        client_fd = accept(tcp_sock_fd, (struct sockaddr*) &client_sockaddr, (socklen_t*) &client_len);
        if (client_fd < 0) {
            printf("accept() failed: %s\n", strerror(errno));
            close(tcp_sock_fd);
            exit(1);
        }

        pid = fork();
        if (pid < 0) {
            printf("fork() failed: %s\n", strerror(errno));
            close(tcp_sock_fd);
            exit(1);
        } else if (pid == 0) {
            break;
        }
    }

    client_len = sizeof(client_sockaddr);
    char buffer[BUFFER_SIZE];
    int n;
    while (1) {
        printf("Listen\n");
        memset(buffer, 0, BUFFER_SIZE);
        n = recv(client_fd, buffer, BUFFER_SIZE, 0);

        if (n < 0) {
            printf("recvfrom() failed: %s\n", strerror(errno));
            close(tcp_sock_fd);
            exit(1);
        }
        printf("server received %d bytes with message: %s\n", n, buffer);

        n = send(client_fd, buffer, n, 0);
        if (n < 0) {
            printf("send_to() failed: %s\n", strerror(errno));
            close(tcp_sock_fd);
            exit(1);
        }
    }
}