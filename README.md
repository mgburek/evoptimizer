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
To build the example executable you need to enable COMPILE_EXAMPLE cmake option. **By default it's OFF**.
```
cmake ./ -B build -DCOMPILE_EXAMPLE=ON
```