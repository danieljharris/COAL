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

void voidFunc()
{
    println("Testing!");
}

int myFunction()
{
    return 8;
}

tuple<int, int> myDoubleFunction()
{
    return make_tuple(37, 42);
}

tuple<str, int, int> returnBack(int x)
{
    return make_tuple("xxxx", 88, x);
}

int main()
{
    println("Yolo World!");


    int counter = 0;


    println(counter);


    voidFunc();


    int first = myFunction();


    println(first);
    println("--------------------");


    int second; int third;
    tie(second, third) = myDoubleFunction();


    println(second);
    println(third);
    println("--------------------");


    tuple<int, int> holdingTuple = myDoubleFunction();
    int u = get<0>(holdingTuple);
    int k = get<1>(holdingTuple);


    println(u);
    println(k);
    println("--------------------");


    str x; int y; int z;
    tie(x, y, z) = returnBack(10);


    println(x);
    println(y);
    println(z);




    return 0;
}
