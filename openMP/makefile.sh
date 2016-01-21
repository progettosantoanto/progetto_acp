#!/bin/bash
cd /home/user/project
rm -r buildomp
mkdir buildomp
cd buildomp
cmake ../openMP/ -DCMAKE_BUILD_TYPE=Release
make
./dense
./sparse