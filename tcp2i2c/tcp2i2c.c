/*
	C socket server example copied from:
	https://www.binarytides.com/server-client-example-c-sockets-linux/
*/

#include "tcp2i2c.h"
#include "tpm_tcp.h"

int deal_with_client(int socket) {
	tpm_frame_t frame;

	if (tcp_get_frame(socket, &frame) < 0) {
		log_warn("Invalid frame received.");
		return -1;
	}

	//i2c_send_frame(i2c, &frame)
	//free(frame.data);
	
	// reuse frame struct
	//i2c_get_response(i2c, &frame)

	tcp_write_frame(socket, &frame);
	free(frame.data);
	
	//write(socket, "Ok\n", 3);
	log_trace("Ok");
	
	return 0;
}





int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c;
	struct sockaddr_in server , client;
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		perror("Critical: Could not create socket. Error");
		return 1;
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("Critical: bind failed. Error");
		return 1;
	}
	
	while(1) {
		//Listen
		listen(socket_desc , 3);
	
		//Accept and incoming connection
		log_info("Waiting for incoming connections...");
		c = sizeof(struct sockaddr_in);
	
		//accept connection from an incoming client
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_sock < 0)
		{
			perror("Error: accept failed");
			return 1;
		}
		log_debug("Connection accepted");
	
		deal_with_client(client_sock);

		close(client_sock);
	}

	return 0;
}





