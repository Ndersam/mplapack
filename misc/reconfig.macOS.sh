#!/bin/bash

USE_CCACHE=yes

if [ x$USE_CCACHE = x"yes" ] ; then
CXX="ccache g++-mp-10" ; export CXX
CC="ccache gcc-mp-10" ; export CC
FC="gfortran-mp-10"; export FC
F77="gfortran-mp-10"; export F77
ccache -M 60G
else
CXX="g++-mp-10" ; export CXX
CC="gcc-mp-10" ; export CC
FC="gfortran-mp-10"; export FC
F77="gfortran-mp-10"; export F77
fi

pushd mplapack/test/compare ; bash gen.Makefile.am.sh ; popd

aclocal ; autoconf ; automake --add-missing
autoreconf --force --install

./configure --prefix=$HOME/MPLAPACK --with-system-gmp=/opt/local --with-system-mpfr=/opt/local --with-system-mpc=/opt/local --enable-gmp=yes --enable-mpfr=yes --enable-_Float128=yes --enable-qd=yes --enable-dd=yes --enable-double=yes --enable-_Float64x=yes --enable-test=yes
