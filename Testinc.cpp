#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <variant>
#include <tuple>
#include <cstdio>
#include "mpark/patterns.hpp"

using namespace std;
using namespace mpark::patterns;
using str = std::string;

template <typename T>
void println(T var) { cout << var << endl; }

variant<int, string> multiReturnType(int in)
{
    if (in == 1) return 10;
    if (in == 2) return "11";
    else         return "Hello World!";
}

class lit : public string {};

variant<tuple<lit, int>, tuple<lit, lit>> litVariReturn(int in)
{
    if (in == 1) return make_tuple((lit)"ok", 42);
    if (in == 2) return make_tuple((lit)"ok", 85);
    else         return make_tuple((lit)"error", (lit)"unexpected_type");
}

tuple<lit, int> litVariReturn2(int in)
{
    if (in == 1) return make_tuple((lit)"ok", 42);
    if (in == 2) return make_tuple((lit)"ok", 85);
    else         return make_tuple((lit)"error", 404);
}

variant<tuple<lit, int>, tuple<lit, lit>> litVariReturn3(int in)
{
    if (in == 1) return make_tuple((lit)"ok", 42);
    if (in == 2) return make_tuple((lit)"not", 85);
    else         return make_tuple((lit)"error", (lit)"unexpected_type");
}

// variant<tuple<lit, int>, tuple<lit, lit>> function(int in) {
//     return match(in)(
//         pattern(0, 0) = [] { std::printf("fizzbuzz\n"); },
//         pattern(0, _) = [] { std::printf("fizz\n"); },
//         pattern(_, 0) = [] { std::printf("buzz\n"); },
//         pattern(_, _) = [i] { std::printf("%d\n", i); }
//         );
// }

// match (giveVariant2(1))
// {
//     (lit ok, int variInt) => println("ok: " + variInt)
//     (lit error, lit msg)  => println("error: " + msg)
// }

// (lit, int | lit, lit)function(int in)
// {
//     if (in == 1) return ok, 10
//     if (in == 2) return ok, 88
//     else         return error, unexpected_int
// }

int main()
{

    // fizzbuzz();




    // // variant
    // variant<int, string> val1 = multiReturnType(1);
    // if (const auto ptr = get_if<int>(&val1))
    // {
    //     cout << "int: " << *ptr << "\n";
    // }
    // else if (const auto ptr = get_if<string>(&val1))
    // {
    //     cout << "string: " << *ptr << "\n";
    // }

    // // atom
    // variant<tuple<lit, int>, tuple<lit, lit>> litVari = litVariReturn(1);

    // if (const auto ptr = get_if<tuple<lit, int>>(&litVari)) 
    // {
    //     tuple<lit, int> t = *ptr;
    //     cout << "ok: " << get<1>(t) << "\n";
    // }
    // else if (const auto ptr = get_if<tuple<lit, lit>>(&litVari))
    // {
    //     tuple<lit, lit> t = *ptr;
    //     cout << "error: " << get<1>(t) << "\n";
    // }

    // // litVariReturn3
    // variant<tuple<lit, int>, tuple<lit, lit>> litVari3 = litVariReturn3(1);

    // if (const auto ptr = get_if<tuple<lit, int>>(&litVari3); ) 
    // {
    //     tuple<lit, int> t = *ptr;
    //     cout << "ok: " << get<1>(t) << "\n";
    // }
    // else if (const auto ptr = get_if<tuple<lit, lit>>(&litVari3))
    // {
    //     tuple<lit, lit> t = *ptr;
    //     cout << "error: " << get<1>(t) << "\n";
    // }



    // variant<tuple<lit, int>, tuple<lit, lit>> litVari = litVariReturn3(1);

    // // IDENTIFIERS(x, y);
    // match(litVari)
    // (
    //     pattern(ds((lit)"ok"), arg(as<int>)) = [](int variInt) { println("ok: " + variInt) },
    //     pattern(ds((lit)"error"), arg(as<string>)) = [](string msg) { println("error: " + msg); },

    //     // pattern(as<tuple<lit, int>>(_)) = []() { printf("1\n"); },
    //     // pattern(as<tuple<lit, lit>>(_)) = []() { printf("1\n"); },

    //     // pattern(as<lit>((lit)"ok"), as<int>(_)) = []() { printf("1\n"); },
    //     // pattern(as<lit>((lit)"ok"), as<int>(_)) = []() { printf("1\n"); },
    //     // pattern(0, _) = [] { std::printf("fizz\n"); },
    //     // pattern(_, 0) = [] { std::printf("buzz\n"); },
    //     // pattern(_, _) = [i] { std::printf("%d\n", i); }
    // );

    // // variant<tuple<lit, int>, tuple<lit, str>> litVari = litVariReturn3(1);
    // tuple<int, string> my_tuple = make_tuple(101, "hello");
    // tuple<int, string> my_tuple = make_tuple(101, "hello");
    // // IDENTIFIERS(i, s);
    // match(my_tuple)
    // (
    //     // working
    //     // pattern(ds(i, s)) = [](auto i, auto s) { cout << "Result: " << i << " - " << s << "\n"; }
    //     // pattern(ds(i, s)) = [](int i, string s) { cout << "Result: " << i << " - " << s << "\n"; }

    //     pattern(ds(arg, arg)) = [](int i, string s) { cout << "Result: " << i << " - " << s << "\n"; }


    //     // pattern(ds(as<int>(_), as<string>(_))) = [](int i, string s) { cout << "Result: " << i << " - " << s << "\n"; }
    //     // pattern(as<tuple<int, string>>(ds(i, s)) = [](int i, string s) { cout << "Result: " << i << " - " << s << "\n"; }
    //     // pattern(as<tuple<lit, int>>(_)) = [] { std::cout << "int\n"; }

    //     // pattern(ds(i, s)) = [](int i, string s) { cout << "Result: " << i << " - " << s << "\n"; }
    // );


    // variant<tuple<int, str>, tuple<str, str>> varTuple = make_tuple(101, "hello");
    // // variant<tuple<int, str>, tuple<str, str>> varTuple = make_tuple("test", "bob");
    // // IDENTIFIERS(i, s);
    // match(varTuple)
    // (
    //     // working
    //     // pattern(as<tuple<int, str>>(_)) = [] { std::cout << "int, str\n"; },
    //     // pattern(as<tuple<str, str>>(_)) = [] { std::cout << "str, str\n"; }

    //     pattern(as<tuple<int, str>>(ds(arg, arg))) = [](int i, string s) { cout << "int, str: " << i << " - " << s << "\n"; },
    //     pattern(as<tuple<str, str>>(ds(arg, arg))) = [](string s1, string s2) { cout << "str, str: " << s1 << " - " << s2 << "\n"; }

    //     // pattern(as<tuple<int, str>>(_)) = [](int i, string s) { cout << "asdasd\n"; }
    //     // pattern(as<tuple<int, str>>(_)) = [] { std::cout << "str, str\n"; }


    //     // pattern(ds(i, s)) = [](auto i, auto s) { cout << "Result: " << i << " - " << s << "\n"; }
    //     // pattern(ds(i, s)) = [](int i, string s) { cout << "Result: " << i << " - " << s << "\n"; }

    //     // pattern(ds(arg, arg)) = [](int i, string s) { cout << "Result: " << i << " - " << s << "\n"; }


    //     // pattern(ds(as<int>(_), as<string>(_))) = [](int i, string s) { cout << "Result: " << i << " - " << s << "\n"; }
    //     // pattern(as<tuple<int, string>>(ds(i, s)) = [](int i, string s) { cout << "Result: " << i << " - " << s << "\n"; }

    //     // pattern(ds(i, s)) = [](int i, string s) { cout << "Result: " << i << " - " << s << "\n"; }
    // );


    

    // variant<int, str> val1 = multiReturnType(1);
    // if (const auto ptr = get_if<int>(&val1))
    // {
    //     cout << "int: " << *ptr << "\n";
    // }
    // else if (const auto ptr = get_if<string>(&val1))
    // {
    //     cout << "string: " << *ptr << "\n";
    // }

    // // variant<int, str> v = 42;
    // match(val1)
    // (
    //     pattern(as<int>(_)) = [] { std::cout << "int\n"; },
    //     pattern(as<str>(_)) = [] { std::cout << "str\n"; }
    // );

    // match(v)
    // (
    //     pattern(as<int>(_)) = [] { std::cout << "int\n"; },
    //     pattern(as<str>(_)) = [] { std::cout << "str\n"; }
    // );

    // match (litVari)
    // {
    //     (lit ok, int variInt)   => println("ok: " + variInt)
    //     (lit error, string msg) => println("error: " + msg)
    // }



    variant<tuple<int, str>, tuple<str, str>> varTuple = make_tuple(101, "hello");
    // variant<tuple<int, str>, tuple<str, str>> varTuple = make_tuple("test", "bob");

    match (litVari)
    {
        (int i, str s) => cout << "int, str: " << i << " - " << s << "\n"
        (str s1, str s2) => cout << "str, str: " << s1 << " - " << s2 << "\n"
    }

    match(varTuple)
    (
        pattern(as<tuple<int, str>>(ds(arg, arg))) = [](int i, str s) { cout << "int, str: " << i << " - " << s << "\n"; },
        pattern(as<tuple<str, str>>(ds(arg, arg))) = [](str s1, str s2) { cout << "str, str: " << s1 << " - " << s2 << "\n"; }
    );


    



    return 0;
}