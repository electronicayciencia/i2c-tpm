
#include "translation.h"
#include "tpm_tcp.h"
#include "log.h" // https://github.com/rxi/log.c

/* Read N bytes from TCP socket.
 * Die on failure */
ssize_t tcp_recv_or_die(int sockfd, char *buf, size_t len) {
	int readed = recv(sockfd, buf, len, MSG_WAITALL);
	
	if(readed == -1) {
		perror("Error: recv failed");
		exit(1);
		return -1;
	}
	
	log_debug("Received %d bytes.", readed);
	return readed;
}


/* Get the header of tpm_frame via TCP socket.
 * Return -1 if invalid header */
int tcp_get_header(int socket, tpm_frame_t* frame) {
	unsigned char buffer[LEN_HEADER];
	ssize_t readed = tcp_recv_or_die(socket, buffer, LEN_HEADER);

	if (readed < LEN_HEADER)
		return -1;
	
	frame->tag = buffer[0+0] * 0x100 +
	             buffer[0+1] * 0x1;
	
	frame->size = buffer[2+0] * 0x1000000 +
	              buffer[2+1] * 0x10000 +
	              buffer[2+2] * 0x100 +
	              buffer[2+3] * 0x1;

	frame->code = buffer[6+0] * 0x1000000 +
	              buffer[6+1] * 0x10000 +
	              buffer[6+2] * 0x100 +
	              buffer[6+3] * 0x1;

	memcpy(frame->wire_header, buffer, LEN_HEADER);

	log_info(" --> tag: 0x%04x (%s), size: %d bytes, ordinal: 0x%08x (%s)",
		frame->tag, 
		tpmtag_to_text(frame->tag), 
		frame->size, 
		frame->code, 
		ord_to_text(frame->code));

	return readed;
}


/* Get the data of tpm_frame into the reserved buffer via TCP 
 * Return -1 if unexpected end of data */
int tcp_get_the_rest(int socket, tpm_frame_t* frame) {
	if (frame->size - LEN_HEADER <= 0)
		return 0;

	ssize_t readed = tcp_recv_or_die(
		socket, 
		frame->data, 
		frame->size - LEN_HEADER);

	log_debug("Read %ld bytes of data, expected %d.", 
		readed, frame->size - LEN_HEADER);
	
	if (readed < frame->size - LEN_HEADER) {
		log_warn("Unexpected end of data.");
		return -1;
	}
	
	return readed;
}


/* Fill a tpm_frame from the TCP socket.
 * Malloc a buffer if succesful.
 * On failure return -1 (and free the buffer). */
int tcp_get_frame(int socket, tpm_frame_t* frame) {
	// Get first part, to determine size
	if (tcp_get_header(socket, frame) <= 0) {
		log_error("Incomplete header.");
		return -1;
	}

	if (frame->size < LEN_HEADER) {
		log_warn("Illegal size < 10.");
		return -1;
	}
	else if (frame->size > MAX_SIZE) {
		log_warn("Frame too big (%d), limited to %d bytes.", frame->size, MAX_SIZE);
		frame->size = MAX_SIZE;
	}

	// Reserve memory, let's assume it worked
	frame->data = (char *) malloc(frame->size - LEN_HEADER);
	if (tcp_get_the_rest(socket, frame) < 0) {
		log_warn("Incomplete frame.");
		free(frame->data);
		return -1;
	}

	return 0;
}



int tcp_write_frame(int socket, tpm_frame_t* frame) {
	write(socket, frame->wire_header, LEN_HEADER);
	write(socket, frame->data, frame->size - LEN_HEADER);
}




