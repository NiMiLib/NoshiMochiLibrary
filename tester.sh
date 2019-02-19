#!/bin/sh
cd test
for file in `find $1 -name "*.cpp"`; do
  echo "$file"
  g++ -std=c++14 -I ./../ $file -o a.out
  ./a.out
done