src = log.c tcp2i2c.c tpm_i2c.c tpm_tcp.c

CFLAGS = -DLOG_USE_COLOR -g
LDFLAGS =

ifeq ($(shell uname -m), armv7l)
  src := $(src) soft_i2c.c
  CFLAGS = -D_BSD_SOURCE -std=c99 $(CFLAGS)
  LDFLAGS = -lwiringPi $(LDFLAGS)
else
  src := $(src) mock_i2c.c
  CFLAGS := -DI2C_MOCK $(CFLAGS)
endif

obj = $(src:.c=.o)
hdr = $(src:.c=.h)

tcp2i2c: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) tcp2i2c

