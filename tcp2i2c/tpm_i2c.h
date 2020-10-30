#include <string.h> // memcpy
#include <unistd.h> // write
#include <stdlib.h> // free

#include "mock_i2c.h"
#include "tcp2i2c.h"

int i2c_write_frame(i2c_t i2c, tpm_frame_t* frame);
int i2c_get_frame(i2c_t i2c, tpm_frame_t* frame);

