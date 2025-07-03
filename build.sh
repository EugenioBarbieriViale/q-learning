#!/bin/bash

set -e

g++ src/main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

./a.out

rm a.out

exit
