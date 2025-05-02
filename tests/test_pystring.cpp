#include "test_pystring.hpp"

#include "../include/pystring.hpp"

#include <cassert>
#include <iostream>
#include <vector>

using gstd::pystring;

void run_pystring_tests() {
     run_pystring_slice_tests();
     run_pystring_arithmetic_tests();
     run_pystring_split_join_tests();
     run_pystring_strip_tests();
}

void run_pystring_slice_tests() {
    pystring s("abcdef");

    // Basic forward slicing
    assert(s(0, 3).get() == "abc");
    assert(s(2, 5).get() == "cde");

    // Negative indices
    assert(s(-3, -1).get() == "de");
    assert(s(-6, -1).get() == "abcde");
    assert(s(-6, 3).get() == "abc");
    assert(s(1, -1).get() == "bcde");

    // start == end
    assert(s(2, 2).get() == "");

    // start > end (python returns "", not reversed)
    assert(s(4, 2).get() == "");

    // Negative start, positive end
    assert(s(-4, 5).get() == "cde");

    // start or end out of bounds
    assert(s(-100, 3).get() == "abc");    // clamps to 0
    assert(s(1, 100).get() == "bcdef");   // clamps to end

    // Full slice
    assert(s(0, static_cast<int>(s.get().length())).get() == "abcdef");
    assert(s(-6, static_cast<int>(s.get().length())).get() == "abcdef");
    assert(s(-6, 6).get() == "abcdef");

    // Single-character string
    pystring single("x");
    assert(single(0, 1).get() == "x");
    assert(single(0, 0).get() == "");
    assert(single(-1, 1).get() == "x");

    // Empty string
    pystring empty("");
    assert(empty(0, 0).get() == "");
    assert(empty(-1, 0).get() == "");
}

void run_pystring_arithmetic_tests() {
    pystring s("a");
    
    // Addition
    assert((s + "b").get() == "ab");
    s += "b";
    assert(s.get() == "ab");
    
    // Multiplication
    assert((s * 2).get() == "abab");
    s *= 2;
    assert(s.get() == "abab");
}

void run_pystring_split_join_tests() {
    // Split
    pystring s("Hello/my/name/is/foobar");
    auto v_test = s.split("/");
    std::vector<std::string> v_actual{"Hello", "my", "name", "is", "foobar"};
    assert(v_test == v_actual);
    
    // Join
    auto s2 = pystring::join(v_actual, "/");
    assert(s == s2);
}

void run_pystring_strip_tests() {
    pystring s("   s");
    s.lstrip();
    assert(s.get() == "s");
    
    pystring s1("s    ");
    s.rstrip();
    assert(s.get() == "s");
    
    pystring s2("    s    ");
    s.strip();
    assert(s.get() == "s");
}
