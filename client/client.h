#ifndef __CLIENT_H
#define __CLIENT_H
/***********************Include header files*/
//standard lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//linux API lib
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>

/*******************************Macro define*/
#define TEST_PORT 9988      //socket connect port
#define MTU_NUM 1400    //length of each socket packet
#define MAX_READ_BUFF_LENGTH 128  
#define SERVER_IP "127.0.0.1"
#define CLIENT_MAX_NUM 8
/******************Declearation of structure*/
/*
typedef struct _thread_arg_struct {
	int socket_fd;
	struct sockaddr_in *socket_struct;
	int struct_len;
}thread_arg_struct;
*/

/*******************Declearation of function*/
void *thread_receive(void *arg);
char *malloc_packet(void);

#endif
