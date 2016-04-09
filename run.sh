#!/bin/bash
echo $1

if [ $1  = 'e' ]; then
  ./exp --type=dp
elif [ $1  = 'de' ]; then
  gdb --args ./exp --type=dp
elif [ $1  = 'init' ]; then
  if [ $2  = 'd' ]; then
    export CPP=/opt/gcc-4.8.2/bin/g++
    export BOOST_DIR=/cac/u01/mfa51/Desktop/boost_1_56_0/install
  
    unset LD_LIBRARY_PATH
    LD_LIBRARY_PATH=/cac/u01/mfa51/Desktop/boost_1_56_0/install/lib:$LD_LIBRARY_PATH
    LD_LIBRARY_PATH=/opt/gcc-4.8.2/lib64:$LD_LIBRARY_PATH
    export LD_LIBRARY_PATH
    echo "LD_LIBRARY_PATH=" $LD_LIBRARY_PATH
fi
else
  echo "Argument did not match!"
fi