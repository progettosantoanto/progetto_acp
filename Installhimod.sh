#!/bin/bash

LifeV_DIR=$PWD
LifeV_SRC=$LifeV_DIR/himodparallel
LifeV_BUILD=$LifeV_DIR/LifeV-build
LifeV_LIB=$LifeV_DIR/LifeV-install

[ -d $LifeV_DIR ]   || mkdir -p $LifeV_DIR
[ -d $LifeV_SRC ]   || mkdir -p $LifeV_SRC
[ -d $LifeV_BUILD ] || mkdir -p $LifeV_BUILD
[ -d $LifeV_LIB ]   || mkdir -p $LifeV_LIB

HOMESCRIPT=$PWD

pushd $LifeV_BUILD
rm -r CMake* 
cmake \
    -D BUILD_SHARED_LIBS:BOOL=ON \
    -D CMAKE_BUILD_TYPE:STRING=RELEASE \
    -D CMAKE_INSTALL_PREFIX:PATH=${LifeV_LIB}\
    -D CMAKE_C_COMPILER:STRING="/usr/bin/mpicc" \
    -D CMAKE_CXX_COMPILER:STRING="/usr/bin/mpicxx" \
    -D CMAKE_CXX_FLAGS:STRING="-O3 -msse3  " \
    -D CMAKE_C_FLAGS:STRING="-O3 -msse3 " \
    -D CMAKE_Fortran_COMPILER:STRING="/usr/bin/mpif90" \
    -D CMAKE_Fortran_FLAGS:STRING="-Og -g" \
    -D CMAKE_AR:STRING="/usr/bin/ar" \
    -D CMAKE_MAKE_PROGRAM:STRING="/usr/bin/make" \
    -D TPL_ENABLE_AMD=ON \
    -D      AMD_INCLUDE_DIRS=/usr/local/inc \
    -D      AMD_LIBRARY_DIRS=/usr/local/lib \
    -D      AMD_LIBRARY_NAMES=amd \
    -D TPL_ENABLE_BLAS=ON \
    -D      TPL_BLAS_INCLUDE_DIRS=/usr/lapack-3.5.0/lib \
    -D      BLAS_LIBRARY_DIRS=/usr/lapack-3.5.0/lib/ \
    -D      BLAS_LIBRARY_NAMES= \
    -D TPL_ENABLE_Boost=ON \
    -D      Boost_INCLUDE_DIRS=/usr/include \
    -D TPL_ENABLE_BoostLib=ON \
    -D      Boost_NO_BOOST_CMAKE:BOOL=ON \
    -D      BoostLib_INCLUDE_DIRS=/usr/include \
    -D      BoostLib_LIBRARY_DIRS=/usr/lib \
    -D TPL_ENABLE_HDF5=ON \
    -D      HDF5_INCLUDE_DIRS=/usr/include \
    -D      HDF5_LIBRARY_DIRS=/usr/lib \
    -D TPL_ENABLE_LAPACK=ON \
    -D      TPL_LAPACK_INCLUDE_DIRS=/usr/lapack-3.5.0/lib \
    -D      LAPACK_LIBRARY_DIRS=/usr/lapack-3.5.0/lib/ \
    -D      LAPACK_LIBRARY_NAMES= \
    -D TPL_ENABLE_MPI=ON \
    -D      MPI_BASE_DIR:PATH=/usr/lib/openmpi \
    -D ParMETIS_INCLUDE_DIRS="/usr/parmetis/4.0.3/include;/usr/metis/5.1.0/include" \
    -D ParMETIS_LIBRARY_DIRS="/usr/parmetis/4.0.3/lib;/usr/metis/5.1.0/lib" \
    -D TPL_ParMETIS_INCLUDE_DIRS="/usr/parmetis/4.0.3/include;/usr/metis/5.1.0/include" \
    -D TPL_ENABLE_UMFPACK=ON \
    -D      UMFPACK_INCLUDE_DIRS=/usr/local/include \
    -D      UMFPACK_LIBRARY_DIRS=/usr/local/lib \
    -D      UMFPACK_LIBRARY_NAMES=umfpack \
    -D Trilinos_INCLUDE_DIRS:PATH="/usr/trilinos/inc" \
    -D Trilinos_LIBRARY_DIRS:PATH="/usr/trilinos/lib" \
    -D LifeV_ENABLE_TESTS:BOOL=ON \
    -D LifeV_ENABLE_Core:BOOL=ON \
    -D LifeV_ENABLE_ETA:BOOL=ON \
    -D LifeV_ENABLE_HiMod:BOOL=ON \
    -D LifeV_ENABLE_ALL_PACKAGES:BOOL=OFF \
    -D LifeV_ENABLE_STRONG_CXX_COMPILE_WARNINGS:BOOL=ON \
    -D LifeV_ENABLE_CPP11:BOOL=ON\
    -D Core_ENABLE_TESTS=ON \
      ${LifeV_SRC}


make  -j 1 > make.out
#
#make install > make_install.out 2>&1
#
popd

pushd $HOMESCRIPT
