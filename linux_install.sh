#!/bin/bash

if [ ! -d linux-build ] ; then
    mkdir linux-build
fi

printf "\n   >>> CMAKE CONFIGURATION <<<\n"
cmake -H. -B./linux-build
cd linux-build

printf "\n  >>> COMPILATION <<<\n"
make

if [ $? == 0 ]; then

    printf "\n   >>> COPYING LIBRARY FILES <<<"
    cd ../lib

    if [ ! -d linux ] ; then
        mkdir linux
    fi

    cp ../linux-build/libpoly.a linux/libpoly.a

    printf "\nDone.\n"
fi
