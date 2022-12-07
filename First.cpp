#include <iostream> 
#include <tuple> 
using namespace std; 
template <typename T> 
void println(T var) { cout << var << endl; } 

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

tuple<int, int, int> returnBack(int x)
{
    return make_tuple(x, 88, x);
}

int main()
{
    println("Yolo World!");

    int counter = 0;

    println(counter);

    voidFunc();

    int first = myFunction();

    int second; int third;
    tie(second, third) = myDoubleFunction();

    println(first);
    println(second);
    println(third);
    println("--------------------");

    int x; int y; int z;
    tie(x, y, z) = returnBack(10);

    println(x);
    println(y);
    println(z);

    return 0;
}
