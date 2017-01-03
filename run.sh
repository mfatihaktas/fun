#!/bin/bash
echo $1

PYTHON=/cac/u01/mfa51/Desktop/Python-3.5.1/install/bin/./python3
MATLAB=/cac/u01/mfa51/Desktop/matlab_2016/install_/bin/./matlab

if [ $1  = 'p' ]; then
  $PYTHON
elif [ $1  = 'h' ]; then
  # $PYTHON ldpc.py
  $MATLAB -r "run hw.m; quit"
  # $MATLAB -nojvm
elif [ $1  = 'm' ]; then
  $MATLAB
elif [ $1  = 'e' ]; then
  ./exp --type=dp
elif [ $1  = 'de' ]; then
  gdb --args ./exp --type=dp
elif [ $1  = 'qs' ]; then
  $PYTHON q_sim.py
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
