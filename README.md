# C Reservoir Library

C Reservoir Library is my very own C library that contains many useful data structures, safe file management, and so on. It is written in C89, with minimal dependencies.

It is currently a work-in-progress. 

Requires git and CMake 3.5 or later to build.

## Dependencies
* CMake 3.5 or greater
* C89 compiler

## Compiling and Running
Clone the repository:
```shell
git clone https://github.com/jagger-harris/rsvr.git
cd c-reservoir
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
