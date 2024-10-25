# Evoptimzer
## How to build and run
To build the library follow these steps from the root directory:

1. Create a build directory:
```
mkdir build
```

2. Configure Cmake files
```
cmake ./ -B build
```

3. Build the project:
```
cmake --build build
```

### Example executable 
To build the example executable you need to enable COMPILE_EXAMPLE option. 
```
cmake ./ -B build -DCOMPILE_EXAMPLE=ON
```

## Running unit tests
To build the tests first run cmake with BUILD_TESTING option enabled.
```
cmake ./ -B build -DBUILD_TESTING=ON
```
Build the project the same way as shown in "**How to build and run**"

To run the tests run the ctest command:
- Directly from the build directory:
```
cd build 
ctest
```
- From root directory:
```
ctest --test-dir build
```