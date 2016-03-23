#ifndef ___VVFS_H_INCLUDED___
#define ___VVFS_H_INCLUDED___

#define FUSE_USE_VERSION 26

using namespace std;

//	VIRTUAL FILE SYSTEM FUNCTION CALLS:  -- from svfs.cpp
namespace vvfs {
	static int svfs_getattr(const char *path, struct stat *stbuf);
	static int svfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
	static int svfs_open(const char *path, struct fuse_file_info *fi);
	static int svfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
//	GLOBAL VARIABLES AND STRUCTURES ENTRY POINT:  -- from svfs.cpp

static struct svfs_operations : fuse_operations {
	svfs_operations () {
			getattr = vvfs::svfs_getattr;
			readdir = vvfs::svfs_readdir;
			open    = vvfs::svfs_open;
			read    = vvfs::svfs_read;
		}
	} svfs_oper_init;
	svfs_operations so;


//************************************************************************************//
//**  BEGIN FUNCTION CALL BACK HERE                                                 **//
//************************************************************************************//

	static int svfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi){
		printf("************************* CALL [READDIR] : PATH %s\n",path);
		(void) offset;
		(void) fi;


		//	********** VALIDATE PATHS HERE, TO DETERMINE
		//			WHAT PATHS ARE AVAILABLE FROM THIS POINT
		if (strcmp(path, "/") == 0) {
			//      --- BASIC STRUCTURE
			//filler(buf, ".", NULL, 0);
			//filler(buf, "..", NULL, 0);
			//      --- OPERATIONS
			filler(buf, vvfs::extensions::ADD.Listing.c_str()+1, NULL, 0);
			filler(buf, vvfs::extensions::RAW.Listing.c_str()+1, NULL, 0);
			filler(buf, vvfs::extensions::INVERT.Listing.c_str()+1, NULL, 0);
			//      --- DATA OUTPUT
			//filler(buf, svfs_solution_path+1, NULL, 0);
			//filler(buf, svfs_evaluate_path+1, NULL, 0);
			//
			/*
			//      --- READ THE ENTIRE DATA DIRECTORY AND PLACE IT HERE
            vector<string> datasourceentries = vvfs_data::directory(vvfs::svfs_data);

            for (vector<string>::iterator it = datasourceentries.begin() ; it != datasourceentries.end(); ++it){
                cout << *it << "\n";
                string filename = *it;
                filler(buf, filename.c_str()+1, NULL, 0);
            }
            */

			return 0;
		} else if(vvfs::extensions::ADD.matches(path)){
            //      --- BASIC STRUCTURE
			//filler(buf, ".", NULL, 0);
			//filler(buf, "..", NULL, 0);
			//      --- READ THE ENTIRE DATA DIRECTORY AND PLACE IT HERE
            vector<string> datasourceentries = vvfs_data::directory(vvfs::svfs_data_path);

            for (vector<string>::iterator it = datasourceentries.begin() ; it != datasourceentries.end(); ++it){
                cout << *it << "\n";
                string filename = *it;
                filler(buf, filename.c_str()+1, NULL, 0);
            }

			return 0;
		} else if(vvfs::extensions::RAW.matches(path)){
            //      --- BASIC STRUCTURE
			//filler(buf, ".", NULL, 0);
			//filler(buf, "..", NULL, 0);
			//      --- READ THE ENTIRE DATA DIRECTORY AND PLACE IT HERE
            vector<string> datasourceentries = vvfs_data::directory(vvfs::svfs_data_path);

            for (vector<string>::iterator it = datasourceentries.begin() ; it != datasourceentries.end(); ++it){
                cout << *it << "\n";
                string filename = *it;
                filler(buf, filename.c_str()+1, NULL, 0);
            }

			return 0;
		} else if(vvfs::extensions::INVERT.matches(path)){
            //      --- BASIC STRUCTURE
			//filler(buf, ".", NULL, 0);
			//filler(buf, "..", NULL, 0);
			//      --- READ THE ENTIRE DATA DIRECTORY AND PLACE IT HERE
            vector<string> datasourceentries = vvfs_data::directory(vvfs::svfs_data_path);

            for (vector<string>::iterator it = datasourceentries.begin() ; it != datasourceentries.end(); ++it){
                cout << *it << "\n";
                string filename = *it;
                filler(buf, filename.c_str()+1, NULL, 0);
            }

			return 0;
		}

		/*
		else if (strcmp(svfs_evaluate_path, path) == 4 ) {
			//	--- BASIC STRUCTURE
			filler(buf, ".", NULL, 0);
			filler(buf, "..", NULL, 0);
			//      --- OPERATIONS
			//filler(buf, svfs_add_operation+1, NULL, 0);	// Can only add once, so it does not appear in sub folders under add.
			//      --- DATA OUTPUT
			//filler(buf, svfs_solution_path+1, NULL, 0);
			//filler(buf, svfs_evaluate_path+1, NULL, 0);
			//      --- READ THE ENTIRE DATA DIRECTORY AND PLACE IT HERE
            vector<string> datasourceentries = vvfs_data::directory(vvfs::svfs_data_path);

            for (vector<string>::iterator it = datasourceentries.begin() ; it != datasourceentries.end(); ++it){
                cout << *it << "\n";
                string filename = *it;
                filler(buf, filename.c_str()+1, NULL, 0);
            }

			return 0;
		}
		*/

		return -ENOENT;	// NO VALID PATH
	}

	static int svfs_getattr(const char *path, struct stat *stbuf){
        printf("************************* CALL [GETATTR] : PATH %s\n",path);

		int res = 0;
		memset(stbuf, 0, sizeof(struct stat));
		//
		//-----------------------------------------
		//	evaluate each step of the path
		string str_path (path);
		vector<string> commands = newSplit(str_path, '/');
		int targetCommandIndex = commands.size()-1;



		printf("--svfs_getattr [len:%d :%d] %s\n", (int)str_path.length(), (int)commands.size(), str_path.c_str());

		//-----------------------------------------
		//
		//  FIRST, CHECK ALL KNOWN COMMANDS
		if (strcmp(path, "/") == 0) {
			//		printf("*** LISTING : DIRECTORY : %s\n", path);
			stbuf->st_mode = S_IFDIR | 0755;
			stbuf->st_nlink = 2;    //  NUMBER OF HARD LINKS
			stbuf->st_size = 0;     //  FILE SIZE (IN BYTES)
			//
		} else {
		    if (commands.size() > 0) {
		        //  compare command options
		        cout << "GETATTR : HAS " << commands.size() << " COMMANDS TO PROCESS\n";
		        for  (int i=0; i< commands.size(); i++){
                    cout << "MATCHING AGAINST " << i << " : " << commands[i] << "\n";
                    if(vvfs::extensions::ADD.matches(commands[targetCommandIndex])) {
                        cout << "COMMAND MATCH!!!  ::: ADD\n";
                        stbuf->st_mode = S_IFDIR | S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
                        stbuf->st_nlink = 1;
                        stbuf->st_size = 0;
                    } else if(vvfs::extensions::RAW.matches(commands[targetCommandIndex])) {
                        cout << "COMMAND MATCH!!!  ::: RAW\n";
                        stbuf->st_mode = S_IFDIR | S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
                        stbuf->st_nlink = 1;
                        stbuf->st_size = 0;
                    } else if(vvfs::extensions::INVERT.matches(commands[targetCommandIndex])) {
                        cout << "COMMAND MATCH!!!  ::: INVERT\n";
                        stbuf->st_mode = S_IFDIR | S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
                        stbuf->st_nlink = 1;
                        stbuf->st_size = 0;
                    } else {
                        //  IF NOT A KNOWN COMMAND, CHECK DATA DIRECTORY TO SEE IF ITS A TARGET FILE
                        cout << "getattr : PATH:" << path << "\n";
                        cout << "   commands :";
                        for(vector<string>::iterator it = commands.begin() ; it != commands.end(); ++it){
                            string filename = *it;
                            cout << ": " << filename << " :";
                            //filler(buf, filename.c_str()+1, NULL, 0);
                        }
                        cout << "-\n";

                        vector<string> datasourceentries = vvfs_data::directory(vvfs::svfs_data_path);

                        for (vector<string>::iterator it = datasourceentries.begin() ; it != datasourceentries.end(); ++it){
                            string filename = *it;
                            if(filename.compare(commands[targetCommandIndex])==0){
                                cout << "MATCHING DATA FILE : " << filename << "\n";
                                stbuf->st_mode = S_IFREG  | S_IRUSR | S_IRGRP | S_IROTH;
                                stbuf->st_nlink = 1;
                                stbuf->st_size = vvfs_data::DataFileSize(filename);


                            }
                        }

                    }
		        }
		    }
        }
		return res;
	}

	static int svfs_open(const char *path, struct fuse_file_info *fi){
        printf("************************* CALL [OPEN] : PATH %s\n",path);

		int result = -ENOENT;
		//        printf("***** CALL [OPEN] : PATH %s\n",path);
		if (strcmp(path, vvfs::extensions::ADD.Header.c_str()) == 0) result = 0;
		if (strcmp(path, vvfs::extensions::INVERT.Header.c_str()) == 0) result =0;

/*
		if (hasEnding(path, svfs_solution_path)) result = 0;
		if (hasEnding(path, svfs_evaluate_path)) result = 0;
		*/

		if ((fi->flags & 3) != O_RDONLY)  return -EACCES;
		return result;
	}

	static int svfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi){
	    printf("************************* CALL [READ] : PATH %s\n",path);
		string str_path (path);
		size_t len;
		(void) fi;

		//printf("* * * * * ********** CALL [READ] : PATH %s\n",path);

		vector<string> commands = newSplit(str_path, '/');
		size=0;

/*
		if(hasEnding(str_path, svfs_evaluate_path)){
			printf("Evaluating...\n");
			for(vector<string>::iterator it = commands.begin(); it != commands.end(); ++it){
				string command = *it;
				printf(" ..... %s\n", (char*)command.c_str());
				if(command.compare(0,4, vvfs::extensions::ADD.Listing.c_str()+1)==-4){
					//	parse and execute
					string operands = command.substr(4, command.length()-5);
					printf(" ........ Operands:%s\n", (char*)operands.c_str());
					vector<string> args = split(operands, ',');
					int sum=0;
					for(vector<string>::iterator itarg = args.begin(); itarg != args.end(); ++itarg){
						sum+=atoi((*itarg).c_str());
					}
					printf(" ............Result : %d\n", sum);

					stringstream output;
					output << str_path << " = " << sum << "\n";
					const char* result = output.str().c_str();

					len = strlen(result);
					printf(" .................output : [%d] %s\n", (int)len, result);
					if (offset < len) {
						if (offset + size > len) size = len - offset;
						memcpy(buf, result + offset, size);
					}
					size = len;
				}
			}
			printf("Program completed\n");

			//
		} else if(hasEnding(str_path, svfs_solution_path)){
			printf("Hello World, you are at '%s'!!!\n", path);
			len = strlen(svfs_str);
			if (offset < len) {
				if (offset + size > len)
					size = len - offset;
				memcpy(buf, svfs_str + offset, size);
			}
			//
		} else {
			size = 0;
		}
		*/
		//        if(strcmp(path, svfs_path) != 0 ) return -ENOENT;
		return size;
	}

}


#endif
