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

void list_devices() {
    struct usb_bus *bus;
    for (bus = usb_get_busses(); bus; bus = bus->next) {
	struct usb_device *dev;
	
	for (dev = bus->devices; dev; dev = dev->next)
	    printf("0x%04x 0x%04x\n",
		   dev->descriptor.idVendor,
		   dev->descriptor.idProduct);
    }
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
    int ret, vendor, product;
    struct usb_device *dev;
    char buf[65535], *endptr;
#if 0
    usb_urb *isourb;
    struct timeval isotv;
    char isobuf[32768];
#endif

    usb_init();
    usb_set_debug(255);
    usb_find_busses();
    usb_find_devices();

    if (argc!=3) {
	printf("usage: %s vendorID productID\n", argv[0]);
	printf("ID numbers of currently attached devices:\n");
	list_devices();
	exit(1);
    }
    vendor = strtol(argv[1], &endptr, 16);
    if (*endptr != '\0') {
	printf("invalid vendor id\n");
	exit(1);
    }
    product = strtol(argv[2], &endptr, 16);
    if (*endptr != '\0') {
	printf("invalid product id\n");
	exit(1);
    }
    dev = find_device(vendor, product);
    assert(dev);

    devh = usb_open(dev);
    assert(devh);
    
    signal(SIGTERM, release_usb_device);

    ret = usb_get_driver_np(devh, 0, buf, sizeof(buf));
    printf("usb_get_driver_np returned %d\n", ret);
    if (ret == 0) {
	printf("interface 0 already claimed by driver \"%s\", attempting to detach it\n", buf);
	ret = usb_detach_kernel_driver_np(devh, 0);
	printf("usb_detach_kernel_driver_np returned %d\n", ret);
    }
    ret = usb_claim_interface(devh, 0);
    if (ret != 0) {
	printf("claim failed with error %d\n", ret);
		exit(1);
    }
    
    ret = usb_set_altinterface(devh, 0);
    assert(ret >= 0);

ret = usb_get_descriptor(devh, 0x0000001, 0x0000000, buf, 0x0000012);
printf("1 get descriptor returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_get_descriptor(devh, 0x0000002, 0x0000000, buf, 0x0000009);
printf("2 get descriptor returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(3*100);
ret = usb_get_descriptor(devh, 0x0000002, 0x0000000, buf, 0x0000027);
printf("3 get descriptor returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_release_interface(devh, 0);
if (ret != 0) printf("failed to release interface before set_configuration: %d\n", ret);
ret = usb_set_configuration(devh, 0x0000001);
printf("4 set configuration returned %d\n", ret);
ret = usb_claim_interface(devh, 0);
if (ret != 0) printf("claim after set_configuration failed with error %d\n", ret);
ret = usb_set_altinterface(devh, 0);
printf("4 set alternate setting returned %d\n", ret);
memcpy(buf, "\x10\x00\x00\x00\x01\x00\x02\x10\x00\x00\x00\x00\x01\x00\x00\x00", 0x0000010);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
printf("5 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("6 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(5*100);
memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x01\x10\x01\x00\x00\x00", 0x000000c);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
printf("7 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(1*100);
ret = usb_interrupt_read(devh, 0x00000083, buf, 0x0000008, 1000);
printf("8 interrupt read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("9 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(3*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("10 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(5*100);
memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x04\x10\x02\x00\x00\x00", 0x000000c);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
printf("11 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("12 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("13 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x03\x10\x03\x00\x00\x00", 0x000000c);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
printf("14 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("15 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
memcpy(buf, "\x10\x00\x00\x00\x01\x00\x02\x10\x00\x00\x00\x00\x01\x00\x00\x00", 0x0000010);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
printf("16 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(6*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("17 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(5*100);
memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x01\x10\x01\x00\x00\x00", 0x000000c);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
printf("18 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(3*100);
ret = usb_interrupt_read(devh, 0x00000083, buf, 0x0000008, 1000);
printf("19 interrupt read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(3*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("20 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("21 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x04\x10\x02\x00\x00\x00", 0x000000c);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
printf("22 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(8*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("23 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("24 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(17*100);
memcpy(buf, "\x18\x00\x00\x00\x01\x00\x01\x92\x03\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 0x0000018);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000018, 1000);
printf("25 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(10*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("26 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(9*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("27 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(10*100);
memcpy(buf, "\x18\x00\x00\x00\x01\x00\x01\x92\x04\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 0x0000018);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000018, 1000);
printf("28 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("29 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("30 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x02\x92\x05\x00\x00\x00", 0x000000c);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
printf("31 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(6*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("32 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(7*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("33 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(6*100);
memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x06\x00\x00\x00\x01\xd2\x00\x00", 0x0000010);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
printf("34 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(5*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("35 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("36 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(5*100);
memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x07\x00\x00\x00\x03\xd2\x00\x00", 0x0000010);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
printf("37 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(7*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("38 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(5*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("39 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(6*100);
memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x08\x00\x00\x00\x05\x50\x00\x00", 0x0000010);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
printf("40 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(5*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("41 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("42 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(10*100);
memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x09\x00\x00\x00\x13\x50\x00\x00", 0x0000010);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
printf("43 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("44 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("45 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(6*100);
memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x0a\x00\x00\x00\x04\x50\x00\x00", 0x0000010);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
printf("46 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(5*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("47 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(6*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("48 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(5*100);
memcpy(buf, "\x10\x00\x00\x00\x01\x00\x06\x92\x0b\x00\x00\x00\x10\xd2\x00\x00", 0x0000010);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
printf("49 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("50 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("51 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(5*100);
memcpy(buf, "\x10\x00\x00\x00\x01\x00\x03\x92\x0c\x00\x00\x00\x11\xd2\x00\x00", 0x0000010);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
printf("52 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(6*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("53 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(6*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("54 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(6*100);
memcpy(buf, "\x10\x00\x00\x00\x01\x00\x06\x92\x0d\x00\x00\x00\x0f\xd2\x00\x00", 0x0000010);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
printf("55 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(3*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("56 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(5*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("57 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
memcpy(buf, "\x18\x00\x00\x00\x01\x00\x01\x92\x0e\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 0x0000018);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000018, 1000);
printf("58 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("59 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("60 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(6*100);
memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x08\x92\x0f\x00\x00\x00", 0x000000c);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
printf("61 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("62 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("63 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(8*100);
memcpy(buf, "\x10\x00\x00\x00\x01\x00\x07\x92\x10\x01\x00\x00\x07\x50\x00\x00", 0x0000010);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x0000010, 1000);
printf("1147 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(4*100);
memcpy(buf, "\x0d\x00\x00\x00\x02\x00\x07\x92\x10\x01\x00\x00\x01", 0x000000d);
ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000d, 1000);
printf("1148 bulk write returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
usleep(3*100);
ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
printf("1149 bulk read returned %d, bytes: ", ret);
print_bytes(buf, ret);
printf("\n");
	ret = usb_release_interface(devh, 0);
	assert(ret == 0);
	ret = usb_close(devh);
	assert(ret == 0);
	return 0;
}
