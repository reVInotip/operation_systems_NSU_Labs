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

    int udp_sock_fd;
    struct sockaddr_in server_sockaddr;
    struct sockaddr_in client_sockaddr;
    struct hostent *clientp;
    int port_to_listen;
    size_t client_len;
    char *clientaddrp;

    udp_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock_fd < 0) {
        printf("socket() failed: %s\n", strerror(errno));
        exit(1);
    }

    port_to_listen = atoi(argv[1]);

    memset(&server_sockaddr, 0, sizeof(struct sockaddr_in));

    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(port_to_listen);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;

    if ((bind(udp_sock_fd, (struct sockaddr*) &server_sockaddr, (socklen_t) sizeof(server_sockaddr))) < 0) {
        printf("bind() failed: %s\n", strerror(errno));
        close(udp_sock_fd);
        exit(1);
    } 


    client_len = sizeof(client_sockaddr);
    char buffer[BUFFER_SIZE];
    int n;
    while (1) {
        printf("Listen\n");
        memset(buffer, 0, BUFFER_SIZE);
		n = recvfrom(udp_sock_fd, buffer, BUFFER_SIZE, 0,
			     (struct sockaddr *)&client_sockaddr, (socklen_t*) &client_len);
                 
		if (n < 0) {
			printf("recvfrom() failed: %s\n", strerror(errno));
            close(udp_sock_fd);
            exit(1);
        }

		clientp = gethostbyaddr((const char *)&client_sockaddr.sin_addr.s_addr,
				      sizeof(client_sockaddr.sin_addr.s_addr),
				      AF_INET);
		if (clientp == NULL) {
            printf("recvfrom() failed: %s\n", strerror(errno));
            close(udp_sock_fd);
            exit(1);
        }

		clientaddrp = inet_ntoa(client_sockaddr.sin_addr);
		if (clientaddrp == NULL) {
            printf("inet_ntoa() failed: %s\n", strerror(errno));
            close(udp_sock_fd);
            exit(1);
        }
		printf("server received %d bytes with message: %s\n", n, buffer);

		n = sendto(udp_sock_fd, buffer, n, 0,
			   (struct sockaddr *)&client_sockaddr, (socklen_t) client_len);
		if (n < 0) {
			printf("send_to() failed: %s\n", strerror(errno));
            close(udp_sock_fd);
            exit(1);
        }
    }
}