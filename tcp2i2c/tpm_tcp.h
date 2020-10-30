#include <sys/socket.h>
#include <sys/types.h> // ssize_t
#include <string.h> // memcpy
#include <unistd.h> // write
#include <stdlib.h> // free

#include "tcp2i2c.h"

ssize_t tcp_recv_or_die(int sockfd, char *buf, size_t len);
int tcp_get_header(int socket, tpm_frame_t* frame);
int tcp_get_the_rest(int socket, tpm_frame_t* frame);
int tcp_get_frame(int socket, tpm_frame_t* frame);
int tcp_write_frame(int socket, tpm_frame_t* frame);
