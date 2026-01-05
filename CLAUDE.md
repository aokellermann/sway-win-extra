# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

sway-win-extra is a C++23 utility providing Windows 10-style multihead workspace management for swaywm. It allows treating all visible workspaces as a singular entity when switching, so changing workspace doesn't affect other outputs.

## Build Commands

```sh
# Configure and build
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr ..
make

# Install
sudo make install

# Format code
clang-format -i *.cpp *.h
```

## Dependencies

- CMake 3.21+
- C++23 compiler
- [swayipc-cpp](https://github.com/aokellermann/swayipc-cpp) 1.0.0+

## Architecture

Header-only design with `main.cpp` as the only compilation unit. All logic lives in headers under the `swe` namespace:

- **`client.h`** - `swe::client::Client` wraps swayipc-cpp socket connection, provides methods for workspace/container operations
- **`env.h`** - Reads display configuration from `~/.config/sway_win_extra` (one monitor name per line, format: `Make Model Serial`)
- **`workspace.h`** - `changeAllWorkspaces()` switches all outputs simultaneously; `getTargetWorkspace()` maps logical workspace number to physical workspace per-output
- **`container.h`** - `moveContainerToWorkspace()` and `moveContainerToOutput()` for moving focused container
- **`util.h`** - Template string join utility
- **`log.h`** - Simple LOG_INFO/LOG_ERROR macros

## Workspace Numbering Scheme

Physical workspaces are numbered based on output index and logical workspace:
```
physical = output_index + ((logical_target - 1) * num_outputs) + 1
```

For 3 outputs, logical workspace 2 maps to physical workspaces 4, 5, 6.
