#!/bin/bash
# Written by Suzhengchun on 20160213

set -e
export BOOST_LIBRARYDIR="/usr/lib/x86_64-linux-gnu"

BUILDDIR=build
rm -rf $BUILDDIR
if [ ! -f $BUILDDIR ]; then
    mkdir -p $BUILDDIR
fi
pushd $BUILDDIR
cmake ..
make VERBOSE=1 -j 1
ln -fs `pwd`/lib/vnctpmd.so ../vnctpmd/test/vnctpmd.so
ln -fs `pwd`/lib/vnctptd.so ../vnctptd/test/vnctptd.so
cp ../vnctpmd/test/vnctpmd.* ../../vn.trader/gateway/ctpGateway/
cp ../vnctptd/test/vnctptd.* ../../vn.trader/gateway/ctpGateway/
popd
