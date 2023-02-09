#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include "LineIn.cpp"

using namespace std;

bool matchLit = false;

string boilerPlate()
{
return
"#include <iostream> \n\
#include <variant> \n\
#include <tuple> \n\
#include <cstdio> \n\
#include \"mpark/patterns.hpp\" \n\
using namespace std; \n\
using namespace mpark::patterns; \n\n\
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



void insideMatch(str l, ofstream &out)
{
    // out << ".";
    out << l.getSpacing();

    if (l.firstIs('}'))
    {
        matchLit = false;
        out << ");" << "\n";
        return;
    }

    else if (l.firstIs('{')) out << "(" << "\n";

    else if (l.firstIs('('))
    {
        out << "pattern(as<";

        str returns = l.returns();
        str returnsTypes = returns.getReturnTypes();

        if (!l.has(","))
        {
            out << returnsTypes << ">(arg) = [](" << returns << ")) {";
        }
        else
        {
            out << "tuple<";
            // TODO: Change number of args with number of tuples
            out << returnsTypes << ">>(ds(arg, arg))) = [](" << returns << ") {";
            //out << returns.replace(",", ";");
            // out << "tie(" << returns.getReturnNames() << ") = ";
            // out << l.afterReturns() << ";\n";
        }

        out << l.getAfter("=>") << "; }\n";
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
    str l(line);
    
    // Match
    if (l.has("match"))
    {
        matchLit = true;
        out << l << "\n";
    }
    else if (matchLit) insideMatch(l, out);

    // Returns Conversions, for tuple and tie
    else if (l.firstIs('('))
    {
        // (int x, int y, int z)returnBack(10)

        // int x; int y; int z;
        // tie(x, y, z) = returnBack(10);

        str returns = str(l.returns());

        if (returns.has(",", "|"))
        {
            out << "    variant<";

            vector<str> types = returns.split('|');

            int i = 1;
            for(str seg : types)
            {
                str s = seg.trim();
                if (s.has(","))
                {
                    out << "tuple<";
                    out << s.s;
                    out << ">";
                }
                else
                {
                    out << s.s;
                }

                if(i < types.size()) out << ", ";
                i++;
            }
            out << ">" << l.afterReturns() << ";\n";
        }
        else if (returns.has(",") && l.has("="))
        {
            // (int, int) holdingTuple = myDoubleFunction()
            // tuple<int, int> holdingTuple = myDoubleFunction()

            // out << "tuple<" << split(returns, ',') << "> ";
            out << "    tuple<" << returns.getReturnTypes() << ">";
            out << l.afterReturns() << ";\n";
        }
        else if (returns.has(","))   
        {
            out << "    " << returns.replace(",", ";") << ";\n";
            out << "    ";
            out << "tie(" << returns.getReturnNames() << ") = ";
            out << l.afterReturns() << ";\n";
        }
        else
        {
            if (returns.has("|"))
                out << "//PLACE HOLDER 2";
            else
                out << "    " << returns.s << " = " <<  l.afterReturns() << ";\n";
        }
    }
    else if (l.has("return", ","))
    {
        out << l.getBefore("return");
        out << "return make_tuple(" << l.returnsOut() << ");\n";
    }
    else if (l.lastIs('>'))
    {
        out << l.getBefore("=")
            << "= get<" << l.extractBetween("<", ">")
            << ">(" << l.extractBetween(" = ", "<")
            << ");\n";
    }
    else
    {
        out << l.s;
        if (l.s.length() > 0) out << ";";
        out << endl;
    }
}

void burnCoalOutside(string line, ofstream &out)
{
    str l = str(line);
    if (l.firstIs('('))
    {
        str returns = l.returns();
        str rest = l.getAfter(")");

        if (returns.s.length() == 0)
        {
            out << "void ";
        }
        else if (returns.has(",", "|"))
        {
            out << "variant<";
            
            vector<str> types = returns.split('|');

            int i = 1;
            for(str seg : types)
            {
                str s = seg.trim();
                if (s.has(","))
                {
                    out << "tuple<";
                    out << s.s;
                    out << ">";
                }
                else out << s.s;

                if(i < types.size()) out << ", ";
                i++;
            }
            out << "> ";
        }
        else if (returns.has(","))
        {
            out << "tuple<";
            out << line.substr(1, line.find(")") - 1);
            out << "> ";
        }
        else if (l.has("|"))
        {
            out << "variant<";
            out << returns.replace(" |", ",");
            out << "> ";
        }
        else
        {
            out << line.substr(1, line.find(")") - 1);
            out << " ";
        }

        out << rest;
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

    //string file = "First";
    string file = "Second";

    ifstream in(file + ".co");
    ofstream out(file + ".cpp");

    out << boilerPlate();

    for (string line; getline(in, line);)
    {
        str l = str(line);
        if (l.firstIs('/')) continue; //Skips over comments

        if (insideFunction && line.length() == 0)
        {
            out << endl;
        }
        else if (l.firstIs('{') && !matchLit)
        {
            out << "\n{\n";
            insideFunction = true;
            depth++;
            continue;
        }
        else if (l.firstIs('}') && !matchLit)
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