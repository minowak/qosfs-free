#include "xattrs.hh"

XAttrs::XAttrs()
{

}

inline string XAttrs::GetXAttrsFilename(string filename)
{
        return "." + filename + ".xattrs";
}

int XAttrs::SaveXAttr(string filename, string attr_name, string value)
{
        string attr_filename = GetXAttrsFilename(filename);
        ofstream file;
        printf("[QoSFS] Opening file %s\n", attr_filename.c_str());
        file.open(attr_filename.c_str(), ios::out | ios::app);
        if(!file.is_open())
        {
                printf("[QoSFS] Error: %s\n", strerror(errno));
                return -1;
        }
        file << attr_name.c_str() << ":" << value.c_str() << endl;
        file.close();
        printf("[QoSFS] Opening file went OK\n");
        return 0;
}

int XAttrs::RemoveXAttr(string filename, string attr_name)
{
        return 0;
}

string XAttrs::GetXAttr(string filename, string attr_name)
{
        string attr_filename = GetXAttrsFilename(filename);
        ifstream file;
        printf("[QoSFS] Opening file %s\n", attr_filename.c_str());
        file.open(attr_filename.c_str());
        if(!file.is_open())
        {
                printf("[QoSFS] Error: %s\n", strerror(errno));
                return "";
        }

        string line, value;
        while(getline(file, line))
        {
                size_t i = line.find(":");
                string a_name = line.substr(0, i);
                if(a_name.compare(attr_name) == 0)
                {
                        value = line.substr(i+1, line.size() - i);
                        break;
                }
        }

        file.close();

        return value;
}

string XAttrs::ListXAttr(string filename)
{
        string attr_filename = GetXAttrsFilename(filename);
        ifstream file;
        printf("[QoSFS] Opening file %s\n", attr_filename.c_str());
        file.open(attr_filename.c_str());
        if(!file.is_open())
        {
                printf("[QoSFS] Error: %s\n", strerror(errno));
                return "";
        }

        string line, result;
        while(getline(file, line))
        {
                size_t i = line.find(":");
                string a_name = line.substr(0, i);
                result = result + a_name + "\0";
        }

        file.close();

        return result;
}

int XAttrs::GetXAttrCount(string filename)
{
        string attr_filename = GetXAttrsFilename(filename);
        ifstream file;
        printf("[QoSFS] Opening file %s\n", attr_filename.c_str());
        file.open(attr_filename.c_str());
        if(!file.is_open())
        {
                printf("[QoSFS] Error: %s\n", strerror(errno));
                return -1;
        }

        string line;
        int result = 0;
        while(getline(file, line))
                result++;
        file.close();

        return result;
}
