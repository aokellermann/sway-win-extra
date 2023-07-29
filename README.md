# sway-win-extra

Win10-like multihead workspace commands for swaywm.

All visible sway workspaces are discrete from each other. Switching a workspace does not affect any others. Using sway-win-extra, you can treat all visible workspaces as a singular entity, similarly to how you can in Win10.

When not using multihead, the commands default to monohead equivalent commands.

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

### Setup
Define all displays in environment variables `$MON0`-`$MON9`:
```shell
export MON0="Unknown 0x313D 0x00000000"
export MON1="Unknown 2367 AJMG79A000532"
export MON2="Unknown 2367 AJMG79A000521"
```

Display names can be obtained with `swaymsg -t get_outputs`.

### Switch all workspaces

```shell
sway_win_extra workspaces [number]
```

## Move container

```shell
sway_win_extra move container to [number]
```

