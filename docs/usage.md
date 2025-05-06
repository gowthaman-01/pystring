# pystring

Python-style string manipulation in modern C++.

## Constructors

```cpp
pystring();                                         // ""
pystring("hello");                                  // from const char*
pystring(std::string("hi"));                        // from std::string
pystring('x');                                      // from char → "x"
pystring(true);                                     // from bool → "true"
pystring(42);                                       // from int → "42"
pystring(3.14);                                     // from float → "3.140000"
```

## String value

Use `get()` to retrieve the internal `std::string` from a pystring object.

```cpp
pystring s("hello");
std::string raw = s.get();                          // "hello"
```

## Operators

### Addition

```cpp
pystring a("foo"), b("bar");
(a + b).get();                                      // "foobar"

pystring s("foo");
s += "bar";                                         // s == "foobar"
```

### Multiplication

```cpp
pystring s("a");
(s * 3).get();                                      // "aaa"

pystring s("ab");
s *= 2;                                             // s == "abab"
```

### Equality

```cpp
pystring s1("test"), s2("test");
bool same = (s1 == s2);     // true
```

### Indexing

```cpp
pystring s("hello");
s[0].get();                                         // "h"
s[-1].get();                                        // "o"
```

## Slicing

```cpp
pystring s("abcdef");

// Basic forward slicing
s(0, 3).get();                                      // "abc"
s(2, 5).get();                                      // "cde"

// Negative indices
s(-3, -1).get();                                    // "de"
s(-6, -1).get();                                    // "abcde"
s(-6, 3).get();                                     // "abc"
s(1, -1).get();                                     // "bcde"

// Edge cases
s(2, 2).get();                                      // "" (start == end)
s(4, 2).get();                                      // "" (start > end, step > 0)

// Mixed signs
s(-4, 5).get();                                     // "cde"
s(-100, 3).get();                                   // "abc"   (start < 0 clamps to 0)
s(1, 100).get();                                    // "bcdef" (end > size clamps to size)

// Full slice
s(0, s.length()).get();                             // "abcdef"
s(-6, s.length()).get();                            // "abcdef"
s(-6, 6).get();                                     // "abcdef"

// Single character
pystring single("x");
single(0, 1).get();                                 // "x"
single(0, 0).get();                                 // ""
single(-1, 1).get();                                // "x"

// Empty string
pystring empty("");
empty(0, 0).get();                                  // ""
empty(-1, 0).get();                                 // ""
```

## Methods

### Length

```cpp
pystring s("abc");
s.length();                                         // 3
s.size();                                           // 3
```

### Reverse

```cpp
pystring s("abc");
s.reverse();                                        // s == "cba"

pystring s("abc");
auto r = s.reversed();                              // "cba"
```

### Count

```cpp
pystring s("banana");
s.count("na");                                      // 2
```

### Start with, ends with

```cpp
pystring s("hello");
s.starts_with("he");                                // true

pystring s("file.txt");
s.ends_with(".txt");                                // true
```

## Trimming

```cpp
pystring s1("  x");
s1.lstrip();                                        // "x"

pystring s2("x   ");
s2.rstrip();                                        // "x"

pystring s3("  x  ");
s3.strip();                                         // "x"
```

## Split and Join

```cpp
pystring s("a/b/c");
auto v = s.split("/");
```

```cpp
std::vector<std::string> parts = {"a", "b", "c"};
pystring joined = pystring::join(parts, "/");       // "a/b/c"
```

## Printing

```cpp
pystring s("hello");
std::cout << s;                                     // prints: hello
```
