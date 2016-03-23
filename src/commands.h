#ifndef ___COMMANDS_H_INCLUDED___
#define ___COMMANDS_H_INCLUDED___


#include "support.h"


using namespace std;

namespace vvfs{

    class vvfs_ext_opearation{
        public:
        std::string Listing;
        std::string Header;
        std::string Tail;
        //
        private:
        int mvTailLength;
        int mvHeadLength;
        //bool (*process) (vector<string> args);

        public:
        vvfs_ext_opearation(std::string const vListing, std::string const vHeader, std::string const vTail){
            Listing = vListing;
            Header = vHeader;
            Tail = vTail;
            mvTailLength = Tail.length();
            mvHeadLength = Header.length();
        }
        bool matches(std::string vExtensionCommand){

            bool retVal = true;

            int lvExtensionCommandLength = vExtensionCommand.length();
            if (vExtensionCommand.compare(0, mvHeadLength, Header) != 0) retVal=false;
            if (vExtensionCommand.compare(vExtensionCommand.length()-mvTailLength, mvTailLength, Tail) != 0) retVal=false;

            return retVal;
        }
    };

    //vvfs_extension ADD;

    namespace extensions{
        vvfs::vvfs_ext_opearation ADD("/add[x,y,...]", "/add[", "]");
        vvfs::vvfs_ext_opearation RAW("/raw", "/raw", "");
        vvfs::vvfs_ext_opearation INVERT("/invert[x,y,...]", "/invert[", "]");
    }
/*
    ADD.Listing = "/add[x,y]";
    ADD.Header = "/add[";
    ADD.Tail = "]";
*/


//    class ADD{
//        public:
//			static const char *Listing;// = "/add[x,y]";
//			static const char *Header;// = "/add[";
//			static const char *Tail;// = "]";
//			ADD(){
//			    Listing = "/add[x,y]";
//                Header = "/add[";
//                Tail = "]";
//			}
//			void Process(std::vector<char*> vParameters){
//			}
//    } Add;

//        static struct ADD {
//            public:
//			static const char *Listing = "/add[x,y]";
//			static const char *Header = "/add[";
//			static const char *Tail = "]";
//			static void Process(std::vector<char*> vParameters){
//			}
//	    }
//
//	    static struct RAW {
//            public:
//			static const char *Listing = "/Raw";
//			static const char *Header = "/Raw";
//			static const char *Tail = "";
//			static void Process(std::vector<char*> vParameters){
//			}
//	    }
//
//	    static struct INVERT {
//            public:
//	        static const char *Listing = "/Invert[x]";
//			static const char *Header = "/Invert[";
//			static const char *Tail = "]";
//			static void Process(std::vector<char*> vParameters){
//			}
//	    }

	/*
		namespace Add{
			static const char *Listing = "/add[x,y]";
			static const char *Header = "/add[";
			static const char *Tail = "]";
			static void Process(std::vector<char*> vParameters){

			}
		}
		namespace Raw{
		}


		namespace Invert{
			static const char *Listing = "/Invert[x]";
			static const char *Header = "/Invert[";
			static const char *Tail = "]";
			static void Process(std::vector<char*> vParameters){
			}
		}
		*/
	}






#endif
