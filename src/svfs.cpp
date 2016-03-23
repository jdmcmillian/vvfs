/*
g++ -Wall -Wno-sign-compare svfs.cpp `pkg-config fuse --cflags --libs` -o svfs

development system was Ubuntu 12.04
*/

#define FUSE_USE_VERSION 26
#include "support.h"

using namespace std;



int main(int argc, char *argv[])
{
	std::vector<char*> fuseArgs;
	printf("Arguments passed : %d\n", (int)fuseArgs.size());

	printf("PRIMARY STARTUP ARGUMENTS : %d\n", argc);
	for (int i=0; i< argc; i++){
		printf("PRIMARY ARGUMENT #[%d] : %s\n", i, argv[i]);

		if(strncmp("mount=", argv[i],6)==0) {
			strcpy(vvfs::svfs_mountpoint, argv[i]+6);
			//strcpy(argv[i], svfs_mountpoint);
			fuseArgs.push_back(argv[i]+6);
		 }
		else if(strncmp("data=", argv[i],5)==0) {
            strcpy(vvfs::svfs_data_path, argv[i]+5);
		 //argv[i] = " ";
		 }
		else if(strncmp("functions=", argv[i],10)==0) {
			strcpy(vvfs::svfs_functions, argv[i]+10);
			argv[i] = " ";
			}
		else {
			fuseArgs.push_back(argv[i]);
		}
	}

	printf("Mounting at   : %s\n", vvfs::svfs_mountpoint);
	printf("Data Files at : %s\n", vvfs::svfs_data_path);
	printf("Functions at  : %s\n", vvfs::svfs_functions);

	printf("STARTING FUSE MAIN\n");

	printf("Arguments passed : %d\n", fuseArgs.size());

	return fuse_main(fuseArgs.size(), &fuseArgs[0], &vvfs::svfs_oper_init, NULL);
}



