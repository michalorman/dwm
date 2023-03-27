# dwm - dynamic window manager

My build of the [dwm](https://dwm.suckless.org/).

Included patches:

- `actualfullscreen` to toggle window fullscreen.
- `alwayscenter` to center floating windows.
- `attachaside` attach new clients in stacking area instead of
becoming a new master window.
- `colorbar` more options of changing bar colors.
- `focusonclick` focus client only by mouse click instead of hovering
over the window.
- `fullgaps` add gaps between windows.
- `movestack` allow moving clients around the stack and swap with
the master.
- `noborderselflickerfix` hide border, when only one window is visible.
- `notitle` remove window title from the bar.
- `scratchpads` enable scratchpads for dwm.
- `viewontag` focus a tag to which a window has been moved to.
- `zeroastenthtag` make 0 a 10th tag instead of a select all.

## Build

dwm requires Xlib, Xinerama and Xft header files:

```sh
pacman -S libx11 libxinerama libxft
```

To build and install dwm run as root:

```sh
make clean install
```

To modify configuration edit the `config.def.h` file. Next
remove the generated `config.h` file and resintall:

```sh
# as root
rm config.h && make clean install
```
