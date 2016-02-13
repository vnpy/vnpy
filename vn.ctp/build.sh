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
make VERBOSE=1 -j 2
ln -fs `pwd`/lib/libvnctpmd.so ../vnctpmd/test
ln -fs `pwd`/lib/libvnctptd.so ../vnctptd/test
popd
