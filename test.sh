#!/bin/bash
try() {
    expected="$1"
    input="$2"
    ./Hcc "$input" > tmp.s
    gcc tmp.s -o tmp
    ./tmp
    actual="$?"
    if [ "$actual" != "$expected" ]; then
        echo "$input expected, but got $actual"
        exit 1
    fi
}
try 0 0
try 10 10
# try 256 256
echo OK