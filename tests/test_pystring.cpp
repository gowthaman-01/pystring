#include "test_pystring.hpp"

#include "../include/pystring.hpp"

#include <cassert>
#include <iostream>
#include <vector>

void run_pystring_tests() {
    run_pystring_slice_tests();
    run_pystring_slice_with_step_tests();
    run_pystring_arithmetic_tests();
    run_pystring_split_join_tests();
    run_pystring_strip_tests();
    run_pystring_count_tests();
    run_pystring_starts_ends_with_tests();
    run_pystring_contains_tests();
    run_pystring_find_tests();
    run_pystring_case_conversion_tests();
    run_pystring_conversion_tests();

    std::cout << "All tests passed!\n";
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

void run_pystring_slice_with_step_tests() {
    pystring s("abcdef");

    // Step = 1 (equivalent to normal slicing)
    assert(s(0, 6, 1).get() == "abcdef");
    assert(s(1, 5, 1).get() == "bcde");

    // Step = 2
    assert(s(0, 6, 2).get() == "ace");
    assert(s(1, 6, 2).get() == "bdf");
    assert(s(0, 5, 2).get() == "ace");
    assert(s(1, 5, 2).get() == "bd");

    // Step = 3
    assert(s(0, 6, 3).get() == "ad");

    // Full reverse
    assert(s(5, -7, -1).get() == "fedcba");
    assert(s(5, -10, -1).get() == "fedcba");
    assert(s(5, std::numeric_limits<int>::min(), -1).get() == "fedcba");

    // Partial reverse
    assert(s(5, 0, -1).get() == "fedcb");
    assert(s(4, 1, -1).get() == "edc");

    // Negative step with negative indices
    assert(s(-1, -7, -1).get() == "fedcba");
    assert(s(-2, -5, -1).get() == "edc");

    // Out-of-bounds with positive step
    assert(s(-100, 100, 2).get() == "ace");

    // Out-of-bounds with negative step
    assert(s(100, -100, -2).get() == "fdb");

    // Edge cases
    assert(s(2, 2, 1).get() == "");
    assert(s(4, 2, 1).get() == "");
    assert(s(2, 2, -1).get() == "");
    assert(s(2, 4, -1).get() == "");
    
    // Step = 0: returns ""
    assert(s(0, 5, 0).get() == "");

    // Empty string
    pystring empty("");
    assert(empty(0, 0, 1).get() == "");
    assert(empty(0, 0, -1).get() == "");
    assert(empty(10, -10, 1).get() == "");
    assert(empty(10, -10, -1).get() == "");
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
    
    pystring s2("s    ");
    s2.rstrip();
    assert(s2.get() == "s");
    
    pystring s3("    s    ");
    s3.strip();
    assert(s3.get() == "s");
}

void run_pystring_count_tests() {
    pystring s("banana");
    assert(s.count("na") == 2);

    pystring s2("hello");
    assert(s2.count("z") == 0);
  
    pystring s3("abc");
    assert(s3.count("abc") == 1);
  
    pystring s4("aaaa");
    assert(s4.count("aa") == 2);
   
    pystring s5("abc");
    assert(s5.count("") == 0);
}

void run_pystring_starts_ends_with_tests() {
    pystring s("hello world");
    assert(s.starts_with("hello"));
    assert(!s.starts_with("world"));

    pystring s2("data.csv");
    assert(s2.ends_with(".csv"));
    assert(!s2.ends_with(".txt"));

    pystring s3("abcdef");
    assert(s3.starts_with(""));
    assert(s3.ends_with(""));

    pystring s4("abc");
    assert(!s4.starts_with("abcd"));
    assert(!s4.ends_with("abcd"));

    pystring s5("aaaaa");
    assert(s5.starts_with("aaa"));
    assert(s5.ends_with("aaa"));
}

void run_pystring_contains_tests() {
    pystring s("hello world");
    assert(s.contains("hello"));
    assert(s.contains("world"));
    assert(s.contains("lo wo"));
    assert(!s.contains("planet"));
    assert(!s.contains("hello world!"));
    assert(s.contains(""));                 // empty substring always returns true
}

void run_pystring_find_tests() {
    pystring s("hello world");

    assert(s.find("hello") == 0);
    assert(s.find("world") == 6);
    assert(s.find("lo") == 3);
    assert(s.find("planet") == std::string::npos);
    assert(s.find("") == 0);                // consistent with std::string behavior
}

void run_pystring_case_conversion_tests() {
    pystring s1("Hello World");
    assert(s1.upper().get() == "HELLO WORLD");
    assert(s1.lower().get() == "hello world");

    pystring s2("123abc!");
    assert(s2.upper().get() == "123ABC!");
    assert(s2.lower().get() == "123abc!");

    pystring empty("");
    assert(empty.upper().get() == "");
    assert(empty.lower().get() == "");
}

void run_pystring_conversion_tests() {
    // Valid integer strings
    assert(pystring("42").to_int() == 42);
    assert(pystring("-7").to_int() == -7);
    assert(pystring("0009").to_int() == 9);

    // Valid floating point strings
    assert(pystring("3.14").to_double() == 3.14);
    assert(pystring("-2.5").to_double() == -2.5);
    assert(pystring("0.0").to_double() == 0.0);

    // Scientific notation
    assert(pystring("1e2").to_double() == 100.0);
    assert(pystring("-1.5e1").to_double() == -15.0);

    // Edge cases
    assert(pystring("0").to_int() == 0);
    assert(pystring("0.0001").to_double() == 0.0001);
}



