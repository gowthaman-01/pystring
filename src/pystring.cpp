#include "../include/pystring.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>

namespace {

// Utils
std::string multiply_string(std::string s, int multiplier) {
    std::string res{};
    for (int i = 0; i < multiplier; ++i) {
        res += s;
    }
    return res;
}

}

// Constructors
pystring::pystring() : data_("") {}

pystring::pystring(std::string s) : data_(std::move(s)) {}

pystring::pystring(const char* s) : data_(s) {}

pystring::pystring(char c) : data_(std::string(1, c)) {}

pystring::pystring(bool b) : data_(b ? "true" : "false") {}

// Operator overloads
pystring pystring::operator+(const pystring &other) {
    return pystring(data_ + other.data_);
}

pystring& pystring::operator+=(const pystring &other) {
    data_ += other.data_;
    return *this;
}

pystring pystring::operator*(int multipler) {
    return pystring(multiply_string(data_, multipler));
}

pystring& pystring::operator*=(int multipler) {
    data_ = multiply_string(data_, multipler);
    return *this;
}

bool pystring::operator==(const pystring &other) const {
    return data_ == other.data_;
}

pystring pystring::upper() const {
    std::string result = data_;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return pystring(result);
}

pystring pystring::lower() const {
    std::string result = data_;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return pystring(result);
}

pystring pystring::operator[](int idx) {
    // Adjust for negative index
    if (idx < 0) {
        idx += data_.length();
    }
    
    return pystring(data_.at(idx));
}

pystring pystring::operator()(int start, int stop, int step) {
    // Step of 0 is invalid
    if (step == 0) {
        return pystring("");
    }

    const int len = static_cast<int>(data_.size());

    if (stop == std::numeric_limits<int>::max()) {
        stop = step > 0 ? len : -1;
    }

    // Handle negative indices
    if (start < 0) {
        start += len;
    }
    if (stop < 0) {
        stop += len;
    }

    // Clamp start/stop to valid bounds
    if (step > 0) {
        start = std::max(start, 0);
        stop = std::min(stop, len);
    } else {
        start = std::min(start, len - 1);
        stop = std::max(stop, -1);
    }

    std::string result;

    if (step > 0) {
        for (int i = start; i < stop; i += step) {
            result += data_[i];
        }
    } else {
        for (int i = start; i > stop; i += step) {
            result += data_[i];
        }
    }

    return pystring(result);
}

// Member functions
std::string pystring::get() const {
    return data_;
}

size_t pystring::length() const {
    return data_.length();
}

size_t pystring::size() const {
    return data_.length();
}

void pystring::reverse() {
    std::reverse(data_.begin(), data_.end());
}

pystring pystring::reversed() {
    std::string reverse_data{data_};
    std::reverse(reverse_data.begin(), reverse_data.end());

    return pystring(reverse_data);
}

int pystring::count(std::string_view substr) const {
    if (substr.empty()) {
        return 0;
    }
    
    int count = 0;
    size_t pos = 0;
    while (pos < data_.length()) {
        size_t idx = data_.find(substr, pos);
        if (idx == std::string::npos) {
            return count;
        }
        ++count;
        pos = idx + substr.length();
    }
    
    return count;
}

bool pystring::starts_with(std::string_view substr) const {
    return data_.find(substr) == 0;
}

bool pystring::ends_with(std::string_view substr) const {
    if (substr.length() > data_.length()) {
        return false;
    }
    
    return std::string_view(data_).substr(data_.size() - substr.size()) == substr;
}

int pystring::find(std::string_view substr) const {
    return static_cast<int>(data_.find(substr));
}

bool pystring::contains(std::string_view substr) const {
    return data_.find(substr) != std::string::npos;
}

int pystring::to_int() const {
    return std::stoi(data_);
}

int pystring::to_double() const {
    return std::stod(data_);
}

std::vector<std::string> pystring::split(std::string_view delimiter) const {
    if (delimiter.empty()) {
        return {data_};
    }
    
    std::vector<std::string> v;
    
    size_t pos{};
    while (pos < data_.length()) {
        auto idx = data_.find(delimiter, pos);
        if (idx == std::string::npos) {
            v.emplace_back(data_.substr(pos, data_.length() - pos));
            break;
        }
        v.emplace_back(data_.substr(pos, idx - pos));
        pos = idx + delimiter.length();
    }
    
    return v;
}

pystring pystring::join(std::vector<std::string> &v, std::string_view delimiter) {
    std::string s{};
    
    for (int i = 0; i < v.size(); ++i) {
        // Don't append delimeter for last string
        s += i == v.size() - 1
            ? v[i]
            : v[i] + std::string(delimiter);
    }
        
    return pystring(s);
}

void pystring::lstrip() {
    size_t idx = 0;
    while (idx < data_.length()) {
        if (data_[idx] != ' ') {
            break;
        }
        ++idx;
    }
    
    data_.erase(data_.begin(), data_.begin() + idx);
}

void pystring::rstrip() {
    int idx = static_cast<int>(data_.length() - 1);
    while (idx >= 0) {
        if (data_[idx] != ' ') {
            break;
        }
        --idx;
    }
    
    data_.erase(data_.begin() + idx + 1, data_.end());
}

void pystring::strip() {
    lstrip();
    rstrip();
}

// ostream overload
std::ostream& operator<<(std::ostream& stream, const pystring& ps) {
    stream << ps.get();
    return stream;
}
