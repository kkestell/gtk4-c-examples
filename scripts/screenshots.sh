#!/bin/bash

examples_dir="examples"
build_dir="build"

meson $build_dir
ninja -C $build_dir

for example in "$examples_dir"/*; do
  if [ -d "$example" ]; then
    echo "Processing example: $example"

    example_name=$(basename "$example")
    executable_name="example-$example_name"
    binary_path="$build_dir/$executable_name"

    "$binary_path" &

    sleep 1

    window_id=$(dbus-send --session --dest=org.gnome.Shell --type=method_call --print-reply /org/gnome/Shell org.gnome.Shell.SearchProvider2.GetResultMetas array:dict:string:string "s" "example" | grep 'object path "/org/gnome/Shell/Window/"' | awk '{print $NF}' | tr -d '"' | xargs)
    gnome-screenshot --window=$window_id --file="$example/screenshot.png"

    sleep 1

    killall "$executable_name"
  fi
done

echo "All examples processed."
