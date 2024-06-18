#!/bin/sh

build=false
test=false
test_case=""

if [ "$1" = "build" ]; then
  build=true
fi

if [ "$1" = "test" ] ; then
  test=true
  test_case="$2"
fi

if [ "$2" = "test" ] ; then
  test=true
  test_case="$3"
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
    if [ -n "$test_case" ]; then
      ./tests/"$test_case"
    else
      test=false
    fi
  else
    echo "Build folder not located: ./build.sh build"
  fi
fi

if ! $build && ! $test; then
  echo "Command usage: ./build.sh command [command: build, test <test_case>, build test <test_case>]"
fi
