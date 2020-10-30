
#include "tpm_i2c.h"
#include "log.h" // https://github.com/rxi/log.c


/* Get the header of tpm_frame via TCP socket.
 * Cannot check for errors, always return LEN_HEADER. */
int i2c_get_header(i2c_t i2c, tpm_frame_t* frame) {
	int i;
	unsigned char buffer[LEN_HEADER];
	
	for (i = 0; i < LEN_HEADER; i++) {
		uint8_t byte = i2c_read_byte(i2c);
		i2c_send_bit(i2c, I2C_ACK);
		buffer[i] = byte;
		log_trace("I2C read 0x%02x", byte & 0xFF);
	}

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
	
	log_trace("Tag: 0x%02x, Size: %d, Code: 0x%08x",
		frame->tag, frame->size, frame->code);

	return LEN_HEADER;
}


/* Fill a tpm_frame from the I2C wire.
 * Malloc a buffer if succesful.
 * On failure return -1 (and free the buffer). */
int i2c_get_frame(i2c_t i2c, tpm_frame_t* frame) {
	int i;

	i2c_start(i2c);
	if (i2c_send_byte(i2c, I2C_ADDRESS << 1 | I2C_READ) != I2C_ACK) {
		log_warn("Device not ready");
		i2c_stop(i2c);
		return -1;
	}

	// Get first part, to determine size
	if (i2c_get_header(i2c, frame) <= 0) {
		log_error("i2c: incomplete header.");
		i2c_stop(i2c);
		return -1;
	}

	if (frame->size < LEN_HEADER) {
		log_warn("i2c: illegal size < 10.");
		i2c_stop(i2c);
		return -1;
	}
	else if (frame->size > MAX_SIZE) {
		log_warn("i2c: frame too big (%d), limited to %d bytes.", frame->size, MAX_SIZE);
		frame->size = MAX_SIZE;
	}

	// Reserve memory, let's assume it worked
	frame->data = (char *) malloc(frame->size - LEN_HEADER);
	
	for (i = 0; i < frame->size - LEN_HEADER; i++) {
		uint8_t byte = i2c_read_byte(i2c);
		i2c_send_bit(i2c, I2C_ACK);
		frame->data[i] = byte;
		log_trace("I2C data byte %d/%d read 0x%02x",
			i, 
			frame->size - LEN_HEADER, 
			byte & 0xFF);
	}

	i2c_stop(i2c);
	return 0;
}




/* Send a frame via initialized I2C port 
 * Return -1 on error */
int i2c_write_frame(i2c_t i2c, tpm_frame_t* frame) {
	int i;

	i2c_start(i2c);
	i2c_send_byte(i2c, I2C_ADDRESS << 1 | I2C_WRITE);
	
	// header
	for (i = 0; i < LEN_HEADER; i++) {
		log_trace("I2C sent byte 0x%02x", frame->wire_header[i] & 0xFF);
		if (i2c_send_byte(i2c, frame->wire_header[i]) != I2C_ACK) {
			log_warn("Device didn't ack'ed");
			return -1;
		}
	}
	
	// data
	for (i = 0; i < frame->size - LEN_HEADER; i++) {
		log_trace("I2C sent byte 0x%02x", frame->data[i] & 0xFF);
		if (i2c_send_byte(i2c, frame->data[i]) != I2C_ACK) {
			log_warn("Device didn't ack'ed");
			return -1;
		}
	}

	i2c_stop(i2c);

	return 0;
}


