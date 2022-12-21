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
    return make_tuple("ok", 10);
    return make_tuple("ok", 88);
    return make_tuple("error", "unexpected_int");
}

variant<int, tuple<str, int>> giveVariant4(int in)
{
    return make_tuple("ok", 10);
    return make_tuple("ok", 88);
    return make_tuple("error", "unexpected_int");
}

int main()
{
    str; int | str; str;
    tie(str, str, str) = giveVariant2(1);




    return 0;
}
