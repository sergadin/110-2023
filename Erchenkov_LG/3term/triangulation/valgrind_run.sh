#!/usr/bin/env bash
#

rm triangulation.out 2>/dev/null
make
valgrind --leak-check=full --track-origins=yes -s ./triangulation.out
