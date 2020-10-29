#include <stdio.h>
#include <string.h>	// strlen
#include <sys/socket.h>
#include <arpa/inet.h>	// inet_addr
#include <unistd.h>	// write
#include <stdlib.h> // exit
#include "log.h" // https://github.com/rxi/log.c


#define MAX_SIZE 0x1fff
#define LEN_HEADER 10

typedef struct {
   uint16_t tag;
   uint32_t size; // Total number of input bytes including size and tag
   uint32_t code; // command code / result code
   char* data;    // may be empty
   char wire_header[LEN_HEADER]; // header as seen in the wire
} tpm_frame_t;




