#include "../include/pystring.hpp"

#include <algorithm>
#include <cmath>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>

namespace gstd {

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

pystring pystring::operator+=(const pystring &other) {
    data_ += other.data_;
    return *this;
}

pystring pystring::operator*(int multipler) {
    return pystring(multiply_string(data_, multipler));
}

pystring pystring::operator*=(int multipler) {
    data_ = multiply_string(data_, multipler);
    return *this;
}

bool pystring::operator==(pystring &other) {
    return data_ == other.data_;
}

pystring pystring::operator[](int idx) {
    // Adjust for negative index
    if (idx < 0) {
        idx += data_.length();
    }
    
    return pystring(data_.at(idx));
}

pystring pystring::operator()(int start_idx, int end_idx, int step) {
    // A step of 0 is not allowed
    if (step == 0) {
        return pystring();
    }
    
    int length = static_cast<int>(data_.length());
    
    // If no end_idx was provided
    if (end_idx == std::numeric_limits<int>::max()) {
         end_idx = length;
    }
    
    // Adjust for negative indices
    if (start_idx < 0) {
        start_idx += length;
    }
    if (end_idx < 0) {
        end_idx += length;
    }
    if (start_idx > end_idx) {
        if (step < 0) {
            std::swap(start_idx, end_idx);
        } else {
            // Step is positive, so cannot go backward
            return pystring();
        }
    }
    
    // Adjust for out of bound indices
    start_idx = std::max(start_idx, 0);
    end_idx = std::min(end_idx, length);
    
    std::string temp_str = data_.substr(start_idx, end_idx - start_idx);
    
    if (step == 1) {
        return pystring(temp_str);
    }
    if (step == -1) {
        std::reverse(temp_str.begin(), temp_str.end());
        return pystring(temp_str);
    }

    int positive_step = std::abs(step);
    std::string s{};
    
    for (int i = start_idx; i < end_idx; i += positive_step) {
        s += temp_str[i];
    }
    
    if (step < 0) {
        std::reverse(s.begin(), s.end());
    }
    
    return pystring();
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

std::vector<std::string> pystring::split(std::string_view delimiter) {
    if (delimiter.empty()) {
        return {data_};
    }
    
    std::vector<std::string> v;
    
    size_t cur{};
    while (cur < data_.length()) {
        auto idx = data_.find(delimiter, cur);
        if (idx == std::string::npos) {
            v.emplace_back(data_.substr(cur, data_.length() - cur));
            break;
        }
        v.emplace_back(data_.substr(cur, idx - cur));
        cur = idx + delimiter.length();
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

} // namespace gstd
