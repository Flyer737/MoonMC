# Linux

Use any modern and up-to-date linux distro.

## Install build dependencies
* `gcc`
* `cmake`
* `zlib1g-dev`
* `openjdk-8-jdk`
* `libgl1-mesa-dev`

Once downloaded and/or extracted, open the terminal and cd into the MoonMC directory.
Run the following:
```
mkdir build && mkdir install
cd build
cmake -DCMAKE_INSTALL_PREFIX=../install ../src
# build & install (use -j# with # being the number of cores your CPU has.)
make -j4 install
```

Once completed, the built MoonMC executable will be in the install folder.
