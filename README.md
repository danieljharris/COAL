# COAL

A C++ transpiler to convert my new language "COAL" into C++. Plays with new ways to approach program syntax

# Examples

### Easy return of tuples
```
(str, int, int)returnBack(int x)
{
    return "xxxx", 88, x
}
```

### Return vairables of different types
```
(int | str)giveVariant3(int in)
{
    if (in == 1) return "ok"
    if (in == 2) return 88
    else         return "error"
}
```

### Multiple types with tuples
```
(int | str, int)giveVariant4(int in)
{
    if (in == 1) return "ok", 10
    if (in == 2) return "ok", 88
    else         return 0
}
```

### Pattern matching
```
match (varTuple)
{
    (int i, str s) => cout << "int, str: " << i << " - " << s << "\n"
    (str s1, str s2) => cout << "str, str: " << s1 << " - " << s2 << "\n"
    (int x) => cout << "int: " << x << "\n"
    (int i, str s1, str s2) => cout << "Yolo"
}
```

# How to run

clear && g++ COAL.cpp -o COAL && ./COAL

clear && g++ -std=c++20 Testinc.cpp -o Testinc && ./Testinc
