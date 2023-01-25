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
    return make_tuple("ok", 10);
    return make_tuple("ok", 88);
    return make_tuple("error", "unexpected_int");
}

variant<int, str> giveVariant3(int in)
{
    if (in == 1) return "ok";
    if (in == 2) return 88;
    else         return "error";
}

variant<int, tuple<str, int>> giveVariant4(int in)
{
    return make_tuple("ok", 10);
    return make_tuple("ok", 88);
    else         return 0;
}

int main()
{






//PLACE HOLDER



(
pattern(as<    lit ok; int variInt) =>;
    tie(ok, =>) =  => println("ok: " + variInt);
pattern(as<    lit error; lit msg)  =;
    tie(error, =) =   => println("error: " + msg);


    return 0;
}
