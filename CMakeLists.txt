cmake_minimum_required(VERSION 3.10)
project(pystring LANGUAGES CXX)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the library target using the implementation file
add_library(pystring src/pystring.cpp)

# Specify public include directory for consumers of the library
target_include_directories(pystring PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>      # during local build
    $<INSTALL_INTERFACE:include>                                # after installation
)

# Install the compiled library (static/shared)
install(TARGETS pystring EXPORT pystringTargets
    ARCHIVE DESTINATION lib                                     # .a (static library)
    LIBRARY DESTINATION lib                                     # .so/.dylib (shared library)
    RUNTIME DESTINATION bin                                     # .exe (if ever added)
)

# Install the public header files
install(DIRECTORY include/ DESTINATION include)

# Export CMake targets so users can do `find_package(pystring)`
install(EXPORT pystringTargets
    FILE pystringConfig.cmake
    NAMESPACE pystring::                                        # so users write `pystring::pystring`
    DESTINATION lib/cmake/pystring
)

# Create an alias target: allows `pystring::pystring` instead of just `pystring`
add_library(pystring::pystring ALIAS pystring)
