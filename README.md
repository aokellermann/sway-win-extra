# sway-win-extra

Personal swaywm extensions that I use.

## Multihead

Win10-like multihead workspace commands for swaywm.

All visible sway workspaces are discrete from each other. Switching a workspace does not affect any others. Using sway-win-extra, you can treat all visible workspaces as a singular entity, similarly to how you can in Win10.

When not using multihead, the commands default to monohead equivalent commands.

## Scratchpad

"Named scratchpads" are already possible using swaywm, but the annoying part is if you have
scratchpad X open and you open scratchpad Y, both X and Y will now be open, with Y on top of X.
I prefer in this case for X to be hidden so only one scratchpad is ever shown (per display output).

## Build

### PKGBUILD

```sh
mkdir build && cd build
curl -o PKGBUILD https://raw.githubusercontent.com/aokellermann/sway-win-extra/master/PKGBUILD
yay -Bi .
```

### Manual

Dependencies:
- CMake (build only)
- [swayipc-cpp](https://github.com/aokellermann/swayipc-cpp)

```shell
git clone git@github.com:aokellermann/sway-win-extra.git
mkdir sway-win-extra/build && cd "$_"
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..
sudo make install
```

## Usage

### Multihead

#### Setup
Define all displays in environment variables `$MON0`-`$MON9`:
```shell
export MON0="Unknown 0x313D 0x00000000"
export MON1="Unknown 2367 AJMG79A000532"
export MON2="Unknown 2367 AJMG79A000521"
```

Display names can be obtained with `swaymsg -t get_outputs`.

#### Switch all workspaces

```shell
sway_win_extra workspaces [number]
```

#### Move container

```shell
sway_win_extra move_container_to [number]
```

### Scratchpad

#### Setup

Floating windows with `app_id` that starts with `scratch` will be hidden, so make sure your named
scratchpads are such.

Example showing two named scratchpads:
1. shell
2. python
```
set $term kitty

set $scratchterm scratch_term
for_window [app_id=$scratchterm] move scratchpad
for_window [app_id=$scratchterm] scratchpad show
bindsym $mod+minus exec sway_win_extra scratchpad_show_except $scratchterm && swaymsg [app_id=$scratchterm] scratchpad show || exec $term --class $scratchterm

set $scratchpy scratch_py
for_window [app_id=$scratchpy] move scratchpad
for_window [app_id=$scratchpy] scratchpad show
bindsym $mod+equal exec sway_win_extra scratchpad_show_except $scratchpy && swaymsg [app_id=$scratchpy] scratchpad show || exec $term --class $scratchpy -e python -q
```

#### Hide showing scratchpad

```shell
sway_win_extra scratchpad_show_except [app_id]
```
