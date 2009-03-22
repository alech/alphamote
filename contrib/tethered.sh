#!/bin/sh

# a quick script to do tethered shooting in (c)RAW + JPG mode:
# download the photo, rename it, show it using qiv, download the ARW file
alphamote download
DATE=`date +%s`
mv /tmp/foo.jpg $DATE.jpg
qiv -f -m $DATE.jpg &
alphamote download
mv /tmp/foo.jpg $DATE.arw
