#!/bin/bash

for dir in examples/*; do
    if [ -d "$dir" ]; then
        echo "Cleaning $dir"
        make -C $dir clean
    fi
done