
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
        printf("00: ");
	for (i=0; i<len; i++) {
	    printf("%02x ", (int)((unsigned char)bytes[i]));
            if ((i + 1) % 10 == 0) {
                printf("\n");
                printf("%02d: ", (i / 10) + 1);
            }
	}
        printf("\n");
    }
}

void print_interpretation(char *buf) {
    // byte 35 and 36 are 100 * fstop
    long fstop_scaled = buf[35] & 255;
    fstop_scaled |= (buf[36] << 8);
    double fstop;
    fstop = (fstop_scaled / 100.0); 
    printf("f%2.1f\n", fstop);

    if (buf[95] == 1) {
        // if byte 95 is 1
        // byte 93 and 94 are 1/time
        printf("using 1/s\n");
        long time = (buf[93] & 255) | (buf[94] << 8);
        printf("1/%ds\n", time);
    }
    else {
        // byte 95 and 96 are 10*s (or bulb if 0)
        long time = (buf[95] & 255) | (buf[96] << 8);
        if (time != 0) {
            double time_s;
            time_s = (time / 10.0);
            printf("%2.1fs\n", time_s);
        }
        else {
            printf("bulb\n");
        }
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

    // get info (bulk read 62)
    usleep(100*1000);
    memcpy(buf, "\x0c\x00\x00\x00\x01\x00\x08\x92\x0f\x00\x00\x00", 0x000000c);
    ret = usb_bulk_write(devh, 0x00000001, buf, 0x000000c, 1000);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    int i;
    print_interpretation(buf);
    printf("\n");
    print_bytes(buf, ret);
    usleep(4*1000);
    ret = usb_bulk_read(devh, 0x00000082, buf, 0x0000200, 1030);
    ret = usb_release_interface(devh, 0);
    assert(ret == 0);
    ret = usb_close(devh);
    assert(ret == 0);
    return 0;
}
