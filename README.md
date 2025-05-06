# pystring

A Python-style string manipulation library in modern C++.

- Python-like slicing: `s(1, 4)` → `"bcd"`
- Negative indices
- `+`, `*`, `==`, `[]` operators
- `split()`, `join()`, `strip()`, `startswith()`, `endswith()`, `count()`
- Prefix/suffix checks: `starts_with()`, `ends_with()`  
- Substring counting: `count("na")` → `2`  

## Installation

### Option 1: Add as Subdirectory (Recommended)

1. Clone `pystring` into your own project directory:

```bash
git clone https://github.com/gowthaman01/pystring
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

### Option 2: Install Globally

1. Install `pystring` once on your system:

```bash
git clone https://github.com/gowthaman01/pystring
cd pystring
cmake -Bbuild
cmake --build build
sudo cmake --install build
```

2. In the CMakeLists.txt of any project where you want to use pystring, add:

```cmake
find_package(pystring REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE pystring::pystring)
```

> 💡 Again, replace `my_app` with the name of your own CMake executable target.

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
