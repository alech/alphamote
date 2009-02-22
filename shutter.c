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

    init_usb();

    usleep(50*1000);
    // shutter release
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x07\x92\x0e\x05\x00\x00\xc7\xd2\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    printf("3982 bulk write returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(7*1000);
    memcpy(buf, "\x0e\x00\x00\x00\x02\x00\x07\x92\x0e\x05\x00\x00\x02\x00", 0x000000e);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000e, 1000);
    printf("3983 bulk write returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(6*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    printf("3984 bulk read returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(68*1000);
    memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x08\x92\x0f\x05\x00\x00", 0x000000c);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
    printf("3985 bulk write returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    printf("3986 bulk read returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(9*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    printf("3987 bulk read returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(8*1000);
    usleep(8*1000);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x07\x92\x10\x05\x00\x00\xc2\xd2\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    printf("3988 bulk write returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(4*1000);
    memcpy(buf, "\x0e\x00\x00\x00\x02\x00\x07\x92\x10\x05\x00\x00\x01\x00", 0x000000e);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000e, 1000);
    printf("3989 bulk write returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(10*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    printf("3990 bulk read returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(65*1000);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x07\x92\x11\x05\x00\x00\xc1\xd2\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    printf("3991 bulk write returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(5*1000);
    memcpy(buf, "\x0e\x00\x00\x00\x02\x00\x07\x92\x11\x05\x00\x00\x01\x00", 0x000000e);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000e, 1000);
    printf("3992 bulk write returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(3*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    printf("3993 bulk read returned %d, bytes: ", ret);
    print_bytes(buf, ret);
    printf("\n");
    usleep(73*1000);

    ret = usb_release_interface(devh, 0);
    assert(ret == 0);
    ret = usb_close(devh);
    assert(ret == 0);
    return 0;
}
