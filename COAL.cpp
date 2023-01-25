#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include "LineIn.cpp"

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

void insideMatch(LineIn l, ofstream &out)
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

void burnCoalInside(LineIn l, ofstream &out)
{
    // Match
    if (l.has("match")) isInsideMatch = true;
    else if (isInsideMatch) insideMatch(l, out);

    // Returns Conversions, for tuple and tie
    else if (l.firstIs('('))
    {
        // (int x, int y, int z)returnBack(10)

        // int x; int y; int z;
        // tie(x, y, z) = returnBack(10);

        string returns = l.returnsIn();

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

        if (l.has(",", returns))
        {
            if (l.has("|", returns))
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