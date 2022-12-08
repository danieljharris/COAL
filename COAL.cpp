#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

template <typename T>
void println(T var) { cout << var << endl; }

string boilerPlate()
{
return

"#include <iostream> \n\
#include <tuple> \n\
using namespace std; \n\
template <typename T> \n\
void println(T var) { cout << var << endl; } \n\
class lit : public string {};\n\
\n";

//int main() \n\
//{ \n\
//";
}

char firstC(string str)
{
    const char* t = " \t\n\r\f\v";
    return str[str.find_first_not_of(t)];
}
bool has(string str, string find)
{
    return str.find(find) != string::npos;
}
bool has(string str, string find1, string find2)
{
    return str.find(find1) != string::npos && str.find(find2) != string::npos;
}
string returnsOut(string str)
{
    return str.substr(str.find("return") + 7);
}
string returnsIn(string str)
{
    return str.substr(str.find("(") + 1, str.find(")") - 5);
}
string funcAndArgsIn(string str)
{
    return str.substr(str.find(")") + 1);
}
string replace(string str, string find, string replace)
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
string getReturnVars(string returns)
{
    string returnVars = "";

    int start = 0;
    for (int i = 0; i < returns.length(); i++)
    {
        if (returns[i] == ' ')
            start = i + 1;
        else if (returns[i] == ',')
            returnVars += returns.substr(start, i - start) + ", ";
    }
    returnVars += returns.substr(start);

    return returnVars;
}

void burnCoalInside(string line, ofstream &out)
{
    if(firstC(line) == '(') // Returns Conversions, for tuple and tie
    {
        string returns = returnsIn(line);

        if (!has(returns, ","))
        {
            out << "    " << returns << " = " << funcAndArgsIn(line) << ";\n";
        }
        else
        {
            out << "    " << replace(returns, ",", ";") << ";\n";
            out << "    ";
            out << "tie(" << getReturnVars(returns) << ") = ";
            out << funcAndArgsIn(line) << ";\n";
        }
    }
    else if (has(line, "return", ","))
    {
        out << "    return make_tuple(" << returnsOut(line) << ");\n";
    }
    else if (has(line, "match"))
    {

    }
    else
    {
        out << line;
        if (line.length() > 0) out << ";";
        out << endl;
    }
}

void burnCoalOutside(string line, ofstream &out)
{
    if (line[0] == '(')
    {
        string returns = line.substr(1, line.find(")") - 1);
        string funcAndArgs = line.substr(line.find(")") + 1);

        if (returns.length() == 0)
        {
            out << "void ";
            out << funcAndArgs;
        }
        else if (returns.find(",") == string::npos)
        {
            out << line.substr(1, line.find(")") - 1);
            out << " ";
            out << funcAndArgs;
        }
        else
        {
            out << "tuple<";
            out << line.substr(1, line.find(")") - 1);
            out << "> " << funcAndArgs;
        }
    }
    else
    {
        out << line;
        if (line.length() > 0) out << ";";
        out << endl;
    }
}

int main()
{
    bool insideFunction = false;
    int depth = 0;

    ifstream in("First.co");
    ofstream out("First.cpp");

    out << boilerPlate();

    for (string line; getline(in, line); )
    {
        if (insideFunction && line.length() == 0)
        {
            out << endl;
        }
        else if (line[0] == '{')
        {
            out << "\n{\n";
            insideFunction = true;
            depth++;
            continue;
        }
        else if (line[0] == '}')
        {
            out << "}\n";
            depth--;
            if (depth == 0) insideFunction = false;
            continue;
        }

        if (insideFunction)
            burnCoalInside(line, out);
        else
            burnCoalOutside(line, out);
    }

    //out << "\n    return 0;\n}";

    out.close();

    system("g++ -std=c++11 First.cpp -o First");
    system("./First");

    return 0;
}