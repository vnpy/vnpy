#!/bin/bash

CONDA_HOME=~/anaconda3
source $CONDA_HOME/bin/deactivate
source $CONDA_HOME/bin/activate $CONDA_HOME/envs/py35

############
# To solve the problem about Javascript runtime
export PATH=$PATH:/usr/local/bin
############ Ended

BASE_PATH=$(cd `dirname $0`; pwd)
echo $BASE_PATH
cd `dirname $0`
PROGRAM_NAME=./runServer.py

python $PROGRAM_NAME >$BASE_PATH/logs/service.log 2>>$BASE_PATH/logs/service-error.log &
