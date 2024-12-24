#!/usr/bin/env bash

rm out 2>/dev/null
make
valgrind --leak-check=full --track-origins=yes -s ./out
