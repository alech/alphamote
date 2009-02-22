#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <ctype.h>
#include <usb.h>

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

void init_usb() {
    int vendor, product, ret;
    struct usb_device *dev;
    char buf[65535];

    usb_init();
    usb_find_busses();
    usb_find_devices();

    // vendor and product code for Sony alpha 700
    vendor  = 0x054c;
    product = 0x02e7;
    dev = find_device(vendor, product);
    if (! dev) {
        fprintf(stderr, "No camera found!\n");
        exit(1);
    }

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

    return;
}

