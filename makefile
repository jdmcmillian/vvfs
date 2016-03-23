Release:
	g++ -Wall -Wno-sign-compare src/svfs.cpp `pkg-config fuse --cflags --libs` -o vvfs
Debug:
	g++ -Wall -Wno-sign-compare src/svfs.cpp `pkg-config fuse --cflags --libs` -o vvfs
all:
	g++ -Wall -Wno-sign-compare src/svfs.cpp `pkg-config fuse --cflags --libs` -o vvfs

#	gcc -Wall svfs.cpp `pkg-config fuse --cflags --libs` -o svfs	:: DEFAULT COMPILER LINE
#
#	Additional Flags
#	-Wno-sign-compare	:: Disables warning 'warning: comparison between signed and unsigned integer expressions [-Wsign-compare]'
