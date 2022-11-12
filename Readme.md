Arduino Nibbles
===============
A collection of arduino mini-programs.

## Getting Started
Run `git submodule update` if cloned without the `--recurse-submodules` option.

### Configure
```sh
cmake --toolchain Arduino-CMake-Toolchain/Arduino-toolchain.cmake -B build
```
and edit `build/BoardOptions.cmake` to match your Arduino model.
then, rerun the same `cmake` command to finish configuring.

### Build
```sh
cd build
make <target>
```
where `<target>` is one of the program names (as specified in `CMakeLists.txt`),
or blank to make all.

### Upload
```
make SERIAL_PORT=<port> <target>-upload
```
where `<port>` is the port to which the board is connected, e.g. `/dev/ttyUSB0`.
Again, run in the `build` directory, with the desired `<target>`.
