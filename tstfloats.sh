#!/bin/bash

GREEN="\\033[32;7m"
GREEN_RES="\\033[32m"
RED="\\033[31;5m"
RED_RES="\\033[31m"
BLUE="\\033[34m"
MAGENTA="\\033[35m"
YELLOW="\\033[33m"
NORMAL="\\033[m"

set size rand_number
gen_random() {
    rand_number=""
    for a in $(seq $size); do
	rand_number=${rand_number}${RANDOM}
    done
    rand_number=${rand_number}"."
    for a in $(seq $size); do
	rand_number=${rand_number}${RANDOM}
    done
}

if [ $# -ne 3 ]; then
    op="+"
    n_tests=20
    size=1
else
    op=$1
    n_tests=$2
    size=$3
fi
export ne op rand_number n_tests size;

for a in $(seq $n_tests); do
    gen_random
    ne=$rand_number
    gen_random
    echo $ne $op $rand_number
    diff <(echo $ne $op $rand_number | ./calc) <(echo $ne $op $rand_number | bc)
done
