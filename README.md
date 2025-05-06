# pystring

A Python-style string manipulation library in modern C++.

- Python-like slicing: `s(1, 4)` → `"bcd"`
- Negative indices
- `+`, `*`, `==`, `[]` operators
- `split()`, `join()`, `strip()`, `startswith()`, `endswith()`, `count()`

## Installation

### Option 1: Use as Subdirectory (Recommended)

```bash
git clone https://github.com/gowthaman01/pystring
```

In your `CMakeLists.txt`:

```cmake
add_subdirectory(pystring)
target_link_libraries(my_app PRIVATE pystring::pystring)
```

### Option 2: Install Globally

```bash
git clone https://github.com/gowthaman01/pystring
cd pystring
cmake -Bbuild
cmake --build build
sudo cmake --install build
```

Then in your own project:

```cmake
find_package(pystring REQUIRED)
target_link_libraries(my_app PRIVATE pystring::pystring)
```

## Usage

See [**docs/usage.md**](docs/usage.md) for complete examples and API coverage.

```cpp
#include <pystring.hpp>

int main() {
    pystring s("hello world");
    auto sliced = s(0, 5);
    std::cout << sliced.get() << "\n";    // "hello"
}
```

## License

MIT License © 2025 Gowthaman Aravindan
