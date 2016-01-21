#!/bin/bash
cd /home/user/project
rm -r build
mkdir build
cd build
cmake ../sequential/ -DCMAKE_BUILD_TYPE=Release
make
./dense
./sparse