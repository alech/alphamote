/* This file is generated with usbsnoop2libusb.pl from a usbsnoop log file. */
/* Latest version of the script should be in http://iki.fi/lindi/usb/usbsnoop2libusb.pl */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <ctype.h>
#include <usb.h>
#include <getopt.h>
#include "alphamote.h"

void print_bytes(char *bytes, int len) {
    int i;
    if (len > 0) {
	for (i=0; i<len; i++) {
	    printf("%02x ", (int)((unsigned char)bytes[i]));
	}
	printf("\"");
        for (i=0; i<len; i++) {
	    printf("%c", isprint(bytes[i]) ? bytes[i] : '.');
        }
        printf("\"");
    }
}


int main(int argc, char **argv) {
    int ret,  c;
    char buf[65535];
    char *filename = "/tmp/foo.jpg";

    // command line options
    opterr = 0;
    while ((c = getopt(argc, argv, "o:")) != -1) {
        switch (c) {
            case 'o':
                if (optarg != NULL) {
                    filename = optarg;
                }
                break;
        }
    }

    printf("filename: %s", filename);

    init_usb();

    // retrieving image
    usleep(50*1000);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x08\x10\xfa\x06\x00\x00\x01\xc0\xff\xff", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    printf("5469 bulk write returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(6*1000);
    // 5470 contains the filename
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    printf("5470 bulk read returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(2*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    printf("5471 bulk read returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(4*1000);
    ret = usb_interrupt_read(devh, 0x00000083, buf, 0x0000008, 1000);
    printf("5472 interrupt read returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(16*1000);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x09\x10\xfb\x06\x00\x00\x01\xc0\xff\xff", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    printf("5473 bulk write returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(5*1000);
    FILE *out;
    out = fopen("/tmp/foo.jpg", "w"); // TODO - error handling
    // here, the actual image data starts (ignore 12 byte ptp headers)
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 4932);
    int j;
    for (j = 12; j < ret; j++) {
        fputc(buf[j], out);
    }

    while (ret > 0) {
        // something to read left
        ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 4932);
        // append to file
        int i;
        for (i = 0; i < ret; i++) {
            fputc(buf[i], out);
        }
    }
    fclose(out);
    ret = usb_release_interface(devh, 0);
    assert(ret == 0);
    ret = usb_close(devh);
    assert(ret == 0);
    return 0;
}
