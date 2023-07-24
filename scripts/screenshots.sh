#!/bin/bash

cd examples
for example in ./*; do
  if [ -d "$example" ]; then
    example_name=$(basename "$example")
    echo "Processing example: $example_name"
    cd $example
    make
    "./$example_name" &
    sleep 1
    gnome-screenshot --window --file="screenshot.png"
    sleep 1
    killall "$example_name"
    cd ..
  fi
done
cd ..
