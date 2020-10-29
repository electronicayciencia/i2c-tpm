GCCOPTS=-DLOG_USE_COLOR

all: tcp2i2c

clean:
	rm -f tcp2i2c
	rm -f *.o

tpm_tcp.o: tpm_tcp.c tpm_tcp.h
	gcc $(GCCOPTS) -c -o tpm_tcp.o tpm_tcp.c

log.o: log.c log.h
	gcc $(GCCOPTS) -c -o log.o log.c

mock_i2c.o: mock_i2c.c mock_i2c.h
	gcc $(GCCOPTS) -c -o mock_i2c.o mock_i2c.c

tcp2i2c.o: tcp2i2c.c tcp2i2c.h
	gcc $(GCCOPTS) -c -o tcp2i2c.o tcp2i2c.c

tcp2i2c: tcp2i2c.o tcp2i2c.o mock_i2c.o mock_i2c.o log.o
	gcc $(GCCOPTS) -o tcp2i2c tcp2i2c.o log.o tpm_tcp.o mock_i2c.o

