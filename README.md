# gtkmm 4.10 Examples

## Dependencies

Arch:

```console
$ sudo pacman -Sy gtkmm-4.0
```

Debian/Ubuntu:

```console
$ sudo apt install libgtkmm-4.0-dev
```


## Building the Examples

```console
$ cd examples/hello-world
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./example
```

## Examples

### Hello World

Creating a window.

![Hello World](examples/hello-world/screenshot.png)

### Signals

Create a window containing a button, and bind a method to the button's `clicked` signal.

![Signals](examples/signals/screenshot.png)

## Generating Screenshots

Build each example, run it, and take a screenshot of the window.

```console
$ scripts/screenshots.sh
```
