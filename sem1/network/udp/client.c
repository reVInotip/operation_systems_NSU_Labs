#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 13

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("too low count args\n");
        exit(1);
    }

    int udp_sock_fd;
    struct sockaddr_in server_sockaddr;
    int port_to_send = atoi(argv[2]);
    unsigned serveraddr = inet_addr(argv[1]);

    udp_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock_fd < 0) {
        printf("socket() failed: %s\n", strerror(errno));
        exit(1);
    }

    memset(&server_sockaddr, 0, sizeof(struct sockaddr_in));

    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(port_to_send);
    server_sockaddr.sin_addr.s_addr = serveraddr;

    char message_buffer[BUFFER_SIZE];
    char server_answer_buffer[BUFFER_SIZE];
    int len = BUFFER_SIZE;

    char *message = "Hello world!";
    strcpy(message_buffer, message);

    int n;
    while (1) {
        printf("Send message\n");
        memset(server_answer_buffer, 0, BUFFER_SIZE);

        n = sendto(udp_sock_fd, message_buffer, BUFFER_SIZE, 0,
			   (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr));
		if (n < 0) {
			printf("send_to() failed: %s\n", strerror(errno));
            close(udp_sock_fd);
            exit(1);
        }


		n = recvfrom(udp_sock_fd, server_answer_buffer, BUFFER_SIZE, 0,
			     (struct sockaddr *)&server_sockaddr, &len);
                 
		if (n < 0) {
			printf("recvfrom() failed: %s\n", strerror(errno));
            close(udp_sock_fd);
            exit(1);
        }

		printf("client received %d bytes with message: %s\n", n, server_answer_buffer);
    }
}