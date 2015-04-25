#ifndef xattrs_hh
#define xattrs_hh

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <errno.h>

using namespace std;

class XAttrs
{
        private:
                inline string GetXAttrsFilename(string filename);
        public:
                XAttrs();
                int SaveXAttr(string filename, string attr_name, string value);
                int RemoveXAttr(string filename, string attr_name);
                string GetXAttr(string filename, string attr_name);
                string ListXAttr(string filename);
                
                int GetXAttrCount(string filename);
};


#endif //xattrs.hh
