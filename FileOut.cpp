#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class FileOut
{
private:
    stringstream ss;
public:
    void print(ofstream &outFile)
    {
        outFile << ss.rdbuf();
    }
    friend ostream& operator<<(ostream& output, const FileOut& stringOut)
    {   
        output << stringOut.ss.rdbuf();
        return output;
    }
    void operator<<(const string& stringOut)
    {   
        ss << stringOut;
    }
};