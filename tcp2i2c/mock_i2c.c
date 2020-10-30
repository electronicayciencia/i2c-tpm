/*
 *      This is a mock of my software implementation of I2C protocol 
 *
 *      https://github.com/electronicayciencia/wPi_soft_i2c
 *
 *      Reinoso G.
 */

 
#include <stdint.h>
#include <stdio.h>

#include "mock_i2c.h"

int _mock_i2c_read_pointer = 0;
char _mock_i2c_read_text[] = "\x81\x82\x00\x00\x00\x0c\x01\x01\x01\x01\xaa\xaa";
int _mock_i2c_read_len = 12;

/* Initializes software emulated i2c */
i2c_t i2c_init(int scl, int sda) {
	i2c_t port;
	puts("I2C: initialized");

	port.scl = scl;
	port.sda = sda;

	i2c_reset(port);

	return port;
}

/* Sends 0 or 1: 
 * Clock down, send bit, clock up, wait, clock down again 
 * In clock stretching, slave holds the clock line down in order
 * to force master to wait before send more data */
void i2c_send_bit(i2c_t port, int bit) {
	return;
}

/* Start: pull SDA while SCL is up*/
/* Best practice is to ensure the bus is not busy before start */
void i2c_start(i2c_t port) {
	_mock_i2c_read_pointer = 0;
	puts("I2C: start");
}

/* Stop: release SDA while SCL is up */
void i2c_stop(i2c_t port) {
	_mock_i2c_read_pointer = 0;
	puts("I2C: stop");
}

/* Reset bus sequence */
void i2c_reset(i2c_t port) {
	_mock_i2c_read_pointer = 0;
	puts("I2C: reset");
	i2c_stop(port);
}


/* Sends 8 bit in a row, MSB first and reads ACK.
 * Returns I2C_ACK if device ack'ed */
int i2c_send_byte(i2c_t port, uint8_t byte) {
	_mock_i2c_read_pointer = 0;
	printf("I2C: send 0x%02X\n", byte);
	return I2C_ACK;
}

/* Reads a byte, MSB first */
uint8_t i2c_read_byte(i2c_t port) {
	if (_mock_i2c_read_pointer < _mock_i2c_read_len) {
		return _mock_i2c_read_text[_mock_i2c_read_pointer++];
	}
	else {
		return 0xFF;
	}
}

