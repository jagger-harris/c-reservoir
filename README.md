# Reservoir library

Reservoir library is a header-only C library that contains many useful data structures, safe file management, and so on. It is written in C99, with minimal dependencies. The goal is to make C safe and easy to use.

It is currently a work-in-progress.

Requires git and CMake >=3.0 to build.

## Documentation

You can read the documentation [here](https://jagger-harris.github.io/reservoir/).

## Dependencies

- CMake >=3.0
- C99 compiler

## Testing

Clone the repository:

```shell
git clone https://github.com/jagger-harris/reservoir.git
cd reservoir
```

Using provided test script:

```shell
./test.sh
```

Without test script:

```shell
mkdir build
cd build
cmake ..
make
ctest --verbose --rerun-failed --output-on-failure
```

## Contributing

See the contributing guidelines [here](docs/CONTRIBUTING.md).

## License

- [MIT](https://choosealicense.com/licenses/mit/)
