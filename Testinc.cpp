#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <variant>
#include <tuple>

using namespace std;

template <typename T>
void println(T var) { cout << var << endl; }

variant<int, string> multiReturnType(int in)
{
    if (in == 1) return 10;
    if (in == 2) return "11";
    else         return "Hello World!";
}

class lit : public string {
// public:
//     lit(string s) : string(s) {}
};

variant<tuple<lit, int>, tuple<lit, lit>> litVariReturn(int in)
{
    if (in == 1) return make_tuple((lit)"ok", 42);
    if (in == 2) return make_tuple((lit)"ok", 85);
    else         return make_tuple((lit)"error", (lit)"unexpected_type");
}


int main()
{
    // variant
    variant<int, string> val1 = multiReturnType(1);
    if (const auto ptr = get_if<int>(&val1))
    {
        cout << "int: " << *ptr << "\n";
    }
    else if (const auto ptr = get_if<string>(&val1))
    {
        cout << "string: " << *ptr << "\n";
    }

    // atom
    auto litVari = litVariReturn(1);

    if (const auto ptr = get_if<tuple<lit, int>>(&litVari)) 
    {
        tuple<lit, int> t = *ptr;
        cout << "ok: " << get<1>(t) << "\n";
    }
    else if (const auto ptr = get_if<tuple<lit, lit>>(&litVari))
    {
        tuple<lit, lit> t = *ptr;
        cout << "error: " << get<1>(t) << "\n";
    }




    return 0;
}