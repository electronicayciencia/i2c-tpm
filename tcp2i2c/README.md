# TCP to I2C bridge

This software is a TCP to i2c bridge. It listen to a TCP port for TSCD frames, resend them to a TPM using bit-banged I2C protocol. Waits for the device to answer and send the response back to TSCD.

## Build

You can set some defaults while building editing Makefile.

**LOG_LEVEL**: set the log level according to <https://github.com/rxi/log.c> library.

**I2C_MOCK**: use simulated i2c library instead real one. Useful to test using other box a then deploy in raspberry.

You can edit tcp2i2c.h for some other options.

To build, use `make`. You will need WiringPi library.


## Run

Run the binary:

    $ ./tcp2i2c
    11:27:42 INFO  tcp2i2c.c:96: TPM TCP to I2C bridge by electronicaYciencia.
    11:27:42 INFO  tcp2i2c.c:97: Listening on port 8888.

Send a frame to the listening IP and port, like, for example a startup command:

    $ echo -ne "\x00\xC1\x00\x00\x00\x0C\x00\x00\x00\x99\x00\x01" | netcat 192.168.1.121 8888 | hd
    00000000  00 c4 00 00 00 0a 00 00  00 00                    |..........|
    0000000a

Bridge writes some info:

    19:07:35 INFO:  --> tag: 0x00c1 (TPM_TAG_RQU_COMMAND), size: 12 bytes, ordinal: 0x00000099 (TPM_ORD_Startup)
    19:07:35 WARN: Device not ready (try 1 of 10)
    19:07:35 WARN: Device not ready (try 2 of 10)
    19:07:35 WARN: Device not ready (try 3 of 10)
    19:07:35 WARN: Device not ready (try 4 of 10)
    19:07:35 INFO:  <-- tag: 0x00c4 (TPM_TAG_RSP_COMMAND), size: 10 bytes, return code: 0x00000000 (TPM_SUCCESS)

