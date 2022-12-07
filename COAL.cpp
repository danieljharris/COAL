#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

template <typename T>
void println(T var) { cout << var << endl; }

char firstChar(string str)
{
    const char* t = " \t\n\r\f\v";
    return str[str.find_first_not_of(t)];
}

int main()
{
    bool insideFunction = false;

    ifstream in("First.co");
    ofstream out("First.cpp");

    out << "#include <iostream> \n\
#include <tuple> \n\
using namespace std; \n\
template <typename T> \n\
void println(T var) { cout << var << endl; } \n\n";
//int main() \n\
//{ \n\
//";
    for (string line; getline(in, line); )
    {
        // if line includes "(" and ")"

        //if (line.find("(") != string::npos && line.find(")") != string::npos)
        //{
        //    
        //}
        //if (insideFunction) out << ".";
        //if (insideFunction) out << firstChar(line) << "    ";

        if (insideFunction && line.length() == 0)
        {
            out << endl;
        }
        else if (!insideFunction && line[0] == '(')
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
        //else if(insideFunction)
        else if(insideFunction && firstChar(line) == '(')
        {
            string returns = line.substr(line.find("(") + 1, line.find(")") - 5);
            string funcAndArgs = line.substr(line.find(")") + 1);

            if (line.find(",") == string::npos)
            {
                out << "    " << returns << " = " << funcAndArgs << ";\n";
            }
            else
            {
                // replace , with ; in returns
                string returnsCPP = returns;
                for (int i = 0; i < returnsCPP.length(); i++)
                {
                    if (returnsCPP[i] == ',') returnsCPP[i] = ';';
                }

                out << "    " << returnsCPP << ";\n";
                out << "    ";

                // replace "int" with "" in returns
                for (int i = 0; i < returns.length(); i++)
                {
                    if (returns[i] == 'i' && returns[i + 1] == 'n' && returns[i + 2] == 't')
                    {
                        returns.erase(i, 4);
                    }
                }

                out << "tie(" << returns << ") = ";
                out << funcAndArgs << ";\n";
            }
        }
        else if (line[0] == '{')
        {
            out << "\n{\n";
            insideFunction = true;
        }
        else if (line[0] == '}')
        {
            out << "}\n";
            insideFunction = false;
        }
        //else if line contains the string "return"
        else if (line.find("return") != string::npos && line.find(",") != string::npos)
        {
            string returns = line.substr(line.find("return") + 7);
            out << "    return make_tuple(" << returns << ");\n";
        }
        else
        {
            out << line;
            if (line.length() > 0) out << ";";
            out << endl;
        }
    }


    //out << "\n    return 0;\n}";

    out.close();

    system("g++ -std=c++11 First.cpp -o First");
    system("./First");

    return 0;
}