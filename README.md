# GTK 4.10 Examples

## Dependencies

Arch:

```console
sudo pacman -Sy gcc pkg-config cmake gtk4 meson ninja
```

Debian/Ubuntu:

```console
sudo apt update && sudo apt install gcc pkg-config cmake libgtk-4-dev meson ninja-build
```

## Building the Examples

```console
./build.sh
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
