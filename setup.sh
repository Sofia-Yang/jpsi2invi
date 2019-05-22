#!/usr/bin/env bash


cd besenv
source setupCVS.sh
source setupCMT.sh
cmt config
source setup.sh

cd ../TestRelease/TestRelease-00-00-84/cmt/
source setup.sh
cd ../../../


# export ROOTSYS="/afs/ihep.ac.cn/soft/common/ROOT/root-6.12.04/"
# export PATH="$ROOTSYS/bin:$PATH"
# export LD_LIBRARY_PATH="$ROOTSYS/lib:$LD_LIBRARY_PATH"

