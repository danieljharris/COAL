#include "str.cpp"

using namespace std;

template <typename T>
void println(T var) { cout << var << endl; }

class LineIn : public str
{
protected:
    bool isInsideMatch = false;
    ifstream in;

public:
    LineIn(string file)
    {
        in.open(file + ".cpp");
    }
    ~LineIn() { in.close(); }

    string getNextLine()
    {
        string line;
        getline(in, line);
        s = line;
        return line;
    }
    string getNextLine(string line)
    {
        getline(in, line);
        s = line;
        return line;
    }

    string getCurrentLine()
    {
        return s;
    }
};