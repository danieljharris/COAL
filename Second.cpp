#include <iostream> 
#include <variant> 
#include <tuple> 
#include <cstdio> 
#include "mpark/patterns.hpp" 
using namespace std; 
using namespace mpark::patterns; 

using str = std::string; 
template <typename T> 
void println(T var) { cout << var << endl; } 
class lit : public string {};

variant<tuple<str, int>, tuple<str, str>> giveVariant2(int in)
{
    if (in == 1) return make_tuple("ok", 10);
    if (in == 2) return make_tuple("ok", 88);
    else         return make_tuple("error", "unexpected_int");
}

variant<int, str> giveVariant3(int in)
{
    if (in == 1) return "ok";
    if (in == 2) return 88;
    else         return "error";
}

variant<int, tuple<str, int>> giveVariant4(int in)
{
    if (in == 1) return make_tuple("ok", 10);
    if (in == 2) return make_tuple("ok", 88);
    else         return 0;
}

int main()
{




    variant<tuple<str, int>, tuple<str, str>> myVari = giveVariant2(1);




    variant<tuple<int, str>, tuple<str, str>, int, tuple<int, str, str>> varTuple = 54;


    match (varTuple)
    (
        pattern(as<tuple<int, str>>(ds(arg, arg))) = [](int i, str s) { cout << "int, str: " << i << " - " << s << "\n"; },
        pattern(as<tuple<str, str>>(ds(arg, arg))) = [](str s1, str s2) { cout << "str, str: " << s1 << " - " << s2 << "\n"; },
        pattern(as<int>(arg)) = [](int x) { cout << "int: " << x << "\n"; },
        pattern(as<tuple<int, str, str>>(ds(arg, arg, arg))) = [](int i, str s1, str s2) { cout << "Yolo"; }
    );


    return 0;
}
