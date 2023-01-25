#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class str
{
public:
    string s;
public:
    str()
    {
        s = "";
    }
    str(string string)
    {
        s = string;
    }

    char firstC()
    {
        const char* t = " \t\n\r\f\v";
        return s[s.find_first_not_of(t)];
    }

    bool firstIs(char isChar)
    {
        return firstC() == isChar;
    }

    char lastC()
    {
        const char* t = " \t\n\r\f\v";
        return s[s.find_last_not_of(t)];
    }

    bool lastIs(char isChar)
    {
        return lastC() == isChar;
    }

    bool has(string find)
    {
        return s.find(find) != string::npos;
    }

    bool has(string find1, string find2)
    {
        return s.find(find1) != string::npos && s.find(find2) != string::npos;
    }

    // "  Hello World  " -> "Hello World"
    string trim(const string& whitespace = " \t")
    {
        const auto strBegin = s.find_first_not_of(whitespace);
        if (strBegin == string::npos) return "";

        const auto strEnd = s.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;

        return s.substr(strBegin, strRange);
    }

    // "str, int | str, str | int" -> [str, int], [str, str], [int]
    vector<string> split(char splitOn)
    {
        string tmp; 
        stringstream ss(s);
        vector<string> seglist;

        while(getline(ss, tmp, splitOn)){
            seglist.push_back(tmp);
        }
        
        return seglist;
    }

    string returnsOut()
    {
        return s.substr(s.find("return") + 7);
    }

    // get values inside first set of ( )
    string returnsIn()
    {
        return s.substr(s.find("(") + 1, s.find(")") - 5);
    }

    // (str, int, int)returnBack(int x) -> returnBack(int x)
    string funcAndArgsIn()
    {
        return s.substr(s.find(")") + 1);
    }

    string getBefore(string until)
    {
        return s.substr(0, s.find(until));
    }
    string getAfter(string after)
    {
        return s.substr(s.find(after) + after.length());
    }

    // int k = holdingTuple<1> with < and > would reutrn 1
    string extractBetween(string start, string end)
    {
        return s.substr(s.find(start) + start.length(), s.find(end) - s.find(start) - (start.length() - end.length()) - 1);
    }

    string replace(string find, string replace)
    {
        int pos = s.find(find);
        string replacedString = s;
        while (pos != string::npos)
        {
            replacedString.replace(pos, find.length(), replace);
            pos = replacedString.find(find);
        }
        return replacedString;
    }

    // get vairable names from string "int height, double width, string name" -> "height, width, name"
    string getReturnNames()
    {
        string returns = s;
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
    string getReturnTypes()
    {
        string returns = s;
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