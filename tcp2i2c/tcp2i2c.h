#ifndef TCP2I2C_H__
#define TCP2I2C_H__

#include <stdint.h> // uint16_t

#define MAX_SIZE 0x1fff
#define I2C_SCL 24
#define I2C_SDA 23
#define I2C_ADDRESS 0x29
#define TCP_PORT 8888

#define I2C_WAIT_TIME_MS 10
#define I2C_MAX_WAIT_CYCLES 10

#define LEN_HEADER 10

typedef struct {
   uint16_t tag;
   uint32_t size; // Total number of input bytes including size and tag
   uint32_t code; // command code / result code
   uint8_t* data; // may be empty
   uint8_t  wire_header[LEN_HEADER]; // header as seen in the wire
} tpm_frame_t;

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_DEBUG
#endif

#endif /* TCP2I2C_H__ */

