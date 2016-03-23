#ifndef ___SUPPORT_H_INCLUDED___
#define ___SUPPORT_H_INCLUDED___

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <tiffio.h>

#include <fstream>
#include <iostream>

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>



using namespace std;


//	vector<string> &split(const string &s, char delim, vector<string> &elems);
//	vector<string> split(const string &s, char delim);
	bool hasEnding (std::string const &fullString, std::string const &ending);
	string IntToString(int number);
	vector<string> newSplit(const string &text, char delim);


	namespace vvfs_data{
        vector<string> directory(const string &path);
        int64_t DataFileSize(const string &filename);

	}

/*
static const char *svfs_str = "Hello World!\n";
static const char *svfs_evaluate_path 			= "/process";
static const char *svfs_details_path 			= "/details";
static const char *svfs_solution_path 			= "/solution.txt";
*/

namespace vvfs{
    char svfs_mountpoint[512];
    char svfs_data_path[512];
    char svfs_functions[512];
}

#include "commands.h"
#include "integration.h"

//namespace vvfs{

	bool hasEnding (std::string const &fullString, std::string const &ending) {
		if (fullString.length() >= ending.length()) {
			return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
		} else {
			return false;
		}
	}
/*
	vector<string> &split(const string &s, char delim, vector<string> &elems) {
		stringstream ss(s);
		string item;
		while (getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}


	vector<string> split(const string &s, char delim) {
		vector<string> elems;
		split(s, delim, elems);
		return elems;
	}
*/

	vector<string> newSplit(const string &text, char delim){
	    vector<string> tokens;//{istream_iterator<string>{iss}, istream_iterator<string>{}};

        int start = 0, end = 0;
        while ((start=text.find(delim, end)) != string::npos) {
            end = text.find(delim, start+1);
            if (end!=string::npos){
                //  found a new split
                tokens.push_back(text.substr(start, end - start));
            } else {
                //  this is last one.
                tokens.push_back(text.substr(start));
            }
            start = end;
        }



        return tokens;
	}



	string IntToString(int number)
	{
		stringstream ss;//create a stringstream
		ss << number;//add number to the stream
		return ss.str();//return a string with the contents of the stream
	}

namespace vvfs_data {
    vector<string> directory(const string &path){
        vector<string> entries;
        DIR *dp;

  ifstream fin;
  string dir, filepath;
  int num;
  struct dirent *dirp;
  struct stat filestat;


        dp = opendir( path.c_str() );
        if (dp == NULL)
            {
            cout << "Error(" << errno << ") opening " << dir << endl;
            return entries;
            }

        while ((dirp = readdir( dp )))
            {
            filepath = dir + "/" + dirp->d_name;

//             If the file is a directory (or is in some way invalid) we'll skip it
//            if (stat( filepath.c_str(), &filestat )) continue;
//            if (S_ISDIR( filestat.st_mode ))         continue;
//
////             Endeavor to read a single number from the file and display it
//            fin.open( filepath.c_str() );
//            if (fin >> num)
            entries.push_back(filepath);
            //fin.close();
            }
//
        closedir( dp );
        return entries;
    }

    int64_t DataFileSize(const string &filename){
        int64_t size = 0;

        string fullPath;

        fullPath = vvfs::svfs_data_path;
        fullPath.append(filename);

        struct stat st;
        stat(fullPath.c_str(), &st);
        size = st.st_size;
        return size;
    }


}




//}





#endif

