src = $(wildcard *.c)
obj = $(src:.c=.o)
hdr = $(src:.c=.h)

CFLAGS = -DLOG_USE_COLOR -g
LDFLAGS = 

tcp2i2c: $(obj) $(hdr)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) tcp2i2c

