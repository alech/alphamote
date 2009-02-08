#ifndef ALPHAMOTE_H
#define ALPHAMOTE_H
// exported variables
extern struct usb_dev_handle *devh;
// exported functions
void release_usb_device(int);
struct usb_device *find_device(int, int);
void init_usb();
#endif
struct usb_dev_handle *devh;
