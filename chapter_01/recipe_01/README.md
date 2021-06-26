# Program with option base
Refer to: https://www.boost.org/doc/libs/1_37_0/doc/html/program_options/tutorial.html
## How to build
```
mkdir build
cd build
cmake ..
cmake --build .
```

## How to run
**1. Show help option**
```
./bin/main --help

All options:
  --apples arg          how many apples do you have
  --oranges arg         how many oranges do you have
  --help                produce help message
```

```
./bin/main --apples=3 --oranges=4

Fruits count: 7
```
