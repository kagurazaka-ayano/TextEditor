#!/usr/bin/env bash
doxygen -q ./Doc/config
echo "output files are at $PWD/Doc/out/(corresponding format)"
