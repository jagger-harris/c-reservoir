# Reservoir C Library

Reservoir C Library is my very own C library that contains many useful data structures, safe file management, and so on. It is written in C89, with minimal dependencies. The goal is to make C safe and easy to use.

It is currently a work-in-progress. 

Requires git and CMake 3.5 or later to build.

## Documentation
You can read the documentation [here](https://jagger-harris.github.io/c-reservoir/).

## Dependencies
* CMake 3.5 or greater
* C89 compiler

## Compiling and Running
Clone the repository:
```shell
git clone https://github.com/jagger-harris/c-reservoir.git
cd reservoir
```

Using provided build script:
```shell
./build.sh build
```

Without build script:
```shell
mkdir build
cd build
cmake ..
make
```

Using testing with build script:
```shell
./build.sh test <test_case>
```

Without build script:
```shell
./tests/<test_case>
```

## Contributing
See the contributing guidelines [here](docs/CONTRIBUTING.md).

## License
- [MIT](https://choosealicense.com/licenses/mit/)
