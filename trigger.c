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

    usb_init();
    usb_find_busses();
    usb_find_devices();

    vendor  = 0x054c;
    product = 0x02e7;
    dev = find_device(vendor, product);
    assert(dev);

    devh = usb_open(dev);
    assert(devh);
    
    signal(SIGTERM, release_usb_device);

    ret = usb_get_driver_np(devh, 0, buf, sizeof(buf));
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

usleep(5000*1000);
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

// retrieving image
usleep(2500*1000);
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
int i;
for (i = 12; i < ret; i++) {
    fputc(buf[i], out);
}

while (ret > 0) {
    // something to read left
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 4932);
    // append to file
    int i;
    for (i = 0; i < ret; i++) {
        fputc(buf[i], out);
    }
    usleep(10*1000);
}
fclose(out);
    ret = usb_release_interface(devh, 0);
    assert(ret == 0);
    ret = usb_close(devh);
    assert(ret == 0);
    return 0;
}
