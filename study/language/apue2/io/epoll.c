#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EVENTS 100

int set_socket_nonblocking(int fd){
	int opts = fcntl(fd, F_GETFL, 0);
	if(opts < 0){
		printf("fcntl failed: %s\n", strerror(errno));
		return -1;
	}
	opts = opts | O_NONBLOCK;
	if(fcntl(fd, F_SETFL, opts) < 0){
		printf("fcntl failed: %s\n", strerror(errno));
		return -1;
	}
	return 0;
}

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

	struct epoll_event event;
	struct epoll_event *events;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9734);
    server_len = sizeof(server_address);

    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    listen(server_sockfd, 5);

	int ans = set_socket_nonblocking(server_sockfd);
	if(ans < 0){
		return 1;
	}

	int efd = epoll_create1(0);
	if(efd == -1){
		perror("epoll create: ");
		return 1;
	}

	event.data.fd = server_sockfd;
	event.events = EPOLLIN | EPOLLET;
	ans = epoll_ctl(efd, EPOLL_CTL_ADD, server_sockfd, &event);
	if(ans == -1){
		perror("epoll_ctl: ");
		return 1;
	}

	events = (struct epoll_event *)calloc(MAX_EVENTS, sizeof(struct epoll_event));

    while(1) {
        char ch;
        int nread;
		int n = epoll_wait(efd, events, MAX_EVENTS, -1);

		for(int i = 0; i < n; i++){
			int cfd = events[i].data.fd;
			if(cfd == server_sockfd){
				client_len = sizeof(client_address);
				client_sockfd = accept(server_sockfd, 
					(struct sockaddr *)&client_address, &client_len);
				printf("adding client on fd %d\n", client_sockfd);

				ans = set_socket_nonblocking(client_sockfd);
				if(ans < 0){
					return 1;
				}

				event.data.fd = client_sockfd;
				event.events = EPOLLIN | EPOLLET;
				ans = epoll_ctl(efd, EPOLL_CTL_ADD, client_sockfd, &event);
				if(ans == -1){
					perror("epoll_ctl: ");
					return 1;
				}
			}else{
				ioctl(cfd, FIONREAD, &nread);
				if(nread == 0){
					close(cfd);
					printf("removing client on fd %d\n", cfd);
				}else{
					read(cfd, &ch, 1);
					sleep(1);
					printf("serving client on fd %d\n", cfd);
					ch++;
					write(cfd, &ch, 1);
				}
			}
		}
    }
	free(events);
}
