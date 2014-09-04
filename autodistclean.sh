#!/bin/bash

rm -rf aclocal.m4 autom4te.cache INSTALL autoscan.log COPYING
rm -rf compile depcomp install-sh ltmain.sh missing stamp-h1 libtool
rm -rf configure config.{guess,h,h.in,h.in~,log,status,sub} 
rm -rf Makefile{,.in}
rm -rf src/{.deps,.libs} src/Makefile{,.in}
rm -rf include/Makefile{,.in}
rm -rf include/moss/Makefile{,.in}

