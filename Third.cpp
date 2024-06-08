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

int main()
{
;
;
;
;
;
    ;
;
;
;
;
;
;
;
    variant<tuple<str, int>, tuple<str, str>> myVari = giveVariant2(1);
;
;
    match (testing123)
    (
        pattern(as<tuple<lit, int>>(ds(arg, arg))) = [](lit ok, int variInt) { println("ok: " + variInt); },
        pattern(as<tuple<lit, lit>>(ds(arg, arg))) = [](lit error, lit msg) { println("error: " + msg); }
    );
;
    return 0;
}
