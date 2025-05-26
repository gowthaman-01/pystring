#pragma once

#include <string>
#include <type_traits>
#include <vector>

class pystring {
public:
    pystring();
    pystring(std::string s);
    pystring(const char* s);
    pystring(char c);
    pystring(bool b);
    
    // General constructor for all integral and floating point types
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    pystring(T number) {
        data_ = std::to_string(number);
    }
    
    pystring operator+(const pystring &other);
    pystring& operator+=(const pystring &other);
    pystring operator*(int multipler);
    pystring& operator*=(int multiplier);
    bool operator==(const pystring& other) const;
    pystring operator[](int idx);
    pystring operator()(
        int start = 0,
        int stop = std::numeric_limits<int>::max(),
        int step = 1
    );
  
    std::string get() const;
    size_t length() const;
    size_t size() const;
    void reverse();
    pystring reversed();

    int count(std::string_view substr) const;
    bool starts_with(std::string_view substr) const;
    bool ends_with(std::string_view substr) const;
    int find(std::string_view substr) const;
    bool contains(std::string_view substr) const;
    
    int to_int() const;
    double to_double() const;
    
    pystring upper() const;
    pystring lower() const;
    
    // Whitespace trimming
    void lstrip();
    void rstrip();
    void strip();
    
    std::vector<std::string> split(std::string_view delimiter) const;
    static pystring join(std::vector<std::string> &v, std::string_view delimiter);
    
private:
    std::string data_;
    
};

std::ostream& operator<<(std::ostream& stream, const pystring& ps);
