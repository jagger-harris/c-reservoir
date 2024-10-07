#!/bin/sh

build=false
test=false

if ! [ -d "./build" ]; then
  mkdir build
fi

cd build || exit
cmake .. -DCMAKE_C_COMPILER=clang -DCMAKE_EXPORT_COMPILE_COMMANDS=1
make
cd .. || exit

if [ -d "./build" ]; then
  cd build || exit
  ctest --verbose --rerun-failed --output-on-failure
else
  echo "Build folder not located..."
fi
