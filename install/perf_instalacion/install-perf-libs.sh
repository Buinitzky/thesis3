#!/bin/bash
pwd=$(pwd)
cp "$pwd/libdw.so.1" /usr/lib
cp "$pwd/libunwind.so.8" /usr/lib
cp "$pwd/libunwind-x86_64.so.8" /usr/lib
cp "$pwd/perf" /usr/bin
chmod a+x /usr/bin/perf
ln -s /usr/bin/perf /bin
echo "Instalacion Finalizada..."
