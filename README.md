# pystring

A Python-style string manipulation library in modern C++.

- Python-like slicing: `s(1, 4)` → `"bcd"`
- Negative indices
- `+`, `*`, `==`, `[]` operators
- `split()`, `join()`, `strip()`, `startswith()`, `endswith()`, `count()`
- Prefix/suffix checks: `starts_with()`, `ends_with()`
- Substring counting: `count("na")` → `2`

## Installation

1. Clone `pystring` into your own project directory:

```bash
git clone https://github.com/gowthaman-01/pystring.git
```

2. Your project structure might look like:

```
your_project/
├── CMakeLists.txt
├── main.cpp
└── pystring/              ← cloned here
```

3. In your own CMakeLists.txt, add these lines to build your app and link pystring:

```cmake
add_executable(my_app main.cpp)

add_subdirectory(pystring)
target_link_libraries(my_app PRIVATE pystring::pystring)
```

> 💡 Replace `my_app` with the name of your own CMake executable target.

#### ⚠️ Warning

This library uses modern C++ features like `if constexpr` and `std::is_arithmetic_v`, so you **must** enable C++17 in your project:

```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

If you don’t, you may get errors like:

```
error: no template named 'is_arithmetic_v' in namespace 'std'
```

## Usage

See [**docs/usage.md**](docs/usage.md) for more detailed examples.

```cpp
#include <pystring.hpp>

int main() {
    pystring s("hello world");
    auto sliced = s(0, 5);
    std::cout << sliced.get() << "\n";    // "hello"
}
```
