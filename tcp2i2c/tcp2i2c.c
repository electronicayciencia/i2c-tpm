/*
	C socket server example copied from:
	https://www.binarytides.com/server-client-example-c-sockets-linux/
*/

#include <stdint.h> // uint16_t
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>	// inet_addr
#include <stdlib.h> // exit, free
#include <unistd.h> // close, usleep

#ifndef I2C_MOCK
#include <wiringPi.h> // wiringPiSetup
#endif /* I2C_MOCK */

#include "tcp2i2c.h"
#include "log.h"
#include "tpm_tcp.h"
#include "soft_i2c.h"
#include "tpm_i2c.h"


int deal_with_request(int socket, i2c_t i2c) {
	tpm_frame_t frame;

	if (tcp_get_frame(socket, &frame) < 0) {
		log_warn("Invalid frame received.");
		return -1;
	}

	i2c_write_frame(i2c, &frame);
	free(frame.data);

	usleep(17*1000);
	
	// reuse frame struct
	i2c_get_frame(i2c, &frame);
	tcp_write_frame(socket, &frame);
	free(frame.data);
	
	log_trace("Ok");
	
	return 0;
}



int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server, client;
	
	//Create server socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1) {
		perror("Critical: Could not create socket. Error");
		return 1;
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(TCP_PORT);
	
	int reuse = 1;
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

	#ifdef SO_REUSEPORT
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0) 
        perror("setsockopt(SO_REUSEPORT) failed");
	#endif

	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
		perror("Critical: bind failed. Error");
		return 1;
	}

	//Listen
	listen(socket_desc , 3);
	
	// Prepare I2C communication
	#ifndef I2C_MOCK
	if (wiringPiSetup () == -1)
		return 1;
	#endif /* I2C_MOCK */

	i2c_t i2c = i2c_init(I2C_SCL, I2C_SDA);


	while(1) {
		struct sockaddr_in client;
		int connected_sock;
		int c = sizeof(struct sockaddr_in);

		//Accept and incoming connection
		log_info("Waiting for incoming connections...");
	
		//accept connection from an incoming client
		connected_sock = accept(
			socket_desc, 
			(struct sockaddr *)&client, 
			(socklen_t*)&c);

		if (connected_sock < 0) {
			perror("Error: accept failed");
			return 1;
		}

		log_debug("Connection accepted");
	
		deal_with_request(connected_sock, i2c);

		close(connected_sock);
	}

	i2c_stop(i2c);
	return 0;
}





