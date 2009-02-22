CC      = gcc
OBJS    = alphamote.o
LDFLAGS = -lusb

default: init aperture_dec aperture_inc info shutter download

init: $(OBJS)
	$(CC) -o alphamote-init init.c $(OBJS) $(LDFLAGS)

info: $(OBJS)
	$(CC) -o alphamote-info info.c $(OBJS) $(LDFLAGS)

aperture_inc: $(OBJS)
	$(CC) -o alphamote-aperture-inc aperture_inc.c $(OBJS) $(LDFLAGS)

aperture_dec: $(OBJS)
	$(CC) -o alphamote-aperture-dec aperture_dec.c $(OBJS) $(LDFLAGS)

shutter: $(OBJS)
	$(CC) -o alphamote-shutter shutter.c $(OBJS) $(LDFLAGS)

download: $(OBJS)
	$(CC) -o alphamote-download download.c $(OBJS) $(LDFLAGS)

clean:
	rm alphamote-*
	rm *.o
