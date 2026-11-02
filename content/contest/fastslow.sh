#!/bin/bash

FAST=./$1
SLOW=./$1slow
GEN=./$1gen

IN=$1.tin
OUT=$1.tout
EXP=$1.texp

ITERS=0

echo building..
./build $FAST
./build $SLOW
./build $GEN

while [ 1 ]; do
    ITERS=$((ITERS+1))
    echo running case $ITERS
    $GEN > $IN
    $SLOW < $IN > $EXP
    $FAST < $IN > $OUT
    diff $OUT $EXP
    if [ $? -ne 0 ]; then
        echo bad!
        exit 1
    fi
done