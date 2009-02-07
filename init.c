/* This file is generated with usbsnoop2libusb.pl from a usbsnoop log file. */
/* Latest version of the script should be in http://iki.fi/lindi/usb/usbsnoop2libusb.pl */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <ctype.h>
#include <usb.h>
#if 0
 #include <linux/usbdevice_fs.h>
 #define LIBUSB_AUGMENT
 #include "libusb_augment.h"
#endif

struct usb_dev_handle *devh;

void release_usb_device(int dummy) {
    int ret;
    ret = usb_release_interface(devh, 0);
    if (!ret)
	printf("failed to release interface: %d\n", ret);
    usb_close(devh);
    if (!ret)
	printf("failed to close interface: %d\n", ret);
    exit(1);
}

struct usb_device *find_device(int vendor, int product) {
    struct usb_bus *bus;
    
    for (bus = usb_get_busses(); bus; bus = bus->next) {
	struct usb_device *dev;
	
	for (dev = bus->devices; dev; dev = dev->next) {
	    if (dev->descriptor.idVendor == vendor
		&& dev->descriptor.idProduct == product)
		return dev;
	}
    }
    return NULL;
}

int main(int argc, char **argv) {
    int ret, vendor, product;
    struct usb_device *dev;
    char buf[65535], *endptr;

    usb_init();
    usb_find_busses();
    usb_find_devices();

    // vendor and product code for Sony alpha 700
    vendor  = 0x054c;
    product = 0x02e7;
    dev = find_device(vendor, product);
    assert(dev);

    devh = usb_open(dev);
    assert(devh);
    
    signal(SIGTERM, release_usb_device);

    ret = usb_get_driver_np(devh, 0, buf, sizeof(buf));
    ret = usb_claim_interface(devh, 0);
    if (ret != 0) {
	printf("claim failed with error %d\n", ret);
	exit(1);
    }
    
    ret = usb_set_altinterface(devh, 0);
    assert(ret >= 0);

    ret = usb_get_descriptor(devh, 0x0000001, 0x0000000, buf, 0x0000012);
    usleep(4*1000);
    ret = usb_get_descriptor(devh, 0x0000002, 0x0000000, buf, 0x0000009);
    usleep(3*1000);
    ret = usb_get_descriptor(devh, 0x0000002, 0x0000000, buf, 0x0000027);
    usleep(4*1000);
    ret = usb_release_interface(devh, 0);
    if (ret != 0) printf("failed to release interface before set_configuration: %d\n", ret);
    ret = usb_set_configuration(devh, 0x0000001);
    ret = usb_claim_interface(devh, 0);
    if (ret != 0) printf("claim after set_configuration failed with error %d\n", ret);
    ret = usb_set_altinterface(devh, 0);

    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x02\x10\x00\x00\x00\x00\x01\x00\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    if (buf[6] == 1) {
        printf("not yet initialized, initializing ...\n");
    }
    else {
        printf("already initialized, no need to do it again\n");
        exit(0);
    }
    printf("\n");
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
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x06\x00\x00\x00\x01\xd2\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    usleep(5*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(5*1000);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x07\x00\x00\x00\x03\xd2\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    usleep(7*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(5*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(6*1000);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x08\x00\x00\x00\x05\x50\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    usleep(5*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(10*1000);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x09\x00\x00\x00\x13\x50\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(6*1000);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x0a\x00\x00\x00\x04\x50\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    usleep(5*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(6*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(5*1000);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x06\x92\x0b\x00\x00\x00\x10\xd2\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(5*1000);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x0c\x00\x00\x00\x11\xd2\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    usleep(6*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(6*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(6*1000);
    memcpy(buf, "\x10\x00\x00\x00\x01\x00\x06\x92\x0d\x00\x00\x00\x0f\xd2\x00\x00", 0x0000010);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
    usleep(3*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(5*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    usleep(4*1000);
    memcpy(buf, "\x18\x00\x00\x00\x01\x00\x01\x92\x0e\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 0x0000018);
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