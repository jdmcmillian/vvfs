#!/bin/sh
clear
echo '------------- Unmounting Old Smart Virtual FileSystem'
fusermount -u ref/mount
rm svfs
echo '------------- Compiling ...'
make
chmod +x vvfs
echo '------------- Mounting Smart Virtual FileSystem'
###	diagnopstic mode
###./svfs -d reference-points/mountpoint
./vvfs -d mount=ref/mount data=ref/data functions=ref/extensions
##./svfs reference-points/mountpoint
#echo ''
#echo '------------- Current Directory'
#ls -al
echo ''
echo ''
echo '------------- Smart Virtual File System Root Folder ---------------'
echo '-------------------------------------------------------------------'
ls -al ref/mount
