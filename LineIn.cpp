#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

template <typename T>
void println(T var) { cout << var << endl; }

class LineIn
{
private:
    bool isInsideMatch = false;
    static string currentLine;
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
        currentLine = line;
        return line;
    }
    string getNextLine(string line)
    {
        getline(in, line);
        currentLine = line;
        return line;
    }

    string getCurrentLine()
    {
        return currentLine;
    }

    char firstC(string str = currentLine)
    {
        const char* t = " \t\n\r\f\v";
        return str[str.find_first_not_of(t)];
    }

    bool firstIs(char isChar, string str = currentLine)
    {
        return firstC(str) == isChar;
    }

    char lastC(string str = currentLine)
    {
        const char* t = " \t\n\r\f\v";
        return str[str.find_last_not_of(t)];
    }

    bool lastIs(char isChar, string str = currentLine)
    {
        return lastC(str) == isChar;
    }

    bool has(string find, string str = currentLine)
    {
        return str.find(find) != string::npos;
    }

    bool has2(string find1, string find2, string str = currentLine)
    {
        return str.find(find1) != string::npos && str.find(find2) != string::npos;
    }

    // "  Hello World  " -> "Hello World"
    string trim(const string& str, const string& whitespace = " \t")
    {
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == string::npos) return "";

        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }

    // "str, int | str, str | int" -> [str, int], [str, str], [int]
    vector<string> split(char splitOn, string str = currentLine)
    {
        stringstream ss(str);
        string segment;
        vector<string> seglist;

        while(getline(ss, segment, splitOn))
            seglist.push_back(trim(segment));
        
        return seglist;
    }

    string returnsOut(string str = currentLine)
    {
        return str.substr(str.find("return") + 7);
    }

    // get values inside first set of ( )
    string returnsIn(string str = currentLine)
    {
        return str.substr(str.find("(") + 1, str.find(")") - 5);
    }

    // (str, int, int)returnBack(int x) -> returnBack(int x)
    string funcAndArgsIn(string str = currentLine)
    {
        return str.substr(str.find(")") + 1);
    }

    string getBefore(string until, string str = currentLine)
    {
        return str.substr(0, str.find(until));
    }
    string getAfter(string after, string str = currentLine)
    {
        return str.substr(str.find(after) + after.length());
    }

    // int k = holdingTuple<1> with < and > would reutrn 1
    string extractBetween(string start, string end, string str = currentLine)
    {
        return str.substr(str.find(start) + start.length(), str.find(end) - str.find(start) - (start.length() - end.length()) - 1);
    }

    string replace(string find, string replace, string str = currentLine)
    {
        int pos = str.find(find);
        while (pos != string::npos)
        {
            str.replace(pos, find.length(), replace);
            pos = str.find(find);
        }
        return str;
    }

    // get vairable names from string "int height, double width, string name" -> "height, width, name"
    string getReturnNames(string returns)
    {
        string returnNames = "";

        int start = 0;
        for (int i = 0; i < returns.length(); i++)
        {
            if (returns[i] == ' ')
                start = i + 1;
            else if (returns[i] == ',')
                returnNames += returns.substr(start, i - start) + ", ";
        }
        returnNames += returns.substr(start);

        return returnNames;
    }

    // get vairable types from string "int height, double width, string name" -> "int, double, string"
    string getReturnTypes(string returns)
    {
        string returnTypes = "";

        int start = 0;
        for (int i = 0; i < returns.length(); i++)
        {
            if (returns[i] == ' ')
                returnTypes += returns.substr(start + 1, i) + ",";
            else if (returns[i] == ',')
                start = i + 1;
        }
        returnTypes += returns.substr(start);

        return returnTypes;
    }

};