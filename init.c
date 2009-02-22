/* This file is generated with usbsnoop2libusb.pl from a usbsnoop log file. */
/* Latest version of the script should be in http://iki.fi/lindi/usb/usbsnoop2libusb.pl */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <ctype.h>
#include <usb.h>
#include "alphamote.h"

int main(int argc, char **argv) {
    int ret;
    char buf[65535];

    init_usb();

    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x02\x10\x00\x00\x00\x00\x01\x00\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    if (buf[6] == 1) {
        printf("initializing ...\n");
    }
    else {
        printf("already initialized, no need to do it again\n");
        exit(0);
    }
    usleep(5*1000);
    memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x01\x10\x01\x00\x00\x00", 0x000000c);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
    usleep(1*1000);
    ret = usb_interrupt_read(devh, 0x00000083, buf, 0x0000008, 1000);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(3*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(5*1000);
    memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x04\x10\x02\x00\x00\x00", 0x000000c);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x03\x10\x03\x00\x00\x00", 0x000000c);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x02\x10\x00\x00\x00\x00\x01\x00\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    usleep(6*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(5*1000);
    memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x01\x10\x01\x00\x00\x00", 0x000000c);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
    usleep(3*1000);
    ret = usb_interrupt_read(devh, 0x00000083, buf, 0x0000008, 1000);
    usleep(3*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(4*1000);
    memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x04\x10\x02\x00\x00\x00", 0x000000c);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
    usleep(8*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(17*1000);
    memcpy(buf, "\x18\x00\x00\x00\x01\x00\x01\x92\x03\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 0x0000018);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000018, 1000);
    usleep(10*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(9*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(10*1000);
    memcpy(buf, "\x18\x00\x00\x00\x01\x00\x01\x92\x04\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 0x0000018);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000018, 1000);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(4*1000);
    memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x02\x92\x05\x00\x00\x00", 0x000000c);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
    usleep(6*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(7*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(6*1000);
    memcpy(buf, "\x18\x00\x00\x00\x01\x00\x01\x92\x06\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 0x0000018);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000018, 1000);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    ret = usb_release_interface(devh, 0);
    assert(ret == 0);
    ret = usb_close(devh);
    assert(ret == 0);
    return 0;
}
