#!/bin/sh

build=false
test=false

if [ "$1" = "build" ]; then
  build=true
fi

if [ "$1" = "test" ] || [ "$2" = "test" ]; then
  test=true
fi

if $build; then
  if ! [ -d "./build" ]; then
    mkdir build
  fi

  cd build || exit
  cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_EXPORT_COMPILE_COMMANDS=1
  make
  cd .. || exit
fi

if $test; then
  if [ -d "./build" ]; then
    cd build || exit
    ./tests/rsv_test
  else
    echo "Build folder not located: ./build.sh build"
  fi
fi

if ! $build && ! $test; then
  echo "Command usage: ./build.sh command [command: build, test <test_case>, build test <test_case>]"
fi
