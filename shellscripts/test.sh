#!/bin/sh
g++ -std=c++20 src/main.cpp -o out/pain;

echo "Compiled!"
echo "---------------"

./out/pain -i ./tests/test.pain;