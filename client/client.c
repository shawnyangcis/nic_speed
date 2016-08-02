#include "client.h"

int main(int argc, char **argv)
{
	//define var for thread
	pthread_t thread_receive_id[CLIENT_MAX_NUM];

	printf("Creating thread..\n");
	for(int id_num = 0; id_num < CLIENT_MAX_NUM; ++id_num) {
		if(pthread_create(&thread_receive_id[id_num], NULL, thread_receive, (void *)&id_num) != 0) {
			perror("Thread create failed");
			exit(EXIT_FAILURE);
		}
	}

	printf("Thread create finished. Test running...\n");
	while(1) {
		sleep(10);
		printf("Main process.\n");
	}

	printf("Client process exit.\n");
	exit(EXIT_SUCCESS);
}

void *thread_receive(void *arg)
{
	int seq_num = *(int *)arg;
	int local_sockfd = 0, local_len = 0;
	struct sockaddr_in local_address;

	int rd_res = 0;
	char *recv_buff = NULL;

	if((local_sockfd = socket(AF_INET, SOCK_STREAM, 0 )) < 0) {
		perror("Create socket failed:");
		exit(EXIT_FAILURE);
	}

	local_address.sin_family = AF_INET;
	local_address.sin_addr.s_addr = inet_addr(SERVER_IP);
	local_address.sin_port = htons(TEST_PORT);
	local_len = sizeof(local_address);

	if((recv_buff = malloc_packet()) == NULL) {
		printf("Malloc receive buff error.\n");
		pthread_exit("");
	}
	memset(recv_buff, 0, MTU_NUM);

	if(connect(local_sockfd, (struct sockaddr *)&local_address, local_len) < 0) {
		perror("Connect error");
		free(recv_buff);
		pthread_exit("");
	}

	printf("Connect successfully,seq_num:%d, id:%d\n", seq_num, pthread_self());

	while(1) {
		rd_res = recv(local_sockfd, recv_buff, MTU_NUM, 0);
		if(rd_res == 0) {
			printf("Disconnected, thread seq:%d", seq_num);
			break;
		}
		else if(rd_res < 0) {
			perror("Receive error");
			break;
		}
	}

	free(recv_buff);
	printf("Thread exit, seq:%d\n", seq_num);
	pthread_exit("");
}

char *malloc_packet()
{
	char *malloc_res = NULL;

	malloc_res = (char *)malloc(MTU_NUM * sizeof(char));
	if(malloc_res == NULL) {
		return (char *)NULL;
	}

	memset(malloc_res, 0, MTU_NUM);
	return malloc_res;
}
