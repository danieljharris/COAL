#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

template <typename T>
void println(T var) { cout << var << endl; }

bool isInsideMatch = false;

string boilerPlate()
{
return

"#include <iostream> \n\
#include <variant> \n\
#include <tuple> \n\
#include <cstdio> \n\
#include \"mpark/patterns.hpp\" \n\
using namespace std; \n\
using namespace mpark::patterns; \n\
using str = std::string; \n\
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

bool firstIs(string str, char isChar)
{
    return firstC(str) == isChar;
}

char lastC(string str)
{
    const char* t = " \t\n\r\f\v";
    return str[str.find_last_not_of(t)];
}

bool lastIs(string str, char isChar)
{
    return lastC(str) == isChar;
}

bool has(string str, string find)
{
    return str.find(find) != string::npos;
}

bool has(string str, string find1, string find2)
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
vector<string> split(string str, char splitOn)
{
    stringstream ss(str);
    string segment;
    vector<string> seglist;

    while(getline(ss, segment, splitOn))
        seglist.push_back(trim(segment));
    
    return seglist;
}

string returnsOut(string str)
{
    return str.substr(str.find("return") + 7);
}

// get values inside first set of ( )
string returnsIn(string str)
{
    return str.substr(str.find("(") + 1, str.find(")") - 5);
}

// (str, int, int)returnBack(int x) -> returnBack(int x)
string funcAndArgsIn(string str)
{
    return str.substr(str.find(")") + 1);
}

string getBefore(string str, string until)
{
    return str.substr(0, str.find(until));
}
string getAfter(string str, string after)
{
    return str.substr(str.find(after) + after.length());
}

// int k = holdingTuple<1> with < and > would reutrn 1
string extractBetween(string str, string start, string end)
{
    return str.substr(str.find(start) + start.length(), str.find(end) - str.find(start) - (start.length() - end.length()) - 1);
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

// (str, int | str, str | int) -> [str, int], [str, str], [int]
// string getVariantVars(string returns)
// {
//     list<string> variantVarList;
//     string variantVars = "";

//     int start = 0;
//     for (int i = 0; i < returns.length(); i++)
//     {
//         if (returns[i] == '|')
//         {
//             variantVarList.push_back(variantVars);
//             variantVars = "";
//             continue;
//         }

//         if (returns[i] == ' ')
//             start = i + 1;
//         else if (returns[i] == ',')
//             returnNames += returns.substr(start, i - start) + ", ";
//     }
//     returnNames += returns.substr(start);

//     return returnNames;
// }

void insideMatch(string line, ofstream &out)
{
    if (has(line, "}")) isInsideMatch = false;

    else if (firstIs(line, '{')) out << "(" << "\n";
    else if (firstIs(line, '}')) out << ");" << "\n";

    else if (firstIs(line, '('))
    {
        out << "pattern(as<";

        string returns = returnsIn(line);
        string returnsTypes = getReturnTypes(returns);

        if (!has(returns, ","))
        {
            out << "    " << "    " << returnsTypes << ">(arg)) = [](" << returns << ") {" << ";\n";
        }
        else
        {
            out << "    " << replace(returns, ",", ";") << ";\n";
            out << "    ";
            out << "tie(" << getReturnNames(returns) << ") = ";
            out << funcAndArgsIn(line) << ";\n";
        }
    }

    // match (litVari)
    // {
    //     (int i, str s) => cout << "int, str: " << i << " - " << s << "\n"
    //     (str s1, str s2) => cout << "str, str: " << s1 << " - " << s2 << "\n"
    //     (int x) => cout << "int: " << x << "\n"
    // }

    // match(varTuple)
    // (
    //     pattern(as<tuple<int, str>>(ds(arg, arg))) = [](int i, str s) { cout << "int, str: " << i << " - " << s << "\n"; },
    //     pattern(as<tuple<str, str>>(ds(arg, arg))) = [](str s1, str s2) { cout << "str, str: " << s1 << " - " << s2 << "\n"; },
    //     pattern(as<int>(arg))                      = [](int x) { cout << "int: " << x << "\n"; }
    // );
}

void burnCoalInside(string line, ofstream &out)
{
    // Match
    if (has(line, "match")) isInsideMatch = true;
    else if (isInsideMatch) insideMatch(line, out);

    // Returns Conversions, for tuple and tie
    else if (firstIs(line, '('))
    {
        // (int x, int y, int z)returnBack(10)

        // int x; int y; int z;
        // tie(x, y, z) = returnBack(10);

        string returns = returnsIn(line);

        // else
        // {
        //     vector<string> types = split(returns, '|');

        //     int index = 1;
        //     for (string seg : types)
        //     {
        //         if (has(seg, ","))
        //             out << "tuple<" << seg << ">";
        //         else
        //             out << seg;

        //         // Only put , between segments and not at the end
        //         if (index != types.size()) out << ", ";
        //         index++;
        //     }

        //     out << "> ";
        // }

        if (has(returns, ","))
        {
            if (has(returns, "|"))
            {
                // (str, int | str, str)giveVariant2(1)

                out << "PLACE HOLDER";
            }
            else if (has(line, "="))
            {
                // (int, int) holdingTuple = myDoubleFunction()
                // tuple<int, int> holdingTuple = myDoubleFunction()

                // out << "tuple<" << split(returns, ',') << "> ";
                out << "    tuple<" << getReturnTypes(returns) << ">";
                out << funcAndArgsIn(line) << ";\n";
            }
            else
            {
                out << "    " << replace(returns, ",", ";") << ";\n";
                out << "    ";
                out << "tie(" << getReturnNames(returns) << ") = ";
                out << funcAndArgsIn(line) << ";\n";
            }
        }
        else
        {
            if (has(returns, "|"))
                out << "PLACE HOLDER";
            else
                out << "    " << returns << " = " <<  funcAndArgsIn(line) << ";\n";
        }
    }
    else if (has(line, "return", ","))
    {
        out << "    return make_tuple(" << returnsOut(line) << ");\n";
    }
    else if (lastIs(line, '>'))
    {
        out << getBefore(line, "=")
            << "= get<" << extractBetween(line, "<", ">")
            << ">(" << extractBetween(line, " = ", "<")
            << ");\n";
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
        else if (has(returns, ","))
        {
            if (has(returns, "|"))
            {
                out << "variant<";

                vector<string> types = split(returns, '|');

                int index = 1;
                for (string seg : types)
                {
                    if (has(seg, ","))
                        out << "tuple<" << seg << ">";
                    else
                        out << seg;

                    // Only put , between segments and not at the end
                    if (index != types.size()) out << ", ";
                    index++;
                }

                out << "> " << funcAndArgs;
            }
            else
            {
                out << "tuple<";
                out << line.substr(1, line.find(")") - 1);
                out << "> " << funcAndArgs;
            }
        }
        else if (has(line, "|"))
        {
            out << "variant<";

            vector<string> types = split(returns, '|');

            int index = 1;
            for (string seg : types)
            {
                out << seg;

                // Only put , between segments and not at the end
                if (index != types.size()) out << ", ";
                index++;
            }

            out << "> " << funcAndArgs;
        }
        else
        {
            out << line.substr(1, line.find(")") - 1);
            out << " ";
            out << funcAndArgs;
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

    string file = "First";
    // string file = "Second";

    ifstream in(file + ".co");
    ofstream out(file + ".cpp");

    out << boilerPlate();

    for (string line; getline(in, line); )
    {
        if (firstIs(line, '/')) continue; //Skips over comments

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

        if (insideFunction) burnCoalInside(line, out);
        else                burnCoalOutside(line, out);
    }

    //out << "\n    return 0;\n}";

    out.close();

    system(("g++ -std=c++20 " + file + ".cpp -o " + file).c_str());
    system(("./" + file).c_str());

    return 0;
}