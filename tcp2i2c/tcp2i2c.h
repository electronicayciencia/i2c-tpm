#ifndef H1_H__
#define H1_H__

#include <stdint.h> // uint16_t
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>	// inet_addr
#include <stdlib.h> // exit, free
#include <unistd.h> // close

#define MAX_SIZE 0x1fff
#define LEN_HEADER 10

typedef struct {
   uint16_t tag;
   uint32_t size; // Total number of input bytes including size and tag
   uint32_t code; // command code / result code
   char* data;    // may be empty
   char wire_header[LEN_HEADER]; // header as seen in the wire
} tpm_frame_t;


#endif /* h1.h */

