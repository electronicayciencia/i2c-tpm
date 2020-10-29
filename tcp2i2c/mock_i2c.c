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


/* Initializes software emulated i2c */
i2c_t i2c_init(int scl, int sda) {
	i2c_t port;
	printf("I2C: initialized");

	port.scl = scl;
	port.sda = sda;

	i2c_reset(port);

	return port;
}

/* Start: pull SDA while SCL is up*/
/* Best practice is to ensure the bus is not busy before start */
void i2c_start(i2c_t port) {
	printf("I2C: start");
}

/* Stop: release SDA while SCL is up */
void i2c_stop(i2c_t port) {
	printf("I2C: stop");
}

/* Reset bus sequence */
void i2c_reset(i2c_t port) {
	printf("I2C: reset");
	i2c_stop(port);
}


/* Sends 8 bit in a row, MSB first and reads ACK.
 * Returns I2C_ACK if device ack'ed */
int i2c_send_byte(i2c_t port, uint8_t byte) {
	printf("I2C: send 0x%x", byte);
}

/* Reads a byte, MSB first */
uint8_t i2c_read_byte(i2c_t port) {
	return 0x00;
}

