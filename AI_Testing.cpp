// Write a c++ program that reads a file called "input.co" that contains the following:
// "
// (lit, int | lit, lit)function(int in)
// {
//     if (in == 1) return ok, 10
//     if (in == 2) return ok, 88
//     else         return error, unexpected_int
// }
// "

// and converts it to a c++ program and outputs it to a file called "output.cpp" that contains the following:
// "
// variant<tuple<lit, int>, tuple<lit, lit>> function(int in)
// {
//     if (in == 1) return make_tuple((lit)"ok", 10);
//     if (in == 2) return make_tuple((lit)"not", 88);
//     else         return make_tuple((lit)"error", (lit)"unexpected_int");
// }
// "


Write a c++ program that reads a file called "input.co" that contains the following:
"
match (varTuple)
{
    (int i, str s) => cout << "int, str: " << i << " - " << s << "\n"
    (str s1, str s2) => cout << "str, str: " << s1 << " - " << s2 << "\n"
}
"

and converts it to a c++ program and outputs it to a file called "output.cpp" that contains the following:
"
match (varTuple)
(
    pattern(as<tuple<int, str>>(ds(arg, arg))) = [](int i, str s) { cout << "int, str: " << i << " - " << s << "\n"; },
    pattern(as<tuple<str, str>>(ds(arg, arg))) = [](str s1, str s2) { cout << "str, str: " << s1 << " - " << s2 << "\n"; }
);
"

match (varTuple)
{
    (int i, str s) => cout << "int, str: " << i << " - " << s << "\n"
    (str s1, str s2) => cout << "str, str: " << s1 << " - " << s2 << "\n"
}

match (varTuple)
(
    pattern(as<tuple<int, str>>(ds(arg, arg))) = [](int i, str s) { cout << "int, str: " << i << " - " << s << "\n"; },
    pattern(as<tuple<str, str>>(ds(arg, arg))) = [](str s1, str s2) { cout << "str, str: " << s1 << " - " << s2 << "\n"; }
);





int main()
{
    bool insideFunction = false;
    int depth = 0;

    ifstream in("input.co");
    ofstream out("output.cpp");

    

    out.close();

    system("g++ -std=c++11 First.cpp -o First");
    system("./First");

    return 0;
}