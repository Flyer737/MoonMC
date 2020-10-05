# Linux Build

Getting the project to build and run on Linux is easy if you use any modern and up-to-date linux distribution.

## Build dependencies
* gcc or any other compiler 
* cmake 3.1 or newer
* zlib1g-dev
* openjdk-8-jdk
* libgl1-mesa-dev

Once downloaded and/or extracted, cd into the directory.
Build and install directories have already been created.
```
cd build
cmake -DCMAKE_INSTALL_PREFIX=../install ../src
# build & install (use -j with the number of cores your CPU has)
make -j8 install
```

The built application will be in the install folder. :)
