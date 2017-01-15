#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <poll.h>
#define OPEN_MAX 100

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9734);
    server_len = sizeof(server_address);

    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    listen(server_sockfd, 5);

	struct pollfd clients[OPEN_MAX];
	int maxindex = 0; // clients 数组当前最大下标

	clients[0].fd = server_sockfd;
	clients[0].events = POLLIN;

	for(int i = 1; i < OPEN_MAX; i++)
		clients[i].fd = -1;

    while(1) {
        char ch;
        int nread;
		int result = poll(clients, maxindex+1, -1);

		if(result == -1){
			perror("poll error");
			exit(1);
		}

		if(clients[0].revents & POLLIN){
			client_len = sizeof(client_address);
			client_sockfd = accept(server_sockfd, 
				(struct sockaddr *)&client_address, &client_len);
			printf("adding client on fd %d\n", client_sockfd);
			int k;
			for(k = 0; k < OPEN_MAX; k++){
				if(clients[k].fd == -1){
					clients[k].fd = client_sockfd;
					clients[k].events = POLLIN;
					break;
				}
			}
			if(k == OPEN_MAX){
				fprintf(stderr, "too many clients\n");
				close(client_sockfd);
				//continue;
			}
			if(k > maxindex){
				maxindex = k;
			}
		}

		for(int i = 1; i <= maxindex; i++){
			int cfd = clients[i].fd;
			if(cfd == -1){
				continue;
			}
			if(clients[i].revents & POLLIN){
				ioctl(cfd, FIONREAD, &nread);
				if(nread == 0){
					close(cfd);
					printf("removing client on fd %d\n", cfd);
					clients[i].fd = -1;
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
}
