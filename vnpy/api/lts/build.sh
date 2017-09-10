#!/bin/bash
# Written by Suzhengchun on 20160213

set -e
BUILDDIR=build
rm -rf $BUILDDIR
if [ ! -f $BUILDDIR ]; then
    mkdir -p $BUILDDIR
fi
pushd $BUILDDIR
cmake ..
make VERBOSE=1 -j 1
ln -fs `pwd`/lib/vnltsmd.so ../vnltsmd/test/vnltsmd.so
ln -fs `pwd`/lib/vnltstd.so ../vnltstd/test/vnltstd.so
ln -fs `pwd`/lib/vnltsqry.so ../vnltsqry/test/vnltsqry.so
cp ../vnltsmd/test/vnltsmd.* ../
cp ../vnltstd/test/vnltstd.* ../
cp ../vnltsqry/test/vnltsqry.* ../
popd
