#!/bin/bash

while getopts 'gnh' OPTION; do
    case "$OPTION" in
        g)
            cmake .. -DCMAKE_BUILD_TYPE=Debug && make && ./xv6-qemu -g
            ;;
        n)
            cmake .. -DCMAKE_BUILD_TYPE=Debug && make && ./xv6-qemu
            ;;
        h)
            echo "n - Runs xv6 in normal mode. g - Runs xv6 in gdb mode. h - Display this help text."
            ;;
    esac
done